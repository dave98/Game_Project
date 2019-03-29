#ifndef CAT2DUNIT_H
#define CAT2DUNIT_H

#include <iostream>

using namespace std;


template<typename T>
class Cat2DUnit{
public:
  T x;
  T y;

  Cat2DUnit();
  Cat2DUnit(T, T);
  ~Cat2DUnit();

  Cat2DUnit<T> operator + (const Cat2DUnit<T>&);
  Cat2DUnit<T> operator - (const Cat2DUnit<T>&);
};


template<typename T>
Cat2DUnit<T>::Cat2DUnit(){
  this-> x = 0;
  this-> y = 0;
}

template<typename T>
Cat2DUnit<T>::Cat2DUnit(T _x, T _y){
  this->x = _x;
  this->y = _y;
}

template<typename T>
Cat2DUnit<T>::~Cat2DUnit(){}


template <typename T>
Cat2DUnit<T> Cat2DUnit<T>::operator + (const Cat2DUnit<T>& a){
  Cat2DUnit<T> answer;
  answer.x = this->x + a.x;
  answer.y = this->y + a.y;
  return answer;
}


template <typename T>
Cat2DUnit<T> Cat2DUnit<T>::operator - (const Cat2DUnit<T>& a){
  Cat2DUnit<T> answer;
  answer.x = this->x - a.x;
  answer.y = this->y - a.y;
  return answer;
}


//Non Member overloadings
template <typename S>
ostream& operator << (ostream& os, const Cat2DUnit<S>& obj){
  os << "(" << obj.x << ";" << obj.y << ")";
  return os;
}


#endif
