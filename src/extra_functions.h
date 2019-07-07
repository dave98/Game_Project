#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H

#include <iostream>
#include <string>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <GL/glext.h>


using namespace std;
using namespace glm;

struct TLuz
{
	glm::vec4 m_position;

	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
};

struct TMaterial
{
	glm::vec4 m_ambient;
	glm::vec4 m_diffuse;
	glm::vec4 m_specular;
	float m_shininess;
};


//Función para imprimir datos del tipo glm::vec3
template<typename T = glm::vec3>
void print_vector(T _in){
  cout<<"( "<<_in.x<<" : "<<_in.y<<" : "<<_in.z<<" )"<<endl;
}

float uno_emit[]    = {1.0, 1.0, 1.0, 1.0};

void dibujar_luz(TLuz _l, float _r){
	glPushMatrix();
		glTranslatef(_l.m_position.x, _l.m_position.y, _l.m_position.z);
     	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, uno_emit);
     	glColor3f(1.0f, 1.0f, 1.0f);
     	glutSolidSphere(_r,15,15);
	glPopMatrix();
}

string vec3_to_str(glm::vec3 _vec){
	return "["+to_string(_vec.x)+","+to_string(_vec.y)+","+to_string(_vec.z)+"]";
}

void Font(string w, float x, float y){
	glRasterPos2f(x, y);
	for (char c: w){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

//RANDOM Functions
int RandomInt(int _a, int _b){
	return (rand()%(_b - _a)) + _a;
}

vec3 RandomPosition(int _x, int _y, int _z){
	return vec3(RandomInt(-_x,_x), _y, RandomInt(-_z,_z));
}

float Random(){
	return (float)rand()/(float)RAND_MAX;
}

vec3 RandomVect(){
	float x = (Random()*2.0f)-1;
	float y = 0;
	float z = (Random()*2.0f)-1;
	return normalize(vec3(x,y,z));
}

vec3 RandomUnitVect(){
	float x = (Random()*2.0f)-1;
	float y = (Random()*2.0f)-1;
	float z = (Random()*2.0f)-1;

	return normalize(vec3(x,y,z));
}

vec3 RandomColor(){
	return vec3(Random(), Random(), Random());
}

float RandomBeetwen(float a, float b){
	float rnd = Random();
	float diff = b-a;
	return (rnd*diff) + a;
}



#endif
