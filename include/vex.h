/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"
#include "usercontrol.h"
#include "matchauton.h"
#include "subsystems.h"
#include "chassisFunctions.h"

#include <iostream>

/// LOGGING FUNCTIONS USING C++ TEMPLATES
template <class T>
void LOG(T x)
{
    std::cout << x << std::endl;
}

template <class T, class U>
void LOG(T x, U y)
{
    std::cout << x << " " << y << std::endl;
}

template <class T, class U, class V>
void LOG(T x, U y, V z)
{
    std::cout << x << " " << y << " " << z << std::endl;
}

template <class T, class U, class V, class W>
void LOG(T x, U y, V z, W a)
{
    std::cout << x << " " << y << " " << z << " " << a << std::endl;
}

template <class T, class U, class V, class W, class X>
void LOG(T x, U y, V z, W a, X b)
{
    std::cout << x << " " << y << " " << z << " " << a << " " << b << std::endl;
}

template <class T, class U, class V, class W, class X, class Y>
void LOG(T x, U y, V z, W a, X b, Y c)
{
    std::cout << x << " " << y << " " << z << " " << a << " " << b << " " << c << std::endl;
}
/// radians operator
long double operator"" _rad(long double x);

/// degree operator (converted to radians)
long double operator"" _deg(long double x);

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)