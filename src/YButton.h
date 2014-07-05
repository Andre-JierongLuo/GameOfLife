#ifndef _YBUTTON_H_
#define _YBUTTON_H_

#include "YComponent.h"
#include "ActionListener.h"

class YButton : public YComponent{
public:
	string name;
	void paint();
	void paint(bool running);
	YButton(const string& name);
	ActionListener* action;
	void AddActionListener(ActionListener* action);
	void RemoveActionListener(ActionListener* action);
	bool HandelEvent(XEvent &event);

};


#endif /* _YBUTTON_H_ */

