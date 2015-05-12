#pragma once
#include "ofMain.h"
#include "ofxMSAInteractiveObject.h"

class ofxDraggable : public ofxMSAInteractiveObject {
public:
	ofBaseDraws *content; // this will point to your image, video, grabber etc.
	ofxDraggable() {
		content = NULL;
		dragging = false;
		rotating=false;
		angle=lastAngle=0;
		lastWidth = 0;
		lastHeight =0;
		lastY = 0;
		resizing=false;
	}

	void onPress(int mx, int my, int button) {
		// save the offset of where the mouse was clicked...
		// ...relative to the position of the object
		rotateZone.set(x,y,width,10);
		resizeZone.set(x,y+height-10,width,10);
		if(rotateZone.inside(ofPoint(mx,my)))
		{
			rotating = true;
			lastAngle = angle;
		}else if(resizeZone.inside(ofPoint(mx,my)))
		{
			resizing = true;
			lastWidth = width;
			lastHeight = height;
			lastX = this->x;
			lastY = this->y;
		}else
		{
			dragging =true;
		}
		saveX = mx - this->x;
		saveY = my - this->y;
	}

	void onDragOver(int mx, int my, int button) {
		rotateZone.set(x,y,width,10);
		resizeZone.set(x,y+height-10,width,10);
		if(dragging){
			this->x = mx - saveX;    // update x position
			this->y = my - saveY;    // update mouse y position
		}else if(rotating)
		{
			angle =lastAngle+10*atan((mx - this->x - saveX)/height);
		}else if(resizing)
		{
			float pc = (mx - this->x - saveX)/2;
			width = lastWidth+pc;
			height = lastHeight + (pc*lastHeight/lastWidth);
			x = lastX - pc/2;
			y = lastY - (pc*lastHeight/lastWidth);
			anchor = ofPoint(this->width/2,this->height);
		}
	}

	void onDragOutside(int mx, int my, int button)
	{
		
	}
	
	void onRelease(int mx, int my, int button){
		dragging=false;
		rotating=false;
		resizing = false;
	}

	void onReleaseOutside(int x, int my, int button)
	{
		onRelease(x,y,button);
	}

	void draw() {
		ofPushStyle();
		ofPushMatrix();
			ofCircle(x+width/2,y+height,2);
			if(isMouseOver())
			{
				ofSetColor(ofColor::blue,100);
				ofRect(rotateZone);//rotation zone
				ofSetColor(ofColor::yellow,100);
				ofRect(resizeZone);
			}
		ofPopMatrix();
		ofPopStyle();
	}

	float getAngle(){ return angle;}
	ofPoint getAnchor(){ return anchor;}
	void setAngle(float a){ angle=a; }
protected:
	int saveX, saveY;
	bool dragging;
	bool rotating;
	bool resizing;
	float angle;
	float lastAngle;
	float lastWidth,lastHeight,lastX,lastY;
	ofRectangle rotateZone;
	ofRectangle resizeZone;
	ofPoint anchor;
	
	
};