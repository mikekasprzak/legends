#include <stdio.h>

struct RectBase {
    int x,y,w,h;
};

struct RectRight : RectBase {
    operator const int () const {
        return x+w;
    }
    const int operator = ( const int& v ) {
        x = v - w;
        return x + w;
    }
};

union Rect {
	struct { int x,y,w,h; };
	RectRight right;

	Rect() {
		// Constructor -- C++11 Only //
		x=0;
		y=0;
		w=0;
		h=0;
	}
};

int main(int argc, char *argv[]) {
    Rect r;
    
    fprintf(stderr,"x: %d, right: %d\n",(int)r.x,(int)r.right);
    
    r.x = 10;
    r.y = 20;
    r.w = 100;
    r.h = 50;
    
    fprintf(stderr,"x: %d, right: %d\n",(int)r.x,(int)r.right);
    r.right = 120;
    fprintf(stderr,"x: %d, right: %d\n",(int)r.x,(int)r.right);
    
    return 0;
}