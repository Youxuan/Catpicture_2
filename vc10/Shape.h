#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <string>

using namespace std;

class Shape{

public:
	Shape();
	Shape(int);
	void draw();
	int x_;
	int y_;
	int type;
};