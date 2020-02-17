#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "./include/dataset.h"
#include "./include/render.h"


int main(int argc,char *argv[]) {
    Dataset::Ptr dataset(new Dataset());
    dataset->fitting();
    get_data(dataset);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(width_, height_);
    glutCreateWindow("show");
    init();
    glutKeyboardFunc(&KeyBoards);
    glutDisplayFunc(&display);
    glutMainLoop();

    return 0;
}