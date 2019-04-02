//
//  morphing3D.cpp
//  openGL
//
//  Created by Keita Nonaka on 3/31/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
#define LEN 512

double x = 0;
double dt = 0.0001;
double mv = 0;
GLdouble PI = 4.0 * atan(1.0);
static GLint axis = 2;
static GLfloat theta[] = {0.0,0.0,0.0};

void init(void) {
  glClearColor(0.0, 0.0, 1.0, 1.0);
}

void idle(void) {
  glutPostRedisplay();
}

void deltaTime(){
  if(mv < 0 || mv > 1) dt = -dt;
  mv += dt;
  glutPostRedisplay();
}

void resize(int w, int h) {
  glViewport(0, 0, LEN, LEN);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)LEN / (double)LEN, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void arrow() {
  glBegin(GL_POLYGON);
    glColor3d(1.0, 1.0, 0.0);
    glVertex3d(0, 1, 0);
    glVertex3d(-1, 0.5, 0);
    glVertex3d(-0.5, 0.5, 0);
    glVertex3d(-0.5, 0, 0);
    glVertex3d(0.5, 0, 0);
    glVertex3d(0.5, 0.5, 0);
    glVertex3d(1, 0.5, 0);
  glEnd();

  glBegin(GL_POLYGON);
    glColor3d(0.5, 0.0, 0.0);
    glVertex3d(0, 1, 1);
    glVertex3d(-1, 0.5, 1);
    glVertex3d(-0.5, 0.5, 1);
    glVertex3d(-0.5, 0, 1);
    glVertex3d(0.5, 0, 1);
    glVertex3d(0.5, 0.5, 1);
    glVertex3d(1, 0.5, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(0, 1.0, 1.0);
    glVertex3d(0, 1, 0);
    glVertex3d(0, 1, 1);
    glVertex3d(-1, 0.5, 1);
    glVertex3d(-1, 0.5, 0);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(0, 0, 1.0);
    glVertex3d(-1, 0.5, 0);
    glVertex3d(-0.5, 0.5, 0);
    glVertex3d(-0.5, 0.5, 1);
    glVertex3d(-1, 0.5, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(1, 0, 0);
    glVertex3d(-0.5, 0.5, 0);
    glVertex3d(-0.5, 0, 0);
    glVertex3d(-0.5, 0, 1);
    glVertex3d(-0.5, 0.5, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(1, 0, 1);
    glVertex3d(-0.5, 0, 0);
    glVertex3d(0.5, 0, 0);
    glVertex3d(0.5, 0, 1);
    glVertex3d(-0.5, 0, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(1, 0, 1);
    glVertex3d(0.5, 0, 0);
    glVertex3d(0.5, 0.5, 0);
    glVertex3d(0.5, 0.5, 1);
    glVertex3d(0.5, 0, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(1, 0, 1);
    glVertex3d(0.5, 0.5, 0);
    glVertex3d(1, 0.5, 0);
    glVertex3d(1, 0.5, 1);
    glVertex3d(0.5, 0.5, 1);
  glEnd();

  glBegin(GL_QUADS);
    glColor3d(1, 1, 1);
    glVertex3d(1, 0.5, 0);
    glVertex3d(0, 1, 0);
    glVertex3d(0, 1, 1);
    glVertex3d(1, 0.5, 1);
  glEnd();

  glFlush();
  deltaTime();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glViewport(0 , 0, LEN , LEN); // view port

	glRotatef( theta[0] , 1.0, 0.0, 0.0);
	glRotatef( theta[1] , 0.0, 1.0, 0.0);
	glRotatef( theta[2] , 0.0, 0.0, 1.0);
  
  arrow();

  glLineWidth(5);
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	  //x axis
	  glVertex3f(0,0,0);
	  glVertex3f(5,0,0);
	  // y axis
	  glVertex3f(0,0,0);
	  glVertex3f(0,5,0);
	  // z axis
	  glVertex3f(0,0,0);
	  glVertex3f(0,0,5);
	glEnd();

  deltaTime();
  glFlush();
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
  bool isLeft =false;

  switch(button) {
    case GLUT_LEFT_BUTTON:
      isLeft = true;
      glutIdleFunc(idle);
      break;
    case GLUT_RIGHT_BUTTON:
      exit(0);
      break;
  }

  switch(state) {
    case GLUT_DOWN:
      if(isLeft){
        
      }
      isLeft = false;
      break;
  }
}

void keyboard (unsigned char key, int x , int y) {
	if (key=='x' || key=='X') {axis = 0;glutPostRedisplay();}
	if (key=='y' || key=='Y') {axis = 1;glutPostRedisplay();}
	if (key=='z' || key=='Z') {axis = 2;glutPostRedisplay();}
	if (key=='q' || key=='Q') exit(0);

	theta[axis] += 2.0;
	if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
}

void timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(30, timer, 0);
}

int main(int argc, char **argv) {
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(LEN, LEN);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("Morphing 3D");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(100, timer, 0);
  glutMainLoop();
  return 0;
}
