#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPicture_2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event, uint8_t* dataArray );	
	void update();
	void draw();
	void prepareSettings(Settings *settings);   //set size of window
	void drawHorizonalLine(uint8_t* pixels, int start, int end, int row);      //draw horizonal line
	void drawVerticalLine(uint8_t* pixels, int start, int end, int col);      //draw vertical line
	void drawRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color);      //draw rectangle
	void drawTriangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int x3, int y3, Color8u color);       //draw triangle
	void drawCircle(uint8_t* pixels, float radius, float center_x, float center_y);    //draw circle
	void paintChimney(uint8_t* pixels, Color8u color);   //paint chimney
	void blur(uint8_t* pixels);   //do blur

  private:
	Surface* mySurface;  //The Surface object I modify array on
	Surface* mySurface_2;  //The Surface we work for blur
	Color8u colorRoof;
	Color8u colorWall;
	Color8u colorWindow;
	Color8u colorDoor;
	Color8u colorChimney;
	Color8u colorSky;
	float circle_x;
	float circle_y;
	int mouse_x;
	int mouse_y;
};


//do blur
void CatPicture_2App::blur(uint8_t* pixels){
	for(int x=0; x<=600; x++){
		for(int y=0; y<=600; y++){
			//the first line
			if(y == 0){
				if(x == 0){
				  pixels[3*(x+y*600)] = (pixels[3*(x+y*600)] + pixels[3*((x+1)+y*600)] + pixels[3*((x+2)+y*600)] + pixels[3*(x+(y+1)*600)] + pixels[3*((x+1)+(y+1)*600)] + pixels[3*((x+2)+(y+1)*600)] + pixels[3*(x+(y+2)*600)] + pixels[3*((x+1)+(y+2)*600)] + pixels[3*((x+2)+(y+2)*600)])/9;
				  pixels[3*(x+y*600)+1] = (pixels[3*(x+y*600)+1] + pixels[3*((x+1)+y*600)+1] + pixels[3*((x+2)+y*600)+1] + pixels[3*(x+(y+1)*600)+1] + pixels[3*((x+1)+(y+1)*600)+1] + pixels[3*((x+2)+(y+1)*600)+1] + pixels[3*(x+(y+2)*600)+1] + pixels[3*((x+1)+(y+2)*600)+1] + pixels[3*((x+2)+(y+2)*600)+1])/9;
				  pixels[3*(x+y*600)+2] = (pixels[3*(x+y*600)+2] + pixels[3*((x+1)+y*600)+2] + pixels[3*((x+2)+y*600)+2] + pixels[3*(x+(y+1)*600)+2] + pixels[3*((x+1)+(y+1)*600)+2] + pixels[3*((x+2)+(y+1)*600)+2] + pixels[3*(x+(y+2)*600)+2] + pixels[3*((x+1)+(y+2)*600)+2] + pixels[3*((x+2)+(y+2)*600)+2])/9;
				}
				else if(x == 600){
				  pixels[3*(x+y*600)] = (pixels[3*(x+y*600)] + pixels[3*((x-1)+y*600)] + pixels[3*((x-2)+y*600)] + pixels[3*(x+(y-1)*600)] + pixels[3*((x-1)+(y-1)*600)] + pixels[3*((x-2)+(y-1)*600)] + pixels[3*(x+(y-2)*600)] + pixels[3*((x-1)+(y-2)*600)] + pixels[3*((x-2)+(y-2)*600)])/9;
				  pixels[3*(x+y*600)+1] = (pixels[3*(x+y*600)+1] + pixels[3*((x-1)+y*600)+1] + pixels[3*((x-2)+y*600)+1] + pixels[3*(x+(y-1)*600)+1] + pixels[3*((x-1)+(y-1)*600)+1] + pixels[3*((x-2)+(y-1)*600)+1] + pixels[3*(x+(y-2)*600)+1] + pixels[3*((x-1)+(y-2)*600)+1] + pixels[3*((x-2)+(y-2)*600)+1])/9;
				  pixels[3*(x+y*600)+2] = (pixels[3*(x+y*600)+2] + pixels[3*((x-1)+y*600)+2] + pixels[3*((x-2)+y*600)+2] + pixels[3*(x+(y-1)*600)+2] + pixels[3*((x-1)+(y-1)*600)+2] + pixels[3*((x-2)+(y-1)*600)+2] + pixels[3*(x+(y-2)*600)+2] + pixels[3*((x-1)+(y-2)*600)+2] + pixels[3*((x-2)+(y-2)*600)+2])/9;
				}
				else{
				  pixels[3*(x+y*600)] = (pixels[3*(x+y*600)] + pixels[3*((x+1)+y*600)] + pixels[3*((x-1)+y*600)] + pixels[3*(x+(y+1)*600)] + pixels[3*((x+1)+(y+1)*600)] + pixels[3*((x-1)+(y+1)*600)] + pixels[3*(x+(y+2)*600)] + pixels[3*((x+1)+(y+2)*600)] + pixels[3*((x-1)+(y+2)*600)])/9;
				  pixels[3*(x+y*600)+1] = (pixels[3*(x+y*600)+1] + pixels[3*((x+1)+y*600)+1] + pixels[3*((x-1)+y*600)+1] + pixels[3*(x+(y+1)*600)+1] + pixels[3*((x+1)+(y+1)*600)+1] + pixels[3*((x-1)+(y+1)*600)+1] + pixels[3*(x+(y+2)*600)+1] + pixels[3*((x+1)+(y+2)*600)+1] + pixels[3*((x+2)+(y+2)*600)+1])/9;
				  pixels[3*(x+y*600)+2] = (pixels[3*(x+y*600)+2] + pixels[3*((x+1)+y*600)+2] + pixels[3*((x+2)+y*600)+2] + pixels[3*(x+(y+1)*600)+2] + pixels[3*((x+1)+(y+1)*600)+2] + pixels[3*((x+2)+(y+1)*600)+2] + pixels[3*(x+(y+2)*600)+2] + pixels[3*((x+1)+(y+2)*600)+2] + pixels[3*((x+2)+(y+2)*600)+2])/9;
				}
			}

			

		}
	}
}

