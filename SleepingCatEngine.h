#ifndef SLEEPING_CAT_ENGINE_H
#define SLEEPING_CAT_ENGINE_H

#include <iostream>
#include <math.h>
#include "GL/glut.h"
#include "CatUserControl.h" //Controls users parameters
#include "Cat3DGeometry.h"
#include "CatMath.h"
using namespace std;

CatUserControl Cat_Director_1;
//Temporal Delete Later
float sense = 0.1;
float circle_control_1_position = 0.0; //Cotrolador temporal
float circle_control_1_rotation = 0.0;
float circle_control_1_traslation = 0.0;
float circle_control_1_sense = 1.0;

float circle_control_2_traslation = 0.0;
float circle_control_2_position = 0.0;
float circle_control_2_rotation = 0.0;
float circle_control_2_sense = 1.0; //Para la derecha


//Definig key entrances
#define KEY_ESC 27 //Exit key
#define W_DIRECTIONAL 87
#define S_DIRECTIONAL 83
#define A_DIRECTIONAL 65
#define D_DIRECTIONAL 68
#define Z_SHOW_AXIS 90

#define pi 3.1416

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

//----HEADERS-----//
void SCAT_Engine_Init(void); //Parametros iniciales para arrancar opengl
void SCAT_reshape_window(int, int); //Funcion orientada a la reconfiguración de loa gráficos en caso la pantalla se redimensione
void SCAT_draw_function(void); // Funcion encargada de realizar el dibujado
void SCAT_key_entrance(unsigned char, int, int); //Permite la entrada de teclas comunes
void SCAT_special_key_entrance(int, int, int); //Permite la entrada de flechas especiales
void SCAT_mouse_key_entrance(int, int, int, int);
void SCAT_idle(); //Funcion activa mientras OpenGL no hace nada


void example_draw_1(void);
void example_draw_axis(void);
void example_draw_cuadrado(void);
void example_draw_circle_v2(void);
void example_draw_line_circle(void);
void example_draw_circle_in_circle_v2(void);
void example_draw_circle_in_line(void);
void example_draw_circle_angle(void);
void example_draw_pendulum_animation(void);
  void pendulum_conf();
