#ifndef CATMATH_H
#define CATMATH_H

#define pi 3.1416

//Library dedicated to all matemathics functions related to the engine


//Degreess Operation
float degree_to_radians(float _d){ //Returns equivalent values of degrees in radians. Useful in functions
                                  //like sin or cos in math library for opengl
  return _d * pi / 180;
}


#endif
