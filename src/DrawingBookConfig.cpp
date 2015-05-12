#include "DrawingBookConfig.h"

using namespace DrawingBookApp;

DrawingBookConfig* DrawingBookConfig::instance = nullptr;

DrawingBookConfig* DrawingBookConfig::getInstance()
{
	if(instance)
		return instance;
	else{
		instance = new DrawingBookConfig();
		return instance;
	}
}

void DrawingBookConfig::loadSettings(string path)
{

	if(xml.loadFile(path))
	{
		xml.pushTag("params");
		//app details
		app_name					= xml.getValue("app_name", "Drawing Book");
		app_background_image		= xml.getValue("app_background_image", "");
		app_foreground_image		= xml.getValue("app_foreground_image", "");
		app_splash_video			= xml.getValue("app_splash_video", "");
		//app details

		inactivity_timeout_ms	= xml.getValue("inactivity_timeout_ms",20000);
		game_duration_ms		= xml.getValue("game_duration_ms",30000);
		game_over_timeout		= xml.getValue("game_over_timeout",5000);
		countdown_duration_ms	= xml.getValue("countdown_duration_ms",50);
		precountdown_duration_ms= xml.getValue("precountdown_duration_ms",5000);

		countdown_colour.r		= xml.getAttribute("countdown_colour","r",255);
		countdown_colour.g		= xml.getAttribute("countdown_colour","g",255);
		countdown_colour.b		= xml.getAttribute("countdown_colour","b",255);
		countdown_colour.a		= xml.getAttribute("countdown_colour","a",128);

		face_rectangle_v_margin_px	= xml.getValue("face_rectangle_v_margin_px",0);
		face_rectangle_h_margin_px	= xml.getValue("face_rectangle_h_margin_px",0);
		face_min_width_px			= xml.getValue("face_min_width_px",50);

		//FaceInABoxManager::loadXml(xml);

		xml.popTag();
		loaded = true;
	}else
		ofLog(OF_LOG_WARNING,"[DrawingBookConfig] Could not load config file: "+path);
}

bool DrawingBookConfig::isLoaded()
{
	return loaded;
}