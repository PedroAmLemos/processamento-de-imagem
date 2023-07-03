#include <GL/glut.h>
#include <cmath>

const float EARTH_RADIUS = 1.0f;
const float MOON_RADIUS = 0.3f;
const float MOON_DISTANCE = 3.0f;
const float EARTH_ROTATION_SPEED = 0.5f;
const float MOON_ROTATION_SPEED = 1.0f;

float cameraDist = 8.0f;
float cameraAng = 0.0f;

void drawLine(float radius, float lat) {
  const float DEG2RAD = 3.14159 / 180;
  glPushMatrix();
  glRotatef(lat, 1.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; i++) {
    float degInRad = i * DEG2RAD;
    glVertex3f(cos(degInRad) * radius, 0.0f, sin(degInRad) * radius);
  }
  glEnd();
  glPopMatrix();
}

void drawMeridian(float radius) {
  const float DEG2RAD = 3.14159 / 180;
  glBegin(GL_LINE_LOOP);
  for (int i = -90; i <= 90; i++) {
    float degInRad = i * DEG2RAD;
    glVertex3f(0.0f, sin(degInRad) * radius, cos(degInRad) * radius);
  }
  glEnd();
}

void drawEarthAndMoon() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(1, 1, cameraDist, 0, 0, 0, 0, 1, 0);

  glColor3f(0.0f, 0.5f, 1.0f);
  glRotatef(cameraAng, 0.0f, 1.0f, 0.0f);
  glutSolidSphere(EARTH_RADIUS, 50, 50);

  glColor3f(1.0f, 0.0f, 0.0f);
  drawLine(EARTH_RADIUS, 23.5f);
  drawLine(EARTH_RADIUS, -23.5f);
  drawMeridian(EARTH_RADIUS);

  glPushMatrix();

  glRotatef(cameraAng * MOON_ROTATION_SPEED, 0.0f, 1.0f, 0.0f);
  glTranslatef(MOON_DISTANCE, 0.0f, 0.0f);

  glColor3f(1.0f, 1.0f, 1.0f);
  glutSolidSphere(MOON_RADIUS, 50, 50);

  glColor3f(1.0f, 0.0f, 0.0f);
  drawMeridian(MOON_RADIUS);

  glPopMatrix();

  glutSwapBuffers();
}

void updateScene(int value) {
  cameraAng += EARTH_ROTATION_SPEED;
  glutPostRedisplay();
  glutTimerFunc(16, updateScene, 0);
}

void adjustViewport(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float)w / h, 0.1, 100);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Earth and Moon Simulation");

  glutDisplayFunc(drawEarthAndMoon);
  glutReshapeFunc(adjustViewport);
  glEnable(GL_DEPTH_TEST);
  gluLookAt(0, 0, cameraDist, 0, 0, 0, 0, 1, 0);
  glutTimerFunc(16, updateScene, 0);

  glutMainLoop();

  return 0;
}
