//
//  ticTacToe.cpp
//  openGL
//
//  Created by Keita Nonaka on 3/13/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
using namespace std;

#define LEN 512

bool firstPlayer = true; // first player or not
bool boardAvail[3][3] = {{false, false, false}, {false, false, false}, {false, false, false}};
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void frame() {
  for(GLfloat i = 0.3; i < 1; i += 0.6) { 
    glBegin(GL_LINES); 
      glColor3d(1.0, 0.0, 0.0);
      glVertex2d(-0.9, i); // row line
      glVertex2d(0.9, i);
      glVertex2d(-0.9, i * -1);
      glVertex2d(0.9, i * -1);

      glVertex2d(i, -0.9); // col line
      glVertex2d(i, 0.9);
      glVertex2d(i * -1, -0.9);
      glVertex2d(i * -1, 0.9);
    glEnd();
  }
  glFlush();
}

void cross(GLfloat x, GLfloat y) {
  glBegin(GL_LINES);
    glVertex2d(x - 0.2, y - 0.2);
    glVertex2d(x + 0.2, y + 0.2);

    glVertex2d(x - 0.2, y + 0.2);
    glVertex2d(x + 0.2, y - 0.2);
  glEnd();
  glFlush();
}

void circle(GLfloat cx, GLfloat cy) {
  const GLfloat r = 0.25;
  const GLint num_segments = 30;
  glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++) {
      GLfloat theta = 2.0f * 3.1415926f * GLfloat(ii) / GLfloat(num_segments);
      GLfloat x = r * cosf(theta);
      GLfloat y = r * sinf(theta);
      glVertex2f(x + cx, y + cy);
    }
  glEnd();
  glFlush();
}

void drawSign() {
  if(boardAvail[0][0]) {
    if(board[0][0] == 'o') circle(-0.6, 0.6);
    else cross(-0.6, 0.6);
  }
  if(boardAvail[0][1]) {
    if(board[0][1] == 'o') circle(0, 0.6);
    else cross(0, 0.6);
  }
  if(boardAvail[0][2]) {
    if(board[0][2] == 'o') circle(0.6, 0.6);
    else cross(0.6, 0.6);
  }

  if(boardAvail[1][0]) {
    if(board[1][0] == 'o') circle(-0.6, 0);
    else cross(-0.6, 0);
  }
  if(boardAvail[1][1]) {
    if(board[1][1] == 'o') circle(0, 0);
    else cross(0, 0.6);
  }
  if(boardAvail[1][2]) {
    if(board[1][2] == 'o') circle(0.6, 0);
    else cross(0.6, 0.6);
  }

  if(boardAvail[2][0]) {
    if(board[2][0] == 'o') circle(-0.6, -0.6);
    else cross(-0.6, -0.6);
  }
  if(boardAvail[2][1]) {
    if(board[2][1] == 'o') circle(0, -0.6);
    else cross(0, -0.6);
  }
  if(boardAvail[2][2]) {
    if(board[2][2] == 'o') circle(0.6, -0.6);
    else cross(0.6, -0.6);
  }
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear the window
  glViewport(0 , 0, LEN , LEN); // view port

  frame();
  drawSign();

  glFlush();
}

void clickBoard(GLdouble x, GLdouble y, char turn) {
  if(0.9 > y && y > 0.3) { // first row
    if(-0.3 > x && x > -0.9) {
      boardAvail[0][0] = true;
      board[0][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      boardAvail[0][1] = true;
      board[0][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      boardAvail[0][2] = true;
      board[0][2] = turn;
    }
  } else if(0.3 > y && y > -0.3) { // second row
    if(-0.3 > x && x > -0.9) {
      boardAvail[1][0] = true;
      board[1][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      boardAvail[1][1] = true;
      board[1][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      boardAvail[1][2] = true;
      board[1][2] = turn;
    }
  } else if(-0.3 > y && y > -0.9) { // third row
    if(-0.3 > x && x > -0.9) {
      boardAvail[2][0] = true;
      board[2][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      boardAvail[2][1] = true;
      board[2][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      boardAvail[2][2] == true;
      board[2][2] = turn;
    }
  }
}

void mouse(int button, int state, int x, int y) {
  bool isLeft =false;
  double xPos = (double(x)/(glutGet(GLUT_WINDOW_WIDTH)/2) - 1); // conversion world pos to ndc
  double yPos = (double(y)/(glutGet(GLUT_WINDOW_HEIGHT)/2) - 1) * -1; // conversion world pos to ndc

  switch(button) {
    case GLUT_LEFT_BUTTON:
      isLeft = true;
      break;
    case GLUT_RIGHT_BUTTON:
      exit(0);
      break;
  }

  switch(state) {
    case GLUT_DOWN:
      if(isLeft){
        if(firstPlayer) {
          clickBoard(xPos, yPos, 'x'); 
          firstPlayer = false;
        } else {
          clickBoard(xPos, yPos, 'o'); 
          firstPlayer = true;
        }
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
  glutCreateWindow("Tic Tac Toe");
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutTimerFunc(100, timer, 0);
  glutMainLoop();
  return 0;
}
