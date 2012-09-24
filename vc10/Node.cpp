#include "Node.h"
#include <string>

using namespace std;

/**
*Node constructor
*/
Node::Node() {
	next_ = this;
	prev_ = this;
	shape_ = new Shape();
}

/**
* Node Constructor specifying the shape within node
*/

Node::Node(Shape* shape) {
	this->shape_ = shape;
	next_ = this;
	prev_ = this;
}

//Works
/**
*Returns true if there is only the sentinal node
*/
bool Node::isEmpty() {
	if (this->next_ == this)
		return true;
	return false;
}



/**
*Inserts a new Node* after the specifyed node
* @param Node* node to be inserted
*/
void Node::insertAfter(Node* where_at) {
	if (where_at->isEmpty() == true) {
		where_at->prev_=this;
		where_at->next_=this;

		this->next_ = where_at;
		this->prev_ = where_at;
	}

	else {
	this->next_ = where_at->next_;
	this->prev_ = where_at;
	where_at->next_ = this;
	this->next_->prev_=this;
	}
}

/**
*Removes this node
*/
void Node::remove(){
	Node* temp = this;
	Node* next = this->next_;
	Node* prev = this->prev_;


	next->prev_=this->prev_;
	prev->next_=this->next_;
	next_=this;
	prev_=this;
	


}

//Good
/**
*Pops a Node* onto the end of the list
*@param Node* sentinal the sentinal node of the linked list
*/
void Node::popOn(Node* sentinal){ 

	if (sentinal->isEmpty() == true) {
		insertAfter(sentinal);
	}

	else{
	insertAfter(sentinal->prev_);
	}
}

/**
*Removes the last node off list, "only if used on sentinal node"
*/
void Node::popOffEnd() {
	prev_->remove();
}

/**
* Draws the shape within the node
*/
void Node::draw() {
	shape_->draw();
}

/**
*Draws all the shapes
*/
void Node::drawList() {
	cur = new Node();
	cur = next_;

	while(cur != this) {
		cur->draw();
		cur = cur->next_;
	}
}


//Satisfies Goal E
/**
*reverses the linked list
*/
void Node::reverseAll() {
		Node* cur = this;

	do {
		Node* temp = cur->next_;
		cur->next_ = cur->prev_;
		cur->prev_ = temp;

		cur = cur->prev_;

	} while(cur!=this);
}