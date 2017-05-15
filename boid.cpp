#include <GL/glut.h>
#include "boid.h"

Boid :: Boid(const Vector3d &p, const Vector3d &v,const Vector3d &a
        ,const double m,const float s,
         float t, int d,double r,double an):
    position(p),
    velocity(v),
    acceleration(a),
    mass(m),
    step(s),
    theta(t),
    direction(d),
    rotateSpeed(r),
    angle(an)
{
}

Boid::~Boid(){}

void Boid::headerRoute(){
    angle=angle + 2*3.14/180;
    Vector3d nv(80*cos(angle),0.0,80*sin(angle));
    position=nv;
    velocity=nv % Vector3d(0,1,0);
}

void Boid::steer(Vector3d& st){
    acceleration =st-velocity;
    if(acceleration.norm()!=0)
        acceleration.normalize();
}

void Boid::rotate(){
    theta+=rotateSpeed*direction;
    if(theta>=45)
        direction=-1;
    if(theta< -45)
        direction=1;
}

void Boid::draw()
{
   float t=theta*3.14/180;
    float x0=1.4*2.0;
    float x=x0+3,y=2.0,z=0.0;
    float nx,ny,nz;
    nx=(x-x0)*cos(t)+x0;
    ny=y;
    nz=(x-x0)*sin(t);
	Vector3d right=(velocity)% Vector3d(0,1,0);
    Vector3d top= right % velocity;
    Vector3d front = velocity.normalize();
    right =right.normalize();
    top =top.normalize();
    float mat[16]={-front.x,-front.y,-front.z,0,right.x,right.y,right.z,0,
        top.x,top.y,top.z,0,0,0,0,1};
	glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    glTranslatef(position.x,position.y,position.z);
    glMultMatrixf(mat);

    glPushMatrix();
    glScalef(1.5,0.5,0.5);
    glutSolidSphere(2.0,100,100);

    glPopMatrix();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(x0,0.0,0.0);
        glVertex3f(nx,ny,nz);
        glVertex3f(nx-1,0.0,nz);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(x0,0.0,0.0);
        glVertex3f(nx,-ny,nz);
        glVertex3f(nx-1,0.0,nz);
    glEnd();
    glPopMatrix();
}

void Boid::drawHeader()
{
   float t=theta*3.14/180;
    float x0=1.4*2.0;
    float x=x0+3,y=2.0,z=0.0;
    float nx,ny,nz;
    nx=(x-x0)*cos(t)+x0;
    ny=y;
    nz=(x-x0)*sin(t);
	Vector3d right=(velocity)% Vector3d(0,1,0);
    Vector3d top= right % velocity;
    Vector3d front = velocity.normalize();
    right =right.normalize();
    top =top.normalize();
    float mat[16]={-front.x,-front.y,-front.z,0,right.x,right.y,right.z,0,
        top.x,top.y,top.z,0,0,0,0,1};
	glPushMatrix();
    glColor3f(0.0,1.0,0.0);
    glTranslatef(position.x,position.y,position.z);
    glMultMatrixf(mat);

    glPushMatrix();
    glScalef(1.5,0.5,0.5);
    glutSolidSphere(5.0,100,100);

    glPopMatrix();
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex3f(x0,0.0,0.0);
        glVertex3f(nx*2,ny*2,nz);
        glVertex3f(nx*2-3,0.0,nz);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(x0,0.0,0.0);
        glVertex3f(nx*2,-ny*2,nz);
        glVertex3f(nx*2-3,0.0,nz);
    glEnd();
    glPopMatrix();
}


void Boid:: update(){
    Vector3d init(0,0,0);
    velocity = velocity + acceleration*step ;
    position = position + velocity*step ;
    acceleration=init;
}




void Boid::setPosition(const Vector3d &p)
{
    position = p;
}

void Boid::setVelocity(const Vector3d &v)
{
    velocity = v;
}

void Boid::setAcceleration(const Vector3d &a)
{
    acceleration = a;
}

void Boid::setMass(const double m)
{
    mass = m;
}



 Vector3d& Boid::getPosition()
{
    return position;
}

 Vector3d& Boid::getVelocity()
{
    return velocity;
}

 Vector3d& Boid::getAcceleration()
{
    return acceleration;
}

const double Boid::getMass()
{
    return mass;
}


