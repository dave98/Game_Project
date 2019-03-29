#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include "SleepingCatEngine.h"
#include "CatUserControl.h"
#include "Cat3DUnit.h"
#include "Cat3DGeometry.h"

using namespace std;

extern CatUserControl Cat_Director_1;

int main(int argc, char** argv) {

  Cat_Director_1.c_circle = new Circle<float>(Cat3DUnit<float>(0,0,0), 4);
  Cat_Director_1.c_circle->angle = 270;
  cout<<"Presione H para obtener ayuda"<<endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(720, 720);
  glutInitWindowPosition(20, 20);
  glutCreateWindow("EDDJ Game");
  SCAT_Engine_Init();

  glutDisplayFunc(SCAT_draw_function);
  glutReshapeFunc(SCAT_reshape_window);
  glutKeyboardFunc(SCAT_key_entrance);
  glutSpecialFunc(SCAT_special_key_entrance);

  glutMainLoop();
  return 0;
}

//------FUNCTION DEVELOPMENT
