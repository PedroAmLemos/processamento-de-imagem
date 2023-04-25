#include <GL/glut.h>

void drawHouse() {

  // Base da casa

  glBegin(GL_TRIANGLES);

  glColor3f(0.5f, 0.35f, 0.05f);

  glVertex2f(-0.4f, -0.2f);

  glVertex2f(0.4f, -0.2f);

  glVertex2f(0.4f, 0.2f);

  glVertex2f(-0.4f, -0.2f);

  glVertex2f(0.4f, 0.2f);

  glVertex2f(-0.4f, 0.2f);

  glEnd();

  // Telhado

  glBegin(GL_TRIANGLES);

  glColor3f(0.7f, 0.0f, 0.0f);

  glVertex2f(-0.5f, 0.2f);

  glVertex2f(0.5f, 0.2f);

  glVertex2f(0.0f, 0.6f);

  glEnd();

  // Porta

  glBegin(GL_LINES);

  glColor3f(0.3f, 0.0f, 0.0f);

  glVertex2f(-0.1f, -0.2f);

  glVertex2f(0.1f, -0.2f);

  glVertex2f(0.1f, -0.2f);

  glVertex2f(0.1f, 0.0f);

  glVertex2f(0.1f, 0.0f);

  glVertex2f(-0.1f, 0.0f);

  glVertex2f(-0.1f, 0.0f);

  glVertex2f(-0.1f, -0.2f);

  glEnd();
}

void display() {

  glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  drawHouse();

  glFlush();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(640, 480);

  glutInitWindowPosition(100, 100);

  glutCreateWindow("Casa Simples com Primitivas OpenGL e GLUT");

  glutDisplayFunc(display);

  glutMainLoop();

  return 0;
}
