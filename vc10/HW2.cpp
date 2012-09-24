#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Shape.h"
#include "Resources.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Node.h"
#include "cinder/gl/TextureFont.h"

using namespace ci;
using namespace ci::app;
using namespace std;


// This project satisfies Goals A, B, D, E, F, K
class HW2 : public AppBasic {
public:
	void MoveAll(Node*);
	void setup();
	void mouseDown( MouseEvent event );	
	void mouseMove( MouseEvent event);
	void keyDown( KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings*);

private:
	  bool move_all;
	  bool display_message;
	  Shape* shape;
	  Shape* circle;
	  Node* ball;
	  Node* linked_list; //Main list
	  int click_count;
	  int mouse_x;
	  int mouse_y;
	  int frame_number;
	  Font mFont;
	  Font mFont2;
	  gl::TextureFontRef mTextureFont;
	  gl::TextureFontRef mTextureFont2;
	  int mouse_click;

	  static const int surfaceSize_ = 1028;
	  static const int appHeight_ = 600;
	  static const int appWidth_ = 800;
};

//Satisfies Goal. F
/**
*Moves all shapes 200 right
*@param Node* sentinal node of linked list
*/
void HW2::MoveAll(Node* linked_list) {

	if (linked_list->next_->shape_->type == 0) {
		return;
	}
	else {
	linked_list->next_->shape_->x_ = linked_list->next_->shape_->x_+200;
	MoveAll(linked_list->next_);
	}

}
void HW2::prepareSettings(Settings* settings) {
	settings->setWindowSize(appWidth_,appHeight_);
	settings->setResizable(false);
}

void  HW2::setup()
{
	move_all=false;
	shape = new Shape();
	display_message = true;
	circle = new Shape(2);
	ball = new Node(circle);
	circle->x_=400;
	circle->y_=300;
	click_count = 0;
	linked_list = new Node();
	frame_number=0;
}

//Satisfies Goal. D
/**
*Handles the keyboard events, moving the circle,
*displaying the message, and reversing the list
*/
void HW2::keyDown( KeyEvent event) {
	if (event.getCode() ==KeyEvent::KEY_DOWN) {
		circle->y_ = circle->y_+5;
	}
	if (event.getCode() ==KeyEvent::KEY_UP) {
		circle->y_ = circle->y_-5;	
	}
	if (event.getCode() ==KeyEvent::KEY_LEFT) {
		circle->x_ = circle->x_-5;
	}
	if (event.getCode() ==KeyEvent::KEY_RIGHT) {
		circle->x_ = circle->x_+5;
	}
	if (event.getCode() == KeyEvent::KEY_SPACE) {
		display_message =false;
	}
	if (event.isShiftDown()) {
		linked_list->reverseAll();
	}
	if (event.getCode() == KeyEvent::KEY_r) {
		move_all = true;
	}
}

/**
*Tracks the mouse's movements,
*not really implemented
*/
void HW2::mouseMove( MouseEvent event) {
	mouse_x = event.getX();
	mouse_y = event.getY();


}

/**
*Handles mouse clicks, draws and deletes shapes
*/
void  HW2::mouseDown( MouseEvent event ) {
	Node* shape = new Node();

	if (event.isLeftDown()) {
		if (click_count%2==0) {
		shape->shape_= new Shape(1);
		}
		else {
		shape->shape_= new Shape(4);
		}
		shape->shape_->x_=event.getX();
		shape->shape_->y_=event.getY();
		shape->popOn(linked_list);
	}
	if (event.isRightDown()) {
		linked_list->popOffEnd();
	}
	click_count++;
}

void  HW2::update()
{

	if (circle->x_ ==860) {
		circle->x_=-5;
	}
	if (circle->x_ ==-60) {
		circle->x_=810;
	}

	if (circle->y_ ==660) {
		circle->y_=0;
	}
	if (circle->y_ ==-60) {
		circle->y_=600;
	}


	//Satisfies Goal D.
	//Loops through the list, checking if shapes need to
	// move closer to the large circle
	Node* cur = linked_list->next_;
		while(cur!= linked_list) {
			if (circle->x_ <= cur->shape_->x_+45)
				cur->shape_->x_= cur->shape_->x_--;

			if (circle->x_ >= cur->shape_->x_-45)
				cur->shape_->x_= cur->shape_->x_++;
				
			if (circle->y_ <= cur->shape_->y_+45)
				cur->shape_->y_= cur->shape_->y_--;
				
			if (circle->y_ >= cur->shape_->y_-45)
				cur->shape_->y_= cur->shape_->y_++;
				
			cur=cur->next_;

			if (circle->y_ == cur->prev_->shape_->y_+45 ||
				circle->x_ == cur->prev_->shape_->x_+45 ||
				circle->y_ == cur->prev_->shape_->y_-45 ||
				circle->x_ == cur->prev_->shape_->x_-45) {
				shape->type=3;
				shape->x_=cur->prev_->shape_->x_;
				shape->y_=cur->prev_->shape_->y_;
			}
		}
		if (move_all == true) {
			MoveAll(linked_list);
			move_all = false;
		}




		frame_number++;
}

void  HW2::draw()
{

	gl::clear( Color( 0, 0, 0 ) );
	linked_list->drawList();
	circle->draw();
	shape->draw();

	//Satisfys Goal B
	//Displays message
		if (display_message==true) {
		mFont = Font( "Times New Roman", 24 );
		mTextureFont = gl::TextureFont::create( mFont );
		std::string str("Welcome! Left click to create shapes. Right click to delete shapes. Press Shift to reverse the list of shapes.Use the Arrow Keys to move the large circle.Press the space bar to hide this message. Have Fun!");
		gl::color( Color8u( 255,255,255 ) );
		gl::enableAlphaBlending();
		Rectf boundsRect( 40, mTextureFont->getAscent() + 40, getWindowWidth() - 40, getWindowHeight() - 40 );
		mTextureFont->drawStringWrapped( str, boundsRect );
		gl::color(Color8u(255,255,255));
		}

		//gl::drawSolidCircle(
}

CINDER_APP_BASIC(  HW2, RendererGl )
