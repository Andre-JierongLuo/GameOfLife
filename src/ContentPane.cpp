#include "ContentPane.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "Life.h"
#include "YComponent.h"
#include "YPanel.h"
#include "YButton.h"
#include "YLabel.h"
#include "YSlider.h"
#include "ActionListener.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "dirent.h"

using namespace std;

ContentPane::ContentPane(Display* display, Window window, GC gc):YPanel("ContentPane"){
	this->display = display;
	this->window = window;
	this->gc = gc;
	this->isSet = false;
	this->isEditing = false;
	this->fileID = 0;

	if((this->dir = opendir("./patterns/")) != NULL){
		int i = 0;
		while((this->ent = readdir(this->dir)) != NULL){
			if(i < 2){
				i++;
				continue;
			}
			string cn = string(ent->d_name);
			this->filename.push_back(cn);
		}
		closedir(this->dir);
	} else {
		cerr << "can't open dir" << endl;
		exit(0);
	}


	//this->lm = (*(this->listOfLife.begin()));
	this->Focus = NULL;
	this->running = false;
	this->FPS = 0;

	this->setParameters(0,0,1000,650);

	// GraphicsPanel with (300, 0, 700, 650);
	this->GraphicsPanel = new YPanel("GraphicsPanel");
	this->GraphicsPanel->setParameters(300,0,700,650);
	this->AddComponent(this->GraphicsPanel);
	this->GraphicsPanel->setTop(this);


	// CurrentLabel with (350, 50, 100, 50);
	this->CurrentLabel = new YLabel("CurrentLabel", "GEN  1 / 1000");
	this->CurrentLabel->setParameters(550,30,200,30);
	this->GraphicsPanel->AddComponent(this->CurrentLabel);
	this->CurrentLabel->setTop(this);

	//cout << "CurrentLabel is set" << endl;

	this->LifeGraphics = new YLifeGraphics("LifeGraphics");
	this->LifeGraphics->setParameters(400,70,560,560);
	this->GraphicsPanel->AddComponent(this->LifeGraphics);
	this->LifeGraphics->setTop(this);
	this->LifeGraphics->AddActionListener(this);

	//cout << "LifeGraphics is set" << endl;


	// ButtonPanel with (0,0,300,110)
	this->ButtonPanel = new YPanel("ButtonPanel");
	this->ButtonPanel->setParameters(0,0,300,110);
	this->AddComponent(this->ButtonPanel);
	this->ButtonPanel->setTop(this);

	// start button with (50, 70, 30, 30);
	this->start = new YButton("start");
	this->start->setParameters(50,70,30,30);
	this->ButtonPanel->AddComponent(this->start);
	this->start->setTop(this);
	this->start->AddActionListener(this);

	// backward button with (100, 70, 30, 30);
	this->backward = new YButton("backward");
	this->backward->setParameters(100,70,30,30);
	this->ButtonPanel->AddComponent(this->backward);
	this->backward->setTop(this);
	this->backward->AddActionListener(this);

	// play button with (150, 70, 30, 30);
	this->play = new YButton("play");
	this->play->setParameters(150,70,30,30);
	this->ButtonPanel->AddComponent(this->play);
	this->play->setTop(this);
	this->play->AddActionListener(this);

	// forward button with (100, 70, 30, 30);
	this->forward = new YButton("forward");
	this->forward->setParameters(200,70,30,30);
	this->ButtonPanel->AddComponent(this->forward);
	this->forward->setTop(this);
	this->forward->AddActionListener(this);

	// end button with (250, 70, 30, 30);
	this->end = new YButton("end");
	this->end->setParameters(250,70,30,30);
	this->ButtonPanel->AddComponent(this->end);
	this->end->setTop(this);
	this->end->AddActionListener(this);

	// SliderPanel with (0,150,300,200);
	this->SliderPanel = new YPanel("SliderPanel");
	this->SliderPanel->setParameters(0,120,300,200);
	this->AddComponent(this->SliderPanel);
	this->SliderPanel->setTop(this);

	// GenLabel with (50, 150, 50, 30);
	this->GenLabel = new YLabel("GenLabel", "GEN");
	this->GenLabel->setParameters(50,150,40,30);
	this->SliderPanel->AddComponent(this->GenLabel);

	// GenSlider with (100, 350, 140, 30)
	this->GenSlider = new YSlider("GenSlider");
	this->GenSlider->setParameters(80,130,140,30);
	this->SliderPanel->AddComponent(this->GenSlider);
	this->GenSlider->setTop(this);
	this->GenSlider->AddActionListener(this);

	// SpeedLabel with (50, 200, 50, 30)
	this->SpeedLabel = new YLabel("SpeedLabel", "SPEED");
	this->SpeedLabel->setParameters(50,200,40,30);
	this->SliderPanel->AddComponent(this->SpeedLabel);

	// SpeedSlider with (100, 200, 140, 30)
	this->SpeedSlider = new YSlider("SpeedSlider");
	this->SpeedSlider->setParameters(80,180,140,30);
	this->SliderPanel->AddComponent(this->SpeedSlider);
	this->SpeedSlider->setTop(this);
	this->SpeedSlider->AddActionListener(this);

	this->StartupPanel = new YPanel("StartupPanel");
	this->StartupPanel->setParameters(0,350,300,300);
	this->AddComponent(this->StartupPanel);
	this->StartupPanel->setTop(this);

	this->Label1 = new YLabel("Label1", "Choose a file to play!");
	this->Label1->setParameters(50,350,100,30);
	this->StartupPanel->AddComponent(this->Label1);

	this->CurrentModelLabel = new YLabel("CurrentModelLabel", "SELECTION : " + this->filename.at(0));
	this->CurrentModelLabel->setParameters(50,380,100,30);
	this->StartupPanel->AddComponent(this->CurrentModelLabel);

	this->nextFile = new YButton("nextFile");
	this->nextFile->setParameters(50,400,100,30);
	this->StartupPanel->AddComponent(this->nextFile);
	this->nextFile->setTop(this);
	this->nextFile->AddActionListener(this);

	this->startGame = new YButton("startGame");
	this->startGame->setParameters(180,400,100,30);
	this->StartupPanel->AddComponent(this->startGame);
	this->startGame->setTop(this);
	this->startGame->AddActionListener(this);

	this->save = new YButton("save");
	this->save->setParameters(180,500,100,30);
	this->StartupPanel->AddComponent(this->save);
	this->save->setTop(this);
	this->save->AddActionListener(this);

}

