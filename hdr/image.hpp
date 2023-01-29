#pragma once

// Dependencies
#include "render.hpp"

namespace engine {
	extern sf::Image image; 
	extern std::vector<std::string> imageNames; 
	extern int imageIndex; 
	extern std::string imageName; 
	extern bool imageLoaded;

	void loadImage(const std::string& fileName); 
	gs::Color getPixel(gs::Vec2f position, gs::Vec2i resolution); 
	void updateImageFileDirectory(); 
	void gotoNextImage(); 
	void takeScreenshot(); 
}