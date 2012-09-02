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
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings *settings);   //set size of window
	void drawHorizonalLine(uint8_t* pixels, int start, int end, int row, Color8u color);      //draw horizonal line
	void drawVerticalLine(uint8_t* pixels, int start, int end, int col, Color8u color);      //draw vertical line
	void drawRectangle(uint8_t* pixels, int x1, int y1, int x2, int y2, Color8u color);      //draw rectangle
	void drawTriangle(uint8_t* pixels, int x1, int y1, int x2, int y2, int x3, int y3, Color8u color);       //draw triangle
	void drawCircle(uint8_t* pixels, float radius, float center_x, float center_y, Color8u color);    //draw circle

  private:
	Surface* mySurface;  //The Surface object I modify array on
};

//draw horizonal line
void CatPicture_2App::drawHorizonalLine(uint8_t* pixels, int start, int end, int row, Color8u color){
	int draw;
	for(draw = start; draw <= end; draw++){
		pixels[3*(draw + row*600)] = 0;
		pixels[3*(draw + row*600)+1] = 0;
		pixels[3*(draw + row*600)+2] = 0;
	}
}

//draw vertical line
void CatPicture_2App::drawVerticalLine(uint8_t* pixels, int start, int end, int col, Color8u color){
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

void CatPicture_2App::drawCircle(uint8_t* pixels, float radius, float center_x, float center_y, Color8u color){
	/*int draw_x = center_x - radius;
	int draw_y = center_y - radius;

	for(draw_x;draw_x <= (center_x+radius); draw_x++){
		for(draw_y;draw_y <= (center_y+radius); draw_y++){
			if((center_x - draw_x)*(center_x - draw_x) + (center_y - draw_y)*(center_y - draw_y) <= (radius * radius)){
				pixels[3*(draw_x + draw_y * 600)] = 0;
				pixels[3*(draw_x + draw_y * 600)+1] = 0;
				pixels[3*(draw_x + draw_y * 600)+2] = 0;
			}
		}
	}*/
	
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


}

void CatPicture_2App::mouseDown( MouseEvent event )
{
}

void CatPicture_2App::update()
{
	uint8_t* dataArray = (*mySurface).getData();

	//draw rectangle of background
	drawRectangle(dataArray);

	//draw rectangle of house
	drawRectangle(dataArray, 110, 350, 400, 530);
	drawRectangle(dataArray, 111, 351, 399, 529);
	drawRectangle(dataArray, 112, 352, 398, 528);

	//draw rectangle of window
	drawRectangle(dataArray, 150, 380, 230, 430);
	drawRectangle(dataArray, 151, 381, 229, 429);
	drawRectangle(dataArray, 152, 382, 231, 431);

	//draw lines of window
	drawHorizonalLine(dataArray, 150, 230, 404);
	drawHorizonalLine(dataArray, 150, 230, 405);
	drawHorizonalLine(dataArray, 150, 230, 406);

	drawVerticalLine(dataArray, 380, 430, 189);
	drawVerticalLine(dataArray, 380, 430, 190);
	drawVerticalLine(dataArray, 380, 430, 191);

	//draw rectangle of door
	drawRectangle(dataArray, 290, 417, 360, 530);
	drawRectangle(dataArray, 291, 418, 359, 530);
	drawRectangle(dataArray, 292, 419, 358, 530);

	//draw triangle of roof
	drawTriangle(dataArray, 255, 145, 50, 350, 460, 350);
	drawTriangle(dataArray, 255, 144, 50, 349, 460, 349);
	drawTriangle(dataArray, 255, 143, 50, 348, 460, 348);

	//draw lines of chimney
	drawVerticalLine(dataArray, 220, 300, 99);
	drawVerticalLine(dataArray, 220, 300, 100);
	drawVerticalLine(dataArray, 220, 300, 101);

	drawVerticalLine(dataArray, 220, 250, 149);
	drawVerticalLine(dataArray, 220, 250, 150);
	drawVerticalLine(dataArray, 220, 250, 151);

	//draw rectangle of chimney
	drawRectangle(dataArray, 74, 179, 174, 219);
	drawRectangle(dataArray, 75, 180, 175, 220);
	drawRectangle(dataArray, 73, 178, 173, 218);

	//draw circle of smoke
	drawCircle(dataArray, 20, 120, 145);
	drawCircle(dataArray, 35, 200, 100);
	drawCircle(dataArray, 45, 310, 50);
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
