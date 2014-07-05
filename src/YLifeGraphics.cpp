#include "YLifeGraphics.h"
#include "Life.h"
#include <iostream>

YLifeGraphics::YLifeGraphics(const string& name) : YComponent(name){
	this->name = name;
	this->px = 0;
	this->py = 0;
}

void YLifeGraphics::getGeneration(){
	this->generation = (this->lm)->getCurrentGeneration();
}

void YLifeGraphics::paint(){
	XClearArea(this->display, this->window, this->x, this->y, this->width,this->height,false);

	XDrawRectangle(this->display, this->window, this->gc, this->x, this->y, this->width, this->height);
	int x = this->x;
	int y = this->y;
	int width = this->width;
	int height = this->height;

	for(int i = x+7; i < x+width; i+=7){
		XDrawLine(this->display, this->window, this->gc, i, y, i, y+height);
	}

	for(int j = y+7; j < y+height; j+=7){
		XDrawLine(this->display, this->window, this->gc, x, j, x+width, j);
	}
}

void YLifeGraphics::paint(bool isSet){
	XClearArea(this->display, this->window, this->x, this->y, this->width,this->height,false);

	XDrawRectangle(this->display, this->window, this->gc, this->x, this->y, this->width, this->height);
	int x = this->x;
	int y = this->y;
	int width = this->width;
	int height = this->height;

	for(int i = x+7; i < x+width; i+=7){
		XDrawLine(this->display, this->window, this->gc, i, y, i, y+height);
	}

	for(int j = y+7; j < y+height; j+=7){
		XDrawLine(this->display, this->window, this->gc, x, j, x+width, j);
	}

	if(isSet){
		this->getGeneration();
		//cout << NUM_ROWS << " " << NUM_COLS << endl;
		for(int i = 0; i < NUM_ROWS; i++){
			for(int j = 0; j < NUM_COLS; j++){
				if((this->generation)->islive(i,j)){
					//cout << x+(j*7) << "," << y+(i*7) << endl;
					XFillRectangle(this->display, this->window, this->gc, x+(j*7), y+(i*7), 7, 7);
				}
			}
		}
	}
}

void YLifeGraphics::paint(int isEditing){
	XClearArea(this->display, this->window, this->x, this->y, this->width,this->height,false);

	XDrawRectangle(this->display, this->window, this->gc, this->x, this->y, this->width, this->height);
	int x = this->x;
	int y = this->y;
	int width = this->width;
	int height = this->height;

	for(int i = x+7; i < x+width; i+=7){
		XDrawLine(this->display, this->window, this->gc, i, y, i, y+height);
	}

	for(int j = y+7; j < y+height; j+=7){
		XDrawLine(this->display, this->window, this->gc, x, j, x+width, j);
	}

		//cout << NUM_ROWS << " " << NUM_COLS << endl;
	for(int i = 0; i < NUM_ROWS; i++){
		for(int j = 0; j < NUM_COLS; j++){
			if((this->generation)->islive(i,j)){
				XFillRectangle(this->display, this->window, this->gc, x+(j*7), y+(i*7), 7, 7);
			}
		}
	}
}

void YLifeGraphics::AddActionListener(ActionListener* action){
	this->action = action;
}

void YLifeGraphics::RemoveActionListener(ActionListener* action){
	this->action = NULL;
}

bool YLifeGraphics::HandelEvent(XEvent &event){
	double x = event.xmotion.x;
	double y = event.xmotion.y;
	bool where = this->containsPoint(x,y);
	if(where){
		switch(event.type){
			case ButtonPress:
				this->px = (event.xmotion.x - this->x) / 7;
				this->py = (event.xmotion.y - this->y) / 7;
				(this->action)->ActionPerformed(this);
				return true;
				break;
		}
	}
	return false;
}

