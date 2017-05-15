#include <stdio.h>
#include <GL/glut.h>
#include "Vector.h"
#include <cmath>
class Boid
{
public:
    Boid();
    Boid(const Vector3d &p, const Vector3d &v,const Vector3d &a,
            const double m,const float s,const float t,const int d,const double r,const double an);
    ~Boid();
    void headerRoute();
    void setPosition(const Vector3d&);
    void setVelocity(const Vector3d&);
    void setAcceleration(const Vector3d&);
    void setMass(const double);

     Vector3d& getPosition();
     Vector3d& getVelocity();
     Vector3d& getAcceleration();
    const double   getMass();
    void steer(Vector3d&);
    void rotate();
    void draw();
    void drawHeader();
    void update();
private:
    Vector3d position;
    Vector3d velocity;
    Vector3d acceleration;
    double mass;
    float step;
    float theta;
    int direction;
    double rotateSpeed;
    double angle;

};

