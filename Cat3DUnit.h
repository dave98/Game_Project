#ifndef CAT3DUNIT_H
#define CAT3DUNIT_H

#include <iostream>

using namespace std;


template<typename T>
class Cat3DUnit{
public:
  T x;
  T y;
  T z;

  Cat3DUnit();
  Cat3DUnit(T, T, T);
  ~Cat3DUnit();

  Cat3DUnit<T> operator + (const Cat3DUnit<T>&);
  Cat3DUnit<T> operator - (const Cat3DUnit<T>&);
};


template<typename T>
Cat3DUnit<T>::Cat3DUnit(){
  this-> x = 0;
  this-> y = 0;
  this-> z = 0;
}

template<typename T>
Cat3DUnit<T>::Cat3DUnit(T _x, T _y, T _z){
  this->x = _x;
  this->y = _y;
  this->z = _z;
}

template<typename T>
Cat3DUnit<T>::~Cat3DUnit(){}


template <typename T>
Cat3DUnit<T> Cat3DUnit<T>::operator + (const Cat3DUnit<T>& a){
  Cat3DUnit<T> answer;
  answer.x = this->x + a.x;
  answer.y = this->y + a.y;
  answer.z = this->z + a.z;
  return answer;
}


template <typename T>
Cat3DUnit<T> Cat3DUnit<T>::operator - (const Cat3DUnit<T>& a){
  Cat3DUnit<T> answer;
  answer.x = this->x - a.x;
  answer.y = this->y - a.y;
  answer.z = this->z - a.z;
  return answer;
}


//Non Member overloadings
template <typename S>
ostream& operator << (ostream& os, const Cat3DUnit<S>& obj){
  os << "(" << obj.x << ";" << obj.y << ";" << obj.z << ")";
  return os;
}


#endif
