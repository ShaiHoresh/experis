/*#include <cstdio>*/
#include <stdio.h>
#include <stdlib.h>


typedef void(*Funcs)(void*);

/*struct Color {*/
/*    enum ColorEnum { RED, GREEN, DEFAULT };*/
/*    static void setColor(ColorEnum color){        */
/*        static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };*/
/*        std::puts(pallete[color]);*/
/*    }*/
/*};*/

typedef enum ColorEnum
{
    RED = 0,
    GREEN,
    DEFAULT
} ColorEnum;


typedef struct _G5_Color
{
/*    Funcs** m_funcs;*/
    ColorEnum m_color;
}_G5_Color;

const char* _G5_Color_7Pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };

void _G5_Color_8setColor_9ColorEnum(ColorEnum _color)
{
    puts(_G5_Color_7Pallete[_color]);
}
/***********************************************************************/
/*class Scaleable {*/
/*public:*/
/*    virtual ~Scaleable() { }    */
/*    virtual void scale(double) = 0;*/
/*};*/

typedef struct _N9Scaleable
{
    void(*(*m_table))();
} _N9Scaleable;

/*    virtual ~Scaleable() { }    */
void _N9Scaleable_DTOR(_N9Scaleable* const _this)
{}

/*    virtual void scale(double) = 0;*/
void _N9Scaleable_N5Scale_DOUBLE(_N9Scaleable* const _this, double _f)
{
    printf("Shape::scale(%f)\n", _f);
}

void(*_N9Scaleable_6vTable[])(void) = {(void(*)(void))_N9Scaleable_DTOR, (void(*)(void))_N9Scaleable_N5Scale_DOUBLE};

void _N9Scaleable_CTOR(_N9Scaleable* const _this)
{
    _this->m_table = _N9Scaleable_6vTable;
}

/***********************************************************************/
/*class Shape : public Scaleable {*/
/*public:*/
/*    Shape() : m_id(++NumOfShapes)*/
/*    ~Shape()*/
/*    Shape(const Shape& other) : m_id(++NumOfShapes) */
/*    virtual void draw() const*/
/*    virtual void draw(Color::ColorEnum c) const*/
/*    virtual void scale(double f = 1) */
/*    virtual double area() const { return -1; }*/
/*    static void printInventory() */
/*private:*/
/*    static int NumOfShapes;*/
/*    Shape& operator=(const Shape &); // disabled, no implementation provided*/

/*protected:*/
/*     int m_id;*/
/*};*/

/*int Shape::NumOfShapes = 0;*/
int _N5Shape_11NumOfShapes = 0;

typedef struct _N5Shape
{
/*    Funcs** m_table;*/
    _N9Scaleable m_base;
    int m_id;
}_N5Shape;

void _N5Shape_CTOR(_N5Shape* const _this)
{
    _N9Scaleable_CTOR(&_this->m_base);
/*    _this->m_table = _N9Scaleable_6vTable;*/
    _this->m_id = ++_N5Shape_11NumOfShapes;
    printf("Shape::Shape() - %d\n", _this->m_id);
}

void _N5Shape_CTOR_5CONST_N5Shape_3REF(_N5Shape* const _this, const _N5Shape* const _other)
{
    _N9Scaleable_CTOR(&_this->m_base);
/*    _this->m_base = _other->m_base;*/
    _this->m_id = ++_N5Shape_11NumOfShapes;
    printf("Shape::Shape(Shape&) - %d from - %d\n", _this->m_id, _other->m_id);
}

void _N5Shape_N4draw_4void_E5const(_N5Shape* const _this)
{
    printf("Shape::draw() - %d\n", _this->m_id);
}

void _N5Shape_DTOR(_N5Shape* const _this)
{
    --_N5Shape_11NumOfShapes;
    _N5Shape_N4draw_4void_E5const(_this);
    _N9Scaleable_DTOR(&_this->m_base);
    printf("Shape::~Shape - %d\n", _this->m_id);
}

void _N5Shape_N4draw__9ColorEnum_E5const(_N5Shape* const _this, ColorEnum _color)
{
    printf("Shape::draw(c) - %d\n", _this->m_id);
    _G5_Color_8setColor_9ColorEnum(_color);
    _N5Shape_N4draw_4void_E5const(_this);
    _G5_Color_8setColor_9ColorEnum(DEFAULT);
}

void _N5Shape_N5scale_6double(_N5Shape* const _this, double f)
{
    printf("Shape::scale(%f)\n", f);
}

