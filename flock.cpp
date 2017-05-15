#include "flock.h"


Flock::Flock():speed(2.0),number(80),delta(0.0),boids(){
    boids.push_back(Boid(Vector3d(10,0,0),Vector3d(0,0,0),Vector3d(0,0,0),1,0.2,0.0,1,4,0.0));
    for(int i=1;i<number;i++)
        boids.push_back(Boid(Vector3d(40,gauss(0,20,1),gauss(0,20,1)),
                    Vector3d(-2,0,0),Vector3d(0,0,0),
                    1,0.2,0.0,1,gauss(5,10,1),0.0));
}

Flock::~Flock(){}

void Flock::rotate(){
    for (int i=0;i<boids.size();i++){
        boids[i].rotate();
    }
}

void Flock::draw(){
    boids[0].drawHeader();
    for (int i=1;i<boids.size();i++){
        boids[i].draw();
    }
}



void Flock::update(){
    for (int i=0;i<boids.size();i++){
        boids[i].update();
    }
}

void Flock::clear(){
    boids.clear();
}



void Flock::flock(bool wander) {
    if(wander)
        boids[0].headerRoute();
    else{
        Vector3d ta(0,0,0);
        seek(boids[0],ta);
    }
    for(int i=1;i<boids.size();i++){
    Vector3d follow= seek(boids[i],boids[0].getPosition());//follow
    Vector3d avoid = avoidOb(boids[i]);   //avoid
    Vector3d sep = separate(boids[i]);   // separation
    Vector3d ali = align(boids[i]);      // alignment
    Vector3d coh = cohesion(boids[i]);   // cohesion
    Vector3d target= follow*number/20 +avoid*speed +sep*number/20.0 +ali +coh*3.0;
    boids[i].steer(target);
    }

}

Vector3d Flock::avoidOb(Boid& boid){
    Vector3d center(0,0,0);
    Vector3d dis(0,0,0);
    dis = boid.getPosition()-center;
    float d=dis.norm();
    if(d<40){
       Vector3d sum= dis.normalize();
       sum = sum/(d-10);
       center=sum*20;
       return center;
    }
    else
        return Vector3d(0,0,0);
}

Vector3d Flock::seek(Boid &boid,Vector3d& target) {
     Vector3d d(0,0,0);
    Vector3d goTo = target-boid.getPosition();
    float di =goTo.norm();
    if(di!=0){
        Vector3d sum = goTo.normalize();
        if(di<10.0){
            sum = - 10.0 * sum/di;
        }
       sum = sum * 1.1;
        return sum;
  }
    else
        return goTo;
}

Vector3d Flock::separate(Boid& boid) {
    float separationDis = 30.0f;
    Vector3d sum(0,0,0);
    int count = 0;
    for (int i=1;i<boids.size();i++) {

        Vector3d dif=boid.getPosition()-boids[i].getPosition();
        float d = dif.norm();
      if ((d > 0) && (d < separationDis)) {
        Vector3d steer =  dif.normalize();
        steer=steer+separationDis*steer/d;
        sum=sum+ steer;
        count++;
        }
    }
    if (count > 0) {
      sum=sum/(double) (count);
    }

    if (sum.norm() > 0) {
     return sum.normalize();
    }
    else
        return sum;
  }

 Vector3d Flock::align (Boid& boid) {
    float neighbord = 100.0;
    Vector3d steer(0, 0,0);
    Vector3d s(0, 0,0);
    int count = 0;
    for (int i=1;i<boids.size();i++) {
        Vector3d dif=boids[i].getPosition()-boid.getPosition();
      float d = dif.norm();
        Vector3d diff=boids[i].getVelocity()-boid.getVelocity();
      if ((d > 0) && (d < neighbord)) {
        steer=steer+ boids[i].getVelocity();//diff;
        count++;
      }
    }
    if (count > 0) {
      steer=steer/(double)(count);
      if(steer.norm()!=0){
        Vector3d sum= steer.normalize();
        sum=sum* speed;
        return sum;

      }
      else
          return s;
    }

    else {
      return s;
    }
  }


Vector3d Flock::cohesion (Boid& boid) {
    float neighbord = 100.0;
    Vector3d steer(0, 0,0);
    Vector3d s(0, 0,0);
    int count = 0;
    for (int i=1;i<boids.size();i++) {
        Vector3d dif=boids[i].getPosition()-boid.getPosition();
        float d = dif.norm();
      if ((d > 0) && (d < neighbord)) {
        steer=steer+boids[i].getPosition();
        count++;
      }
    }
    if (count > 0) {
      steer=steer/(double)(count);
      if(steer.norm()!=0){
        return seek(boid,steer);
      }
      else
          return s;
    }
    else {
      return s;
    }
}

