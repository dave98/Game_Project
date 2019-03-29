#ifndef CAT3DGEOMETRY_H
#define CAT3DGEOMETRY_H

#include <iostream>
#include "Cat3DUnit.h"

using namespace std;

template <typename T> //Pls just use numeric expressions
class plane_figure{
public:
  Cat3DUnit<T> center; //For all
  T angle;
  plane_figure();
  plane_figure(Cat3DUnit<T>);
  ~plane_figure();

  virtual void get_description() = 0;
  //Cat3DUnit<T> get_center();
  //Cat3DUnit<T> set_center(Cat3DUnit<T>);
};

template <typename T>
plane_figure<T>::plane_figure(){
  this->center = Cat3DUnit<T>(); // By default 0,0,0 is center
  this->angle = 0;
}

template <typename T>
plane_figure<T>::plane_figure(Cat3DUnit<T> _center){
  this->center = _center;
  this->angle = 0;
}

template <typename T>
plane_figure<T>::~plane_figure(){
}


/*
template <typename T>
void plane_figure<T>::get_description(){
  cout<<"Plane Figure"<<endl;
  cout<<"Center at: "<<this->center<<endl;
}*/

//----------------------- CHILD CLASS -----------------------
template <typename T>
class Circle : public plane_figure<T>{
public:
  T radio;

  Circle() : plane_figure<T>(){this->radio = 0;}
  Circle(Cat3DUnit<T> _center) : plane_figure<T>( _center ){this->radio = 0;}
  Circle(Cat3DUnit<T>, T);

  void get_description();
};

template <typename T>
Circle<T>::Circle(Cat3DUnit<T> _center, T _radio){
  this->center = _center;
  this->radio = _radio;
}

template <typename T>
void Circle<T>::get_description(){
  cout<<"Circle Class"<<endl;
  cout<<"Center in: "<<this->center<<endl;
  cout<<"Radio of: "<<this->radio<<endl;
}


template <typename T>
class Square : public plane_figure<T>{
public:
  T side;
  Square() : plane_figure<T>(){this-> side = 1.0; } //Side can't be 0, default value as 1
  Square(Cat3DUnit<T> _center) : plane_figure<T> (_center){ this->side = 1.0; }
  Square(Cat3DUnit<T>, T);

  void get_description();
};


template <typename T>
Square<T>::Square(Cat3DUnit<T> _center, T _side){
  this->center = _center;
  this->side = _side;
}

template <typename T>
void Square<T>::get_description(){
  cout<<"Square Class"<<endl;
  cout<<"Center in: "<<this->center<<endl;
  cout<<"Side size of: "<<this->side<<endl;
}





#endif
