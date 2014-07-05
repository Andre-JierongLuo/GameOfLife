#include "YLabel.h"
#include <sstream>
#include <iostream>

YLabel::YLabel(const string& name, const string& txt) : YComponent(name){
	this->name = name;
	this->txt = txt;
}

void YLabel::paint(){
	//cout << this->name << endl;
	XDrawImageString( this->display, this->window, this->gc, this->x, this->y, this->txt.c_str(), this->txt.length()  );
}

void YLabel::paint(int x){
	stringstream ss;
	ss << x;
	string str = ss.str();
	this->txt = "GEN  " + str + " / 1000";
	//cout << "txt is " << this->txt << endl;

	XClearArea(this->display, this->window, 400, 0,600,50,false);
	XDrawImageString(this->display, this->window, this->gc, this->x, this->y, this->txt.c_str(), this->txt.length());
}

void YLabel::paint(string fname){
	this->txt = "SELECTION : " + fname;

	XClearArea(this->display, this->window, 130, 365,200,20,false);
	XDrawImageString(this->display, this->window, this->gc, this->x, this->y, this->txt.c_str(), this->txt.length());
}

