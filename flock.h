#include<vector>
#include "gauss.h"
#include "boid.h"



class Flock{
public:
    Flock();
    ~Flock();
    void rotate();
    void draw();
    void update();
    void headerRoute(Boid&);
    void clear();
    void flock(bool n);
    Vector3d avoidOb(Boid&);
    Vector3d speedMatch(Boid&);
    Vector3d seek(Boid & ,Vector3d&);
    Vector3d separate(Boid &);
    Vector3d align(Boid &);
    Vector3d cohesion(Boid &);
private:
    float speed;
    int number;
    float delta;
    std::vector<Boid> boids;
};
