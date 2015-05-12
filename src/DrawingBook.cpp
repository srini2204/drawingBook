#include "DrawingBook.h"

using namespace DrawingBookApp;

#define X 100
#define Y 300
#define W 260
#define H 260

void DrawingBook::setup(){

	config = DrawingBookConfig::getInstance();
	if(config->isLoaded()==false)
		config->loadSettings("xml/parameters.xml");

	//background
	ofLoadImage(backGround, config->app_background_image);

	debug= false;
	ofRegisterTouchEvents(this);
	_willAppear();
	mouseToTouch = true;

	ofLoadImage(colourTexture, "images/CharacterImages/Masks 2.png");
	ofLoadImage(alphaTexture, "images/CharacterMasks/Masks 2.png");
	ofLoadImage(paintBrush, "images/Particle.png");
	paintBrush.setAnchorPercent(0.5f, 0.5f);
	maskShader.load("shaders/shader");

	characterFbo.allocate(400, 400, GL_RGBA);
	characterFbo.begin();
    ofClear(0,0,0,255);
    characterFbo.end();
}

void DrawingBook::_willAppear() {
	lastInteractionTimestamp = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void DrawingBook::update() {

	characterFbo.begin();
    ofClear(0, 0, 0,255);
    maskShader.begin();

    maskShader.setUniformTexture("tex0", colourTexture , 1 );
    maskShader.setUniformTexture("tex1", alphaTexture, 2 );
	maskShader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
	
	/*ofPushStyle();
	ofSetColor(config->countdown_colour);
	colourTexture.draw(0,0);
    ofDrawBitmapString("Final FBO mouse location (" + ofToString(mouseX) + ", " + ofToString(mouseY) + ")", 10, 200);
	ofPopStyle();*/
    
    maskShader.end();
    characterFbo.end();
	paintBrushPoint.x = mouseX;
	paintBrushPoint.y = mouseY;
}

//--------------------------------------------------------------
void DrawingBook::draw(){
	ofEnableAlphaBlending();
	backGround.draw(0,0);

	/*static ofRectangle texRectPct = ofRectangle(X, Y, W, H);
	static ofRectangle rect(X, Y, W, H);*/

	characterFbo.draw(0, 0);
    //ofDrawBitmapString("Final FBO", 320+10+30,240*2+15+30);
	
	//draw the touch points
	ofSetColor(config->countdown_colour);
	for(int i = 0; i<touches.size(); i++)
	{
		//ofCircle(touches.at(i), 5);
		paintBrush.draw(touches.at(i));
	}

	if(debug)
	{
		unsigned int timeout = (config->inactivity_timeout_ms - (ofGetElapsedTimeMillis()-lastInteractionTimestamp))/1000;
		ofDrawBitmapStringHighlight(ofToString(timeout),200,10);
		ofDrawBitmapStringHighlight(ofToString(touches.size()),250,10);
	}
}

void DrawingBook::drawShaderLogic() {

}

//--------------------------------------------------------------
void DrawingBook::keyPressed(int key){
	if(key == 'd')
	{
		debug = !debug;
	}else if (key == 'f')
	{
		ofToggleFullscreen();
	}else if (key == 'c')
	{
		touches.clear();
	}else if (key == 'z')
	{
		if(!touches.empty()) {
			touches.pop_back();
		}
	}
}

//--------------------------------------------------------------
void DrawingBook::keyReleased(int key){

}

// scenes event callback: allows scenes to send messages
// (e.g. scene is done, move to next scene)
void DrawingBook::guiEvent(string &e) {

}

//--------------------------------------------------------------
void DrawingBook::mouseDragged(ofMouseEventArgs &mouse){
	if(mouseToTouch) 
	{
		touchMoved(ofConvertMouseToTouch(mouse));
	}
}

//--------------------------------------------------------------
void DrawingBook::mousePressed(ofMouseEventArgs &mouse){
	if (mouseToTouch)
	{
		touchDown(ofConvertMouseToTouch(mouse));
	}
}

//--------------------------------------------------------------
void DrawingBook::mouseReleased(ofMouseEventArgs &mouse){
	if (mouseToTouch)
	{
		touchUp(ofConvertMouseToTouch(mouse)); 
	}
}

//--------------------------------------------------------------
void DrawingBook::mouseMoved(ofMouseEventArgs &mouse){

}

void DrawingBook::touchDown(ofTouchEventArgs& touch){
	touches.push_back(ofPoint(touch.x,touch.y));
	lastInteractionTimestamp = ofGetElapsedTimeMillis();
}

void DrawingBook::touchMoved(ofTouchEventArgs& touch){
	touches.push_back(ofPoint(touch.x,touch.y));
	lastInteractionTimestamp = ofGetElapsedTimeMillis();
}

void DrawingBook::touchUp(ofTouchEventArgs& touch){
	//touches.clear();
	lastInteractionTimestamp = ofGetElapsedTimeMillis();
}


//--------------------------------------------------------------
void DrawingBook::touchDoubleTap(ofTouchEventArgs &touch){  

}

//--------------------------------------------------------------
void DrawingBook::touchCancelled(ofTouchEventArgs &touch){    

}


ofTouchEventArgs DrawingBook::ofConvertMouseToTouch(ofMouseEventArgs &mouse) {

	ofTouchEventArgs touch;
	touch.x = mouse.x;
	touch.y = mouse.y;
	touch.id = mouse.button;

	return touch;
}