void ContentPane::ActionPerformed(YComponent* c){
	//cout << "ActionPerformed: "  << c->name << endl;
	string name = c->name;
	if(this->isSet && !(this->isEditing)){
		if(name == "forward"){
			(this->lm)->forward();
			(this->LifeGraphics)->paint(this->isSet);
		}
		else if(name == "backward"){
			(this->lm)->back();
			(this->LifeGraphics)->paint(this->isSet);
		}
		else if(name == "start"){
			(this->lm)->beginning();
			(this->LifeGraphics)->paint(this->isSet);
		}
		else if(name == "end"){
			this->running = false;
			(this->lm)->end();
			(this->LifeGraphics)->paint(this->isSet);
			(this->play)->paint(this->running);
		}
		else if(name == "play"){
			if(this->running){
				this->running = false;
			} else {
				this->running = true;
			}
			(this->play)->paint(this->running);
		}
		else if(name == "GenSlider"){
			this->GenSlider->paint();
			double num = NUM_GENERATIONS / 100 * (this->GenSlider->getCurValue());
			(this->lm)->gotoGen(num);
			(this->LifeGraphics)->paint(this->isSet);

		} else {}
		this->CurrentLabel->paint((this->lm)->generationNum() + 1);
		this->GenSlider->setCurValue((this->lm)->generationNum() / 10);
		this->GenSlider->paint();
	}
	if(name == "SpeedSlider"){
		int num = this->SpeedSlider->getCurValue();
		this->SpeedSlider->paint();
		this->setFPS(num);
	}
	if(name == "nextFile"){
		int id = this->fileID;
		if( id+1 == this->filename.size()){
			id = 0;
		} else {
			id++;
		}
		this->fileID = id;
		this->CurrentModelLabel->paint(this->filename.at(this->fileID));
	}
	if(name == "startGame"){
		this->running = false;
		this->isEditing = false;
		this->isSet = false;
		delete this->lm;
		this->lm = NULL;
		this->lm = new LifeModel(this->filename.at(this->fileID),0,0);
		this->LifeGraphics->setLifeModel(this->lm);
		this->isSet = true;
		this->LifeGraphics->paint(this->isSet);
		this->CurrentLabel->paint((this->lm)->generationNum() + 1);
		this->GenSlider->setCurValue((this->lm)->generationNum() / 10);
		this->GenSlider->paint();
		(this->play)->paint(this->running);
	}
	if(name == "LifeGraphics"){
		//cout << this->LifeGraphics->px << "," << this->LifeGraphics->py << endl;
		if(this->isEditing){
		}
		else {
			if(this->isSet){
				this->running = false;
				(this->play)->paint(this->running);
			} else {
				this->LifeGraphics->generation = new Generation(0);
			}
			this->isEditing = true;
		}
		((this->LifeGraphics)->generation)->changeLife(this->LifeGraphics->py, this->LifeGraphics->px);
		this->LifeGraphics->paint(1);
	}
	if(name == "save"){
		//cout << "try to save" << endl;
		this->running = false;
		(this->play)->paint(this->running);
		((this->LifeGraphics)->generation)->saveTOFile();
		this->isEditing = false;
	}
}

YComponent* ContentPane::getMouseFocus(){
	return this->Focus;
}

void ContentPane::resetFocus(){
	this->Focus = NULL;
	//cout << "Focus reset" << endl;
}

void ContentPane::setFocus(YComponent* c){
	this->Focus = c;
	//cout << "set focus to "<< c->name << endl;
}

void ContentPane::autoRun(){
	if((this->lm)->generationNum() == NUM_GENERATIONS - 1) this->running = false;
	(this->lm)->forward();
	(this->LifeGraphics)->paint(this->isSet);
	this->CurrentLabel->paint((this->lm)->generationNum() + 1);
	this->GenSlider->setCurValue((this->lm)->generationNum() / 10);
	this->GenSlider->paint();
	this->play->paint(this->running);
}

void ContentPane::setFPS(int x){
	this->FPS = x;
}

