#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PHASE (2)

/***** Phase 1 *****{{ */
#if PHASE >= 1

typedef struct _L7Point2D
{
    double m_x;
    double m_y;
}_L7Point2D;

void CTOR_L7Point2D_DOUBLE_DOUBLE(_L7Point2D* _this, double _x, double _y)
{
    _this->m_x = _x;
    _this->m_y = _y;
}

void CTOR_L7Point2D(_L7Point2D* _this)
{
    _this->m_x = 0;
    _this->m_y = 0;
}

void DTOR_L7Point2D(_L7Point2D* _this)
{

}

/*double GetX(const Point2D _point)*/
/*{*/
/*    return _point.m_x;*/
/*}*/

/*double GetY(const Point2D _point)*/
/*{*/
/*    return _point.m_y;*/
/*}*/

double _L7Point2D_Distance_CONST_Point2d_REF(const _L7Point2D* _this, const _L7Point2D* _other)
{
    double dx, dy;
    dx = _this->m_x - _other->m_x;
    dy = _this->m_y - _other->m_y;
    
    return sqrt(dx * dx + dy * dy);
}

void _L7Point2D_OPERATORT_CONST_Point2d_REF(_L7Point2D* _this ,const _L7Point2D* _second)
{
    _this->m_x += _second->m_x;
    _this->m_y += _second->m_y;
}

void _L7Point2D_OPERATORX_CONST_Point2d_REF(_L7Point2D* _this, double _factor)
{
    _this->m_x *= _factor;
    _this->m_y *= _factor;
}

void _GNS_Pointless()
{
    _L7Point2D p0, p1, dxy;
    
    CTOR_L7Point2D(&p0);
    CTOR_L7Point2D_DOUBLE_DOUBLE(&p1, 0, 10);
    
    printf("distance p0 --> p1 == %f\n", _L7Point2D_Distance_CONST_Point2d_REF(&p0, &p1));
    
    CTOR_L7Point2D_DOUBLE_DOUBLE(&dxy, 4, -7);    
    _L7Point2D_OPERATORT_CONST_Point2d_REF(&p1, &dxy);
    
    printf("%f, %f\n", p1.m_x, p1.m_y);
	printf("now distance p0 --> p1 == %f\n", _L7Point2D_Distance_CONST_Point2d_REF(&p0, &p1));
	
	DTOR_L7Point2D(&p0);
	DTOR_L7Point2D(&p1);
}

#endif

/* }} ***** Phase 1 *****/


/*----------------------------------------------------------------*/
/***** Phase 2 *****{{ */
/*#if PHASE >= 2*/

/*class NamedPoint2D : public Point2D*/
/*{*/
/*public:*/
/*	NamedPoint2D(const char *_name = "origin");*/
/*	NamedPoint2D(double _x, double _y, const char *_name = "anonymous Point");*/
/*	NamedPoint2D(const Point2D& point, const char *_name = "anonymous Point");*/
/*	const char *GetName() const;*/

/*private:*/
/*	const char *m_name;	*/
/*};*/

typedef struct _L12NamedPoint2D
{
    _L7Point2D m_point;
    /*const*/ char* m_name;
}_L12NamedPoint2D;


/*NamedPoint2D::NamedPoint2D(const char *_name)*/
/*: m_name(_name)*/
/*{*/
/*}*/

/*void CTOR_L12NamedPoint2D_DFLT(_L12NamedPoint2D* _this)*/
/*{*/
/*    _this->m_point = CreateDef();*/
/*    */
/*    _this->m_name = malloc(sizeof(strlen("origin") + 1));*/
/*    strcpy(_this->m_name, "origin");*/
/*}*/


void CTOR_L12NamedPoint2D_CONST_CHAR_PTR(_L12NamedPoint2D* _this, const char *_name)
{
    CTOR_L7Point2D(&_this->m_point);
    
    if(_name)
    {
        _this->m_name = malloc(sizeof(strlen(_name) + 1));
        strcpy(_this->m_name, _name);
    }
    else
    {
        _this->m_name = malloc(sizeof(strlen("origin") + 1));
        strcpy(_this->m_name, "origin");
    }
}

/*NamedPoint2D::NamedPoint2D(double _x, double _y, const char *_name)*/
/*: m_name(_name), Point2D(_x, _y)*/
/*{*/
/*}*/

/*void CTOR_L12NamedPoint2D_DOUBLE_DOUBLE(_L12NamedPoint2D* _this, double _x, double _y)*/
/*{*/
/*    _this->m_point = CreateFromDs(_x, _y);*/
/*    */
/*    _this->m_name = malloc(sizeof(strlen("anonymous Point") + 1));*/
/*    strcpy(_this->m_name, "anonymous Point");*/
/*}*/

