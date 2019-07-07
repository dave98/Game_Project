#ifndef SLEEPING_CAT_ENGINE_H
#define SLEEPING_CAT_ENGINE_H

#include <iostream>
#include <math.h>
#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "CatUserControl.h" //Controls users parameters
#include "extra_functions.h"
#include "ParticleEffect.h"
#include "ElapsedTime.h"

using namespace std;
using namespace glm;

float g_aspect = 1.0f;

CatUserControl Cat_Director_1;
ParticleEffect Cat_Particle;

//Definig key entrances
#define KEY_ESC 27 //Exit key
#define W_DIRECTIONAL 87
#define S_DIRECTIONAL 83
#define A_DIRECTIONAL 65
#define D_DIRECTIONAL 68
#define Z_SHOW_AXIS 90

#define my_pi 3.1416

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

//----HEADERS-----//
void SCAT_Engine_Init(void); //Parametros iniciales para arrancar opengl
void SCAT_reshape_window(int, int); //Funcion orientada a la reconfiguración de loa gráficos en caso la pantalla se redimensione
void SCAT_draw_particle(void);
void SCAT_draw_function(void); // Funcion encargada de realizar el dibujado

//KEY events
void SCAT_key_pressed(unsigned char, int, int); // Detecta la tecla que ha sido presionada
void SCAT_key_up(unsigned char, int, int);
void SCAT_key_operation();
void SCAT_key_static_operation(unsigned char);
void SCAT_special_key_entrance(int, int, int); //Permite la entrada de flechas especiales
void SCAT_special_key_up(int, int, int);


void SCAT_mouse_key_entrance(int, int, int, int);
void SCAT_mouse_passive_entrance(int, int);
void SCAT_idle(); //Funcion activa mientras OpenGL no hace nada

//---------------//


// Por defecto arrancamos con GL_MODELVIEW matriz.
void SCAT_Engine_Init(void){
  GLfloat position[] = {0.0f, 5.0f, 10.0f, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  glClearColor(RED, GREEN, BLUE, ALPHA); //Initial Background Color
}

void SCAT_Engine_Altered(void){

                 // Posicion de luces           // Luz ambiente                 // Luz  diffuse                   // Luz  especular
  TLuz luces = {vec4(0.0f, 35.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f)};
  TMaterial line_material = { vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f), 100.0f};

  glClearColor(0, 0, 0, 0);

  glEnable(GL_TEXTURE_2D);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glLoadIdentity(); //-------------

  glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(luces.m_position));
	glLightfv(GL_LIGHT0, GL_AMBIENT , value_ptr(luces.m_ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE , value_ptr(luces.m_diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(luces.m_specular));

  glMaterialfv(GL_FRONT, GL_AMBIENT,   glm::value_ptr(line_material.m_ambient));
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   glm::value_ptr(line_material.m_diffuse));
	glMaterialfv(GL_FRONT, GL_SPECULAR,  glm::value_ptr(line_material.m_specular));
	glMaterialfv(GL_FRONT, GL_SHININESS, &line_material.m_shininess);


}

void SCAT_reshape_window(int width, int height){//Funcion de reescalado que recibe los nuevos valores del anho y alto de ventana
  /* Allow us to kept proportions in figure*/
  //if(width < height){width = height;}
  //cout<<width<<" -- "<<height<<endl;
  //else if(height < width){height = width;}
  //static double a; a+=5;
  // --> cout<<__PRETTY_FUNCTION__<<endl;
  // --> glViewport(0, 0, width, height);//Porción de ventana en donde GL podrá volver a dibujar tras un reescalado
                                  //Primer y segundo parámetro representan la distancia desde la esquina superior izquierda.
                                  //Tercer y cuarto representan el ancho y alto de la nueva ventana
  // --> glMatrixMode(GL_PROJECTION);
  // --> glLoadIdentity(); //Inicializar los valores de la matriz en 1... más o menos
  //gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0); //Define el ángulo de la visión
                                                                      //Todos los parámetros son del tipo GLdouble
                                                                      // a : Especifica el ángulo del campo de vista
                                                                      // b : Define la proporción del dibujado en base a la altura y el ancho del dibujo
                                                                      // c : Relate to nearest clipping distance
                                                                      // d : Relate to fartest clipping distance
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
  //glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
  //gluLookAt(0.0, 0.0, 14.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // x y < iniciales para configurar distancia del ojo
  //gluLookAt(Cat_Director_1.camera_position.x, Cat_Director_1.camera_position.y, Cat_Director_1.camera_position.z,
  //           Cat_Director_1.camera_reference.x, Cat_Director_1.camera_reference.y, Cat_Director_1.camera_reference.z,
  //           Cat_Director_1.camera_up.x, Cat_Director_1.camera_up.y, Cat_Director_1.camera_up.z);
  //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  // --> glMatrixMode(GL_MODELVIEW);
  glMatrixMode(GL_PROJECTION);
  glViewport(0, 0, width, height);
  g_aspect = (float)width / (float)height;
}

