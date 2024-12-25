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
pole::pole(Vec _s,float _d) : start(_s){
    d=4.0f/((float)_d+3.0f)*1.5f; end=start+Vec(d,0.0f);
}

void pole::pole_draw() const {
    #ifndef HEADLESS
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(start.getX(), start.getY());
    glVertex2f(end.getX(), end.getY());
    glEnd();
    #endif
}

void pole::pole_move(float *pole_switch){
    Vec unit(0.05f,0.0f);    
    if(*pole_switch==0){
        end -=unit; 
        if((end).getX()<=-1.0f){
            *pole_switch=1;
        }
    }else if(*pole_switch==1){
        end +=unit;
        if((end).getX()>=-1.0f+d){
            *pole_switch=3;
        }
    }
}
