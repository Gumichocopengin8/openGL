//
//  morphing.cpp
//  openGL
//
//  Created by Keita Nonaka on 3/25/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
#define LEN 512

double x = 0;
double y = 0;
GLdouble PI = 4.0*atan(1.0);
GLdouble theta = 10.0*PI/360.0;

void init(void) {
  glClearColor(0.0, 0.0, 1.0, 1.0);
}

void idle(void) {
  glutPostRedisplay();
}

void resize(int w, int h) {
  glViewport(0, 0, LEN, LEN);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)LEN / (double)LEN, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

GLdouble shuriken[][2] = {
  {0, 0.6},
  {-0.2, 0.2},
  {-0.6, 0},
  {-0.2, -0.2},
  {0, -0.6},
  {0.2, -0.2},
  {0.6, 0},
  {0.2, 0.2},
  {0, 0.6}
};

GLdouble arrow[][2] = {
  {0, 0.8},
  {-0.6, 0.4},
  {-0.4, 0.4},
  {-0.4, -0.8},
  {0.4, -0.8},
  {0.4, 0.4},
  {0.6, 0.4},
  {0.6, 0.4},
  {0, 0.8},
};

GLdouble shape[9][2];

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear the window
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glViewport(0 , 0, LEN , LEN); // view port
  
  glRotated(x, 0.0, 1.0, 0.0);
  x++;
  glBegin(GL_LINE_LOOP);
    glColor3d(0.0, 1.0, 0.0);
    for (int i = 0; i < 8; i++) {
      glVertex2dv(shuriken[i]);
      glVertex2dv(shuriken[i + 1]);
    }
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void spinDisplay() {
	glRotatef( theta , 0 ,0 , 1 );
	glutPostRedisplay();
}

void menu01 (GLint id) {
	switch (id) {
	case 3:
		theta += 2*2.0*PI/360.0;
		break;
	case 4:
		theta -= 2*2.0*PI/360.0;
		break;
	case 2:
		break;
	}
	glutIdleFunc(spinDisplay);
}

void menu02 (GLint id) {
	switch (id) {
	case 1:
		exit(0);
		break;
	case 5:
		glutIdleFunc(NULL);
		break;
	}
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

void timer(int extra) {
  glutPostRedisplay();
  glutTimerFunc(30, timer, 0);
}

int main(int argc, char **argv) {
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(LEN, LEN);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("Morphing");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutTimerFunc(100, timer, 0);
  glutMainLoop();

  GLint spinMenu = glutCreateMenu(menu01);
	glutAddMenuEntry("spin",2);
	glutAddMenuEntry("speed up",3);
	glutAddMenuEntry("slow down",4);

	glutCreateMenu(menu02);
	glutAddMenuEntry("quit",1);
	glutAddSubMenu("spin options",spinMenu);
	glutAddMenuEntry("stop",5);
	glutAttachMenu(GLUT_LEFT_BUTTON);
  return 0;
}
