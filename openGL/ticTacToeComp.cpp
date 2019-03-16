//
//  ticTacToeComp.cpp
//  openGL
//
//  Created by Keita Nonaka on 3/15/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"
#include <iostream>
using namespace std;

#define LEN 512

bool firstPlayer = true; // first player or not
bool xWin = false;
bool oWin = false;
bool draw = false;
bool boardAvail[3][3] = {{false, false, false}, {false, false, false}, {false, false, false}};
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char player = 'x';
char opponent = 'o'; 

void init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
}

void frame() {
  for(GLfloat i = 0.3; i < 1; i += 0.6) {
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 0.0);
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
  double pos = 0;
  for(int i = 0; i < 3; i++) {
    pos = -0.6;
    for(int j = 0; j < 3; j++) {
      if(boardAvail[i][j]) {
        if(i == 0) {
          (board[0][j] == opponent) ? circle(pos, 0.6) : cross(pos, 0.6);
        } else if(i == 1){
          (board[1][j] == opponent) ? circle(pos, 0) : cross(pos, 0);
        } else if(i == 2){
          (board[2][j] == opponent) ? circle(pos, -0.6) : cross(pos, -0.6);
        }
      }
      pos += 0.6;
    }
  }
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT); // clear the window
  glViewport(0 , 0, LEN , LEN); // view port
  
  if(xWin) glClearColor(0.0, 1.0, 0.0, 1.0);
  else if(oWin) glClearColor(1.0, 0.0, 0.0, 1.0);
  frame();
  drawSign();
  
  glFlush();
}

bool clickBoard(GLdouble x, GLdouble y, char turn) {
  int num = 0;
  if(0.9 > y && y > 0.3) { // first row
    if(-0.3 > x && x > -0.9) {
      num = 0;
    } else if(0.3 > x && x > -0.3) {
      num = 1;
    } else if(0.9 > x && x > 0.3) {
      num = 2;
    }
    if(boardAvail[0][num] == true) return false;
    boardAvail[0][num] = true;
    board[0][num] = turn;
  } else if(0.3 > y && y > -0.3) { // second row
    if(-0.3 > x && x > -0.9) {
      num = 0;
    } else if(0.3 > x && x > -0.3) {
      num = 1;
    } else if(0.9 > x && x > 0.3) {
      num = 2;
    }
    if(boardAvail[1][num] == true) return false;
    boardAvail[1][num] = true;
    board[1][num] = turn;
  } else if(-0.3 > y && y > -0.9) { // third row
    if(-0.3 > x && x > -0.9) {
      num = 0;
    } else if(0.3 > x && x > -0.3) {
      num = 1;
    } else if(0.9 > x && x > 0.3) {
      num = 2;
    }
    if(boardAvail[2][num] == true) return false;
    boardAvail[2][num] = true;
    board[2][num] = turn;
  }
  return true;
}

bool checkBoard(char target) {
  if(board[0][0] == target && board[0][1] == target && board[0][2] == target) return true;
  else if(board[1][0] == target && board[1][1] == target && board[1][2] == target) return true;
  else if(board[2][0] == target && board[2][1] == target && board[2][2] == target) return true;
  else if(board[0][0] == target && board[1][0] == target && board[2][0] == target) return true;
  else if(board[0][1] == target && board[1][1] == target && board[2][1] == target) return true;
  else if(board[0][2] == target && board[1][2] == target && board[2][2] == target) return true;
  else if(board[0][0] == target && board[1][1] == target && board[2][2] == target) return true;
  else if(board[0][2] == target && board[1][1] == target && board[2][0] == target) return true;
  
  int n = 0;
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++)
      if(boardAvail[i][j] == true) n++;
    if(n == 9) draw = true;
  }
  return false;
}


bool isMovesLeft(char board[3][3]) { 
  for (int i = 0; i<3; i++) 
    for (int j = 0; j<3; j++) 
      if (board[i][j]==' ') return true; 
  return false; 
}


int evaluate(char b[3][3]) { 
  for (int row = 0; row<3; row++) { 
    if (b[row][0]==b[row][1] && b[row][1]==b[row][2]) { 
      if (b[row][0]==player) return +10; 
      else if (b[row][0]==opponent) return -10; 
    } 
  } 

  for (int col = 0; col<3; col++) { 
    if (b[0][col]==b[1][col] && b[1][col]==b[2][col]) { 
      if (b[0][col]==player) return +10; 
      else if (b[0][col]==opponent) return -10; 
    } 
  } 

  if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) { 
    if (b[0][0]==player) return +10; 
    else if (b[0][0]==opponent) return -10; 
  } 

  if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) { 
    if (b[0][2]==player) return + 10; 
    else if (b[0][2]==opponent) return - 10; 
  } 
  return 0; 
}

int minimax(char board[3][3], int depth, bool isMax) { 
  int score = evaluate(board); 

  if (score == 10) return score; 
  if (score == -10) return score; 
  if (isMovesLeft(board)==false) return 0; 

  if (isMax) { 
      int best = -1000; 
      for (int i = 0; i<3; i++) { 
        for (int j = 0; j<3; j++) { 
          if (board[i][j]==' ') { 
            board[i][j] = player; 
            best = max( best, minimax(board, depth+1, !isMax) ); 
            board[i][j] = ' '; 
          } 
        } 
      } 
      return best; 
  } else { 
    int best = 1000; 
    for(int i = 0; i<3; i++) { 
      for (int j = 0; j<3; j++) { 
        if (board[i][j]==' ') { 
          board[i][j] = opponent; 
          best = min(best, minimax(board, depth+1, !isMax)); 
          board[i][j] = ' '; 
        } 
      } 
    } 
    return best; 
  }
}

void findBestMove(char board[3][3]) { 
  int bestVal = -1000; 
  int row = -1; 
  int col = -1;

  if(draw) return;
  for (int i = 0; i < 3; i++) { 
    for (int j = 0; j < 3; j++) { 
      if (board[i][j]==' ') { 
        board[i][j] = player;  
        int moveVal = minimax(board, 0, false);  
        board[i][j] = ' '; 
        if (moveVal > bestVal) { 
          row = i; 
          col = j; 
          bestVal = moveVal; 
        } 
      } 
    } 
  }
  board[row][col] = opponent;
  boardAvail[row][col] = true;
  oWin = checkBoard(opponent);
  // firstPlayer = true;
  printf("The value of the best Move is : %d: %d: %d\n\n", row, col, bestVal); 
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
        if(xWin || oWin || draw) exit(0);
        if(firstPlayer && clickBoard(xPos, yPos, player)) {
          xWin = checkBoard(player);
          firstPlayer = false;
          if(!firstPlayer) {
            findBestMove(board);
            oWin = checkBoard(opponent);
            firstPlayer = true;
          }
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
