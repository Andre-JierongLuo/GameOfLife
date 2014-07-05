/*
 * YComponent.cpp
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#include "YComponent.h"
#include "LifeModel.h"
#include <iostream>

 using namespace std;

YComponent::YComponent(const string& name) {
	this->name            = name;
    this->parent          = NULL;
}

YComponent::~YComponent() {
	for(vector<YComponent*>::iterator child = this->children.begin(); child != this->children.end(); child++){
		delete(*child);
	}
	this->children.clear();
}

void YComponent::paint() {
	//cout << this->name << endl;
	for(vector<YComponent*>::iterator child = this->children.begin(); child != this->children.end(); child++){
		(*child)->paint();
	}
}


void YComponent::AddComponent(YComponent* child){
	this->children.push_back(child);
	child->parent = this;
	child->display = this->display;
	child->window = this->window;
	child->gc = this->gc;

}

void YComponent::setLifeModel(LifeModel* lm){
	this->lm = lm;
}

void YComponent::RemoveComponent(YComponent* child){
	for(vector<YComponent*>::iterator i = this->children.begin(); i != this->children.end(); i++){
		if(*i == child){
			child->parent = NULL;
			this->children.erase(i);
			break;
		}
	}
}


YComponent* YComponent::getParent(){
	return this->parent;
}

bool YComponent::containsPoint(double x, double y){
	double lowerboundX = this->x;
	double upperboundX = (this->x) + (this->width);
	double lowerboundY = this->y;
	double upperboundY = (this->y) + (this->height);
	if(lowerboundX <= x && x <= upperboundX && lowerboundY <= y && y <= upperboundY) return true;
	else return false;
}

void YComponent::setParameters(double x, double y, double width, double height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool YComponent::HandelEvent(XEvent &event){
	for(vector<YComponent*>::iterator child = this->children.begin(); child != this->children.end(); child++){
		YComponent* i = (*child);
		if(i->HandelEvent(event)) return true;
	}
	return false;
}

void YComponent::setTop(YComponent* c){
	this->Top = c;
}

YComponent* YComponent::getMouseFocus(){
	return (this->Top)->getMouseFocus();
}

void YComponent::resetFocus(){
	(this->Top)->resetFocus();
}

void YComponent::setFocus(YComponent* c){
	(this->Top)->setFocus(this);
}



