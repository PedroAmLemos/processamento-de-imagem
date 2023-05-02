#include <GL/glut.h>

float xTrans = 0.0, yTrans = 0.0;
float scale = 1.0;
float angle = 0.0;
float minScale = 0.0001;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(xTrans, yTrans, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  glScalef(scale, scale, 1.0);

  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.749f, 1.0f); // Define cor corrente de desenho
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, -0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(-0.5, 0.5);
  glEnd();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    scale += 0.01;
    break;
  case 's':
    if (scale > minScale) { // Verifique se a escala é maior que o mínimo
      scale -= 0.01;
    }
    break;
  case 'a':
    angle += 3.0;
    break;
  case 'd':
    angle -= 3.0;
    break;
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    yTrans += 0.1;
    break;
  case GLUT_KEY_DOWN:
    yTrans -= 0.1;
    break;
  case GLUT_KEY_LEFT:
    xTrans -= 0.1;
    break;
  case GLUT_KEY_RIGHT:
    xTrans += 0.1;
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Transformações 2D");

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -1.0, 1.0);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);

  glutMainLoop();
  return 0;
}
