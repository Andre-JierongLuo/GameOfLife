#ifndef _YLIFEGRAPHICS_H_
#define _YLIFEGRAPHICS_H_

#include "YComponent.h"
#include "ActionListener.h"
#include "Generation.h"

class YLifeGraphics : public YComponent{
public:
	int px;
	int py;

	string name;
	Generation* generation;
	YLifeGraphics(const string& name);
	bool HandelEvent(XEvent &event);
	void paint();
	void paint(bool isSet);
	void paint(int isEditing);
	void getGeneration();
	ActionListener* action;
	void AddActionListener(ActionListener* action);
	void RemoveActionListener(ActionListener* action);
};


#endif /* _YLIFEGRAPHICS_H_ */

