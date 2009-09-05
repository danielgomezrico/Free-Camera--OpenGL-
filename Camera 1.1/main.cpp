// El movimiento de la camara se logro gracias a http://www.lighthouse3d.com/opengl/glut/index.php?6

#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "Camera.h"

using namespace std;

GLfloat angle, fAspect;

void init (void);
void initRendering();

void visualizationParams();
void drawFloor();
void display();

Camera camera;//OBJECT CAMERA
//Camera camera(0.0, 20.0, 70.0);

void init (void)
{           
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  angle=45;
}


void initRendering(){
  glEnable(GL_DEPTH_TEST);
}


void drawFloor(){
  glPushMatrix();
  glBegin(GL_QUADS);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glColor3f(1.0, 1.0, 0.0);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();
  glPopMatrix();
}

// Dibujar toda la escena
void display(void)
{   
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  drawFloor();    
  glPopMatrix();
  glFlush ();
  glutSwapBuffers();
}

//Especify the visualitation params
void visualizationParams(void)
{
  // Sistem of coordenates of projection
  glMatrixMode(GL_PROJECTION);
  // Load the identity matrix 
  glLoadIdentity();

  // Especify the perspective projection
  gluPerspective(angle,fAspect,0.1,1000);
  
  // Especify the sistem of coordenates of the model
  glMatrixMode(GL_MODELVIEW);

  // Load the identity matrix 
  glLoadIdentity();
  
  //Orient the camera		  
  camera.orientAngleCam(false, false, false, false);
}


void reshape(GLsizei w, GLsizei h)
{
  // Prebent division by 0
  if ( h == 0 ) h = 1;
  
  // Size of the viewport
  glViewport(0, 0, w, h);
  
  // Aspect Ration
  fAspect = (GLfloat)w/(GLfloat)h;
  
  visualizationParams();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key){
  case '+': camera.moveCam(true); display();break;
  case '-': camera.moveCam(false); display(); break;
  case 13: break; //ENTER EVENT	      
  }
}

void specialKeyPress(int key, int x, int y) {
  
  switch (key) {
  case GLUT_KEY_LEFT :  camera.orientAngleCam(true, false, false, false); display();break;
  case GLUT_KEY_RIGHT :  camera.orientAngleCam(true, true, false, false); display();break;
  case GLUT_KEY_UP : camera.orientAngleCam(false,false,true,true); display(); break;
  case GLUT_KEY_DOWN : camera.orientAngleCam(false,false,true,false); display(); break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700,700);
  
  glutCreateWindow("Free camera moves");
  
  glutDisplayFunc(display);
  
  glutReshapeFunc(reshape);
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeyPress);
  
  initRendering();   
  
  init();
  glutMainLoop();
  return 0;
}
