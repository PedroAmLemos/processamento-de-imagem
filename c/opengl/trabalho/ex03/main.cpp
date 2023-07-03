#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Labirinto como matriz 10x10
int maze[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 1, 1, 1, 1, 1, 1}};

bool gameStarted = false;
bool gameOver = false;
bool gameWin = false;

void drawText(float x, float y, std::string text) {
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos2f(x, y);
  for (char c : text) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
  }
}

void keyboard(unsigned char key, int x, int y) {
  if ((gameOver || gameWin) && (key == 'r' || key == 'R')) {
    gameStarted = false;
    gameOver = false;
    gameWin = false;
    glutPostRedisplay();
  }
  if ((gameOver || gameWin) && key == 'q') {
    exit(0);
  }
}

void mousePassive(int x, int y) {
  if (gameOver || gameWin) {
    return;
  }

  int i = y / 50;
  int j = x / 50;

  if (!gameStarted) {
    if (i == 9 && j == 1) {
      gameStarted = true;
    }
    return;
  }

  if (i < 0 || i >= 10 || j < 0 || j >= 10) {
    gameOver = true;
    glutPostRedisplay();
    return;
  }

  if (maze[i][j] == 1) {
    gameOver = true;
    glutPostRedisplay();
    return;
  }

  if (i == 1 && j == 8) {
    gameWin = true;
    glutPostRedisplay();
    return;
  }
}

void drawMaze() {
  glClear(GL_COLOR_BUFFER_BIT);

  if (gameOver) {
    drawText(60, 250, "Game Over! Press R to restart or Q to quit.");
  } else if (gameWin) {
    drawText(60, 250, "You Win! Press R to restart or Q to quit.");
  } else {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (maze[i][j] == 1) {
          glColor3f(0.0f, 0.0f, 0.0f); // Color of walls
        } else {
          glColor3f(1.0f, 1.0f, 1.0f); // Color of path
        }

        // Mark the start with a green square
        if (i == 9 && j == 1) {
          glColor3f(0.0f, 1.0f, 0.0f);
        }

        // Mark the finish with checkered lines
        if (i == 1 && j == 8) {
          for (int y = 0; y < 50; y += 10) {
            for (int x = 0; x < 50; x += 10) {
              bool checker = (x + y) % 20 < 10;
              glColor3f(checker, checker, checker);
              glBegin(GL_QUADS);
              glVertex2f(j * 50 + x, i * 50 + y);
              glVertex2f(j * 50 + x + 10, i * 50 + y);
              glVertex2f(j * 50 + x + 10, i * 50 + y + 10);
              glVertex2f(j * 50 + x, i * 50 + y + 10);
              glEnd();
            }
          }
          continue;
        }

        glBegin(GL_QUADS);
        glVertex2f(j * 50, i * 50);
        glVertex2f(j * 50 + 50, i * 50);
        glVertex2f(j * 50 + 50, i * 50 + 50);
        glVertex2f(j * 50, i * 50 + 50);
        glEnd();
      }
    }
  }

  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Maze Game");
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glOrtho(0.0, 500, 500, 0.0, -1.0, 1.0);
  glutDisplayFunc(drawMaze);
  glutPassiveMotionFunc(mousePassive);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
