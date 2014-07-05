#ifndef _CONTENTPANE_H_
#define _CONTENTPANE_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "YComponent.h"
#include "YPanel.h"
#include "YButton.h"
#include "YLabel.h"
#include "YSlider.h"
#include "YLifeGraphics.h"
#include "LifeModel.h"
#include <stdio.h>
#include "dirent.h"
#include <vector>

class ContentPane : public YPanel, ActionListener{
public:
	YPanel* GraphicsPanel;
	YPanel* ButtonPanel;
	YPanel* SliderPanel;
	YPanel* StartupPanel;
	YButton* start;
	YButton* forward;
	YButton* play;
	YButton* backward;
	YButton* end;
	YButton* nextFile;
	YButton* startGame;
	YButton* save;
	YSlider* GenSlider;
	YSlider* SpeedSlider;
	YLabel* GenLabel;
	YLabel* SpeedLabel;
	YLabel* CurrentLabel;
	YLabel* CurrentModelLabel;
	YLabel* Label1;
	YLifeGraphics* LifeGraphics;
	YComponent* Focus;

	DIR *dir;
	struct dirent *ent;
	vector<string> filename;
	int fileID;

	bool isSet;
	bool running;
	bool isEditing;
	int FPS;

	LifeModel* lm;

	ContentPane(Display* display, Window window, GC gc);
	void ActionPerformed(YComponent* c);
	YComponent* getMouseFocus();
	void resetFocus();
	void setFocus(YComponent* c);
	void setFPS(int x);
	void autoRun();
};

#endif

