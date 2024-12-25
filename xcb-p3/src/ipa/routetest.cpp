#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include <unistd.h>
#include  <iostream>
#include "vec.h"
#include "drawing.h"
/*
#ifndef HEADLESS
void TimeStep(int n) {
    glutTimerFunc(n, TimeStep, n); glutPostRedisplay();
}

void glDraw(){
    static int n = 0;
    std::vector<Vec> controlPoints = {
        Vec(0, 0),
        Vec(0, 0.7f),
        Vec(0, 0.8f),
        Vec(0, 0.8f),
        Vec(-0.1f, 0.8f),
        Vec(-0.7f, 0.8f),
        Vec(-0.8f, 0.8f),
        Vec(-0.8f, 0.8f),
        Vec(-0.8f, 0.7f),
        Vec(-0.8f, 0.1f),
        Vec(-0.8f, 0),
        Vec(-0.8f, 0),
        Vec(-0.7f, 0),
        Vec(0, 0),
    };
    static Vec point(0, 0);
    int numPoints = 100;
    if (n > numPoints) return;
    for (int i = 0; i <= n; ++i) {
        float t = (float)i / numPoints;
        point = Vec::bezier(controlPoints, t);
    }
    bool dir = false;
    static float _ang1 = 0.0f; 
    static Vec r_a1(0, 0);
    static Vec an1(0, 0);
    static Car ca(an1, .3f, .1f, dir, _ang1, r_a1);
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout<<atan2((point-ca.getAnchor()).getY(), (point-ca.getAnchor()).getX())-ca.getangle()<<'\n';
    ca.rotate(ca.getAnchor(), (float)atan2((point-ca.getAnchor()).getY(), (point-ca.getAnchor()).getX())-ca.getangle());
    ca.move(point-ca.getAnchor());
    ca.draw();
    glutSwapBuffers();
    glFlush();
    n++;
}
#endif

int main(int argc, char *argv[])
{   

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Parking Lot");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(glDraw);
    glutTimerFunc(150, TimeStep, 150);
    glutMainLoop();
    return 0;
}
*/