double _N5Shape_N4area_4void_E5const()
{
    return -1;
}

void _G14printInventory() 
{
    printf("Shape::printInventory - %d\n", _N5Shape_11NumOfShapes);
}

void(*_N5Shape_6vTable[])(void) = {(void(*)(void))_N5Shape_DTOR ,(void(*)(void))_N5Shape_N4draw_4void_E5const, (void(*)(void))_N5Shape_N4draw__9ColorEnum_E5const, (void(*)(void))_N5Shape_N5scale_6double, (void(*)(void))_N5Shape_N4area_4void_E5const};


/*class Circle : public Shape {    */
/*public:*/
/*    Circle() : m_radius(1)*/
/*    Circle(double r) : m_radius(r)*/
/*    Circle(const Circle& other)    : Shape(other), m_radius(other.m_radius) */
/*    ~Circle() */
/*    void draw() const*/
/*    void scale(double f = 2) */
/*    double area() const */
/*    double radius() const */
/*private:*/
/*    double m_radius;*/
/*};*/

typedef struct _N6Circle
{
    _N5Shape m_base;
    double m_radius;
}_N6Circle;

void _N6Circle_CTOR(_N6Circle* const _this);
void _N6Circle_CTOR_6DOUBLE(_N6Circle* const _this, double _r);
void _N6Circle_CTOR_5CONST_N6Circle_3REF(_N6Circle* const _this, _N6Circle* const _other);
void _N6Circle_DTOR(_N6Circle* const _this);
void _N6Circle_N4draw_4void_E5const(_N6Circle* const _this);
void _N6Circle_N5scale_6DOUBLE(_N6Circle* const _this, double _f);
double _N6Circle_N4area_E5const(_N6Circle* const _this);
double _N6Circle_N6radius_6DOUBLE(_N6Circle* const _this);


void(*_N6Circle_6vTable[])(void) = {(void(*)(void))_N6Circle_DTOR, (void(*)(void))_N6Circle_N4draw_4void_E5const, (void(*)(void))_N5Shape_N4draw__9ColorEnum_E5const, (void(*)(void))_N6Circle_N5scale_6DOUBLE, (void(*)(void))_N6Circle_N4area_E5const};