void SCAT_draw_particle(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0f, g_aspect, 1.0f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt( Cat_Director_1.cam_position.x, Cat_Director_1.cam_position.y, Cat_Director_1.cam_position.z, Cat_Director_1.cam_reference.x, Cat_Director_1.cam_reference.y, Cat_Director_1.cam_reference.z, Cat_Director_1.cam_normal.x, Cat_Director_1.cam_normal.y, Cat_Director_1.cam_normal.z);                                                                     ;


  Cat_Particle.Render_v2();

  glutSwapBuffers();
  glutPostRedisplay();
}


void SCAT_draw_function(void){
    //Limpiar bakcground
    SCAT_key_operation();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //GL_COLOR_BUFFER_BIT evita que se quede la imagen anterior
                                                        //GL_DEPTH_BUFFER_COLOR no sé pa que sirve
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, g_aspect, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    gluLookAt( Cat_Director_1.cam_position.x, Cat_Director_1.cam_position.y, Cat_Director_1.cam_position.z, Cat_Director_1.cam_reference.x, Cat_Director_1.cam_reference.y, Cat_Director_1.cam_reference.z, Cat_Director_1.cam_normal.x, Cat_Director_1.cam_normal.y, Cat_Director_1.cam_normal.z);                                                                     ;
    Cat_Director_1.global_rendering();
    /*--------------------------*/
    glutSwapBuffers();
    glFlush();
}

//Configuracion para todas las teclas
void SCAT_key_pressed(unsigned char key, int x, int y){
  Cat_Director_1.key_interpreter_normal_pressed((int)key);
  SCAT_key_static_operation(key);
}

void SCAT_key_up(unsigned char key, int x, int y){
  Cat_Director_1.key_interpreter_normal_up((int)key);
}

//Funcion para el desarrollo de eventos de teclado de forma personal
void SCAT_key_static_operation(unsigned char key){
  //Añade un evento personalizado con el nombre de la tecla y la accion a realizar
  if(key == KEY_ESC){
    exit(0);
  }
}

void SCAT_key_operation(){ //For continue pressing
  Cat_Director_1.key_effect_operation();
}

void SCAT_special_key_entrance(int key, int x, int y){
  Cat_Director_1.key_interpreter_special_pressed(key);
}

void SCAT_special_key_up(int key, int x, int y){
  Cat_Director_1.key_interpreter_special_up(key);
}


void SCAT_mouse_key_entrance(int button, int state, int x, int y){
  if(Cat_Director_1.player_ship){
      Cat_Director_1.player_ship->ship_shoot();
  }
}

//Define el puntero de la nave en base al recorrdio del mouse en pantalla.
void SCAT_mouse_passive_entrance(int x, int y){
  Cat_Director_1.mouse_interpreter(x, y);
}

void SCAT_idle(void){ //Actualizando posiciones de las párticulas
  static ElapsedTime elapsedTime;
  float deltaTime = elapsedTime.GetElapsedTime();
  Cat_Particle.Update(deltaTime);
  glutPostRedisplay(); //Redraw while doing nothing
}

//MODELVIEW funciona con los siguientes métodos:
  // -> glTranslatef, glRotatef
  // -> glScale
  // -> gluLookAt
  // Para realizar operaciones bajo este tipo de contexto debemos llamar glMatrixMode(GL_MODELVIEW);
  // Ya viene por defecto definida en opengl
  // Al inicio esta matriz solo almacena la matriz IDENTIDAD
  // Dicha matriz se puede resetear en cualquier instante gracias a glLoadIdentity();
  // Cada vez que se realiza dichas operaciones, se trabaja con la matriz en la CIMA de la pila.

//Matriz de PROYECCION:
  // Define como la escena 3D es proyectada en el plano 2D.
  // Esta matriz tiene su propio stack y se le llama utilizando glMatrixMode(GL_PROJECTION), a partir de esa declaración trabajaremos siempre con esa matriz.
  // Matriz de Perspectiva (Perspective)
  // Matriz Orthográfica (Ortho)

//Matriz de TEXTURAS:
  // Solo debes saber que existen :v

  // FUENTE: http://jerome.jouvie.free.fr/opengl-tutorials/Lesson2.php
#endif
