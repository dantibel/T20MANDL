/* Belov Danil, 10-6, 28.10.2021 */

#include <time.h>
#include <math.h>

#include "compl.h"

/* Set complex number by components function */
COMPL ComplSet( DBL A, DBL B)
{
  COMPL Z;

  Z.Re = A, Z.Im = B;
  return Z; 
} /* End 'ComplSet' function */


/* Add two complex numbers function */
COMPL ComplAddCompl( COMPL Z1, COMPL Z2 )
{
  return ComplSet(Z1.Re + Z2.Re, Z1.Im + Z2.Im); 
} /* End of 'ComplAddCompl' function */


/* Multiply two complex numbers function */
COMPL ComplMulCompl( COMPL Z1, COMPL Z2 )
{
  return ComplSet(Z1.Re * Z2.Re - Z1.Im * Z2.Im, Z1.Re * Z2.Im + Z1.Im * Z2.Re);
} /* End of 'ComplMulCompl' function */


/* square of absolute value of complex number function */
DBL ComplNorm2( COMPL Z )
{
  return Z.Re * Z.Re + Z.Im * Z.Im;
} /* End of 'ComplNormCompl2' function */


/* absolute value of complex number function */
DBL ComplNorm( COMPL Z )
{
  return sqrt(ComplNorm2(Z));
} /* End of 'ComplNorm' function */


/* Mandelbrot Set function */
int Mandelbrot( COMPL Z )
{
  COMPL Z0 = Z;
  int n = 0;

  while (n < 255 && ComplNorm2(Z) < 4)
  {
    Z = ComplAddCompl(ComplMulCompl(Z, Z), Z0);
    n++;
  }
  return n;
} /* End of 'Mandelbrot' function */


/* Julia set function */
int Julia( COMPL Z, COMPL C )
{
  int n = 0;

  while (n < 255 && ComplNorm2(Z) < 4)
  {
    Z = ComplAddCompl(ComplMulCompl(Z, Z), C);
    n++;
  }
  return n;
} /* End of 'Julia' function */
/* END OF 'COMPL.C' FILE */