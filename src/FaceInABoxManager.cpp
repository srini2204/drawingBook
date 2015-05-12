#include "FaceInABoxManager.h"
#include "maskShader.h"

using namespace DrawingBookApp;

FaceInABoxManager* FaceInABoxManager::instance=NULL;

FaceInABoxManager* FaceInABoxManager::getInstance()
{
	if(!instance)
	{
		instance = new FaceInABoxManager();
	}
	return instance;
}

void FaceInABoxManager::loadXml(ofxXmlSettings& _xml)
{
	FaceInABoxManager* instance = getInstance();
	instance->xml = &_xml;
	if(instance->xml->tagExists("faceinaboxes"))
	{
		instance->xml->pushTag("faceinaboxes");
		{
			int numfaceInABoxes = instance->xml->getNumTags("faceinabox");
			for(int i=0; i<numfaceInABoxes;++i)
			{
				instance->faceInABoxes.push_back(FaceInABox());
				float x = instance->xml->getAttribute("faceinabox","x",0,i);
				float y = instance->xml->getAttribute("faceinabox","y",0,i);
				float scale = instance->xml->getAttribute("faceinabox","scale",1.0f,i);
				float angle = instance->xml->getAttribute("faceinabox","angle",0.0f,i);
				string fileName = instance->xml->getAttribute("faceinabox","file","",i);
				if(fileName!="")
				{
					//ofImage* image = new ofImage(fileName);
					if(true)
					{
						//instance->spaceSuits.back().setPosAndSize(x,y,scale*image->getWidth(),scale*image->getHeight());
						instance->faceInABoxes.back().setup(fileName);
						instance->faceInABoxes.back().setPosition(x,y);
						instance->faceInABoxes.back().setAngle(angle);
						//instance->spaceSuits.back().setContent(image);
						instance->faceInABoxes.back().enabled = true;
					}
				}
				//face
				instance->xml->pushTag("faceinabox",i);
				{
					if(instance->xml->tagExists("faceRectangle"))
					{
						float face_x = instance->xml->getAttribute("faceRectangle","x",0);
						float face_y = instance->xml->getAttribute("faceRectangle","y",0);
						float face_w = instance->xml->getAttribute("faceRectangle","width",0);
						float face_h = instance->xml->getAttribute("faceRectangle","height",0);
						float face_angle =  instance->xml->getAttribute("faceRectangle","angle",0);
						instance->faceInABoxes.back().face.set(face_x,face_y,face_w,face_h);
						instance->faceInABoxes.back().face.setAngle(face_angle);
					}
					if(instance->xml->tagExists("maskImage"))
					{
						string maskPath = instance->xml->getValue("maskImage", "");
						instance->faceInABoxes.back().face.setMaskPath(maskPath);
					}
				}
				instance->xml->popTag();
			}
		}
		instance->xml->popTag();
	}
	instance->faceDetected = vector<bool>(instance->faceInABoxes.size(),false);
}

void FaceInABoxManager::update()
{
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i).update();
	}

	/*if(debug)
	{
		for(int i=0; i<faceInABoxes.size();++i)
		{
			if(faceDetected.at(i)==false)
				faceInABoxes.at(i).defaultFace();
		}
	}*/
}

void FaceInABoxManager::draw()
{
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i).draw();
	}
}

void FaceInABoxManager::mouseMoved(int x, int y )
{
	if(!debug) return;
	ofMouseEventArgs e;
	e.x = x;
	e.y = y;
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i)._mouseMoved(e);
	}
}
void FaceInABoxManager::mouseDragged(int x, int y, int button)
{
	if(!debug) return;
	ofMouseEventArgs e;
	e.x = x;
	e.y = y;
	e.button = button;
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i)._mouseDragged(e);
	}
}
void FaceInABoxManager::mousePressed(int x, int y, int button)
{
	if(!debug) return;
	ofMouseEventArgs e;
	e.x = x;
	e.y = y;
	e.button = button;
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i)._mousePressed(e);
	}
}
void FaceInABoxManager::mouseReleased(int x, int y, int button)
{
	if(!debug) return;
	ofMouseEventArgs e;
	e.x = x;
	e.y = y;
	e.button = button;
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i)._mouseReleased(e);
	}
}

