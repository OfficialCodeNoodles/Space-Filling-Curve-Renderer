#pragma once

// Dependencies
#include "curves.hpp"
#include "image.hpp"

namespace engine {
	namespace render {
		namespace window {
			extern const gs::Vec2i windowSize; 
			extern const int eventFramerate; 

			extern std::unique_ptr<sf::RenderWindow> window; 
			extern bool isFullscreen; 
			extern int renderingFramerate; 
			extern sf::Image icon; 

			void create(bool fullscreen); 
			void initWindowStates(); 
			void update(); 

			void begin(gs::Color backgroundColor = gs::Color()); 
			void end(); 
		}

		enum class RenderingStyle { Static, HueShift, Image };
		extern const gs::Color backgroundColor; 
		extern const gs::Vec2i imageRenderingAreaSize; 
		extern const gs::Vec2i imageRenderingAreaOffset; 

		extern sf::RenderTexture imageRenderingArea; 
		extern sf::Sprite imageRenderingAreaSprite; 
		extern sf::RectangleShape imageRenderingAreaOutline; 
		extern sf::RectangleShape imageRenderingAreaShade; 
		extern float shadePercentage; 
		extern RenderingStyle renderingStyle;
		extern float curvePercentage; 
		extern int curveOrder; 
		extern float curveThickness;  
		extern float curveHue; 
		extern float curveSaturation; 
		extern int curveBaseHue; 
		extern float curveHueStretch; 
		extern bool paused; 

		void loadAssets(); 
		void handleAssets(); 

		gs::Color hsvToRgb(float h, float s, float v); 

		void renderLine(
			sf::RenderTarget& target, sf::Vertex vertex1, sf::Vertex vertex2,
			float thickness = 1.0f
		); 
		void renderCurve(const BaseCurve* curve, int order); 
		void renderImageRenderingArea(); 
	}
}