void turnig_around_a_point(void);
  void turning_pot(void);
  void turning_pot_with_traslation(void);
  void turning_pot_with_traslation_satelite(void);
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
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //glOrtho( 0.0f, 300.0f, 100.0f,  0.0f, 0.0f, 1.0f);//Setting up configuration of  inner windows
}
void SCAT_reshape_window(int width, int height){//Funcion de reescalado que recibe los nuevos valores del anho y alto de ventana
  /* Allow us to kept proportions in figure*/
  //if(width < height){width = height;}
  //cout<<width<<" -- "<<height<<endl;
  //else if(height < width){height = width;}
  //static double a; a+=5;
  cout<<__PRETTY_FUNCTION__<<endl;
  glViewport(0, 0, width, height);//Porción de ventana en donde GL podrá volver a dibujar tras un reescalado
                                  //Primer y segundo parámetro representan la distancia desde la esquina superior izquierda.
                                  //Tercer y cuarto representan el ancho y alto de la nueva ventana
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); //Inicializar los valores de la matriz en 1... más o menos
  //gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0); //Define el ángulo de la visión
                                                                      //Todos los parámetros son del tipo GLdouble
                                                                      // a : Especifica el ángulo del campo de vista
                                                                      // b : Define la proporción del dibujado en base a la altura y el ancho del dibujo
                                                                      // c : Relate to nearest clipping distance
                                                                      // d : Relate to fartest clipping distance
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();
  //gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
  glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
  //gluLookAt(0.0, 0.0, 14.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // x y < iniciales para configurar distancia del ojo
  //gluLookAt(Cat_Director_1.camera_position.x, Cat_Director_1.camera_position.y, Cat_Director_1.camera_position.z,
  //           Cat_Director_1.camera_reference.x, Cat_Director_1.camera_reference.y, Cat_Director_1.camera_reference.z,
  //           Cat_Director_1.camera_up.x, Cat_Director_1.camera_up.y, Cat_Director_1.camera_up.z);
  glMatrixMode(GL_MODELVIEW);
}
void SCAT_draw_function(void){
    //Limpiar bakcground
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //GL_COLOR_BUFFER_BIT evita que se quede la imagen anterior
                                                        //GL_DEPTH_BUFFER_COLOR no sé pa que sirve
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
    //gluLookAt(0.0, 0.0, 24.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
    //gluLookAt(Cat_Director_1.camera_position.x, Cat_Director_1.camera_position.y, Cat_Director_1.camera_position.z,
    //           Cat_Director_1.camera_reference.x, Cat_Director_1.camera_reference.y, Cat_Director_1.camera_reference.z,
    //           Cat_Director_1.camera_up.x, Cat_Director_1.camera_up.y, Cat_Director_1.camera_up.z);

    glMatrixMode(GL_MODELVIEW);

    /*Here functions to be drawn*/
    if(Cat_Director_1.parameter_0)
      example_draw_1();
    if(Cat_Director_1.parameter_1)
      example_draw_axis();
    if(Cat_Director_1.parameter_2)
      example_draw_cuadrado();
    if(Cat_Director_1.parameter_3)
      example_draw_line_circle();
    if(Cat_Director_1.parameter_4)
      example_draw_circle_v2();
    if(Cat_Director_1.parameter_5)
      example_draw_circle_in_circle_v2();
    if(Cat_Director_1.parameter_6)
      example_draw_circle_in_line();
    if(Cat_Director_1.parameter_7)
      example_draw_circle_angle();
    if(Cat_Director_1.parameter_8)
      example_draw_pendulum_animation();
    if(Cat_Director_1.parameter_9)
      turnig_around_a_point();
    /*--------------------------*/
    glutSwapBuffers();
    glFlush();
}
void SCAT_key_entrance(unsigned char key, int x, int y){// x and y indicates mouse position
                                                        //If its void key entrance are disabled
  cout<<"Entrada: "<<key<<endl;
  //key = Cat_Director_1.identifier(key);

  switch (key) {
    case 'H':
      cout<<"Consola de ayuda"<<endl<<endl;
      cout<<"Presione teclas del 1 - 9 para observar las figuras."<<endl;
      cout<<"Rote figuras con AWSD - mayusculas"<<endl;
      break;

    case '1': //show_axis ---> Must be safe in a separate document.
      //Cat_Director_1.parameter_1 = !Cat_Director_1.parameter_1;
      Cat_Director_1.parameter_0 = !Cat_Director_1.parameter_0;
      break;

    case '2':
      Cat_Director_1.parameter_1 = !Cat_Director_1.parameter_1;
      //glutDisplayFunc(show_axis);
      break;

    case '3':
      Cat_Director_1.parameter_2 = !Cat_Director_1.parameter_2;
      break;

    case '4':
      Cat_Director_1.parameter_3 = !Cat_Director_1.parameter_3;
      break;

    case '5':
      Cat_Director_1.parameter_4 = !Cat_Director_1.parameter_4;
      break;

    case '6':
      Cat_Director_1.parameter_5 = !Cat_Director_1.parameter_5;
      break;

    case '7':
      Cat_Director_1.parameter_6 = !Cat_Director_1.parameter_6;
      break;

    case '8':
      Cat_Director_1.parameter_7 = !Cat_Director_1.parameter_7;
      break;

    case '9':
      Cat_Director_1.parameter_8 = !Cat_Director_1.parameter_8;
      break;

    case 'Z':
      Cat_Director_1.parameter_9 = !Cat_Director_1.parameter_9;
      break;


    case W_DIRECTIONAL:
      //gluLookAt(0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
      glRotatef(1.0, -1.0, 0., 0.); // glRotatef Angle, X, Y, Z
                                    // Angle indicates quantity and X Y Z selects axis
      //glutPostRedisplay(); //Función para un redibujado inmediato
      break;

    case S_DIRECTIONAL: //Movimiento hacia abajo
      //gluLookAt(0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
      glRotatef(1.0, 1., 0., 0.);
      //glutPostRedisplay(); //Función para un redibujado inmediato
      break;

    case A_DIRECTIONAL: //Movimiento hacia la izquierda
      //gluLookAt(0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
      glRotatef(1.0, 0., -1.0, 0.);
      //glutPostRedisplay(); //Función para un redibujado inmediato
      break;

    case D_DIRECTIONAL: // Movimiento a la derecha
      //gluLookAt(0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
      glRotatef(1.0, 0., 1., 0.);
      //glutPostRedisplay(); //Función para un redibujado inmediato
      break;

    case KEY_ESC:
      exit(0);
      break;
    default:
      break;
  }
//    glutPostRedisplay(); //Función para un redibujado inmediato
}
void SCAT_special_key_entrance(int key, int x, int y){
  switch (key) {
    case GLUT_KEY_UP:
      cout<<"Tecla arriba"<<endl;
      //gluLookAt(0.0, 4.2, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // x y < iniciales para configurar distancia del ojo
      Cat_Director_1.camera_position.y += 1;
      Cat_Director_1.camera_position.z += 1;
      //Cat_Director_1.camera_reference.y += 1;

      break;
    case GLUT_KEY_DOWN:
      cout<<"Tecla abajo"<<endl;
      Cat_Director_1.camera_position.y -= 1;
      Cat_Director_1.camera_position.z -= 1;
      //Cat_Director_1.camera_reference.y -= 1;

      break;
    case GLUT_KEY_LEFT:
      cout<<"Tecla izquierda"<<endl;
      Cat_Director_1.camera_position.x -= 1;
      Cat_Director_1.camera_position.z -= 1;
      //Cat_Director_1.camera_reference.x -= 1;
      break;
    case GLUT_KEY_RIGHT:
      cout<<"Tecla derecha"<<endl;
      Cat_Director_1.camera_position.x += 1;
      Cat_Director_1.camera_position.z += 1;
      //Cat_Director_1.camera_reference.x += 1;
      break;
  }
}
void SCAT_idle(void){
  glutPostRedisplay(); //Redraw while doing nothing
}

