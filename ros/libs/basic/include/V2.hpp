#ifndef _V2_H_
#define _V2_H_

template<class T>
class V2{
public:
    T x;
    T y;

    V2() : V2(0,0){
    }

    V2(T _x, T _y){
	x = _x;
	y = _y;
    }
};

#endif
