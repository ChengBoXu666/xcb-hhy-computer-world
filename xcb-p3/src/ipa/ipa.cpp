#include <unistd.h>
#ifdef __APPLE__
/* macos */
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
/* windows & linux */
#include <GL/freeglut.h>
#endif
#include <cstdlib>
#include  <iostream>
#include <vector>
#include "drawing.h"

#ifndef HEADLESS
void TimeStep(int n) {
	glutTimerFunc((unsigned int)n, TimeStep, n); glutPostRedisplay();
}

void glDraw(){
    static ParkingLot p;
    float d=(float)p.slotnum();
    
    int venum=rand()%(int)d+1;

    static std::vector<Vehicle*> ves;
    std::vector<Vehicle*>::iterator it;
    static bool in_for=1; static int timer=0;
    if(in_for==1&&p.available_slots()!=0){
        int tmp_d=0;
        for(int i=0;i<venum;i++){
            static Vec an(-0.9f,-1.0f);
            switch(rand()%4){
                case 0:{
                    Vehicle* tmp=new Car(an,0.17f,0.08f,0,0,Vec(0,0));
                    ves.push_back(tmp); p.park(tmp,tmp_d,rand()%100+50);
                    break;
                }
                case 1:{
                    Vehicle* tmp=new UFO(an,0.08f,0,0,Vec(0,0));
                    ves.push_back(tmp); p.park(tmp,tmp_d,rand()%100+50);
                    break;
                }
                case 2:{
                    Vehicle* tmp=new Spacecraft(an,.1f,.05f,0,0,Vec(0,0));
                    ves.push_back(tmp); p.park(tmp,tmp_d,rand()%100+50);
                    break;
                }
                case 3:{
                    Vehicle* tmp=new Teleporter(an,.15f,.1f);
                    ves.push_back(tmp); p.park(tmp,tmp_d,rand()%100+50);
                    float dm = 4.0f / (d + 3.0f);
                    if (((ves[i])->get_slot()).slot_number+1 > d / 2){
                        int lower_slot_number = (((ves[i])->get_slot()).slot_number+1) - d / 2;
                        Vec center = Vec(-1+1.5f*dm+(float)(lower_slot_number-1)*dm+dm/2.0f,-0.6f);
                        (static_cast<Teleporter*>(ves[i]))->move(center-(static_cast<Teleporter*>(ves[i]))->getAnchor());
                    }else{
                        int upper_slot_number = d/2-(((ves[i])->get_slot()).slot_number+1)+1;
                        Vec center = Vec(1-(float)(upper_slot_number-1)*dm-dm/2.0f,0.6f);
                        (static_cast<Teleporter*>(ves[i]))->move(center-(static_cast<Teleporter*>(ves[i]))->getAnchor());
                    }
                    break;
                }
            }
            tmp_d+=50;
        }
        in_for=0;
    }

    
    for(it=ves.begin();it!=ves.end();++it){
        if ((*it)->unpark()==0) continue;
        if((*it)->gettype()==VehicleType::Car) (static_cast<Car*>(*it))->route(timer,(*it)->get_draw_time(),(*it)->get_stop_time(),(*it)->unpark());
        else if((*it)->gettype()==VehicleType::UFO) (static_cast<UFO*>(*it))->route(timer,(*it)->get_draw_time(),(*it)->get_stop_time(),(*it)->unpark());
        else if((*it)->gettype()==VehicleType::Spacecraft) (static_cast<Spacecraft*>(*it))->route(timer,(*it)->get_draw_time(),(*it)->get_stop_time(),(*it)->unpark());
    }
    
    static float pole_switch1=1;
    static float pole_switch2=0;
    static Vec start1(-1.0f,0.8f);
    static Vec start2(-1.0f,-0.8f);
    
    static pole p1(start1,d);
    static pole p2(start2,d);
    p1.pole_move(&pole_switch1);
    p2.pole_move(&pole_switch2);
    glClear(GL_COLOR_BUFFER_BIT);

    p.draw();
    p2.pole_draw();
    p1.pole_draw();
    for(it=ves.begin();it!=ves.end();++it){
        if(timer>=(*it)->get_draw_time()){
            if((*it)->gettype()==VehicleType::Car) {
                (static_cast<Car*>(*it))->draw();
            } else if((*it)->gettype()==VehicleType::UFO) { 
                (static_cast<UFO*>(*it))->rotate((static_cast<UFO*>(*it))->getAnchor(),PI/10.0f);(static_cast<UFO*>(*it))->draw();
            } else if((*it)->gettype()==VehicleType::Spacecraft) {
                (static_cast<Spacecraft*>(*it))->zoom(); (static_cast<Spacecraft*>(*it))->draw();
            }          
        }
        if((*it)->gettype()==VehicleType::Teleporter) (static_cast<Teleporter*>(*it))->draw();
        if((*it)->gettype()!=VehicleType::Teleporter){
            if(timer==(*it)->get_draw_time()){
                pole_switch2=0; p2.pole_move(&pole_switch2);
            }
            if(timer==(*it)->get_stop_time()+(*it)->get_draw_time()+280){
                p.unpark(*it);
                pole_switch1=0; p1.pole_move(&pole_switch1);
            }  
        }     
    }   
    
    glutSwapBuffers();
    glFlush();
    timer++;
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
    srand((unsigned)time(NULL));
    glutDisplayFunc(glDraw);
    glutTimerFunc(50, TimeStep, 50);
    glutMainLoop();
    return 0;
}
#else
int main(){
    return 0;
}
#endif