//draw horizonal line
void CatPicture_2App::drawHorizonalLine(uint8_t* pixels, int start, int end, int row){
	int draw;
	for(draw = start; draw <= end; draw++){
		pixels[3*(draw + row*600)] = 0;
		pixels[3*(draw + row*600)+1] = 0;
		pixels[3*(draw + row*600)+2] = 0;
	}
}

//draw vertical line
void CatPicture_2App::drawVerticalLine(uint8_t* pixels, int start, int end, int col){
	int draw;
	for(draw = start; draw <=end; draw++){
		pixels[3*(col + draw * 600)] = 0;
		pixels[3*(col + draw * 600)+1] = 0;
		pixels[3*(col + draw * 600)+2] = 0;
	}
}

//draw rectangle
void CatPicture_2App::drawRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color){
	int draw;

	//draw horizonal edges
	for(draw = x1; draw <= x2; draw++){
		pixels[3*(draw + y1*600)] = 0;
		pixels[3*(draw + y1*600)+1] = 0;
		pixels[3*(draw + y1*600)+2] = 0;

		pixels[3*(draw + y2*600)] = 0;
		pixels[3*(draw + y2*600)+1] = 0;
		pixels[3*(draw + y2*600)+2] = 0;
	}

	//draw vertical edges
	for(draw = y1; draw <= y2; draw++){
		pixels[3*(x1 + draw * 600)] = 0;
		pixels[3*(x1 + draw * 600)+1] = 0;
		pixels[3*(x1 + draw * 600)+2] = 0;

		pixels[3*(x2 + draw * 600)] = 0;
		pixels[3*(x2 + draw * 600)+1] = 0;
		pixels[3*(x2 + draw * 600)+2] = 0;
	}

	for(int x=0; x<=600; x++){
		for(int y=0; y<=600; y++){
			if(x>x1 && x<x2 && y>y1 && y<y2){
				if(pixels[3*(x + y * 600)] != 0 && pixels[3*(x + y * 600)+1] != 0 && pixels[3*(x + y * 600)+2] != 0){
					pixels[3*(x + y * 600)] = color.r;
					pixels[3*(x + y * 600)+1] = color.g;
					pixels[3*(x + y * 600)+2] = color.b;
				}
			}
		}
	}
}

//paint chimney
void CatPicture_2App::paintChimney(uint8_t* pixels, Color8u color){
	for(int x=0; x<=600; x++){
		for(int y=0; y<=600; y++){
			if(x > 101 && x < 149 && y > 220 && y < 300){
				pixels[3*(x + y * 600)] = color.r;
				pixels[3*(x + y * 600)+1] = color.g;
				pixels[3*(x + y * 600)+2] = color.b;
			}
		}
	}
}

//draw triangle
void CatPicture_2App::drawTriangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int x3, int y3, Color8u color){
	//draw the first edge
	int draw_x2 = x2;
	int draw_y2 = y2;
	while(draw_x2 <= x1 && draw_y2 >= y1){
		pixels[3*(draw_x2 + draw_y2 * 600)] = 0;
		pixels[3*(draw_x2 + draw_y2 * 600)+1] = 0;
		pixels[3*(draw_x2 + draw_y2 * 600)+2] = 0;

		draw_x2++;
		draw_y2--;
	}

	//draw the second edge
	int draw_x3 = x3;
	int draw_y3 = y3;
	while(draw_x3 >= x1 && draw_y3 >= y1){
		pixels[3*(draw_x3 + draw_y3 * 600)] = 0;
		pixels[3*(draw_x3 + draw_y3 * 600)+1] = 0;
		pixels[3*(draw_x3 + draw_y3 * 600)+2] = 0;

		draw_x3--;
		draw_y3--;
	}

	//draw the third edge
	int draw_x = x2;
	for(draw_x; draw_x <= x3; draw_x++){
		pixels[3*(draw_x + 350 * 600)] = 0;
		pixels[3*(draw_x + 350 * 600)+1] = 0;
		pixels[3*(draw_x + 350 * 600)+2] = 0;
	}
	
}

