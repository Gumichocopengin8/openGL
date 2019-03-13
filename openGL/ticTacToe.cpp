//
//  ticTacToe.cpp
//  openGL
//
//  Created by Keita Nonaka on 3/13/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
#define LEN 512

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
bool firstPlayer = true; // first player or not

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

void drawSign(GLfloat cx, GLfloat cy) {
  firstPlayer ? cross(cx, cy) : circle(cx, cy);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear the window
  glViewport(0 , 0, LEN , LEN); // view port

  frame();

  glFlush();
}

void clickBoard(GLdouble x, GLdouble y, char turn) {
  if(0.9 > y && y > 0.3) { // first row
    if(-0.9 > x && x > -0.3) {
      drawSign(-0.75, 0.75);
      board[0][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      drawSign(0, -0.75);
      board[0][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      drawSign(0.75, 0.75);
      board[0][2] = turn;
    }
  } else if(0.3 > y && y > -0.3) { // second row
    if(-0.9 > x && x > -0.3) {
      drawSign(0, -0.75);
      board[1][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      drawSign(0, 0);
      board[1][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      drawSign(0, 0.75);
      board[1][2] = turn;
    }
  } else if(-0.3 > y && y > -0.9) {
    if(-0.9 > x && x > -0.3) {
      drawSign(-0.75, -0.75);
      board[2][0] = turn;
    } else if(0.3 > x && x > -0.3) {
      drawSign(0, -0.75);
      board[2][1] = turn;
    } else if(0.9 > x && x > 0.3) {
      drawSign(0.75, -0.75);
      board[2][2] = turn;
    }
  }
}

void mouse(int button, int state, int x, int y) {
  bool isLeft =false;
  double xPos = (double(x)/(glutGet(GLUT_WINDOW_WIDTH)/2) - 1);
  double yPos = (double(y)/(glutGet(GLUT_WINDOW_HEIGHT)/2) - 1) * -1;

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
          firstPlayer = false;
          clickBoard(xPos, yPos, 'x');
        } else {
          firstPlayer = true;
          clickBoard(xPos, yPos, 'o');
        }
      }
      isLeft = false;
      break;
    default:
      break;
  }
  printf("%f:%f\n", xPos, yPos);
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
