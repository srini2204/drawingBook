#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "FaceInABox.h"

namespace DrawingBookApp{

	/**
	*	\brief Manages the different SpaceSuit objects.
	*	\details	(Singleton) Takes care of the following:
	*				\li	Instantiate the SpaceSuit objects based on an XML file
	*				\li	Transfer the update/draw/mouse/key events to the SpaceSuit objects
	*				\li	Save the SpaceSuit objects data (position, size, etc.) to the same XML file
	*				\li Assign face rectangles to the SpaceSuit objects
	*/
	class FaceInABoxManager{
	public:

		/**
		*	\brief Singleton stuff
		*/
		static FaceInABoxManager* getInstance();

		/**
		*	\brief Load SpaceSuit data from an XML object.
		*/
		static void loadXml(ofxXmlSettings& _xml);

		void draw();
		void update();
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void keyPressed(int key);
		bool isDebug(){return debug;}

		/**
		*	\brief Save the SpaceSuit objects' details into the XML file
		*/
		void save();

		/**
		*	\brief Set the feed texture and the vector of rectangles that define faces
		*/
		void setFaces(ofTexture* tex,vector<ofRectangle>& rectPct, bool mirrorX=false);

		/**
		*	\brief Propagate the reset to each SpaceSuit object
		*/
		void reset();

		/**
		*	\brief Notify each SpaceSuit object that isn't currently assigned to a face to display an alien face instead.
		*/
		void prepareSnapshot();
	private:
		FaceInABoxManager():debug(false){};
		static FaceInABoxManager* instance;
		ofxXmlSettings* xml;
		vector<FaceInABox> faceInABoxes;
		vector<ofRectangle> faceRectangles;
		bool debug;
		vector<bool> faceDetected;
	};

}