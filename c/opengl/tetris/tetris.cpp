#include "tetris.hpp"

const Tetromino tetrominoes[7] = {
    // I
    {{
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    }},
    // J
    {{
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 0},
    }},
    // L
    {{
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0},
    }},
    // O
    {{
        {1, 1},
        {1, 1},
    }},
    // S
    {{
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    }},
    // T
    {{
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0},
    }},
    // Z
    {{
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    }},
};
Game game;

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();
  glOrtho(0, windowWidth, windowHeight, 0, -1, 1);

  // Desenhe aqui
  game.draw();

  glutSwapBuffers();
}

void drawSquare(float x, float y, float size) {
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + size, y);
  glVertex2f(x + size, y + size);
  glVertex2f(x, y + size);
  glEnd();
}

void drawTetromino(const Tetromino &tetromino, float x, float y,
                   float blockSize) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetromino.shape[i][j]) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawSquare(x + j * blockSize, y + i * blockSize, blockSize);
      }
    }
  }
}

Game::Game() {
  for (int i = 0; i < boardHeight; i++) {
    for (int j = 0; j < boardWidth; j++) {
      board[i][j] = 0;
    }
  }
  spawnTetromino();
}

void Game::draw() {
  drawBoard();

  float blockSize = 30.0f;
  drawTetromino(currentTetromino, currentX * blockSize, currentY * blockSize,
                blockSize);
}

void Game::mergeTetromino() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentTetromino.shape[i][j]) {
        board[currentY + i][currentX + j] = 1;
      }
    }
  }
}
void Game::moveTetromino(int dx, int dy) {
  if (canMove(dx, dy)) {
    currentX += dx;
    currentY += dy;
  } else if (dy > 0) {
    mergeTetromino();
    checkLines();
    spawnTetromino();
  }
}

void Game::rotateTetromino() {
  if (canRotate()) {
    Tetromino rotated;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        rotated.shape[i][j] = currentTetromino.shape[3 - j][i];
      }
    }
    currentTetromino = rotated;
  }
}

void Game::spawnTetromino() {
  currentTetromino = tetrominoes[rand() % 7];
  currentX = boardWidth / 2 - 2;
  currentY = 0;
}

bool Game::canMove(int dx, int dy) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (currentTetromino.shape[i][j]) {
        int newX = currentX + j + dx;
        int newY = currentY + i + dy;

        if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight ||
            board[newY][newX]) {
          return false;
        }
      }
    }
  }

  return true;
}

bool Game::canRotate() {
  Tetromino rotated;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      rotated.shape[i][j] = currentTetromino.shape[3 - j][i];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (rotated.shape[i][j]) {
        int newX = currentX + j;
        int newY = currentY + i;

        if (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight ||
            board[newY][newX]) {
          return false;
        }
      }
    }
  }

  return true;
}

void Game::drawBoard() {
  float blockSize = 30.0f;

  for (int i = 0; i < boardHeight; i++) {
    for (int j = 0; j < boardWidth; j++) {
      if (board[i][j]) {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawSquare(j * blockSize, i * blockSize, blockSize);
      }
    }
  }
}

bool Game::isLineComplete(int row) {
  for (int j = 0; j < boardWidth; j++) {
    if (!board[row][j]) {
      return false;
    }
  }

  return true;
}

void Game::clearLine(int row) {
  for (int i = row; i > 0; i--) {
    for (int j = 0; j < boardWidth; j++) {
      board[i][j] = board[i - 1][j];
    }
  }
}

void Game::checkLines() {
  for (int i = 0; i < boardHeight; i++) {
    if (isLineComplete(i)) {
      clearLine(i);
    }
  }
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'a':
  case 'A':
    game.moveTetromino(-1, 0);
    break;
  case 'd':
  case 'D':
    game.moveTetromino(1, 0);
    break;
  case 's':
  case 'S':
    game.moveTetromino(0, 1);
    break;
  case 'w':
  case 'W':
    game.rotateTetromino();
    break;
  default:
    break;
  }

  glutPostRedisplay();
}


void timer(int value) {
    game.moveTetromino(0, 1);
    glutPostRedisplay();
    glutTimerFunc(500, timer, 0); // 500 milissegundos
}
