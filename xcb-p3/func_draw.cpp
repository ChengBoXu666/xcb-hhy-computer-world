#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include <cstdlib>
#include "drawing.h"

ColoredFig::~ColoredFig(){}

void Group::draw(){
    for(it=sh.begin();it!=sh.end();++it) {
        if(sh.size()==1){
            rectangle* tmp = dynamic_cast<rectangle*>(*it);
            if (tmp) {
                tmp->paint();
            }
        }
        (*it)->draw();
    }
}
void Group::move(Vec dir){
    setAnchor(getAnchor()+dir);
    for(it=sh.begin();it!=sh.end();++it) (*it)->move(dir);
}
void Group::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(getangle()+angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    for(it=sh.begin();it!=sh.end();++it) (*it)->rotate(getrota_anchor(),getangle());
}
void Group::zoom(){
    //std::cout<<getk()<<std::endl;
    static bool flag=0;
    if(getk()>=0.5f && flag==0) {
        setk(getk()/1.01f);
        for(it=sh.begin();it!=sh.end();++it){ (*it)->zoom(1/1.01f,getAnchor()); }
    }else if(getk()<=1.1f) {
        setk(getk()*1.01f); flag=1;
        for(it=sh.begin();it!=sh.end();++it){ (*it)->zoom(1.01f,getAnchor()); }
    }
    else flag=0;
    
}

//different colored figures
void circle::draw(){
    #ifndef HEADLESS
    static const float pi=3.1415926f;
    static const int cnt=1000;
    glColor3f(r,g,b);
    float angleUnit=2*pi/cnt;
    float angle =0;
    glVertex2f(getAnchor().getX(),getAnchor().getY()); //start-point
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0;i<=cnt;i++){
            glVertex2f((float)(getAnchor().getX() + ra*cos(angle)), (float)(getAnchor().getY() + ra*sin(angle)));
            angle+=angleUnit;
        }
    glEnd();
    #endif
}

void triangle::draw(){
    #ifndef HEADLESS
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
        glVertex2f(p1.getX(),p1.getY());
        glVertex2f(p2.getX(),p2.getY());
        glVertex2f(p3.getX(),p3.getY());
    glEnd();
    #endif
}

void semicircle::draw(){
    #ifndef HEADLESS
    static const int cnt=1000;
    glColor3f(r,g,b);
    float angleUnit=PI/cnt;
    float angle =0;
    glVertex2f(getAnchor().getX(),getAnchor().getY()); //start-point
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0;i<=cnt;i++){
            glVertex2f((getAnchor() + ((p2-getAnchor())<<angle)).getX(), (getAnchor() + ((p2-getAnchor())<<angle)).getY());
            angle+=angleUnit;
        }
    glEnd();
    #endif
}

void line::draw(){
    #ifndef HEADLESS
    glColor3f(r,g,b);
    glBegin(GL_LINES);
        glVertex2f(p1.getX(),p1.getY());
        glVertex2f(p2.getX(),p2.getY());
    glEnd();
    #endif
}

void rectangle::draw(){
    #ifndef HEADLESS
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
        glVertex2f(p1.getX(),p1.getY());
        glVertex2f(p2.getX(),p2.getY());
        glVertex2f(p3.getX(),p3.getY());
        glVertex2f(p4.getX(),p4.getY());
    glEnd();
    #endif
}
void rectangle::paint(){
    r=(float)rand()/(float)RAND_MAX;
    g=(float)rand()/(float)RAND_MAX;
    b=(float)rand()/(float)RAND_MAX;
}

void trapezium::draw(){
    #ifndef HEADLESS
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
        glVertex2f(p1.getX(),p1.getY());
        glVertex2f(p2.getX(),p2.getY());
        glVertex2f(p3.getX(),p3.getY());
        glVertex2f(p4.getX(),p4.getY());
    glEnd();
    #endif
}

