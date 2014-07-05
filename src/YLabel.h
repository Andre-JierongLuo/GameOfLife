#ifndef _YLABEL_H_
#define _YLABEL_H_

#include "YComponent.h"

class YLabel : public YComponent{
public:
	string name;
	string txt;
	YLabel(const string& name, const string& txt);
	void paint();
	void paint(int x);
	void paint(string fname);
};


#endif /* _YLABEL_H_ */