void CTOR_L12NamedPoint2D_DOUBLE_DOUBLE_CONST_CHAR_PTR(_L12NamedPoint2D* _this, double _x, double _y, const char *_name)
{
    CTOR_L7Point2D_DOUBLE_DOUBLE(&_this->m_point, _x, _y);
    
    if(_name)
    {
        _this->m_name = malloc(sizeof(strlen(_name) + 1));
        strcpy(_this->m_name, _name);
    }
    else
    {
        _this->m_name = malloc(sizeof(strlen("anonymous Point") + 1));
        strcpy(_this->m_name, "anonymous Point");
    }
}

/*NamedPoint2D::NamedPoint2D(const Point2D& _point, const char *_name)*/
/*: m_name(_name), Point2D(_point)*/
/*{*/
/*}*/

/*void CTOR_L12NamedPoint2D_CONST_Point2D_REF(_L12NamedPoint2D* _this, const Point2D* _point)*/
/*{*/
/*    _this->m_point = *_point;*/
/*    _this->m_name = malloc(sizeof(strlen("anonymous Point") + 1));*/
/*    strcpy(_this->m_name, "anonymous Point");*/
/*}*/

void CTOR_L12NamedPoint2D_CONST_Point2D_REF_CONST_CHAR_PTR(_L12NamedPoint2D* _this, const _L7Point2D* _point, const char *_name)
{
    _this->m_point = *_point;
    
    if(_name)
    {
        _this->m_name = malloc(sizeof(strlen(_name) + 1));
        strcpy(_this->m_name, _name);
    }
    else
    {
        _this->m_name = malloc(sizeof(strlen("anonymous Point") + 1));
        strcpy(_this->m_name, "anonymous Point");
    }
}

void DTOR_L12NamedPoint2D(_L12NamedPoint2D* _this)
{
    free(&_this->m_name);
}

/*const char *NamedPoint2D::GetName() const*/
/*{*/
/*	return m_name;*/
/*}*/

const char* const _L12NamedPoint2D_GetName(const _L12NamedPoint2D* _this)
{
    return _this->m_name;
}

/*class Rectangle*/
/*{*/
/*public:*/
/*	Rectangle(const Point2D& _a, const Point2D& _b, const char *_name = "anonymous Rectangle");*/

/*	const char *GetName() const;*/
/*	double CalcArea() const;*/

/*private:*/
/*	NamedPoint2D m_a;*/
/*	Point2D m_b;*/
/*	static const int s_curvature = 1;	*/
/*};*/

const int _L9Rectangle___s_curvature = 1;

typedef struct _L9Rectangle
{
    _L12NamedPoint2D m_a;
    _L7Point2D m_b;
}_L9Rectangle;


/*Rectangle::Rectangle(const Point2D& _a, const Point2D& _b, const char *_name)*/
/*: m_a(_a, _name), m_b(_b)*/
/*{*/
/*}*/

void CTOR_L9Rectangle_CONST_Point2D_REF__CONST_Point2D_REF__CONST_CHAR_PTR(const _L9Rectangle* _this, const _L7Point2D* _first ,const _L7Point2D* _second, const char* _name)
{
    if(!_first || !_second)
    {
        return;
    }
    
    CTOR_L12NamedPoint2D_CONST_Point2D_REF_CONST_CHAR_PTR((_L12NamedPoint2D*)&_this->m_a, _first, _name);
    ((_L9Rectangle*)_this)->m_b = *(_L7Point2D*)_second;
}

void DTOR_L9Rectangle(_L9Rectangle* _this)
{
    DTOR_L12NamedPoint2D(&_this->m_a);
}

/*void CTOR_L9Rectangle_CONST_Point2D_REF__CONST_Point2D_REF_(const _L9Rectangle* _this, const Point2D* _first ,const Point2D* _second)*/
/*{*/
/*    if(!_first || !_second)*/
/*    {*/
/*        return;*/
/*    }*/
/*    CTOR_L12NamedPoint2D_CONST_Point2D_REF_CONST_CHAR_PTR((_L12NamedPoint2D*)&_this->m_a, _first, NULL);*/
/*    ((_L9Rectangle*)_this)->m_b = *(Point2D*)_second;*/
/*}*/

/*const char *Rectangle::GetName() const*/
/*{*/
/*	return m_a.GetName();*/
/*}*/

const char* _L9Rectangle_GetName(const _L9Rectangle* _this)
{
    return _L12NamedPoint2D_GetName(&_this->m_a);
}


