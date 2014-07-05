/*
 * YComponent.h
 *
 *  Created on: May 29, 2014
 *      Author: cs349
 */

#ifndef _YCOMPONENT_H_
#define _YCOMPONENT_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "LifeModel.h"

using namespace std;

class YComponent {
public:

	string name;
	double x;
	double y;
	double width;
	double height;
	YComponent* parent;
	YComponent* Top;

	Display	 *display;
	Window	 window;
	GC		 gc;
	LifeModel* lm;


	std::vector<YComponent*> children;
	YComponent(const string& name);
	virtual ~YComponent();
    virtual void paint();

    // Adds a child Component to this Component and sets its parent to this Component.
    virtual void AddComponent(YComponent* child);

    // Removes the specified Component from the list of children and
    // sets its parent to NULL. Does nothing if that YComponent is not in
    // the children list.
    virtual void RemoveComponent(YComponent* child);

    virtual YComponent* getParent();

    //
    virtual bool containsPoint(double x, double y);

    virtual void setParameters(double x, double y, double width, double height);

    virtual void setLifeModel(LifeModel* lm);
    virtual bool HandelEvent(XEvent &event);
    virtual void setTop(YComponent* c);
	virtual YComponent* getMouseFocus();
	virtual void resetFocus();
	virtual void setFocus(YComponent* c);
};

#endif /* YCOMPONENT_H_ */

