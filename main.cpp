#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/glut.h>
#include "src/SleepingCatEngine.h"
#include "src/CatUserControl.h"
#include "src/glm/glm/vec3.hpp"
#include "src/glm/glm/vec4.hpp"
#include "src/ParticleEffect.h"

//SCREEN CONFIGURATION

// X = 0
//               Z
//  -------------------------------
//  |            10               | 
//  |                             |
//  |10                        -10|  Y
//  |                             |
//  |           -10               |
//  -------------------------------


using namespace std;

extern ParticleEffect Cat_Particle;
extern CatUserControl Cat_Director_1;

int main(int argc, char** argv) {

  Cat_Director_1.initial_camera_configuration( glm::vec3(-70.0f, 0.0f,  10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0));
  Cat_Director_1.set_new_ship(); //Creamos la nave del jugador
  Cat_Particle = ParticleEffect(10);

  //Particle Configurations

  cout<<"Presione H para obtener ayuda"<<endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1440, 720);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Game");
  //SCAT_Engine_Init();
  SCAT_Engine_Altered();

  Cat_Particle.SetParticleEmitter(NULL);
  Cat_Particle.EmitParticles();


  glutDisplayFunc(SCAT_draw_function);
  //glutDisplayFunc(SCAT_draw_particle);
  glutReshapeFunc(SCAT_reshape_window);
  glutKeyboardFunc(SCAT_key_pressed);
  glutKeyboardUpFunc(SCAT_key_up);
  glutSpecialFunc(SCAT_special_key_entrance);
  glutSpecialUpFunc(SCAT_special_key_up);
  glutMouseFunc(SCAT_mouse_key_entrance);
  glutPassiveMotionFunc(SCAT_mouse_passive_entrance);

  glutIdleFunc(SCAT_idle);
  glutMainLoop();
  return EXIT_SUCCESS ;
}
//------FUNCTION DEVELOPMENT
