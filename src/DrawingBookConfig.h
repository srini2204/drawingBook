#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

namespace DrawingBookApp{

	/**
	*	\brief	(Singleton) Manages all the game's parameters
	*/
	class DrawingBookConfig{
	public:
		//singleton
		static DrawingBookConfig* getInstance();

		//parameters
		unsigned int inactivity_timeout_ms;
		unsigned int game_duration_ms;
		unsigned int game_over_timeout;
		unsigned int precountdown_duration_ms;
		unsigned int countdown_duration_ms;
		unsigned int face_rectangle_v_margin_px;
		unsigned int face_rectangle_h_margin_px;
		unsigned int face_min_width_px;
		ofColor countdown_colour;
		
		//load
		void loadSettings(string path);
		bool isLoaded();

		//app details
		string app_name;
		string app_background_image;
		string app_foreground_image;
		string app_splash_video;
		//app details

	private:
		DrawingBookConfig():loaded(false),
						inactivity_timeout_ms(20000),
						countdown_duration_ms(3000),
						countdown_colour(ofColor(255,255,255,128)),
						game_duration_ms(30000),
						game_over_timeout(5000),
						precountdown_duration_ms(5000),
						face_rectangle_v_margin_px(0),
						face_rectangle_h_margin_px(0),
						face_min_width_px(50)
		{};
		bool loaded;
		static DrawingBookConfig* instance;
		ofxXmlSettings xml;
	};
}
