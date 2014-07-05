#ifndef _YSLIDER_H_
#define _YSLIDER_H_

#include "YComponent.h"
#include "ActionListener.h"

class YSlider : public YComponent{
public:
	string name;
	double curValue;
	ActionListener* action;

  	void paint();
  	void setCurValue(double x);
  	YSlider(const string& name);
  	bool containsPoint(double x, double y);
  	bool HandelEvent(XEvent &event);
  	void AddActionListener(ActionListener* action);
  	void RemoveActionListener(ActionListener* action);
  	double getCurValue();

};

#endif