void FaceInABoxManager::save()
{
	xml->pushTag("params");
	{
		if(xml->tagExists("faceinaboxes"))
		{
			xml->pushTag("faceinaboxes");
			{
				for(int i=0; i<faceInABoxes.size(); ++i)
				{
					xml->setAttribute("faceinabox","x",faceInABoxes.at(i).getPosition().x,i);
					xml->setAttribute("faceinabox","y",faceInABoxes.at(i).getPosition().y,i);
					xml->setAttribute("faceinabox","angle",faceInABoxes.at(i).getAngle(),i);
					xml->setAttribute("faceinabox","scale",faceInABoxes.at(i).getWidth()/faceInABoxes.at(i).sprite->getWidth(),i);
					xml->pushTag("faceinabox",i);
					{ 
						xml->setAttribute("faceRectangle","x",faceInABoxes.at(i).face.getPosition().x,0);
						xml->setAttribute("faceRectangle","y",faceInABoxes.at(i).face.getPosition().y,0);
						xml->setAttribute("faceRectangle","width",faceInABoxes.at(i).face.getWidth(),0);
						xml->setAttribute("faceRectangle","height",faceInABoxes.at(i).face.getHeight(),0);
					}
					xml->popTag();
				}
			}
			xml->popTag();
		}
	}
	xml->popTag();
	xml->saveFile();
}

void FaceInABoxManager::keyPressed(int key)
{
	switch(key)
	{
	case('d'):
		debug = !debug;
		for(int i=0; i<faceInABoxes.size();++i)
		{
			faceInABoxes.at(i).setDebug(debug);
		}
		break;
	case('s'):
		save();
		break;
	case(OF_KEY_LEFT):
	case(OF_KEY_RIGHT):
	case(OF_KEY_UP):
	case(OF_KEY_DOWN):
	case('4'):
	case('6'):
	case('8'):
	case('2'):
		for(int i=0; i<faceInABoxes.size();++i)
		{
			if(faceInABoxes.at(i).isMouseOver())
				faceInABoxes.at(i).face.keyPressed(key);
		}
		break;
	}
}

void FaceInABoxManager::setFaces(ofTexture* tex,vector<ofRectangle>& rect, bool mirrorX)
{
	
	if(rect.size()==0)
	{
		for(int i=0; i<faceInABoxes.size();++i)
		{
			faceInABoxes.at(i).enabled = true;
			if(i < faceRectangles.size())
			{
				faceInABoxes.at(i).face.setTex(tex,faceRectangles.at(i),mirrorX);
			}else
				faceInABoxes.at(i).face.setTex(tex,ofRectangle(0.4,0.4,0.2,0.2*tex->getWidth()/tex->getHeight()),mirrorX);
			faceDetected.at(i) = false;
		}
	}else
	{
		//enable the faceInABoxes which have a face
		for(int i=0; i<min(faceInABoxes.size(),rect.size());++i)
		{
			faceInABoxes.at(i).enabled = true;
			faceInABoxes.at(i).face.setTex(tex,rect.at(i),mirrorX);
			
			while((i+1)>faceRectangles.size())
			{
				faceRectangles.push_back(ofRectangle());
			}
			
			faceRectangles.at(i) = rect.at(i);
			faceDetected.at(i) = true;
		}
		for(int i = rect.size(); i<faceInABoxes.size();++i)
		{
			faceDetected.at(i) = false;
		}
	}

}

void FaceInABoxManager::reset()
{
	for(int i=0; i<faceInABoxes.size();++i)
	{
		faceInABoxes.at(i).reset();
	}
}
void FaceInABoxManager::prepareSnapshot()
{
	for(int i=0; i<faceInABoxes.size();++i)
	{
		if(faceDetected.at(i)==false)
			faceInABoxes.at(i).defaultFace();
	}
}