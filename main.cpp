#ifdef __APPLE__
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <cmath>
#include <vector>
#include "flock.h"
#include "Camera.h"
#include "Vector.h"
#include "gauss.h"
//#include "boid.h"

using namespace std;

#define WIDTH  1000
#define HEIGHT 800

static bool stop;
static bool notWan;
const int TimerDelay=30;
void TimerCallback(int value);
Camera *camera;
Flock flock;


void Simulate(){
   // for(int i=0;i<boids.size();i++)
        flock.rotate();
        flock.update();
	    flock.flock(notWan);

        glutPostRedisplay();
        if(!stop)
	    glutTimerFunc(TimerDelay,TimerCallback,0);
}


void TimerCallback(int value){
	if(value==0)
    {
	    Simulate();
	}
}


void init(){
	 // set up camera
  // parameters are eye point, aim point, up vector
  camera = new Camera(Vector3d(0,0,400), Vector3d(0, 0, 0),
              Vector3d(0, 1, 0));

  // grey background for window
  glClearColor(0, 0, 0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
}

void myDisplay() {
  glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

  // draw the camera created in perspective
  camera->PerspectiveDisplay(WIDTH,HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 // for(int i=0;i<boids.size();i++)
    flock.draw();
    glTranslatef(0.0,0.0,0.0);
    glColor4f(1.0f,1.0f,1.0f,0.5);
    glutWireSphere(20.0,10,10);
    glColor4f(1.0f,0.0f,0.0f,0.5);
    glutSolidSphere(8.0,30,30);
  glutSwapBuffers();
}



//
// Mouse Button Callback
//
void handleButtons(int button, int state, int x, int y){
  camera->HandleMouseEvent(button,state,x,y);
  glutPostRedisplay();
}

void handleMotion(int x,int y){
	camera->HandleMouseMotion(x,y);
	glutPostRedisplay();
}

void handleKey(unsigned char key, int x, int y) {
  switch (key) {
  case 't': case 'T':
		stop=false;
        notWan=true;
//	glutTimerFunc(TimerDelay,TimerCallback,0);
	Simulate();
	break;
  case 'g': case 'G':
    notWan=false;
    break;
  case 'r': case 'R':
	flock.clear();
    break;
  case 'f': case 'F':
    camera->SetCenterOfFocus(Vector3d(0, 0, 0));
    break;
  case 'q': case 'Q':   // q or esc - quit
    exit(0);
  }

  glutPostRedisplay();
}


int main(int argc, char* argv[]){

  // start up the glut utilities
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(50,50);
  glutCreateWindow("Flocking System");
	init();
  // register callback to draw graphics when window needs updating
  glutDisplayFunc(myDisplay);
  glutMouseFunc(handleButtons);
  glutMotionFunc(handleMotion);
  glutKeyboardFunc(handleKey);
  glutMainLoop();
  return(0);
}
