/* Belov Danil, 10-6, 28.10.2021 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "glut.h"

#include "compl.h"

#define FRAME_W 1000
#define FRAME_H 800
#define FRAME_ZOOM 1


/* Time variables */
DBL SyncTime, FPS;

/* Measure time function */
void Timer(void)
{
  long t;
  static long StartTime = -1, FrameCount, FPSTime;

  t = clock();
  if (StartTime == -1)
    StartTime = FPSTime = t;
  FrameCount++;
  SyncTime = (t - StartTime) / (DBL)CLOCKS_PER_SEC;
  if (t - FPSTime > 1 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (DBL)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
  }
} /* End of 'Timer' function */

/* Frame variables */
HWND hWnd;
char Buf[100];
unsigned char Frame[FRAME_H][FRAME_W][3];

/* Draw pixel function */
void PutPixel(int X, int Y, int Red, int Green, int Blue)
{
  if (X > 0 || Y > 0 || X < FRAME_W || Y < FRAME_H)
  {
    Frame[Y][X][0] = Blue;
    Frame[Y][X][1] = Green;
    Frame[Y][X][2] = Red;
  }
} /* End of 'PutPixel' function */


/* Draw Mandelbrot set function */
void DrawMandelbrot( void )
{
  COMPL Z;
  DBL X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, xs, ys;
  int n;

  for (ys = 0; ys < FRAME_H; ys++)
    for (xs = 0; xs < FRAME_W; xs++)
    {
      Z = ComplSet(X0 + xs * (X1 - X0) / FRAME_W, Y0 + ys * (Y1 - Y0) / FRAME_H);
      n = Mandelbrot(Z);
      PutPixel(xs, ys, n, n / 8, n * 8);
    }
} /* End of 'DrawMandelbrot' function */


/* Draw Julia set function */
void DrawJulia( COMPL C )
{
  COMPL Z;
  DBL X0 = -2, X1 = 2, Y0 = -2, Y1 = 2, xs, ys;
  int n;   
  static int a, b;

  if (b++ % 10 == 0)
    a++;

  for (ys = 0; ys < FRAME_H; ys++)
    for (xs = 0; xs < FRAME_W; xs++)
    {
      Z = ComplSet(X0 + xs * (X1 - X0) / FRAME_W, Y0 + ys * (Y1 - Y0) / FRAME_H);
      n = Julia(Z, C);
      switch (a % 3)
      {
      case 0:
        PutPixel(xs, ys, n, n * 4, n * 2);
        break;
      case 1:
        PutPixel(xs, ys, n / 2, n * 2, n);
        break;
      case 2:
        PutPixel(xs, ys, n / 4, n, n / 2);
        break;
      }
    }  
} /* End of 'Julia' function */

int mode = 0; /* 0 - Mandelbrot, 1 - Julia */

/* GLUT Display function */
void Display( void )
{
  COMPL C;

  glClear(GL_COLOR_BUFFER_BIT);

  if (mode == 0)
    DrawMandelbrot();
  else
  {
    Timer();                 
    C = ComplSet(0.35 + 0.07 * cos(SyncTime), 0.39 + 0.08 * sin(1.1 * SyncTime));
    DrawJulia(C);
    sprintf(Buf, "FPS: %.3lf", FPS);
    SetWindowText(hWnd, Buf);
  }

  glPixelZoom(FRAME_ZOOM, -FRAME_ZOOM);
  glRasterPos2d(-1, 1);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */


/* GLUT Keyboard function */
void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(30);
  if (Key == 'm' || Key == 'M')
    mode = 0;
  if (Key == 'j' || Key == 'J')
    mode = 1;
} /* End of 'Keyboard' function */

/* Program main function */
void main( int argc, char*argv[] )
{ 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W, FRAME_H);
  glutCreateWindow("T20MANDL");
  hWnd = FindWindow(NULL, "T20MANDL");
     
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glClearColor(0.30, 0.47, 0.8, 1);

  glutMainLoop();
} /* End of 'main' function */
/* END OF "T20MANDL.C" FILE */