/*double Rectangle::CalcArea() const*/
/*{*/
/*	Point2D p1(m_a.GetX(), m_b.GetY());*/
/*	double sideA = m_a.Distance(p1);*/
/*	double sideB = m_a.Distance(Point2D(m_b.GetX(), m_a.GetY()));*/
/*	return sideA * sideB * s_curvature;*/
/*}*/


double _L9Rectangle_CalcArea(const _L9Rectangle* _this)
{
    double sA, sB;
    _L7Point2D point1, point2;
    
    CTOR_L7Point2D_DOUBLE_DOUBLE(&point1, _this->m_a.m_point.m_x, _this->m_b.m_y);
    CTOR_L7Point2D_DOUBLE_DOUBLE(&point2, _this->m_b.m_x, _this->m_a.m_point.m_y);
    sA = _L7Point2D_Distance_CONST_Point2d_REF(&_this->m_a.m_point, &point1);
    sB = _L7Point2D_Distance_CONST_Point2d_REF(&_this->m_a.m_point, &point2);
    
    DTOR_L7Point2D(&point1);
    DTOR_L7Point2D(&point2);
    
    return sA * sB * _L9Rectangle___s_curvature;
}


/*void dog()*/
/*{*/
/*	NamedPoint2D home(5,7, "home");*/
/*	Point2D point(home);*/
/*	NamedPoint2D dog(point);*/

/*	dog *= 2;*/
/*	printf("Distance from %s to %s is %f\n", home.GetName(), dog.GetName(), home.Distance(dog));*/
/*}*/

void _GNS_dog()
{
    _L12NamedPoint2D home, dog;
    _L7Point2D point;
    
    CTOR_L12NamedPoint2D_DOUBLE_DOUBLE_CONST_CHAR_PTR(&home, 5, 7, "home");
    CTOR_L7Point2D_DOUBLE_DOUBLE(&point, home.m_point.m_x, home.m_point.m_y);
    CTOR_L12NamedPoint2D_CONST_Point2D_REF_CONST_CHAR_PTR(&dog, &point, NULL); 
    
    _L7Point2D_OPERATORX_CONST_Point2d_REF(&dog.m_point, 2);
    
    printf("Distance from %s to %s is %f\n", _L12NamedPoint2D_GetName((_L12NamedPoint2D*)&home), _L12NamedPoint2D_GetName((_L12NamedPoint2D*)&dog), _L7Point2D_Distance_CONST_Point2d_REF((const _L7Point2D*)&home.m_point, (const _L7Point2D*)&dog.m_point));
    
/*    DTOR_L7Point2D(&point);*/
/*    DTOR_L12NamedPoint2D(&home);*/
/*    DTOR_L12NamedPoint2D(&dog);*/
}

/*void area()*/
/*{*/
/*	Point2D p0;*/
/*	Point2D p1(12,12);*/
/*	Rectangle r(p0, p1);*/
/*	*/
/*  printf("The area of %s is %f\n", r.GetName(), r.CalcArea());*/
/*	printf("rectangle size %zu", sizeof(r));*/
/*}*/

void _GNS_area()
{
    _L7Point2D p0, p1;
    _L9Rectangle r;
    
    
    CTOR_L7Point2D(&p0);
    CTOR_L7Point2D_DOUBLE_DOUBLE(&p1, 12, 12);
    
    CTOR_L9Rectangle_CONST_Point2D_REF__CONST_Point2D_REF__CONST_CHAR_PTR(&r, &p0, &p1, NULL);
	printf("The area of %s is %f\n", _L9Rectangle_GetName(&r), _L9Rectangle_CalcArea(&r));
	printf("rectangle size %u\n", sizeof(r));
	
/*	DTOR_L9Rectangle(&r);*/
/*	DTOR_L7Point2D(&p1);*/
/*	DTOR_L7Point2D(&p0);*/
}



/*#endif*/
/*/* }} ***** Phase 2 **** */

/*/*----------------------------------------------------------------*/

int main()
{
/*	_L7Point2D p0, p1;*/
/*	_L9Rectangle r1;*/
#if PHASE >= 1
	_GNS_Pointless();
#endif

#if PHASE >= 2
	_GNS_dog();
	_GNS_area();
#endif
	
/*	CTOR_L7Point2D(&p0);*/
/*	CTOR_L7Point2D_DOUBLE_DOUBLE(&p1, 12, 12);*/
/*	*/
/*	CTOR_L9Rectangle_CONST_Point2D_REF__CONST_Point2D_REF__CONST_CHAR_PTR(&r1, &p0, &p1, NULL);*/
/*	*/
/*	printf("rectangle area is: %f\n", _L9Rectangle_CalcArea(&r1));*/

	return 0;
}
