// ---> wORK DRAWS ------------//

void example_draw_1(void){
    glColor3f(1.0, 0.0, 0.0);
    //glutWireTorus(4, 5, 28, 28);
    glutSolidTeapot(5);
    //glColor3f(0.0, 0.0, 1.0);
    //glutWireCube(.60);

    //glutSwapBuffers();
}
void example_draw_axis(void){
  //glClearColor(1.0, 1.0, 1.0, 0.0); //Background color
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0); //Red color

  glBegin(GL_LINES);
    glVertex3f(-10.0, 0.0, 0.0);//Main Line X Y Z coordinates
    glVertex3f(10.0, 0.0, 0.0);

    glVertex3f(10.0, 0.0f, 0.0f);//Up side
    glVertex3f(8.0, 1.0f, 0.0f);

    glVertex3f(10.0, 0.0f, 0.0f);//Down Side
    glVertex3f(8.0, -1.0f, 0.0f);

    /*glVertex3f(1.0, 0.0f, 0.0f); // Front Side
    glVertex3f(0.8, 0.0f, 0.1f);


    glVertex3f(1.0, 0.0f, 0.0f); // Back Side
    glVertex3f(0.8, 0.0f, -0.1f);*/
    glEnd();

    // y
    glColor3f(0.0,1.0,0.0); // green y
    glBegin(GL_LINES);
    glVertex3f(0.0, -10.0f, 0.0f);
    glVertex3f(0.0, 10.0f, 0.0f);

    // arrow
    glVertex3f(0.0, 10.0f, 0.0f);
    glVertex3f(1.0, 8.0f, 0.0f);

    glVertex3f(0.0, 10.0f, 0.0f);
    glVertex3f(-1.0, 8.0f, 0.0f);
    glEnd();

    // z
    glColor3f(0.0,0.0,1.0); // blue z
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0f ,-10.0f );
    glVertex3f(0.0, 0.0f ,10.0f );

    // arrow
    glVertex3f(0.0, 0.0f ,10.0f );
    glVertex3f(0.0, 1.0f ,8.0f );

    glVertex3f(0.0, 0.0f , 10.0f );
    glVertex3f(0.0, -1.0f , 8.0f );
  glEnd();

  //glutSwapBuffers();

}
void example_draw_cuadrado(void){
  //Space created beetwen -10 to 10
  float center = 5.0; //For X Y Z
  float side_size = 10.0;
  side_size = side_size/2;
  //float start_at = center


  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
    glVertex3f(center - side_size , center - side_size, 0.0f);
    glVertex3f(center + side_size, center - side_size, 0.0f);
    glVertex3f(center + side_size, center + side_size, 0.0f);
    glVertex3f(center - side_size, center + side_size, 0.0f);
    /*glVertex3f(-8.0f, -8.0f, 0.01f);
    glVertex3f(8.0f, -8.0f, 0.0f);1
    glVertex3f(8.0f, 8.0f, 0.0f);
    glVertex3f(-8.0f, 8.0f, 0.0f);*/
  glEnd();
}
void example_draw_circle_v2(void){
                  //Solution as: (x-a)^2 + (y -b)^2 = r^2  -> Not practical
                  //Working with cat director
  int steps = 20; //Number of lines between segments.
  float pi_steps = 2 * pi / steps; //Distance between two lines inside circle
  float pi_progress = 0;

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINE_LOOP);
    for(int i = 0; i < steps; i++){
      glVertex3f(Cat_Director_1. c_circle->center.x + (Cat_Director_1.c_circle->radio * cos(pi_progress)), Cat_Director_1.c_circle->center.y + (Cat_Director_1.c_circle->radio * sin(pi_progress)), Cat_Director_1.c_circle->center.z);
      pi_progress += pi_steps;
    }
  glEnd();
}


