/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Globals
int pts = 50000;
int it = 0;
int itIncrement = 10;
float ptsArray[50000][3];
int mode = 1;
int ph=0;
int th=0;
double z=1;     // Z variable
double w=1;     // W variable

static GLfloat view_rotx = 25.0;
static GLfloat view_roty = 50.0;
static GLfloat view_rotz = 35.0;
//static GLfloat view_posz = 60.0;

 static void key(unsigned char ch,int x,int y);
 static void special(int key,int x,int y);
 static void reshape(int width,int height);


/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;





void display ()
{
  //glClear(GL_COLOR_BUFFER_BIT);   what happens if this has 1 arg
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();

  glRotatef(view_rotx, 1.0,0.0,0.0);
  glRotatef(view_roty, 0.0,1.0,0.0);
  glRotatef(view_rotz, 0.0,0.0,1.0);


  // glColor3f(0,1,1);   manipulate colors???
  glBegin(GL_LINE_STRIP);
  //draw
  int i = 0;
  while (i< it && i < pts)
  {
    glColor3fv(ptsArray[i]);
    glVertex3fv(ptsArray[i++]);
  }
  glEnd();

  if (it < pts)
  {
    if (it + itIncrement > pts) it = pts;
    else it += itIncrement;
  }


  glFlush();
  glutSwapBuffers();

  glPopMatrix();  

}



static void integrate_lorenz(void)
{
   int i;
   /*  Coordinates  */
   float x = ptsArray[0][0] = 1;
   float y = ptsArray[0][1] = 1;
   float z = ptsArray[0][2] = 1;
   /*  Time step  */
   float dt = 0.001;

  //printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
  /*
  *  Integrate 50,000 steps (50 time units with dt = 0.001)
  *  Explicit Euler integration
  */
  for (i=0;i<pts-1;i++)
  {
      float dx = s*(y-x);
      float dy = x*(r-z)-y;
      float dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
      ptsArray[i+1][0] = x;
      ptsArray[i+1][1] = y;
      ptsArray[i+1][2] = z;
  }
}


static void idle(void)
{
  it+=itIncrement;
  glutPostRedisplay();
}














/*
  helper functions below
*/





/*
 *  GLUT calls this routine when an arrow key is pressed
 */
 
static void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      view_roty += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      view_roty -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      view_rotx += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      view_rotx -= 5;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}


static void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   else if (ch == 'r')
   {
    it = 0;
   }
   //  Increase w by 0.1
   else if (ch == '+')
   {
         w += 1.0;
   }
   //  Decrease w by 0.1
   else if (ch == '-')
   {
         w -= 1.0;
   }
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}


// static void reshape(int width,int height)
// {
//    //  Set the viewport to the entire window
//    glViewport(0,0, width,height);
//    //  Tell OpenGL we want to manipulate the projection matrix
//    glMatrixMode(GL_PROJECTION);
//    //  Undo previous transformations
//    glLoadIdentity();

//    //  Switch to manipulating the model matrix
//    glMatrixMode(GL_MODELVIEW);
//    //  Undo previous transformations
//    glLoadIdentity();
//    glTranslatef(0.0,0.0,-60.0);
// }
static void reshape(int width, int height) {
  GLfloat h = (GLfloat) height / (GLfloat) width;

  glViewport(0, 0, (GLint) width, (GLint) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -h*2, h*2, 1.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -60.0);
}


/*
 *  Main
 */
int main(int argc, char *argv[])
{
  integrate_lorenz();

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500,500);
  glutCreateWindow("Lorenz Attractor");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);

  glutMainLoop();
   return 0;
} 











