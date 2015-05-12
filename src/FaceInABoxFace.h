#pragma once

#include "ofMain.h"
#include "ofxDraggable.h"
#include "maskShader.h"

namespace DrawingBookApp{
	
	/**
	*	\brief		Implements the users' face inside the space suit
	*	\details	Uses a mask shader to crop the face rectangle into a circle	
	*/
	class FaceInABoxFace : public ofRectangle{
	public:

		/**
		*	\brief	Get a pointer to the mask shader
		*/
		FaceInABoxFace():debug(false),tex(NULL),mirrorX(false){
			//maskShader = MaskShader::getInstance();
			angle = 0;
		}
		void setDebug(bool d)
		{
			debug = d;
		}
		void draw()
		{
			ofPushMatrix();
			if(tex)
			{
				
				//mask shader
				ofRectangle rect(this->x,this->y,this->width,this->height);

				ofTranslate(rect.x+rect.width/2,rect.y+rect.height/2);
				ofRotate(angle);
				ofTranslate(-rect.width/2,-rect.height/2);
				ofTexture &colourTexture = *tex;
				//ofTexture &alphaTexture = maskShader->mask;
				maskShader->loadTexture(maskPath);
				ofTexture &alphaTexture = maskShader->mask;
				maskShader->shader.begin();

				maskShader->shader.setUniformTexture("tex0", colourTexture, 0);
				maskShader->shader.setUniformTexture("tex1", alphaTexture, 1);
				if(mirrorX)
				{
					glBegin(GL_QUADS);
					{
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*(texRectPct.x+texRectPct.width), colourTexture.getHeight()*texRectPct.y);
						glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
						glVertex2f(0, 0);
					
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*texRectPct.x, colourTexture.getHeight()*texRectPct.y);
						glMultiTexCoord2f(GL_TEXTURE1, alphaTexture.getWidth(), 0);
						glVertex2f(0 + rect.width, 0);
				
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*texRectPct.x,colourTexture.getHeight()*(texRectPct.y+texRectPct.height));
						glMultiTexCoord2f(GL_TEXTURE1, alphaTexture.getWidth(), alphaTexture.getHeight());
						glVertex2f(0 + rect.width, 0 + rect.height);
			
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*(texRectPct.x+texRectPct.width), colourTexture.getHeight()*(texRectPct.y+texRectPct.height));
						glMultiTexCoord2f(GL_TEXTURE1, 0, alphaTexture.getHeight());
						glVertex2f(0,0 + rect.height);
					}
					glEnd();
				}else
				{
					glBegin(GL_QUADS);
					{
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*texRectPct.x, colourTexture.getHeight()*texRectPct.y);
						glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
						glVertex2f(rect.x, rect.y);
			
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*(texRectPct.x+texRectPct.width), colourTexture.getHeight()*texRectPct.y);
						glMultiTexCoord2f(GL_TEXTURE1, alphaTexture.getWidth(), 0);
						glVertex2f(rect.x + rect.width, rect.y);
			
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*(texRectPct.x+texRectPct.width), colourTexture.getHeight()*(texRectPct.y+texRectPct.height));
						glMultiTexCoord2f(GL_TEXTURE1, alphaTexture.getWidth(), alphaTexture.getHeight());
						glVertex2f(rect.x + rect.width, rect.y + rect.height);
			
						glMultiTexCoord2f(GL_TEXTURE0, colourTexture.getWidth()*texRectPct.x,colourTexture.getHeight()*(texRectPct.y+texRectPct.height));
						glMultiTexCoord2f(GL_TEXTURE1, 0, alphaTexture.getHeight());
						glVertex2f(rect.x, rect.y + rect.height);
					}
					glEnd();
				}
			
				maskShader->shader.end();
			}
			ofPopMatrix();
		}
		void drawDebug()
		{
			ofSetColor(ofColor::red);
			ofRect(*this);
			ofLine(this->getTopLeft(),this->getBottomRight());
			ofLine(this->getBottomLeft(),this->getTopRight());
		}

		/**
		*	\brief	Allows to change the geometry & position using the keyboard
		*	\details Use 4 and 8 keys to size down, 6 and 2 to size up, and arrow keys to position.
		*/
		void keyPressed(int key)
		{
			switch(key)
			{
			case('4'): this->width--;
				break;
			case('6'):this->width++;
				break;
			case('2'):this->height++;
				break;
			case('8'):this->height--;
				break;
			case(OF_KEY_LEFT): this->x--;
				break;
			case(OF_KEY_RIGHT):this->x++;
				break;
			case(OF_KEY_UP):this->y--;
				break;
			case(OF_KEY_DOWN):this->y++;
			}
		}

		/**
		*	\brief	Set the texture and subsection that will be rendered inside its rectangle.
		*	\details		Normally this texture is a camera feed and the subsection is the rectangle (in pct of the texture)
		*					that contains the face.
		*	\param	_tex	A pointer to the texture
		*	\param _texRectPct	An ofRectangle object that defines a face boundaries on the texture passed. Expressed in percent
		*						of the texture size. So (0.5,0.5,0.1,0.1) represents a rectangle positioned at the center of the texture
		*						and which width and height are 10% respectively of the texture width and height.
		*	\param	mirrorX		Allows to mirror the x axis of the texture (symetry along the y axis).
		*	\param	maskPath	specifies the file path of the masking image file
		*/
		void setTex(ofTexture* _tex,ofRectangle& _texRectPct,bool mirrorX)
		{
			tex = _tex;
			texRectPct.width = ofLerp(texRectPct.width,_texRectPct.width,0.5);
			texRectPct.height = ofLerp(texRectPct.height,_texRectPct.height,0.5);
			texRectPct.position.interpolate(_texRectPct.position,0.5);
			this->mirrorX = mirrorX;
			maskShader = MaskShader::getInstance();
		}

		void setAngle(float a)
		{
			angle = a;
		}

		void setMaskPath(string path) {
			maskPath = path;
		}
	
	protected:
		bool debug;
		ofTexture* tex;
		ofRectangle texRectPct;
		MaskShader* maskShader;
		string maskPath;
		bool mirrorX;
		float angle;
	};
	
}