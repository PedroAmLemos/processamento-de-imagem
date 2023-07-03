#include <GL/glut.h>

float angleX = 0.0, angleY = 0.0;
float zoom = 1.0;
float xShift = 0.0, yShift = 0.0;

void handleKeypress(unsigned char key, int x, int y) {
  switch (key) {
  case 'w':
    zoom -= 0.1;
    break;
  case 's':
    zoom += 0.1;
    break;
  case 'a':
    xShift -= 0.1;
    break;
  case 'd':
    xShift += 0.1;
    break;
  }
  glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
    angleY -= 2.0;
    break;
  case GLUT_KEY_RIGHT:
    angleY += 2.0;
    break;
  case GLUT_KEY_UP:
    angleX -= 2.0;
    break;
  case GLUT_KEY_DOWN:
    angleX += 2.0;
    break;
  }
  glutPostRedisplay();
}

void drawCube() {
  float size = 0.5f;

  glBegin(GL_QUADS);

  // Front face
  glColor3f(1.0, 0.0, 0.0); // Red
  glVertex3f(size, size, size);
  glVertex3f(-size, size, size);
  glVertex3f(-size, -size, size);
  glVertex3f(size, -size, size);

  // Back face
  glColor3f(0.0, 1.0, 0.0); // Green
  glVertex3f(size, size, -size);
  glVertex3f(size, -size, -size);
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, size, -size);

  // Top face
  glColor3f(0.0, 0.0, 1.0); // Blue
  glVertex3f(size, size, size);
  glVertex3f(size, size, -size);
  glVertex3f(-size, size, -size);
  glVertex3f(-size, size, size);

  // Bottom face
  glColor3f(1.0, 1.0, 0.0); // Yellow
  glVertex3f(size, -size, size);
  glVertex3f(-size, -size, size);
  glVertex3f(-size, -size, -size);
  glVertex3f(size, -size, -size);

  // Right face
  glColor3f(1.0, 0.0, 1.0); // Magenta
  glVertex3f(size, size, size);
  glVertex3f(size, -size, size);
  glVertex3f(size, -size, -size);
  glVertex3f(size, size, -size);

  // Left face
  glColor3f(0.0, 1.0, 1.0); // Cyan
  glVertex3f(-size, size, size);
  glVertex3f(-size, size, -size);
  glVertex3f(-size, -size, -size);
  glVertex3f(-size, -size, size);

  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(xShift, yShift, -7.0f * zoom);
  glRotatef(angleY, 0.0f, 1.0f, 0.0f);
  glRotatef(angleX, 1.0f, 0.0f, 0.0f);
  drawCube();
  glutSwapBuffers();
}

void initRendering() { glEnable(GL_DEPTH_TEST); }

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400, 400);
  glutCreateWindow("3D Cube");
  initRendering();
  glutDisplayFunc(display);
  glutKeyboardFunc(handleKeypress);
  glutSpecialFunc(handleSpecialKeypress);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
