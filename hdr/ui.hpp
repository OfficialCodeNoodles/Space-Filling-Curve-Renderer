#pragma once

// Dependencies
#include "render.hpp"

namespace engine {
	namespace render {
		namespace ui {
			extern const gs::Color subtitleColor; 
			extern const gs::Color labelColor; 

			extern sf::Font font; 
			extern sf::Text text; 
			extern sf::RectangleShape menuBackground; 
			extern gs::Menu menu; 
			extern gs::Button styleButtons[3]; 
			extern gs::Slider orderSlider;
			extern gs::Slider thicknessSlider; 
			extern gs::Button colorButtons[3]; 
			extern gs::Button framerateButton; 
			extern gs::Menu staticMenu; 
			extern gs::Slider hueSlider;
			extern gs::Slider saturationSlider; 
			extern gs::Menu hueShiftMenu; 
			extern gs::Slider hueShiftSlider; 
			extern gs::Slider hueStrengthSlider; 
			extern gs::Menu imageMenu; 
			extern gs::Button changeImageButton; 
			extern gs::Menu subMenu; 
			extern gs::Button subButtons[4]; 
			extern sf::Texture subButtonTextures[4]; 

			void loadAssets(); 
			void handleAssets(); 
			
			void updateUI(); 
	
			void renderText(
				const std::string& string, gs::Vec2f position,
				float scale = 1.0f, gs::Color color = gs::Color::White,
				float outlineThickess = 0.0f,
				gs::Color outlineColor = gs::Color()
			); 
			void renderUI(); 
		}
	}
}