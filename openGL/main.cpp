//
//  main.cpp
//  openGL
//
//  Created by Keita Nonaka on 1/22/19.
//  Copyright © 2019 Keita Nonaka. All rights reserved.
//

#include "Angel.h"


void init( void ) {
  // CHANGE the CLEAR color below (RGB)
  
  glClearColor( 1.0, 0.0, 0.0, 1.0 ); // white background
}

void display( void ) {
  glPointSize(5);
  glClear( GL_COLOR_BUFFER_BIT );     // clear the window
  glFlush();
}

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA );
  glutInitWindowSize( 512, 512 );
  
  // If you are using freeglut, the next two lines will check if
  // the code is truly 3.2. Otherwise, comment them out
  
  //glutInitContextVersion( 3, 2 );
  //glutInitContextProfile( GLUT_CORE_PROFILE );
  
  glutCreateWindow( "Lab00 No Shader" );
  
//  glewInit(); // this doesnt work on Xcode
  
  init();
  
  glutDisplayFunc( display );
  
  glutMainLoop();
  return 0;
}