void example_draw_line_circle(void){
  float center = 0.0;
  float radio = 10.0;
  float pi_val = 3.14;
  unsigned int definition = 50;
  float pi_increment = 2 * pi_val / definition;
  float pi_progress = 0;
  float circle_quantity = 5; //Cannot be zero

  glColor3f(0.0, 1.0, 0.0);
    for(unsigned int j = 0; j < circle_quantity; j++){
      glBegin(GL_LINE_LOOP);
      for(unsigned int i = 0; i < definition; i++){
        glVertex3f(center + (radio * cos(pi_progress)), center +  (radio * sin(pi_progress)), 0.0f);
        pi_progress += pi_increment;
      }
      pi_progress = 0;
      radio = radio - (radio / circle_quantity);
      center = center - (center / circle_quantity);
      glEnd();
    }
}
void example_draw_circle_in_circle_v2(void){
  //--External Data--//
  float t_radio = Cat_Director_1.c_circle->radio;
  Cat3DUnit<float> t_center = Cat_Director_1.c_circle->center;
  Cat3DUnit<float> minor_center;


  int steps = 100;
  int circle_quantity = 5; // Cannot be zero
  float pi_increment = 2 * pi / steps;
  float pi_progress = 0;

  float minor_radio = t_radio / circle_quantity;
  minor_center.x = t_center.x / circle_quantity;

  glColor3f(0.0, 1.0, 0.0);
  for(int i = 0; i < circle_quantity; i++){
    glBegin(GL_LINE_LOOP);
      for(int j = 0; j < steps; j++){
        glVertex3f(t_center.x + (t_radio * cos(pi_progress)), t_center.y + (t_radio * sin(pi_progress)), t_center.z);
        pi_progress += pi_increment;
      }
      pi_progress = 0; // Restart for drawing
      t_radio -= minor_radio;
      t_center.x -= minor_radio;
    glEnd();
  }
}
void example_draw_circle_in_line(void){
  //--External Data--//
  float t_radio = Cat_Director_1.c_circle->radio;
  Cat3DUnit<float> t_center = Cat_Director_1.c_circle->center;
  Cat3DUnit<float> minor_center;


  int steps = 100;
  int circle_quantity = 5; // Cannot be zero
  float pi_increment = 2 * pi / steps;
  float pi_progress = 0;

  float minor_radio = t_radio / circle_quantity;
  minor_center.x = t_center.x / circle_quantity;

  glColor3f(0.0, 1.0, 0.0);
  for(int i = 0; i < circle_quantity; i++){
    glBegin(GL_LINE_LOOP);
      for(int j = 0; j < steps; j++){
        glVertex3f(t_center.x + (t_radio * cos(pi_progress)), t_center.y + (t_radio * sin(pi_progress)), t_center.z);
        pi_progress += pi_increment;
      }
      pi_progress = 0; // Restart for drawing
      t_radio -= minor_radio;
      t_center.x += 2*t_radio + minor_radio;
    glEnd();
  }
}
void example_draw_circle_angle(){
  //--External Data--//
  float t_radio = Cat_Director_1.c_circle->radio;
  Cat3DUnit<float> t_center = Cat_Director_1.c_circle->center;
  Cat3DUnit<float> minor_center;


  int steps = 100;
  int circle_quantity = 5; // Cannot be zero
  float angle = 1.57; //Value between 0 - 90
  float pi_increment = 2 * pi / steps;
  float pi_progress = 0;

  float minor_radio = t_radio / circle_quantity;
  minor_center.x = t_center.x;
  minor_center.y = t_center.y; //Sin(angle)

  //Angle proportions
  glColor3f(0.0, 1.0, 0.0);
  for(int i = 0; i < circle_quantity; i++){
    glBegin(GL_LINE_LOOP);
      for(int j = 0; j < steps; j++){                         /*Changed*/
        glVertex3f(t_center.x + (t_radio * cos(pi_progress)), minor_center.y + (t_radio * sin(pi_progress)), t_center.z);
        pi_progress += pi_increment;
      }
      t_center.x += (cos(angle) * t_radio) + (cos(angle) * (t_radio - minor_radio));
      minor_center.y += (sin(angle) * t_radio) + (sin(angle) * (t_radio - minor_radio));

      pi_progress = 0; // Restart for drawing
      t_radio -= minor_radio; //Radio is universal for all circles
    glEnd();
  }
}
void example_draw_pendulum_animation(){
  //--External Data--//
  float t_radio = Cat_Director_1.c_circle->radio;
  Cat3DUnit<float> t_center = Cat_Director_1.c_circle->center;
  Cat3DUnit<float> minor_center;

  //cout<<Cat_Director_1.c_circle->angle<<endl;

  int steps = 100;
  int circle_quantity = 5; // Cannot be zero
  float angle = Cat_Director_1.c_circle->angle;
  angle = degree_to_radians(angle);
  float pi_increment = 2 * pi / steps;
  float pi_progress = 0;

  float minor_radio = t_radio / circle_quantity;
  minor_center.x = t_center.x;
  minor_center.y = t_center.y; //Sin(angle)

  //Angles goes from 235 to 305 degrees
  //Angle proportions
  glColor3f(0.0, 1.0, 0.0);
  for(int i = 0; i < circle_quantity; i++){
    glBegin(GL_LINE_LOOP);
      for(int j = 0; j < steps; j++){                         /*Changed*/
        glVertex3f(t_center.x + (t_radio * cos(pi_progress)), minor_center.y + (t_radio * sin(pi_progress)), t_center.z);
        pi_progress += pi_increment;
      }
      t_center.x += (cos(angle) * t_radio) + (cos(angle) * (t_radio - minor_radio));
      minor_center.y += (sin(angle) * t_radio) + (sin(angle) * (t_radio - minor_radio));

      pi_progress = 0; // Restart for drawing
      t_radio -= minor_radio; //Radio is universal for all circles
    glEnd();
  }

  pendulum_conf();
  glutPostRedisplay();
  //Balancing animation
}
void pendulum_conf(){
   cout<<Cat_Director_1.c_circle->angle<<endl;
    if(Cat_Director_1.c_circle->angle >= 305){
      sense = -1 * sense;
      Cat_Director_1.c_circle->angle += sense;
    }
    else if(Cat_Director_1.c_circle->angle <= 235){
      sense = -1 * sense;
      Cat_Director_1.c_circle->angle += sense;
    }
    else{
      Cat_Director_1.c_circle->angle += sense;
    }
}

