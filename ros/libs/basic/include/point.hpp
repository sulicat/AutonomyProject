#ifndef _POINT_H_
#define _POINT_H_

template<class T>
class Point{
public:
    T x;
    T y;

    Point() : Point(0,0){
    }

    Point(T _x, T _y){
	x = _x;
	y = _y;
    }
};

#endif
