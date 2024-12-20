#include <GL/glut.h>
#include <iostream>
#include "parkinglot_places.h"

void _slots_::draw_slots() {
    glBegin(GL_LINES);
    if ((float)num <= (float)total / 2) {
        glVertex2f(-1.0f + (float)((1.5f + (float)num) * width), 0.8f); 
        glVertex2f(-1.0f + (float)((1.5f + (float)num) * width), 0.4f);
    } else {
        glVertex2f(-1.0f + (float)((1.5f + (float)num) * width), -0.8f); 
        glVertex2f(-1.0f + (float)((1.5f + (float)num) * width), -0.4f);
    }
    // the separating line of the slots
    glEnd(); 
}