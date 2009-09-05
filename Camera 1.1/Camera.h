//Thanks to http://www.lighthouse3d.com/opengl/glut/index.php?
/*
  Written by: 
  Daniel Gomez Rico
  danielgomezrico@gmail.com   
  Student of system engineering, 6 semester
  at the EAFIT university from Colombia
  19 - August - 2009
*/

#include <stdlib.h>
#include <math.h>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

#ifndef CAMERA_H_
#define CAMERA_H_


/*
  This class manages a camera free movements in a 3D space for opengl
  the movement is like an airplane, it moves trougth ther line of sight
*/
class Camera{
 public:
  Camera();
  Camera(GLdouble posX, GLdouble posY, GLdouble posZ);
  Camera(GLdouble posX, GLdouble posY, GLdouble posZ,GLdouble deltaAngleCamTheta, GLdouble deltaAngleCamBeta,GLdouble deltaMoveCam, GLdouble theta,GLdouble beta);
  void initValues();
  
  void setDeltaAngleCam(GLfloat deltaAngleCamTheta, GLfloat deltaAngleCamBeta);
  void setDeltaMoveCam(GLfloat deltaMoveCam);
  
  /*
    positiveXZ says if is a positive angleChange (true) or if it is negative(false), same for positiveY
    changeN params says if the N angle will have to change
  */
  void orientAngleCam(bool changeBeta, bool positiveBeta,bool changeTheta, bool positiveTheta) ;
  
  /*Move the camera trought the space, front says if wee are going to move frontaly, 
    if not is backward movement*/
  void moveCam(bool toFront);
  

  /*
    Change the line of sight of the camera and orient the camera corresponding to this new line of sight
    Look At Point = Line Of Sight + Camera Position, becouse the camera moves using her line of sight
    
    From polar coordinates
    x = r*sin(theta)*cos(beta)
    z = r*sin(theta)*sin(beta)
    y = r*cos(theta)
    
    in this order becouse the up vector initialy is y
    but if you change this, you have to change this order acording to your idea
  */
  void calcLineSight();
  
  //Say to glu what is the look at
  void setLookAt();
  

  void setUpVector(GLfloat x, GLfloat y, GLfloat z);
  
 private:
  //Position of the camera
  GLfloat _pX,_pY,_pZ;
  
  //Unitary vector that define the line of sight of the camera
  GLfloat _lX,_lY,_lZ;
  
  //Rotation angles
  //theta is the angle between x and z, and beta is the angle between xz and y
  GLfloat _theta, _beta;
  
  //How much the angles change when we need to change the orientation of the camera
  GLfloat _deltaTheta, _deltaBeta;
  
  //How much the camera moves in the space when we need to move the camera
  GLint _deltaMove;
  
  //Radius of the imaginary sphere that is around the camera
  GLfloat _r;
  
  //Up vector of the camera
  GLfloat _uvX, _uvY, _uvZ;
};

#endif 
