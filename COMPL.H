/* Belov Danil, 10-6, 28.10.2021 */

typedef double DBL;

typedef struct
{
  DBL Re, Im;
} COMPL;

COMPL ComplSet( DBL A, DBL B);
int Mandelbrot( COMPL Z );
int Julia( COMPL Z, COMPL C );