void turnig_around_a_point(void){
  glPushMatrix();
    //turning_pot();
    //turning_pot_with_traslation();
    //turning_pot_with_traslation_satelite();
  glPopMatrix();
}


void turning_pot(void){
  float pi_steps = 0.01;
  float degree_steps = 1.0;
  //float pi_steps = pi / steps;
  float radio = 6.0;
  glTranslatef(radio*cos(circle_control_1_position), radio*sin(circle_control_1_position), 0.0f);
  glRotatef(circle_control_1_rotation, 0.0, 0.0, 1.0);
  circle_control_1_position+=pi_steps;
  circle_control_1_rotation+=degree_steps;
      glutSolidTeapot(1);
}

void turning_pot_with_traslation(void){
  float pi_steps = 0.01;
  float degree_steps = 1.0;
  float traslation_steps = 0.01;
  float radio = 6.0;
  float limit = 21.0;
  glTranslatef(radio*cos(circle_control_2_position) + circle_control_2_traslation, radio*sin(circle_control_2_position), 0.0f);
  glRotatef(circle_control_2_rotation, 0.0, 0.0, 1.0);
  circle_control_2_position+=pi_steps;
  circle_control_2_rotation+=degree_steps;

  if((circle_control_2_traslation > limit) or (circle_control_2_traslation < (-1*limit)) ){
    circle_control_2_sense = -1 * circle_control_2_sense;
  }

  circle_control_2_traslation+= (circle_control_2_sense * traslation_steps);
  glutSolidTeapot(1);
}


