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

// Car
Car::Car(Vec an, float _l, float _w, bool dir, float _angle, Vec _rota_an): Vehicle(VehicleType::Car){
    l=_l; w=_w; d=dir; 
    setAnchor(an); setangle(_angle); setrota_anchor(_rota_an); setk(1.0f);
    float r=0.0; float g=0.0; float b=0.0;
    
    // roof
    Vec p1(getAnchor().getX()-l/4,getAnchor().getY()); Vec p2(getAnchor().getX()+l/4,getAnchor().getY());
    Vec p3(getAnchor().getX()+l/8,getAnchor().getY()+w); Vec p4(getAnchor().getX()-l/8,getAnchor().getY()+w);
    p1= getAnchor() + ((p1-getAnchor())<<(getangle())); p2= getAnchor() + ((p2-getAnchor())<<(getangle()));
    p3= getAnchor() + ((p3-getAnchor())<<(getangle())); p4= getAnchor() + ((p4-getAnchor())<<(getangle()));
    Vec tempa((((p1+p2)/2.0f+(p3+p4)/2.0f)/2.0f).getX(),(((p1+p2)/2.0f+(p3+p4)/2.0f)/2.0f).getY());
    r=0.0f; g=1.0f; b=1.0f; ColoredFig* temptr=new trapezium(tempa,p1,p2,p3,p4,r,g,b); addsh(temptr);

    // body
    Vec p5(getAnchor().getX()-l/2,getAnchor().getY()-w); Vec p6(getAnchor().getX()+l/2,getAnchor().getY()-w);
    Vec p7(getAnchor().getX()+l/2,getAnchor().getY()); Vec p8(getAnchor().getX()-l/2,getAnchor().getY());
    p5= getAnchor() + ((p5-getAnchor())<<(getangle())); p6= getAnchor() + ((p6-getAnchor())<<(getangle()));
    p7= getAnchor() + ((p7-getAnchor())<<(getangle())); p8= getAnchor() + ((p8-getAnchor())<<(getangle()));
    tempa=(((p5+p6)/2.0f+(p7+p8)/2.0f)/2.0f);
    r=1.0f; g=1.0f; b=0.0f; temptr=new rectangle(tempa,p5,p6,p7,p8,r,g,b); addsh(temptr);

    // wheels
    float ra=w/3.0f;
    Vec c1(getAnchor().getX()-l/4,getAnchor().getY()-w); Vec c2(getAnchor().getX()+l/4,getAnchor().getY()-w);
    c1= getAnchor() + ((c1-getAnchor())<<(getangle())); c2= getAnchor() + ((c2-getAnchor())<<(getangle()));
    r=1.0f,g=0.0f,b=0.0f; temptr=new circle(c1,ra,r,g,b); addsh(temptr); temptr=new circle(c2,ra,r,g,b); addsh(temptr);
}
Car::~Car(){ deletesh(); }


