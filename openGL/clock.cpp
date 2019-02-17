//
//  clock.cpp
//  openGL
//
//  Created by Keita Nonaka on 2/16/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

/*
* Do you have problems with aliasing?
Yeah. There are still problems with aliasing.
I think few pixels cause aliasing.
*/

#include "Angel.h"
#include <cmath>
#define LEN 512

GLint hour = 2;
GLint minute = 25;
GLint second = 45;

GLfloat hoursConverter(int h, int m) {
  if(h == 12 && m == 0) return 0;
  if(h == 12) h = 0;
  GLfloat h_degree = h * 30;
  GLfloat m_degree = 30 * m / 60;
  return (h_degree + m_degree) * M_PI / 180;
}

GLfloat minutesConverter(int m) {
  GLfloat m_degree = m * 6;
  return m_degree * M_PI / 180;
}

void init(void) {
  glClearColor( 0.0, 0.0, 1.0, 1.0 );
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear the window

  glBegin(GL_LINE_LOOP); // frame
    glColor3d(1.0, 0.0, 0.0);
    glVertex2d(0.99, 0.99);
    glVertex2d(0.99, -0.99);
    glVertex2d(-0.99, -0.99);
    glVertex2d(-0.99, 0.99);
  glEnd();

  GLfloat len = 0.9;
  for(int ang = 0; ang < 360; ang += 6) { // clock tick makrs
    glBegin(GL_LINES);
      if(ang % 30 == 0) {
        glColor3d(1.0, 0.0, 0.0);
        len = 0.8;
      } else {
        glColor3d(1.0, 1.0, 1.0);
        len = 0.9;
      }
      glVertex2d(len*sin(ang*M_PI/180), len*cos(ang*M_PI/180));
      glVertex2d(0.95 * sin(ang*M_PI/180), 0.95 * cos(ang*M_PI/180));
    glEnd();
  }

  glPointSize(5);
  glBegin(GL_POINTS); // center of clock
    glColor3d(1.0, 0.0, 0.0);
    glVertex2d(0, 0);
  glEnd();

  glBegin(GL_TRIANGLE_FAN); // hour hand
    glColor3d(1.0, 0.0, 0.0);
    glVertex2d(0.5 * sin(hoursConverter(hour, minute)), 0.5 * cos(hoursConverter(hour, minute))); 
    glVertex2d(0.4 * sin(hoursConverter(hour, minute - 10)), 0.4 * cos(hoursConverter(hour, minute - 10)));
    glVertex2d(0, 0);
    glVertex2d(0.4 * sin(hoursConverter(hour, minute + 10)), 0.4 * cos(hoursConverter(hour, minute + 10)));
  glEnd();

  glBegin(GL_TRIANGLE_FAN); // minute hand
    glColor3d(1.0, 0.0, 0.0);
    glVertex2d(0.7 * sin(minutesConverter(minute)), 0.7 * cos(minutesConverter(minute)));
    glVertex2d(0.6 * sin(minutesConverter(minute - 1)), 0.6 * cos(minutesConverter(minute - 1)));
    glVertex2d(0, 0);
    glVertex2d(0.6 * sin(minutesConverter(minute + 1)), 0.6 * cos(minutesConverter(minute + 1)));
  glEnd();
  glFlush();
}

void mouse(int button, int state, int x, int y) {
  bool isLeftClick = false;
  switch(button) {
    case GLUT_LEFT_BUTTON:
      isLeftClick = true;
      break;
  }

  switch(state) {
    case GLUT_DOWN:
      if(isLeftClick) minute++;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'q':
    case 'Q':
      exit(0);
    default:
      break;
  }
}

int main(int argc, char **argv) {
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(LEN, LEN);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("A Clockwork Orange");
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
