#ifndef YWINDOW_H_
#define YWINDOW_H_

#include <list>
#include "YComponent.h"
#include "ContentPane.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "LifeModel.h"

using namespace std;


class YWindow {
public:
	YWindow();
	virtual ~YWindow();

    void paint();
    void setContentPane(ContentPane *cp);
private:
    void init();
    void eventloop();
    Display	 *display;
	int		 screen;
	Window	 window;
	GC		 gc;

	ContentPane* cp;

	void handleKeyPress(XEvent &event);
	void handleButtonEvent(XEvent &event);
};

#endif /* YWINDOW_H_ */

