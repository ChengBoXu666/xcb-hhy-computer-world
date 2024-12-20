#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include  <iostream>
#include <unistd.h>
#include "vec.h"
#include "drawing.h"

#ifndef HEADLESS
// just for testing display
// should be changed later
void TimeStep(int n) {
	glutTimerFunc(n, TimeStep, n); glutPostRedisplay();
}

void glDraw(){
    bool dir=0;
    static float _ang1=0.0f; 
    static Vec r_a1(0,0);
    static Vec an1(-0.7f,-0.5f);
    static Car ca(an1, .3f, .1f, dir,_ang1,r_a1);
    static float _ang11=0.0f; 
    static Vec r_a11(0,0);
    static Vec an11(-0.4f,-0.4f);
    static Car ca2(an11, .3f, .1f, dir,_ang11,r_a11);
    static float _ang2=PI/3.0f; 
    static Vec r_a2(0,0);
    static Vec an2(-0.3f,0.3f);
    static UFO ufo(an2,.2f,dir,_ang2,r_a2);
    static float _ang3=PI*2/3.0f; 
    static Vec r_a3(0,0);
    static Vec an3(0.3f,-0.4f);
    static Spacecraft spc(an3,.4f,.2f,dir,_ang3,r_a3);
    static Vec an4(-0.2f,0.7f);
    static Teleporter tltp(an4,.35f,.2f);
    float d=0.2f;
    static bool pole_switch=0;
    static Vec start(-1.0f,0.8f);
    static Vec end=start+Vec(d,0.0f);
    pole(start,&end,d,&pole_switch);
    glClear(GL_COLOR_BUFFER_BIT);
    pole_draw(start, end);
    ca.rotate(Vec(0,0),0.001f);
    ca.draw();
    ca2.draw();
    ca.move(Vec(.002f,.004f));
    ca2.move(Vec(.02f,.02f));
    tltp.move(Vec(.002f,-.001f));
    spc.move(Vec(-.002f,-.001f));
    //ufo.move(Vec(.002f,.001f));
    spc.zoom();
    spc.rotate(Vec(.002f,.01f),0.0000000001f);
    //ufo.zoom();
    ca.zoom();
    static float _angle3=0.00001f; 
    ufo.rotate(an2,_angle3);
    ufo.draw();
    spc.draw();
    tltp.draw();
    glutSwapBuffers();
    glFlush();
}
#endif

#ifndef HEADLESS
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
#else
int main(){
    ParkingLot p(10);
    Vehicle v(VehicleType::Car);
    p.park(&v);
    p.available_slots();
    sleep(5);
    p.unpark(&v);
    p.available_slots();
    return 0;
}
#endif