//UFO 
UFO::UFO(Vec an, float _ra, bool dir, float _angle, Vec _rota_an): Vehicle(VehicleType::UFO){
    d=dir; ra=_ra; 
    setAnchor(an); setangle(_angle); setrota_anchor(_rota_an); setk(1.0f);
    float r=0.0; float g=0.0; float b=0.0;

    // antenna
    Vec p1((float)(getAnchor().getX()+ra*cos(PI/4.0f)),(float)(getAnchor().getY()+ra*sin(PI/4.0f)));
    Vec p2((float)(getAnchor().getX()+1.5*ra*cos(PI/4.0f)),(float)(getAnchor().getY()+1.5*ra*sin(PI/4.0f)));
    p1= getAnchor() + ((p1-getAnchor())<<(getangle())); p2= getAnchor() + ((p2-getAnchor())<<(getangle()));
    Vec tempa=p1/0.2f + p2/0.2f;
    r=1.0f; g=0.0f; b=0.0f; ColoredFig* temptr=new line(tempa,p1,p2,r,g,b); addsh(temptr);
    Vec p3((float)(getAnchor().getX()+ra*cos(PI*3.0/4.0)),(float)(getAnchor().getY()+ra*sin(PI*3.0/4.0)));
    Vec p4((float)(getAnchor().getX()+1.5*ra*cos(PI*3.0/4.0)),(float)(getAnchor().getY()+1.5*ra*sin(3.0*PI/4.0)));
    p3= getAnchor() + ((p3-getAnchor())<<(getangle())); p4= getAnchor() + ((p4-getAnchor())<<(getangle()));
    tempa=p3/0.2f + p4/0.2f;
    r=1.0f; g=0.0f; b=0.0f; temptr=new line(tempa,p3,p4,r,g,b); addsh(temptr);
    
    // foot
    Vec p5(getAnchor().getX()-ra*7.0f/8.0f,getAnchor().getY()-ra/4.0f); Vec p6(getAnchor().getX()-ra/8.0f,getAnchor().getY()-ra/4.0f);
    Vec p7(getAnchor().getX()-ra/4.0f,getAnchor().getY()); Vec p8(getAnchor().getX()-ra*3.0f/4.0f,getAnchor().getY());
    p5= getAnchor() + ((p5-getAnchor())<<(getangle())); p6= getAnchor() + ((p6-getAnchor())<<(getangle()));
    p7= getAnchor() + ((p7-getAnchor())<<(getangle())); p8= getAnchor() + ((p8-getAnchor())<<(getangle()));
    tempa=p5/4.0f+p6/4.0f+p7/4.0f+p8/4.0f;
    r=1.0f; g=1.0f; b=0.0f; temptr=new trapezium(tempa,p5,p6,p7,p8,r,g,b); addsh(temptr);
    Vec p9(getAnchor().getX()+ra/8.0f,getAnchor().getY()-ra/4.0f); Vec p10(getAnchor().getX()+ra*7.0f/8.0f,getAnchor().getY()-ra/4.0f);
    Vec p11(getAnchor().getX()+ra*3.0f/4.0f,getAnchor().getY()); Vec p12(getAnchor().getX()+ra/4.0f,getAnchor().getY());
    p9= getAnchor() + ((p9-getAnchor())<<(getangle())); p10= getAnchor() + ((p10-getAnchor())<<(getangle()));
    p11= getAnchor() + ((p11-getAnchor())<<(getangle())); p12= getAnchor() + ((p12-getAnchor())<<(getangle()));
    tempa=p9/4.0f+p10/4.0f+p11/4.0f+p12/4.0f;
    r=1.0f; g=1.0f; b=0.0f; temptr=new trapezium(tempa,p9,p10,p11,p12,r,g,b); addsh(temptr);

    // head
    Vec p111(getAnchor().getX()-ra,getAnchor().getY()); Vec p222(getAnchor().getX()+ra,getAnchor().getY());
    p111= getAnchor() + ((p111-getAnchor())<<(getangle())); p222= getAnchor() + ((p222-getAnchor())<<(getangle()));
    tempa=p111/2.0f + p222/2.0f;
    r=0.517f; g=0.439f; b=1.0f; temptr=new semicircle(tempa,p111,p222,r,g,b); addsh(temptr);
}
UFO::~UFO(){ deletesh(); }


