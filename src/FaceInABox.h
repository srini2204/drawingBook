#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxDraggable.h"
#include "FaceInABoxFace.h"

namespace JunglePuz{

	/**
	*	\brief Implements the draggable spritesheets that is drawn around the users' face.
	*/
	class FaceInABox: public ofxDraggable{
	public:
		FaceInABox():debug(false){
			disableAllEvents();
		}
		virtual ~FaceInABox(){}
		void setup(string spriteSheetPath)
		{
			sheet = ofPtr<tkm9::ofxSpriteSheet>(new tkm9::ofxSpriteSheet());
			sheet->setup("suit",spriteSheetPath);
			sprite = sheet->generateSprite("helmet");
			sprite->setClipAndPlay("show");
			this->setSize(sprite->getWidth(),sprite->getHeight());
		}

		void setDebug(bool d){ 
			debug=d;
			face.setDebug(debug);
		}
		void update()
		{
			if(!enabled) return;
			sprite->update();
			if(this->getPosition() != sprite->getPosition())
				sprite->setPosition(this->getPosition());
		}
		void draw()
		{
			if(!enabled) return;
			ofPushMatrix();
			ofPushStyle();
			{
			
				ofTranslate(anchor+getPosition());
				ofRotate(angle);
				ofTranslate(-anchor-getPosition());
				ofNoFill();
				if(drawUserFace)
				{
					ofPushMatrix();
					{
						ofTranslate(this->getPosition());
						face.draw();
					}
					ofPopMatrix();
				}
				sprite->draw();
			
				if(debug)
				{
					ofPushMatrix();
					{
						ofTranslate(this->getPosition());
						face.drawDebug();
					}
					ofPopMatrix();
					ofSetColor(ofColor::red);
					ofRect(*this);
					ofCircle(this->getPosition()+anchor,5);
					ofLine(this->getTopLeft(),this->getBottomRight());
					ofLine(this->getBottomLeft(),this->getTopRight());
				}
			}
			ofPopStyle();
			ofPopMatrix();
			if(debug)
				ofxDraggable::draw();

		}
		void reset()
		{
			drawUserFace = true;
		}
		void defaultFace()
		{
			drawUserFace = false;
		}
		FaceInABoxFace face;
	private:
		bool debug;
		bool drawUserFace;
	};

}