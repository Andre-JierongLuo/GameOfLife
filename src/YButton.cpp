#include "YButton.h"
#include <iostream>
#include <string>

using namespace std;

YButton::YButton(const string& name) : YComponent(name){
	this->name = name;
}

void YButton::AddActionListener(ActionListener* action){
	this->action = action;
}

void YButton::RemoveActionListener(ActionListener* action){
	this->action = NULL;
}

void YButton::paint(){
	XDrawRectangle(this->display, this->window, this->gc, this->x, this->y, this->width, this->height);
	string n = this->name;
	if(n == "end" || n == "forward" || n == "start" || n == "backward"){
		XPoint* points = new XPoint[3];
		if(n == "end" || n == "forward"){
			points[0].x = (this->x) + 10;
			points[0].y = (this->y) + 10;
			points[1].x = (this->x) + 20;
			points[1].y = (this->y) + 15;
			points[2].x = (this->x) + 10;
			points[2].y = (this->y) + 20;
			if(n == "end"){
				XDrawLine(this->display, this->window, this->gc, (this->x)+20, (this->y)+10, (this->x)+20, (this->y)+20);
			}
		}
		if(n == "start" || n == "backward"){
			points[0].x = (this->x) + 20;
			points[0].y = (this->y) + 10;
			points[1].x = (this->x) + 10;
			points[1].y = (this->y) + 15;
			points[2].x = (this->x) + 20;
			points[2].y = (this->y) + 20;
			if(n == "start"){
				XDrawLine(this->display, this->window, this->gc, (this->x)+10, (this->y)+10, (this->x)+10, (this->y)+20);
			}
		}
		XDrawLines(this->display,this->window, this->gc, points, 3, CoordModeOrigin);
		delete[] points;
	}
	if(n == "play"){
		XPoint* points = new XPoint[4];
		points[0].x = (this->x) + 10;
		points[0].y = (this->y) + 10;
		points[1].x = (this->x) + 20;
		points[1].y = (this->y) + 15;
		points[2].x = (this->x) + 10;
		points[2].y = (this->y) + 20;
		points[3].x = (this->x) + 10;
		points[3].y = (this->y) + 10;
		XDrawLines(this->display,this->window, this->gc, points, 4, CoordModeOrigin);
		delete[] points;
	}
	if(n == "nextFile"){
		string txt = "NEXT FILE";
		XDrawString(this->display, this->window, this->gc, this->x + 20, this->y + 20, txt.c_str(), txt.length());
	}
	if(n == "startGame"){
		string txt = "SET";
		XDrawString(this->display, this->window, this->gc, this->x + 43, this->y + 20, txt.c_str(), txt.length());
	}
	if(n == "save"){
		string txt = "SAVE GEN";
		XDrawString(this->display, this->window, this->gc, this->x + 25, this->y + 20, txt.c_str(), txt.length());
	}
}

// only for play button.
void YButton::paint(bool running){
	XClearArea(this->display, this->window, this->x, this->y, this->width, this->height, false);
	XDrawRectangle(this->display, this->window, this->gc, this->x, this->y, this->width, this->height);
	if(running){
		XDrawLine(this->display, this->window, this->gc, (this->x)+10, (this->y)+10, (this->x)+10, (this->y)+20);
		XDrawLine(this->display, this->window, this->gc, (this->x)+20, (this->y)+10, (this->x)+20, (this->y)+20);
	} else {
		XPoint* points = new XPoint[4];
		points[0].x = (this->x) + 10;
		points[0].y = (this->y) + 10;
		points[1].x = (this->x) + 20;
		points[1].y = (this->y) + 15;
		points[2].x = (this->x) + 10;
		points[2].y = (this->y) + 20;
		points[3].x = (this->x) + 10;
		points[3].y = (this->y) + 10;
		XDrawLines(this->display,this->window, this->gc, points, 4, CoordModeOrigin);
		delete[] points;
	}
}

bool YButton::HandelEvent(XEvent &event){
	double x = event.xmotion.x;
	double y = event.xmotion.y;
	bool where = this->containsPoint(x,y);
	if(where){
		switch(event.type){
			case ButtonPress:
				this->resetFocus();
				this->setFocus(this);
				return true;
				break;
			case ButtonRelease:
				if(this->getMouseFocus() == this){
					(this->action)->ActionPerformed(this);
					this->resetFocus();
					return true;
				}
				break;
		}
	}
	return false;
}