// Spacecraft
Spacecraft::Spacecraft(Vec an, float _l, float _w, bool dir, float _angle, Vec _rota_an): Vehicle(VehicleType::Spacecraft){
    l=_l; w=_w; d=dir; 
    setAnchor(an); setangle(_angle); setrota_anchor(_rota_an); setk(1.0f);
    float r=0.0; float g=0.0; float b=0.0;

    // wings
    Vec p1(getAnchor().getX()-w*5.0f/6.0f,getAnchor().getY()-l*7.0f/12.0f); Vec p2(getAnchor().getX()+w*5.0f/6.0f,getAnchor().getY()-l*7.0f/12.0f);
    Vec p3(getAnchor().getX()+w*1.0f/2.0f,getAnchor().getY()-l/6.0f); Vec p4(getAnchor().getX()-w*1.0f/2.0f,getAnchor().getY()-l/6.0f);
    p1= getAnchor() + ((p1-getAnchor())<<(getangle())); p2= getAnchor() + ((p2-getAnchor())<<(getangle()));
    p3= getAnchor() + ((p3-getAnchor())<<(getangle())); p4= getAnchor() + ((p4-getAnchor())<<(getangle()));
    Vec tempa((((p1+p2)/2.0f+(p3+p4)/2.0f)/2.0f).getX(),(((p1+p2)/2.0f+(p3+p4)/2.0f)/2.0f).getY());
    r=1.0f; g=0.647f; b=0.0f; ColoredFig* temptr=new trapezium(tempa,p1,p2,p3,p4,r,g,b); addsh(temptr);

    // tail
    Vec p11(getAnchor().getX()-w/3.0f,getAnchor().getY()-l*9.0f/12.0f); Vec p22(getAnchor().getX()+w/3.0f,getAnchor().getY()-l*9.0f/12.0f);
    Vec p33(getAnchor().getX()+w/3.0f/2.0f,getAnchor().getY()-l*7.0f/12.0f); Vec p44(getAnchor().getX()-w/3.0f/2.0f,getAnchor().getY()-l*7.0f/12.0f);
    p11= getAnchor() + ((p11-getAnchor())<<(getangle())); p22= getAnchor() + ((p22-getAnchor())<<(getangle()));
    p33= getAnchor() + ((p33-getAnchor())<<(getangle())); p44= getAnchor() + ((p44-getAnchor())<<(getangle()));
    tempa=p11/4.0f+p22/4.0f+p33/4.0f+p44/4.0f;;
    r=1.0f; g=0.0f; b=0.0f; temptr=new trapezium(tempa,p11,p22,p33,p44,r,g,b); addsh(temptr);

    // hat
    Vec p5(getAnchor().getX()-w/2.0f,getAnchor().getY()+l*5.0f/12.0f); Vec p6(getAnchor().getX(),getAnchor().getY()+l*3.0f/4.0f);
    Vec p7(getAnchor().getX()+w/2.0f,getAnchor().getY()+l*5.0f/12.0f);
    p5= getAnchor() + ((p5-getAnchor())<<(getangle())); p6= getAnchor() + ((p6-getAnchor())<<(getangle()));
    p7= getAnchor() + ((p7-getAnchor())<<(getangle()));
    tempa=p5/3.0f+p6/3.0f+p7/3.0f;
    r=0.19f; g=0.80f; b=0.196f; temptr=new triangle(tempa,p5,p6,p7,r,g,b); addsh(temptr);
 
    //body
    Vec p8(getAnchor().getX()-w/2.0f,getAnchor().getY()-l*7.0f/12.0f); Vec p9(getAnchor().getX()+w/2.0f,getAnchor().getY()-l*7.0f/12.0f);
    p8= getAnchor() + ((p8-getAnchor())<<(getangle())); p9= getAnchor() + ((p9-getAnchor())<<(getangle()));
    tempa=p5/4.0f+p6/4.0f+p8/4.0f+p9/4.0f;
    r=1.0f; g=1.0f; b=0.0f; temptr=new rectangle(tempa,p8,p9,p7,p5,r,g,b); addsh(temptr);

    // mouse
    Vec pp1(getAnchor().getX()-w/3.0f/2.0f,getAnchor().getY()-l/12.0f); Vec pp2(getAnchor().getX()+w/3.0f/2.0f,getAnchor().getY()-l/12.0f);
    Vec pp3(getAnchor().getX()+w/3.0f/2.0f,getAnchor().getY()+l/12.0f); Vec pp4(getAnchor().getX()-w/3.0f/2.0f,getAnchor().getY()+l/12.0f);
    pp1= getAnchor() + ((pp1-getAnchor())<<(getangle())); pp2= getAnchor() + ((pp2-getAnchor())<<(getangle()));
    pp3= getAnchor() + ((pp3-getAnchor())<<(getangle())); pp4= getAnchor() + ((pp4-getAnchor())<<(getangle()));
    tempa=pp1/4.0f+pp2/4.0f+pp3/4.0f+pp4/4.0f;
    r=0.0f; g=1.0f; b=1.0f; temptr=new rectangle(tempa,pp1,pp2,pp3,pp4,r,g,b); addsh(temptr);

    //windows
    Vec pp5(getAnchor().getX()-w/4.0f,getAnchor().getY()+l/3.0f); Vec pp6(getAnchor().getX()-w*5.0f/12.0f,getAnchor().getY()+l/3.0f);
    Vec pp7(getAnchor().getX()-w*5.0f/12.0f,getAnchor().getY()+l/12.0f); Vec pp8(getAnchor().getX()-w/4.0f,getAnchor().getY()+l/12.0f);
    pp5= getAnchor() + ((pp5-getAnchor())<<(getangle())); pp6= getAnchor() + ((pp6-getAnchor())<<(getangle()));
    pp7= getAnchor() + ((pp7-getAnchor())<<(getangle())); pp8= getAnchor() + ((pp8-getAnchor())<<(getangle()));
    tempa=pp5/4.0f+pp6/4.0f+pp7/4.0f+pp8/4.0f;
    r=1.0f; g=0.0f; b=1.0f; temptr=new rectangle(tempa,pp5,pp6,pp7,pp8,r,g,b); addsh(temptr);
    Vec ppp1(getAnchor().getX()+w/4.0f,getAnchor().getY()+l/3.0f); Vec ppp2(getAnchor().getX()+w*5.0f/12.0f,getAnchor().getY()+l/3.0f);
    Vec ppp3(getAnchor().getX()+w*5.0f/12.0f,getAnchor().getY()+l/12.0f); Vec ppp4(getAnchor().getX()+w/4.0f,getAnchor().getY()+l/12.0f);
    ppp1= getAnchor() + ((ppp1-getAnchor())<<(getangle())); ppp2= getAnchor() + ((ppp2-getAnchor())<<(getangle()));
    ppp3= getAnchor() + ((ppp3-getAnchor())<<(getangle())); ppp4= getAnchor() + ((ppp4-getAnchor())<<(getangle()));
    tempa=ppp1/4.0f+ppp2/4.0f+ppp3/4.0f+ppp4/4.0f;
    r=1.0f; g=0.0f; b=1.0f; temptr=new rectangle(tempa,ppp1,ppp2,ppp3,ppp4,r,g,b); addsh(temptr);
}
Spacecraft::~Spacecraft(){ deletesh(); }


