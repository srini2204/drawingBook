#pragma once

#include "ofMain.h"
#include "DrawingBookConfig.h"
#include "MaskShader.h"

namespace DrawingBookApp
{

	class DrawingBook : public ofBaseApp{

	public:
		//from ofBaseApp
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		/*
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		*/

		//touch events
		void touchDown(ofTouchEventArgs &touch);
		void touchMoved(ofTouchEventArgs &touch);
		void touchUp(ofTouchEventArgs &touch);		
		void touchDoubleTap(ofTouchEventArgs &touch);
		void touchCancelled(ofTouchEventArgs &touch);

		//mouse events 
		void mouseMoved(ofMouseEventArgs &mouse);
		void mouseDragged(ofMouseEventArgs &mouse);
		void mousePressed(ofMouseEventArgs &mouse);
		void mouseReleased(ofMouseEventArgs &mouse); 

		//function to convert mouse events to touch, to test on non touch screen
		ofTouchEventArgs ofConvertMouseToTouch(ofMouseEventArgs &mouse);
		bool mouseToTouch;

		//map to store touches
		vector<ofPoint> touches;
	private:

		void guiEvent(string &e);
		void _willAppear();
		DrawingBookConfig* config;
		unsigned long long lastInteractionTimestamp;
		ofTexture backGround;
		bool debug;
		ofShader maskShader;
		void drawShaderLogic();
		ofTexture colourTexture;
		ofTexture alphaTexture;
		ofFbo characterFbo;
		ofTexture paintBrush;
		ofPoint paintBrushPoint;
	};
}