void CatPicture_2App::drawCircle(uint8_t* pixels, float radius, float center_x, float center_y){
	
	for(int y=0; y<=600; y++){
		for(int x=0;x<=600; x++){

			if ((pow(x-center_x,2) + (pow(y-center_y,2))) <= (pow(radius,2))){
				pixels[3*(x + y*600)] = 255;
				pixels[3*(x + y*600)+1] = 255;
				pixels[3*(x + y*600)+2] = 255;
			}
		}
	}

}



void CatPicture_2App::setup()
{
	mySurface = new Surface(600,600,false);
	mySurface_2 = mySurface;

	colorWall.r = 237;
	colorWall.g = 28;
	colorWall.b = 36;

	colorWindow.r = 153;
	colorWindow.g = 217;
	colorWindow.b = 234;

	colorDoor.r = 255;
	colorDoor.g = 242;
	colorDoor.b = 0;

	colorChimney.r = 163;
	colorChimney.g = 73;
	colorChimney.b = 164;

	colorRoof.r = 255;
	colorRoof.g = 127;
	colorRoof.b = 39;

	colorSky.r = 0;
	colorSky.g = 162;
	colorSky.b = 232;

	circle_x = 120;
	circle_y = 145;
}

void CatPicture_2App::mouseDown( MouseEvent event, uint8_t* dataArray )
{
	mouse_x = event.getX();
	mouse_y = event.getY();
	if(event.isLeft()){
		drawCircle(dataArray, 20, mouse_x, mouse_y);
	}
}

void CatPicture_2App::update()
{
	//Surface 1
	uint8_t* dataArray = (*mySurface).getData();

	//draw lines of chimney
	drawVerticalLine(dataArray, 220, 300, 99);
	drawVerticalLine(dataArray, 220, 300, 100);
	drawVerticalLine(dataArray, 220, 300, 101);

	drawVerticalLine(dataArray, 220, 250, 149);
	drawVerticalLine(dataArray, 220, 250, 150);
	drawVerticalLine(dataArray, 220, 250, 151);

	//paint chimney
	paintChimney(dataArray, colorChimney);

	//draw rectangle of chimney
	drawRectangle(dataArray, 74, 179, 174, 219, colorChimney);
	drawRectangle(dataArray, 75, 180, 175, 220, colorChimney);
	drawRectangle(dataArray, 73, 178, 173, 218, colorChimney);

	//draw rectangle of house
	drawRectangle(dataArray, 110, 350, 400, 530, colorWall);
	drawRectangle(dataArray, 111, 351, 399, 529, colorWall);
	drawRectangle(dataArray, 112, 352, 398, 528, colorWall);

	//draw rectangle of window
	drawRectangle(dataArray, 150, 380, 230, 430, colorWindow);
	drawRectangle(dataArray, 151, 381, 229, 429, colorWindow);
	drawRectangle(dataArray, 152, 382, 231, 431, colorWindow);

	//draw lines of window
	drawHorizonalLine(dataArray, 150, 230, 404);
	drawHorizonalLine(dataArray, 150, 230, 405);
	drawHorizonalLine(dataArray, 150, 230, 406);

	drawVerticalLine(dataArray, 380, 430, 189);
	drawVerticalLine(dataArray, 380, 430, 190);
	drawVerticalLine(dataArray, 380, 430, 191);

	//draw rectangle of door
	drawRectangle(dataArray, 290, 417, 360, 530, colorDoor);
	drawRectangle(dataArray, 291, 418, 359, 530, colorDoor);
	drawRectangle(dataArray, 292, 419, 358, 530, colorDoor);

	//draw triangle of roof
	drawTriangle(dataArray, 255, 145, 50, 350, 460, 350, colorRoof);
	drawTriangle(dataArray, 255, 144, 50, 349, 460, 349, colorRoof);
	drawTriangle(dataArray, 255, 143, 50, 348, 460, 348, colorRoof);

	//draw circle of smoke
	drawCircle(dataArray, 20, circle_x, circle_y);
	circle_y = 30*cos(circle_x/20)+130;
	circle_x += 2;


}

void CatPicture_2App::draw()
{
	gl::draw(*mySurface);
}

// Set size of window.
void CatPicture_2App::prepareSettings(Settings *settings){
	settings -> setWindowSize(600,600);
}

CINDER_APP_BASIC( CatPicture_2App, RendererGl )
