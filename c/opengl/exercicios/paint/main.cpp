#include <GL/glut.h>

#include <iostream>

enum Color { RED, GREEN, BLUE };

Color currentColor = RED;

float pointSize = 1.0;

void drawPoint(GLint x, GLint y) {

  glBegin(GL_POINTS);

  glVertex2i(x, y);

  glEnd();
}

void setDrawingColor(Color color) {

  switch (color) {

  case RED:

    glColor3f(1.0, 0.0, 0.0);

    break;

  case GREEN:

    glColor3f(0.0, 1.0, 0.0);

    break;

  case BLUE:

    glColor3f(0.0, 0.0, 1.0);

    break;
  }
}

void display() {

  glClear(GL_COLOR_BUFFER_BIT);

  glutSwapBuffers();
}

void init() {

  glClearColor(1.0, 1.0, 1.0, 1.0);

  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void mouseFunc(int button, int state, int x, int y) {

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

    setDrawingColor(currentColor);

    glPointSize(pointSize);
  }
}

void motionFunc(int x, int y) {

  y = 480 - y;

  drawPoint(x, y);

  glutSwapBuffers();
}

void menuFunc(int value) {

  if (value >= 0 && value <= 2) {

    currentColor = static_cast<Color>(value);

  } else {

    switch (value) {

    case 3:

      pointSize = 1.0;

      break;

    case 4:

      pointSize = 3.0;

      break;

    case 5:

      pointSize = 5.0;

      break;
    }
  }
}

void keyboardFunc(unsigned char key, int x, int y) {

  if (key == 'd' || key == 'D') {

    display();
  }
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(640, 480);

  glutInitWindowPosition(100, 100);

  glutCreateWindow("Drawing Program");

  init();

  glutDisplayFunc(display);

  glutMouseFunc(mouseFunc);

  glutMotionFunc(motionFunc);

  glutKeyboardFunc(keyboardFunc);

  int colorMenu = glutCreateMenu(menuFunc);

  glutAddMenuEntry("Red", RED);

  glutAddMenuEntry("Green", GREEN);

  glutAddMenuEntry("Blue", BLUE);

  int pointSizeMenu = glutCreateMenu(menuFunc);

  glutAddMenuEntry("Small", 3);

  glutAddMenuEntry("Medium", 4);

  glutAddMenuEntry("Large", 5);

  int mainMenu = glutCreateMenu(menuFunc);

  glutAddSubMenu("Color", colorMenu);

  glutAddSubMenu("Point Size", pointSizeMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();

  return 0;
}
