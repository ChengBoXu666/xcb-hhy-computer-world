#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include "drawing.h"

// pole_switch is a boolean that determines whether the pole is on or off
void pole(Vec start, Vec* end,float d,bool* pole_switch) {
    Vec unit(0.05f,0.00f);
    if(*pole_switch==0){
        *end -=unit;
        if((*end).getX()<=-0.95f){
            *pole_switch=1;  
        }
    }else{
        *end +=unit;
        if((*end).getX()>=-0.99f+d){
            *pole_switch=0;
        }
    }
}

void pole_draw(Vec start, Vec end) {
    #ifndef HEADLESS
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(start.getX(), start.getY());
    glVertex2f(end.getX(), end.getY());
    glEnd();
    #endif
}
