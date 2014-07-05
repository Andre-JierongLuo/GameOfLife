#include "YWindow.h"
#include "YComponent.h"
#include "ContentPane.h"
#include "LifeModel.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

using namespace std;
const int Border = 5;


/*
 * Function to put out a message on error exits.
 */
void error( string str ) {
  cerr << str << endl;
  exit(0);
}

YWindow::YWindow() {
	this->init();
	this->eventloop();

	XCloseDisplay(this->display);

}

YWindow::~YWindow() {
}

/**
 * Initialize the window.
 */
void YWindow::init() {

	XSizeHints hints;
	unsigned long white, black;

   /*
	* Display opening uses the DISPLAY	environment variable.
	* It can go wrong if DISPLAY isn't set, or you don't have permission.
	*/
	this->display = XOpenDisplay( "" );
	if ( !this->display )	{
		error( "Can't open display." );
	}

   /*
	* Find out some things about the display you're using.
	*/
	this->screen = DefaultScreen( this->display );

	white = XWhitePixel( this->display, this->screen );
	black = XBlackPixel( this->display, this->screen );

	hints.x = 0;
	hints.y = 0;
	hints.width = 1000;
	hints.height = 650;
	hints.flags = PPosition | PSize;

	this->window = XCreateSimpleWindow(
		this->display,				// display where window appears
		DefaultRootWindow( this->display ), // window's parent in window tree
		hints.x, hints.y,			// upper left corner location
		hints.width, hints.height,	// size of the window
		Border,						// width of window's border
		black,						// window border colour
		white );					// window background colour

	XSetStandardProperties(
		this->display,		// display containing the window
		this->window,		// window whose properties are set
		"Game Of Life",		// window's title
		"Game Of Life",			// icon's title
		None,				// pixmap for the icon
		NULL, 0,			// applications command line args
		&hints );			// size hints for the window

	XSelectInput(	this->display,
					this->window,
					ButtonPressMask
					| ButtonReleaseMask
					| KeyPressMask
					| KeyReleaseMask
					| EnterWindowMask
					| LeaveWindowMask
					| StructureNotifyMask   // for resize events
		);

	/*
	 * Put the window on the screen.
	 */
	XMapRaised( this->display, this->window );

	XFlush(this->display);
	sleep(1);	// let server get set up before sending drawing commands

	/*
	 * Create Graphics Contexts
	 */
	this->gc = XCreateGC(this->display, this->window, 0, 0);
	XSetForeground(this->display, this->gc, BlackPixel(this->display, this->screen));
	XSetBackground(this->display, this->gc, WhitePixel(this->display, this->screen));
	//XSetFillStyle(this->display,this->gc,FillSolid);
	//XSetLineAttributes(this->display,this->gc,1,LineSolid,CapButt,JoinRound);


	//cout <<"set up cp" << endl;
	//this->lm->debug(0);
	this->cp = new ContentPane(this->display, this->window, this->gc);
}

/*
 * The loop responding to events from the user.
 */
void YWindow::eventloop() {
	XEvent event;

	//cout << "eventloop" << endl;

	while(true){
		if(XPending(this->display) > 0){
			XNextEvent(this->display, &event);
			switch( event.type ){
				case ConfigureNotify:
					this->paint();
				break;
				case Expose:
					this->paint();
				break;
				case KeyPress:
					handleKeyPress(event);
				break;
				case ButtonPress:
					handleButtonEvent(event);
				break;
				case ButtonRelease:
					handleButtonEvent(event);
				break;
			}
		}

		if((this->cp)->running){
			this->cp->autoRun();
			usleep(1000000/(this->cp->FPS + 1));
		}

		usleep(1000000/30);

		XFlush(this->display);
	}

}


void YWindow::paint() {
	this->cp->paint();
}

void YWindow::handleKeyPress(XEvent &event){
	KeySym key;
	char text[10];
	int i = XLookupString((XKeyEvent *)&event,
			text,
			10,
			&key,
			NULL);

	if( i == 1 ){
		cout << "Got key press -- " << text[0] << endl;
		if(text[0] == 'q'){
			error("Terminating normally.");
		}
	}
}

void YWindow::handleButtonEvent(XEvent &event){
	//cout << "handel event" << endl;
	(this->cp)->HandelEvent(event);
}

