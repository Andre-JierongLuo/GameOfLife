#include "YSlider.h"
#include <iostream>

YSlider::YSlider(const string& name) : YComponent(name){
	this->name = name;
	this->curValue = 0;
}

 void YSlider::paint(){
	 XClearArea(this->display, this->window, this->x,this->y,this->width,this->height,false);
	 XDrawLine(this->display, this->window, this->gc, (this->x)+20, (this->y)+5, (this->x)+20, (this->y)+25);
	 XDrawLine(this->display, this->window, this->gc, (this->x)+20, (this->y)+15, (this->x)+120, (this->y)+15);
	 XDrawLine(this->display, this->window, this->gc, (this->x)+120, (this->y)+5, (this->x)+120, (this->y)+25);
	 XFillRectangle(this->display, this->window, this->gc, (this->x)+10+(this->curValue), (this->y)+5, 20, 20);
 }


 bool YSlider::containsPoint(double x, double y){
		double lowerboundX = (this->x) + 10 + (this->curValue);
		double upperboundX = (this->x) + 30 + (this->curValue);
		double lowerboundY = (this->y) + 5;
		double upperboundY = (this->y) + 25;
		if(lowerboundX <= x && x <= upperboundX && lowerboundY <= y && y <= upperboundY){
			//std::cout << this->name << " YSlider is click"  << std::endl;
			return true;
		}
		else return false;
 }

 bool YSlider::HandelEvent(XEvent &event){
	double x = event.xmotion.x;
	double y = event.xmotion.y;
	bool where = this->containsPoint(x,y);
	switch(event.type){
		case ButtonPress:
			if(where){
				this->resetFocus();
				this->setFocus(this);
				return true;
			}
			break;
		case ButtonRelease:
			if(this->getMouseFocus() == this){
				double n = min(this->x + 110, x);
				n = max(n, this->x + 10);
				this->curValue = n - (this->x) - 10;
				//cout << this->curValue << " .,. " << endl;
				(this->action)->ActionPerformed(this);
				this->resetFocus();
				return true;
			}
			break;
	}
	return false;
}

 void YSlider::AddActionListener(ActionListener* action){
 	this->action = action;
 }

 void YSlider::RemoveActionListener(ActionListener* action){
 	this->action = NULL;
 }

 double YSlider::getCurValue(){
	 return this->curValue;
 }

 void YSlider::setCurValue(double x){
	 this->curValue = x;
 }

