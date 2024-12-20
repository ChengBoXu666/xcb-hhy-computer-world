#include <GL/glut.h>
#include <iostream>
#include "parkinglot_outline.h"

int parkinglot_outline(){
    int n=getnumslot();
    float d=4.0f/((float)n+3.0f);//the width of each slot
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES); 
    {
        glVertex2f(-1.0f+1.5f*d, 0.8f); 
        glVertex2f(1.0f, 0.8f); 
    }
    {
        glVertex2f(-1.0f, 0.8f); 
        glVertex2f(-1.0f, -0.8f); 
    }
    {
        glVertex2f(-1.0f+1.5f*d, -0.8f); //saving a gap for the entry
        glVertex2f(1.0f, -0.8f); 
    }
    {
        glVertex2f(1.0f, -0.8f); 
        glVertex2f(1.0f, 0.8f); 
    }//the boundary of the parking lot
    {
        glVertex2f(-1.0f+1.5f*d, 0.0f); 
        glVertex2f(1.0f-1.5f*d, 0.0f); 
    }//the horizontal middle line
    glEnd();
    return n;
}

int getnumslot(){
    int num=0;
    while(num<12&&num>22){
        std::cout<<"please input how many slots(range:12-22)"<<"\n";
        std::cin>>num;
    }
    num=num-num%2;
    return num;
}

//these functions fulfill the target of 
//1.prompting the user for how many slots they want 
//2.drawing the outline of the parking lot
