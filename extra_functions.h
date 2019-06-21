#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H

#include <iostream>
#include "glm/glm/vec3.hpp"

using namespace std;

//Función para imprimir datos del tipo glm::vec3
template<typename T = glm::vec3>
void print_vector(T _in){
  cout<<"( "<<_in.x<<" : "<<_in.y<<" : "<<_in.z<<" )"<<endl;
}




#endif
