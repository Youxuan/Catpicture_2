#include "Shape.h"
#include <string>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

/**
**Shape Constructor
*/
Shape::Shape() {
	x_=0;
	y_=0;
	type = 0;

}

/**
* Shape Constructor indicating type of shape
*/
Shape::Shape(int ob_type) {
	x_=0;
	y_=0;
	type = ob_type;
}

/**
* Draws shape depending on type 1, 2, 3
*/
void Shape::draw() {

	//1=tri 2=circle
	if (type==1) {
		gl::color(0,100,255);
		gl::drawSolidCircle( Vec2f(x_,y_), 5.0f);
	//gl::drawSolidCircle( 
	}

	if (type==2) {
		gl::color(255,0,255);
		gl::drawSolidCircle( Vec2f(x_,y_), 50.0f);
	}
	if (type==3) {
		gl::color(255,155,0);
		gl::drawSolidCircle( Vec2f(x_,y_), 5.0f);

	}

	if (type==4) {
		gl::enableAlphaBlending();
		gl::color(1.0,0.0,0.0,1.0);
		gl::drawSolidCircle( Vec2f(x_,y_), 50.0f,5);
	}
}
