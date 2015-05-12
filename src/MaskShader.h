#pragma once
#include "ofMain.h"

class MaskShader{
public:
	static MaskShader* getInstance(){
		if(instance==NULL)
			instance = new MaskShader();
		return instance;
	}

	ofShader shader;
	ofTexture mask;

	void loadTexture(string maskPath) {
		ofLoadImage(mask,maskPath);
	}
	
private:
	static MaskShader* instance;
	MaskShader()
	{
		//ofLoadImage(mask,"images/AR/mask2.png");
		string fullShaderPath = ofToDataPath("shaders/shader",false);
		ofDisableDataPath();
		shader.load(fullShaderPath);
		ofEnableDataPath();
	}
};
