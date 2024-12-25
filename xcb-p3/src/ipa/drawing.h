#ifndef DRAWING_H
#define DRAWING_H
#include <utility>
#include <vector>
#include "parkinglot.h"

class Figure {
    private:
        Vec anchor;
        float angle; // positive=counter clockwise; negative=clockwise
        float rota_angle; // angle of rotation
        Vec rota_anchor;  //anchor which a group performs a rotation on
    protected:
        void setAnchor(Vec a) {anchor = a;}
        void setangle(float _ang) {angle=_ang;}
        void setrota_angle(float r_ang) {rota_angle=r_ang;}
        void setrota_anchor(Vec r_a)  {rota_anchor=r_a;}
    public:
        Figure() : anchor(0, 0), angle(0), rota_angle(0),rota_anchor(0,0) {}
        Vec getAnchor() const {return anchor;}
        float getangle() const {return angle;}
        float getrota_angle() const {return rota_angle;}
        Vec getrota_anchor() const {return rota_anchor;}
        virtual void draw()= 0;
        virtual ~Figure() {}
};

class ColoredFig : public Figure {
    public:
        virtual ~ColoredFig();
        void draw() override=0;
        virtual void move(Vec dir)=0;
        virtual void rotate(Vec r_anchor,float angle)=0;
        virtual void zoom(float k,Vec general_an)=0;
};

class Group : public Figure {
    private:
        std::vector<ColoredFig*> sh;
        std::vector<ColoredFig*>::iterator it;
        float k;  // zoom size
    public:
        Group() { setangle(0.0f); setrota_anchor(Vec (0.0f,0.0f)); k=0;}
        ~Group() {}
        void addsh(ColoredFig* tmp) { sh.push_back(tmp); }
        void deletesh(void) { sh.clear(); }

        void setk(float _k){ k=_k; }
        float getk(){ return k; }

        void draw() override; // Draw out all its figures
        void move(Vec dir); // Move all its figures
        void rotate(Vec r_anchor,float angle); // Rotate the group as a whole.
        void zoom() ; // Zoom the group as a whole.
};


class circle: public ColoredFig {
    public:
        explicit circle(Vec an,float _ra,float _r,float _g,float _b)  { ra=_ra; r=_r; g=_g; b=_b; setAnchor(an); }
        void draw() override;
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
    private:
        float ra; float r,g,b;
};
class triangle: public ColoredFig {
    private:
        Vec p1, p2, p3;
        float r,g,b;
    public:
        explicit triangle(Vec an,Vec p11,Vec p22,Vec p33,float _r,float _g,float _b) :p1(p11),p2(p22),p3(p33) { setAnchor(an); r=_r; g=_g; b=_b; }
        void draw() override;
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
};
class semicircle: public ColoredFig {
    private:
        Vec p1, p2;
        float r,g,b;
    public:
        explicit semicircle(Vec an,Vec p11,Vec p22,float _r,float _g,float _b): p1(p11),p2(p22) { setAnchor(an); r=_r; g=_g; b=_b; }
        void draw() override;
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
};
class line: public ColoredFig {
    private:
        Vec p1, p2;
        float r,g,b;
    public:
        explicit line(Vec an,Vec p11,Vec p22,float _r,float _g,float _b): p1(p11),p2(p22) { setAnchor(an); r=_r; g=_g; b=_b; }
        void draw() override;
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
};
class rectangle: public ColoredFig {
    private:
        Vec p1,p2,p3,p4;
        float r,g,b;
    public:
        explicit rectangle(Vec an,Vec p11,Vec p22,Vec p33,Vec p44,float _r,float _g,float _b): p1(p11),p2(p22),p3(p33),p4(p44) { setAnchor(an); r=_r; g=_g; b=_b; }
        void draw() override;
        void paint();
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
};
class trapezium: public ColoredFig {
    private:
        Vec p1, p2, p3, p4;
        float r,g,b;
    public:
        explicit trapezium(Vec an,Vec p11,Vec p22,Vec p33,Vec p44,float _r,float _g,float _b): p1(p11),p2(p22),p3(p33),p4(p44) { setAnchor(an); r=_r; g=_g; b=_b;}
        void draw() override;
        void move(Vec dir) override;
        void rotate(Vec r_anchor,float angle) override;
        void zoom(float k,Vec general_an) override ;
};


class Car : public Vehicle, public Group {
    private:
        float l,w; bool d; // 0 for right, 1 for left
    public:
        explicit Car(Vec an, float _l, float _w, bool dir, float _angle, Vec _rota_an);
        void route(int timer, int start_time=0, int stop_time=50, int slot_number=0);
        ~Car();
};

class UFO : public Vehicle, public Group {
    private:
        float ra; bool d;
    public:
        explicit UFO(Vec an, float _ra, bool dir, float _angle, Vec _rota_an);
        void route(int timer, int start_time=0, int stop_time=50, int slot_number=0);
        ~UFO();
};

class Teleporter : public Vehicle, public  Group{
    private:
        float l,w;
    public:
        explicit Teleporter(Vec an, float l, float w);
        ~Teleporter();
};

class Spacecraft : public Vehicle, public Group {
    private:
        bool d; float l,w;
    public:
        explicit Spacecraft(Vec an, float _l, float _w, bool dir, float _angle, Vec _rota_an);
        void route(int timer, int start_time=0, int stop_time=50, int slot_number=0);
        ~Spacecraft();
};



#endif //DRAWING_H
