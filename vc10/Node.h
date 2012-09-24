#pragma once
#include "Shape.h"
#include <string>

using namespace std;

class Node{
	public:
		Node();
		Node(Shape*);
		bool isEmpty();
		void insertAfter(Node*);
		void remove();
		void draw();
		void drawList();
		void reverseAll();
		void popOn(Node*);
		void popOffEnd();
		Shape* shape_;
		Node* next_;
		Node* prev_;
		Node* cur;
};