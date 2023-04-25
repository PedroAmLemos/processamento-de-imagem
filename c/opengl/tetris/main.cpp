#include "tetris.hpp"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tetris");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(500, timer, 0); // Adicione esta linha

    glutMainLoop();
    return 0;
}
