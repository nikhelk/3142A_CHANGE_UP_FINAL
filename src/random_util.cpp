#include "vex.h"

/// radians operator
long double operator"" _rad(long double x){return(x);}

/// degree operator (converted to radians)
long double operator"" _deg(long double x){return(x*(M_PI/180));}