void _N6Circle_CTOR(_N6Circle* const _this)
{
    _N5Shape_CTOR(&_this->m_base);
    ((_N9Scaleable*)_this)->m_table = _N6Circle_6vTable;
    _this->m_radius = 1;
    printf("Circle::Circle() - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
} 

void _N6Circle_CTOR_6DOUBLE(_N6Circle* const _this, double _r)
{
    _N5Shape_CTOR(&_this->m_base);
    _this->m_radius = _r;
    ((_N9Scaleable*)_this)->m_table = _N6Circle_6vTable;
    printf("Circle::Circle(double) - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
} 

void _N6Circle_CTOR_5CONST_N6Circle_3REF(_N6Circle* const _this, _N6Circle* const _other)
{
    _N5Shape_CTOR_5CONST_N5Shape_3REF((_N5Shape* const)_this, (_N5Shape* const)_other);
    _this->m_radius = _other->m_radius;
    printf("Circle::Circle(Circle&) - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
}

void _N6Circle_DTOR(_N6Circle* const _this)
{
    printf("Circle::~Circle() - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
    _N5Shape_DTOR((_N5Shape*)_this);
}

void _N6Circle_N4draw_4void_E5const(_N6Circle* const _this)
{
    printf("Circle::draw()  - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
    
}

void _N6Circle_N5scale_6DOUBLE(_N6Circle* const _this, double _f)
{
    printf("Circle::scale(%f)\n", _f);
    _this->m_radius *= _f;
}

double _N6Circle_N4area_E5const(_N6Circle* const _this)
{
    return (_this->m_radius) * (_this->m_radius) * 3.1415;
}

double _N6Circle_N6radius_6DOUBLE(_N6Circle* const _this)
{
    printf("Circle::draw() - %d, r:%f\n", ((_N5Shape*)_this)->m_id, _this->m_radius); 
    return _this->m_radius;
}



/********************************************************************/

/*class Rectangle: public Shape */
/*{*/
/*public:*/
/*    Rectangle() : m_a(1), m_b(1)*/
/*    Rectangle(int a) : m_a(a), m_b(a)*/
/*    Rectangle(int a, int b) : m_a(a), m_b(b)*/
/*    Rectangle(const Rectangle &other ) */
/*    ~Rectangle()*/
/*    void draw() const*/
/*    void draw(Color::ColorEnum c) const */
/*    void scale(double f = 4)*/
/*    double area() const */
/*private:*/
/*    int m_a, m_b;*/
/*};*/

typedef struct _N9Rectangle
{
    _N5Shape m_base;
    int m_a;
    int m_b;
}_N9Rectangle;

void _N9Rectangle_CTOR(_N9Rectangle* const _this);
void _N9Rectangle_CTOR_3INT(_N9Rectangle* const _this, int _a);
void _N9Rectangle_CTOR_3INT_3INT(_N9Rectangle* const _this, int _a, int _b);
void _N9Rectangle_CTOR_5CONST_N9Rectangle_REF(_N9Rectangle* const _this, const _N9Rectangle* const _other);
void _N9Rectangle_DTOR();
void _N9Rectangle_N4draw_4void_E5const(_N9Rectangle* const _this);
void _N9Rectangle_N4draw__9ColorEnum_E5const(_N9Rectangle* const _this, ColorEnum _color);
void _N9Rectangle_N5scale_6DOUBLE(_N9Rectangle* const _this, double _f);
double _N9Rectangle_N4area_E5const(_N9Rectangle* const _this);


void(*_N9Rectangle_6vTable[])(void) = {(void(*)(void))_N9Rectangle_DTOR,(void(*)(void))_N9Rectangle_N4draw_4void_E5const, (void(*)(void))_N9Rectangle_N4draw__9ColorEnum_E5const, (void(*)(void))_N9Rectangle_N5scale_6DOUBLE, (void(*)(void))_N9Rectangle_N4area_E5const};


void _N9Rectangle_CTOR(_N9Rectangle* const _this)
{
    _N5Shape_CTOR(&_this->m_base);
    ((_N9Scaleable*)_this)->m_table = _N9Rectangle_6vTable;
    _this->m_a = 1;
    _this->m_b = 1;
    printf("Rectangle::Rectangle() - %d, [%d, %d]\n",
         ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_CTOR_3INT(_N9Rectangle* const _this, int _a)
{
    _N5Shape_CTOR(&_this->m_base);
    ((_N9Scaleable*)_this)->m_table = _N9Rectangle_6vTable;
    _this->m_a = _a;
    _this->m_b = _a;
    printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_CTOR_3INT_3INT(_N9Rectangle* const _this, int _a, int _b)
{
    _N5Shape_CTOR(&_this->m_base);
    ((_N9Scaleable*)_this)->m_table = _N9Rectangle_6vTable;
    _this->m_a = _a;
    _this->m_b = _b;
    printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_CTOR_5CONST_N9Rectangle_REF(_N9Rectangle* const _this, const _N9Rectangle* const _other)
{
    _N5Shape_CTOR(&_this->m_base);
    ((_N9Scaleable*)_this)->m_table = _N9Rectangle_6vTable;
    _this->m_a = _other->m_a;
    _this->m_b = _other->m_b;
    printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_DTOR(_N9Rectangle* const _this)
{
    printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
    _N5Shape_DTOR((_N5Shape*)_this);
}

void _N9Rectangle_N4draw_4void_E5const(_N9Rectangle* const _this)
{
    printf("Rectangle::draw()  - %d, [%d, %d]\n", ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_N4draw__9ColorEnum_E5const(_N9Rectangle* const _this, ColorEnum _color)
{
    printf("Rectangle::draw(%d) - %d, [%d, %d]\n", _color, ((_N5Shape*)_this)->m_id, _this->m_a, _this->m_b);
}

void _N9Rectangle_N5scale_6DOUBLE(_N9Rectangle* const _this, double _f)
{
    printf("Rectangle::scale(%f)\n", _f);
    _this->m_a *= _f;
    _this->m_b *= _f;
}

double _N9Rectangle_N4area_E5const(_N9Rectangle* const _this)
{
    return _this->m_a * _this->m_b;
}

/*******************************************************************/
/*void report(const Shape& s) {*/
/*    std::puts("-----report-----");*/
/*    s.draw(); */
/*    Shape::printInventory();*/
/*    std::puts("-----report-----");*/
/*}*/

void _G6_report_5CONST_5Shape_3REF(const _N5Shape* const _s)
{
    void(*Draw)(_N5Shape* const) = (void(*)(_N5Shape* const))((_N9Scaleable*)_s)->m_table[1];

    puts("-----report-----");
    
    Draw((_N5Shape*)_s);
    _G14printInventory();

    puts("-----report-----");
}


/*inline void draw(Shape& obj) { */
/*    std::puts("-----draw(Shape&)-----");*/
/*    obj.scale();*/
/*    obj.draw();    */
/*    std::puts("-----draw(Shape&)-----");*/
/*}*/

void _G4_draw_5CONST_5Shape_3REF(const _N5Shape* const _obj)
{
    void(*Scale)(_N5Shape* const, double) = (void(*)(_N5Shape* const, double))((_N9Scaleable*)_obj)->m_table[3];
    void(*Draw)(_N5Shape* const) = (void(*)(_N5Shape* const))((_N9Scaleable*)_obj)->m_table[1];

    puts("-----draw(Shape&)-----");
    
    Scale((_N5Shape* const)_obj, 1);
    Draw((_N5Shape* const)_obj);

    puts("-----draw(Shape&)-----");
}

/*void draw(Circle c) { */
/*    std::puts("-----draw(Circle)-----");*/

/*    static Circle unit(1);*/
/*    */
/*    unit.draw();*/
/*    unit.scale(3);*/
/*    c.draw(); */
/*    std::puts("-----draw(Circle)-----");*/
/*}*/

_N6Circle unit;
int unit_flag = 0;

void _G4_draw_5CONST_N6Circle(_N6Circle* _c)
{
    _N6Circle temp;
    _N6Circle_CTOR_5CONST_N6Circle_3REF(&temp, _c);
    puts("-----draw(Circle)-----");
    if(0 == unit_flag)
    {
        _N6Circle_CTOR_6DOUBLE(&unit, 1);
        unit_flag = 1;
    }
    _N6Circle_N4draw_4void_E5const(&unit);
    _N6Circle_N5scale_6DOUBLE(&unit, 3);
    _N6Circle_N4draw_4void_E5const(&temp);
    
    puts("-----draw(Circle)-----");
    _N6Circle_DTOR(&temp);
}

/*void doObjArray(){*/
/*    Shape objects[] = {*/
/*        Circle(),*/
/*        Rectangle(4),*/
/*        Circle(9)*/
/*    };*/

/*    for(int i = 0; i < 3; ++i) */
/*        objects[i].draw();*/
/*}*/

void _G10doObjArray()
{
    _N6Circle c1, c2;
    _N9Rectangle r;
    _N5Shape objects[3];
    int i;
    
    _N6Circle_CTOR(&c1);
    _N5Shape_CTOR_5CONST_N5Shape_3REF(&objects[0], (_N5Shape*)&c1);
    _N6Circle_DTOR(&c1);

    _N9Rectangle_CTOR_3INT(&r, 4);
    _N5Shape_CTOR_5CONST_N5Shape_3REF(&objects[1], (_N5Shape*)&r);
    _N9Rectangle_DTOR(&r);

    _N6Circle_CTOR_6DOUBLE(&c2, 9);
    _N5Shape_CTOR_5CONST_N5Shape_3REF(&objects[2], (_N5Shape*)&c2);
    _N6Circle_DTOR(&c2);
    
    
    for (i = 0; i < 3; ++i)
    {
        _N5Shape_N4draw_4void_E5const(&objects[i]);
    }

    for (i = 2; i >= 0; --i)
    {
        _N5Shape_DTOR(&objects[i]);
    }
    
/*    for(i = 0; i < 3; ++i)*/
/*    {*/
/*        void(*DTOR)(_N5Shape* const) = (void(*)(_N5Shape* const))((_N9Scaleable*)&objects[i])->m_table[0];*/
/*        DTOR(&objects[i]);*/
/*    }*/
}


/*void disappear() {*/
/*    std::puts("-----disappear-----");*/

/*    Circle defaultCircle();*/

/*    std::puts("-----disappear-----");*/
/*}*/

void _G9disappear()
{

    _N6Circle defaultCircle();

    puts("-----disappear-----");
    puts("-----disappear-----");
}

/*template <class T>*/
/*double diffWhenDoubled(T& shape){*/
/*    double a0 = shape.area();*/
/*    shape.scale(2);*/
/*    double a1 = shape.area();*/
/*    return a1 - a0;*/
/*}*/

double _G15diffWhenDoubled_N6Circle(const _N6Circle* const _c)
{
    double a0, a1;
    a0 = _N6Circle_N4area_E5const((_N6Circle* const)_c);
    _N6Circle_N5scale_6DOUBLE((_N6Circle* const)_c, 2);
    a1 = _N6Circle_N4area_E5const((_N6Circle* const)_c);
    
    return a1 - a0;
}

/*void doPointerArray(){*/
/*    std::puts("-----doPointerArray-----");*/
/*    Shape *array[] =  {*/
/*        new Circle(),*/
/*        new Rectangle(3),*/
/*        new Circle(4)*/
/*    };*/

/*    for(int i = 0; i < 3; ++i){ */
/*        array[i]->scale();*/
/*        array[i]->draw();*/
/*    }*/

/*    std::printf("area: %f\n", diffWhenDoubled(*array[2]));*/

/*    for(int i = 0; i < 3; ++i) { */
/*        delete array[i]; */
/*        array[i] = 0; */
/*    }*/

/*    std::puts("-----doPointerArray-----");*/
/*}*/

void _G14doPointerArray()
{
    _N5Shape *array[3];
    int i;
    _N6Circle *c1, *c2;
    _N9Rectangle *r;
    
    puts("-----doPointerArray-----");
    c1 = malloc(sizeof(_N6Circle));
    r = malloc(sizeof(_N9Rectangle));
    c2 = malloc(sizeof(_N6Circle));
    
    _N6Circle_CTOR(c1);
    _N9Rectangle_CTOR_3INT(r, 3);
    _N6Circle_CTOR_6DOUBLE(c2, 4);
    
    array[0] = (_N5Shape*)c1;
    array[1] = (_N5Shape*)r;
    array[2] = (_N5Shape*)c2;
    
    for(i = 0; i < 3; ++i)
    {
        void(*Scale)(_N5Shape* const, double) = (void(*)(_N5Shape* const, double))((_N9Scaleable*)array[i])->m_table[3];
        
        
        void(*Draw)(_N5Shape* const) = (void(*)(_N5Shape* const))((_N9Scaleable*)array[i])->m_table[1];
    
        Scale(array[i], 1);
        Draw(array[i]);
    }
    
    printf("area: %f\n", _G15diffWhenDoubled_N6Circle((_N6Circle*)array[2]));
    
    for(i = 0; i < 3; ++i)
    {
        void(*DTOR)(_N5Shape* const) = (void(*)(_N5Shape* const))((_N9Scaleable*)array[i])->m_table[0];
        DTOR(array[i]);
        free(array[i]);
        array[i] = 0;
    }
    
    puts("-----doPointerArray-----");
}


/*void dispose(Rectangle* p){*/
/*  delete[] p;*/
/*}*/

void _G7dispose(_N9Rectangle* _p, unsigned int _n)
{
    int i;
    for(i = _n - 1; i >= 0; --i)
    {
        _N9Rectangle_DTOR(&_p[i]);
    }
}

/*class Empty {*/
/*public:*/
/*    Empty(int id = 0) { std::printf("Empty::Empty(%d)\n", id); }*/
/*   ~Empty() { std::puts("Empty::~Empty()");}    */
/*};*/

typedef struct _N5Empty
{
    char m_dummy;
} _N5Empty;

void _N5Empty_CTOR_3INT(_N5Empty* const _this, int _id)
{
    printf("Empty::Empty(%d)\n", _id);
}

void _N5Empty_DTOR(_N5Empty* const _this)
{
    puts("Empty::~Empty()");
}

typedef struct _N10EmptyEmpty
{
/*    _N5Empty m_base;*/
    int m_i;
} _N10EmptyEmpty;

void _N10EmptyEmpty_CTOR_3INT(_N10EmptyEmpty* const _this, int _id)
{
    _this->m_i = _id;
    _N5Empty_CTOR_3INT((_N5Empty*)_this, 0);
    printf("EmptyEmpty::EmptyEmpty(%d)\n", _this->m_i); 
}

void _N10EmptyEmpty_DTOR(_N10EmptyEmpty* const _this)
{}

typedef struct _N8EmptyBag
{
    _N5Empty m_e1;
    _N5Empty m_e2;
    _N10EmptyEmpty m_ee;
} _N8EmptyBag;

void _N8EmptyBag_CTOR(_N8EmptyBag* const _this)
{
    _N5Empty_CTOR_3INT(&(_this->m_e1), 1);
    _N5Empty_CTOR_3INT(&(_this->m_e2), 2);
    _N10EmptyEmpty_CTOR_3INT(&(_this->m_ee), 2);
    puts("EmptyBag::EmptyBag()"); 
}

void _N8EmptyBag_DTOR(_N8EmptyBag* const _this)
{
    puts("EmptyBag::~EmptyBag"); 
    _N5Empty_DTOR((_N5Empty*)&_this->m_ee);
    _N5Empty_DTOR(&_this->m_e2);
    _N5Empty_DTOR(&_this->m_e1);
}

/*class EmptyEmpty  : public Empty{*/
/*    int m_i;*/

/*public:*/
/*    EmptyEmpty(int id) : m_i(id){*/
/*         std::printf("EmptyEmpty::EmptyEmpty(%d)\n", m_i); */
/*    }*/
/*};*/

/*class EmptyBag {*/
/*    Empty e1;*/
/*    Empty e2;*/
/*    EmptyEmpty ee;*/
/*public: */
/*    EmptyBag() : e2(2), e1(1), ee(2) {*/
/*        std::puts("EmptyBag::EmptyBag()");*/
/*    }*/
/*    ~EmptyBag(){*/
/*        std::puts("EmptyBag::~EmptyBag");*/
/*    }    */
/*};*/

int main(int argc, char **argv, char **envp)
{    
/*    Circle c;*/
    _N6Circle c, c2, olympics[5];
/*    Rectangle s(4);*/
    _N9Rectangle s;
    int i;
    _N9Rectangle* fourRectangles;
    _N8EmptyBag eb;
    
    printf("---------------Start----------------\n");
    _N6Circle_CTOR(&c);
    _N9Rectangle_CTOR_3INT(&s, 4);

    printf("0.-------------------------------\n");        
/*    draw(c);*/
    _G4_draw_5CONST_N6Circle(&c);
/*    _G4_draw_5CONST_5Shape_3REF((_N5Shape*)&c);*/

    printf("+..............\n");
    _G4_draw_5CONST_N6Circle(&c);
/*    _N6Circle_N4draw_4void_E5const(&c);*/

    printf("+..............\n");        
    _G4_draw_5CONST_5Shape_3REF((_N5Shape*)&s);
    
    printf("+..............\n");        
/*    report(c);*/
    _G6_report_5CONST_5Shape_3REF((const _N5Shape* const)&c);

    printf("1.-------------------------------\n");    
/*    */
/*    doPointerArray();*/
    _G14doPointerArray();

    printf("2.-------------------------------\n");

/*    doObjArray();*/
    _G10doObjArray();

    printf("3.-------------------------------\n");

/*    Shape::printInventory();*/
    _G14printInventory();
/*    Circle c2 = c;*/
    _N6Circle_CTOR_5CONST_N6Circle_3REF(&c2, &c);
/*    c2.printInventory();*/
    _G14printInventory();

    printf("4.-------------------------------\n");
/*   */
/*    Circle olympics[5];*/
    for (i = 0; i < 5; ++i)
    {
        _N6Circle_CTOR(&olympics[i]);
    }
/*    std::printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));*/
    printf("olympic diff %f\n", _G15diffWhenDoubled_N6Circle(&olympics[1]));

    printf("5.-------------------------------\n");

/*    Rectangle *fourRectangles = new Rectangle[4];*/
    fourRectangles = malloc(4 * sizeof(_N9Rectangle));
    for(i = 0; i < 4; ++i)
    {
        _N9Rectangle_CTOR(&fourRectangles[i]);
    }

/*    dispose(fourRectangles);*/
    _G7dispose(fourRectangles, 4);

    printf("6.-------------------------------\n");
/*    EmptyBag eb;*/
    
    _N8EmptyBag_CTOR(&eb);
    
/*    std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );*/
    printf("Empty things are: %u %u %u\n", sizeof(_N5Empty), sizeof(_N10EmptyEmpty), sizeof(_N8EmptyBag) );

/*    */
    printf("7.-------------------------------\n");
/*    disappear();    */
    _G9disappear();

    printf("---------------END----------------\n");
    
    _N8EmptyBag_DTOR(&eb);
    
    for (i = 4; i >= 0; --i)
    {
        _N6Circle_DTOR(&olympics[i]);
    }
    
    _N6Circle_DTOR(&c2);
    
    _N9Rectangle_DTOR(&s);
    
    _N6Circle_DTOR(&c);
    
    _N6Circle_DTOR(&unit);
    return 0;
}