// teleporter
Teleporter::Teleporter(Vec an, float _l, float _w): Vehicle(VehicleType::Teleporter){
    l=_l; w=_w; 
    setAnchor(an);  setk(1.0f);
    srand((unsigned)time(NULL));
    float r=(float)rand()/(float)RAND_MAX;
    float g=(float)rand()/(float)RAND_MAX;
    float b=(float)rand()/(float)RAND_MAX;
    Vec p1(getAnchor().getX()-w/2.0f,getAnchor().getY()-l/2.0f); Vec p2(getAnchor().getX()+w/2.0f,getAnchor().getY()-l/2.0f);
    Vec p3(getAnchor().getX()+w/2.0f,getAnchor().getY()+l/2.0f); Vec p4(getAnchor().getX()-w/2.0f,getAnchor().getY()+l/2.0f);
    ColoredFig* temptr=new rectangle(getAnchor(),p1,p2,p3,p4,r,g,b); addsh(temptr);
}
Teleporter::~Teleporter(){ deletesh(); }
/*
Teleporter::Teleporter(const Teleporter& other) : Vehicle(other) {
    l = other.l;
    w = other.w;
    sh = new rectangle(*other.sh);
}

Teleporter& Teleporter::operator=(const Teleporter& other) {
    if (this == &other) return *this;
    Vehicle::operator=(other);
    l = other.l;
    w = other.w;
    delete sh;
    sh = new rectangle(*other.sh);
    return *this;
}
*/

