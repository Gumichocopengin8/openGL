//
//  BoxMan.cpp
//  openGL
//
//  Created by Keita Nonaka on 4/10/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
#define LEN 512

GLdouble headAngle = 0;
GLdouble torsoAngle = 0;
GLdouble leftArmAngle = 0;
GLdouble rightArmAngle = 0;
GLdouble leftLegAngle = 0;
GLdouble rightLegAngle = 0;
const GLdouble angle = 10;

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 1.0);
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

void head() {
  glColor3d(0.0, 1.0, 0.0);
  glPushMatrix();
    glScalef(1, 1, 1);
    glRotatef(headAngle, 0, 1, 0);
    glTranslatef(0, 3.5, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void torso() {
  glColor3d(0.0, 0.0, 1.0);
  glPushMatrix();
    glScalef(3, 6, 2);
    glRotatef(torsoAngle, 0, 1, 0);
    glTranslatef(0, 0, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void leftArm() {
  glColor3d(1.0, 0.0, 0.0);
  glPushMatrix();
    glScalef(1, 2, 1);
    glRotatef(leftArmAngle, 1, 0, 0);
    glTranslatef(-2, 0, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void rightArm() {
  glColor3d(1.0, 0.0, 0.0);
  glPushMatrix();
    glScalef(1, 2, 1);
    glRotatef(rightArmAngle, 1, 0, 0);
    glTranslatef(2, 0, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void leftLeg() {
  glColor3d(1.0, 1.0, 0.0);
  glPushMatrix();
    glScalef(1, 2, 1);
    glTranslatef(-1, -2, 0);
    glRotatef(leftLegAngle, 1, 0, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void rightLeg() {
  glColor3d(1.0, 1.0, 0.0);
  glPushMatrix();
    glScalef(1, 2, 1);
    glTranslatef(1, -2, 0);
    glRotatef(rightLegAngle, 1, 0, 0);
    glutWireCube(1.0);
  glPopMatrix();
}

void boxMan() {
  head();
  torso();
  leftArm();
  rightArm();
  leftLeg();
  rightLeg();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
  glLoadIdentity();
  gluLookAt(10.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glViewport(0 , 0, LEN , LEN); // view port

  boxMan();

  glFlush();
  glutSwapBuffers();
}

void keyboard (unsigned char key, int x , int y) {
	if (key=='h') { headAngle += angle; }
  if (key=='H') { headAngle -= angle; }
  if (key=='t') { torsoAngle += angle; }
  if (key=='T') { torsoAngle -= angle;}
  if (key=='l') { leftArmAngle += angle; }
  if (key=='L') { leftArmAngle -= angle; }
  if (key=='r') { rightArmAngle += angle; }
  if (key=='R') { rightArmAngle -= angle; }
  if (key=='k') { leftLegAngle += angle; }
  if (key=='K') { leftLegAngle -= angle; }
  if (key=='e') { rightLegAngle += angle; }
  if (key=='E') { rightLegAngle -= angle; }
	if (key=='q' || key=='Q') exit(0);

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
  glutCreateWindow("Box Man");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(100, timer, 0);
  glutMainLoop();
  return 0;
}
