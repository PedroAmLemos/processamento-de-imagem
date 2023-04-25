#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

const int boardWidth = 10;
const int boardHeight = 20;
const int windowWidth = boardWidth * 30;
const int windowHeight = boardHeight * 30;

struct Tetromino {
    int shape[4][4];
};

extern const Tetromino tetrominoes[7];

void display();
void drawSquare(float x, float y, float size);
void drawTetromino(const Tetromino& tetromino, float x, float y, float blockSize);

class Game {
public:
    Game();
    void draw();
    void moveTetromino(int dx, int dy);
    void rotateTetromino();
    void spawnTetromino();
    bool canMove(int dx, int dy);
    bool canRotate();
    void drawBoard();
    bool isLineComplete(int row);
    void clearLine(int row);
    void checkLines();

private:
    int board[boardHeight][boardWidth];
    Tetromino currentTetromino;
    int currentX;
    int currentY;

    void mergeTetromino();
};

extern Game game;
void keyboard(unsigned char key, int x, int y);

void timer(int value);