void turning_pot_with_traslation_satelite(void){
  glTranslatef(circle_control_2_traslation, 0.0, 0.0);
  glPushMatrix();
    float pi_steps = 0.001;
    float degree_steps = 1.0;
    float traslation_steps = 0.01;
    float radio = 6.0;
    float limit = 21.0;
    glTranslatef(radio*cos(circle_control_2_position) , radio*sin(circle_control_2_position), 0.0f);
    glRotatef(circle_control_2_rotation, 0.0, 0.0, 1.0);
    glutSolidTeapot(1);
    circle_control_2_position+=pi_steps;
    circle_control_2_rotation+=degree_steps;

    if((circle_control_2_traslation > limit) or (circle_control_2_traslation < (-1*limit)) ){
      circle_control_2_sense = -1 * circle_control_2_sense;
    }

    circle_control_2_traslation+= (circle_control_2_sense * traslation_steps);
    glutSolidTeapot(1);

    glPushMatrix();
      pi_steps = 1.5*pi_steps;
      radio = 4.0;
      glTranslatef(radio*cos(circle_control_1_position), radio*sin(circle_control_1_position), 0.0f);
      circle_control_1_position += pi_steps;
      glutSolidTorus(0.1, 0.5, 20, 20);
    glPopMatrix();
  glPopMatrix();
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