// move
void circle::move(Vec dir){ setAnchor(getAnchor()+dir);}
void triangle::move(Vec dir){
    setAnchor(getAnchor()+dir);
    p1+=dir; p2+=dir; p3+=dir;
}
void semicircle::move(Vec dir){
    setAnchor(getAnchor()+dir);
    p1+=dir; p2+=dir;
}
void line::move(Vec dir){
    setAnchor(getAnchor()+dir);
    p1+=dir; p2+=dir;
}
void rectangle::move(Vec dir){
    setAnchor(getAnchor()+dir);
    p1+=dir; p2+=dir; p3+=dir; p4+=dir;
}
void trapezium::move(Vec dir){
    setAnchor(getAnchor()+dir);
    p1+=dir; p2+=dir; p3+=dir; p4+=dir;
}

//rotate
void circle::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
}
void triangle::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    p1= getrota_anchor() + ((p1-getrota_anchor())<<(getangle())); p2= getrota_anchor() + ((p2-getrota_anchor())<<(getangle()));
    p3= getrota_anchor() + ((p3-getrota_anchor())<<(getangle()));
}
void rectangle::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    p1= getrota_anchor() + ((p1-getrota_anchor())<<(getangle())); p2= getrota_anchor() + ((p2-getrota_anchor())<<(getangle()));
    p3= getrota_anchor() + ((p3-getrota_anchor())<<(getangle())); p4= getrota_anchor() + ((p4-getrota_anchor())<<(getangle()));
}
void trapezium::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    p1= getrota_anchor() + ((p1-getrota_anchor())<<(getangle())); p2= getrota_anchor() + ((p2-getrota_anchor())<<(getangle()));
    p3= getrota_anchor() + ((p3-getrota_anchor())<<(getangle())); p4= getrota_anchor() + ((p4-getrota_anchor())<<(getangle()));
}
void semicircle::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    p1= getrota_anchor() + ((p1-getrota_anchor())<<(getangle())); p2= getrota_anchor() + ((p2-getrota_anchor())<<(getangle()));
}
void line::rotate(Vec r_anchor,float angle){
    setrota_anchor(r_anchor); setangle(angle);
    setAnchor(getrota_anchor() + ((getAnchor()-getrota_anchor())<<angle));
    p1= getrota_anchor() + ((p1-getrota_anchor())<<(getangle())); p2= getrota_anchor() + ((p2-getrota_anchor())<<(getangle()));
}

// zoom
void circle::zoom(float k,Vec general_an){ ra*=k; setAnchor(general_an+(getAnchor()-general_an)*k); }
void triangle::zoom(float k,Vec general_an){
    setAnchor(general_an+(getAnchor()-general_an)*k);
    p1=general_an+(p1-general_an)*k; p2=general_an+(p2-general_an)*k; p3=general_an+(p3-general_an)*k;
}
void semicircle::zoom(float k,Vec general_an){
    setAnchor(general_an+(getAnchor()-general_an)*k);
    p1=general_an+(p1-general_an)*k; p2=general_an+(p2-general_an)*k;
}
void line::zoom(float k,Vec general_an){
    setAnchor(general_an+(getAnchor()-general_an)*k);
    p1=general_an+(p1-general_an)*k; p2=general_an+(p2-general_an)*k;
}
void rectangle::zoom(float k,Vec general_an){
    setAnchor(general_an+(getAnchor()-general_an)*k);
    p1=general_an+(p1-general_an)*k; p2=general_an+(p2-general_an)*k;
    p3=general_an+(p3-general_an)*k; p4=general_an+(p4-general_an)*k;
}
void trapezium::zoom(float k,Vec general_an){
    setAnchor(general_an+(getAnchor()-general_an)*k);
    p1=general_an+(p1-general_an)*k; p2=general_an+(p2-general_an)*k;
    p3=general_an+(p3-general_an)*k; p4=general_an+(p4-general_an)*k;
}
