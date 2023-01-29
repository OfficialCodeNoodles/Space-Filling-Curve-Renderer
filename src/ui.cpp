#include "../hdr/ui.hpp"

namespace engine {
	namespace render {
		namespace ui {
			const gs::Color subtitleColor = gs::Color(200, 200, 200);
			const gs::Color labelColor = gs::Color(150, 150, 150); 

			sf::Font font;
			sf::Text text;
			sf::RectangleShape menuBackground;
			gs::Menu menu; 
			gs::Button styleButtons[3];
			gs::Slider orderSlider;
			gs::Slider thicknessSlider;
			gs::Button colorButtons[3];
			gs::Button framerateButton;
			gs::Menu staticMenu;
			gs::Slider hueSlider;
			gs::Slider saturationSlider;
			gs::Menu hueShiftMenu;
			gs::Slider hueShiftSlider;
			gs::Slider hueStrengthSlider;
			gs::Menu imageMenu;
			gs::Button changeImageButton;
			gs::Menu subMenu;
			gs::Button subButtons[4];
			sf::Texture subButtonTextures[4];

			void loadAssets() {
				// Load in font
				if (font.loadFromFile("assets/Retron2000.ttf")) {
					// Please don't do this!
					const_cast<sf::Texture*>(&font.getTexture(
						text.getCharacterSize()))->setSmooth(false); 
					text.setFont(font);
				}

				handleAssets(); 
			}
			void handleAssets() {
				// Handle menuBackground
				menuBackground.setSize(gs::Vec2f(
					window::windowSize.x - imageRenderingAreaSize.x
						- (imageRenderingAreaOffset.x * 3),
					window::windowSize.y - (imageRenderingAreaOffset.y * 2)
				)); 
				menuBackground.setPosition(
					imageRenderingAreaSize.x + (imageRenderingAreaOffset.x * 2),
					imageRenderingAreaOffset.y
				); 
				menuBackground.setFillColor(gs::Color()); 

				// Handle styleButtons
				styleButtons[0].setSize(150.0f, 40.0f); 
				styleButtons[0].setPosition(1310.0f, 240.0f); 
				styleButtons[0].setScaleModifiers(1.0f); 
				styleButtons[0].setShapeColors(gs::Color::Transparent); 
				styleButtons[0].setSelectedFillColor(gs::Color(80, 85, 90)); 
				styleButtons[0].setClickedFillColor(gs::Color(160, 170, 180)); 
				styleButtons[0].setOutlineThickness(3.0f); 
				styleButtons[0].setOutlineColor(gs::Color::White); 
				styleButtons[0].setFont(font); 
				styleButtons[0].setString("Hilbert"); 
				styleButtons[0].setTextColors(gs::Color::White); 

				menu.add(&styleButtons[0]); 

				// Handle orderSlider
				orderSlider.setSize(475.0f, 30.0f); 
				orderSlider.setPosition(1310.0f, 300.0f);
				orderSlider.setOnColor(gs::Color::Transparent); 
				orderSlider.setOffColor(gs::Color::Transparent); 
				orderSlider.setOnOutlineThickness(2.0f); 
				orderSlider.setOnOutlineColor(gs::Color::White); 
				orderSlider.setOffOutlineThickness(
					orderSlider.getOnOutlineThickness()); 
				orderSlider.setOffOutlineColor(
					orderSlider.getOnOutlineColor()); 
				orderSlider.button.setSize(80.0f, 30.0f); 
				orderSlider.button.setScaleModifiers(1.0f); 
				orderSlider.button.setOutlineThickness(3.0f); 
				orderSlider.button.setOutlineColor(gs::Color::Cyan); 

				menu.add(&orderSlider); 

				// Handle thicknessSlider 
				thicknessSlider = orderSlider; 
				thicknessSlider.move(0.0f, 55.0f); 

				menu.add(&thicknessSlider); 

				// Handle framerateButton
				framerateButton = styleButtons[0]; 
				framerateButton.setSize(350.0f, 40.0f); 
				framerateButton.setPosition(1310.0f, 720.0f);
				framerateButton.setString("Change framerate");

				menu.add(&framerateButton); 

				// Handle colorButtons
				colorButtons[0] = styleButtons[0]; 
				colorButtons[0].setPosition(
					colorButtons[0].getPosition().x, 480.0f); 
				colorButtons[0].setString("Static"); 

				colorButtons[1] = colorButtons[0]; 
				colorButtons[1].move(150.0f + (25.0f / 2.0f), 0.0f); 
				colorButtons[1].setString("Hue Shift"); 

				colorButtons[2] = colorButtons[1]; 
				colorButtons[2].move(150.0f + (25.0f / 2.0f), 0.0f); 
				colorButtons[2].setString("Image"); 

				for (int buttonIndex = 0; buttonIndex < 3; buttonIndex++)
					menu.add(&colorButtons[buttonIndex]); 

				// Handle staticMenu
				hueSlider = orderSlider; 
				hueSlider.setPosition(1310.0f, 540.0f); 

				staticMenu.add(&hueSlider); 

				saturationSlider = hueSlider; 
				saturationSlider.move(0.0f, 55.0f); 

				staticMenu.add(&saturationSlider); 

				// Handle hueMenu
				hueShiftSlider = orderSlider; 
				hueShiftSlider.setPosition(1310.0f, 540.0f); 

				hueShiftMenu.add(&hueShiftSlider); 

				hueStrengthSlider = hueShiftSlider; 
				hueStrengthSlider.move(0.0f, 55.0f); 

				hueShiftMenu.add(&hueStrengthSlider); 

				// Handle imageMenu
				changeImageButton = styleButtons[0]; 
				changeImageButton.setSize(475.0f, 40.0f); 
				changeImageButton.setPosition(1310.0f, 590.0f);
				changeImageButton.setString("Move to next image"); 

				imageMenu.add(&changeImageButton); 

				// Handle subMenu

				for (int subButtonIndex = 0; subButtonIndex < 4; 
						subButtonIndex++) {
					gs::Button& currentSubButton = subButtons[subButtonIndex]; 

					currentSubButton.shape = gs::Button::Shape::Circle; 
					currentSubButton.setRadius(60.0f); 
					currentSubButton.setSize(120.0f, 120.0f); 
					currentSubButton.setPosition(
						1210.0f + (subButtonIndex * 180.0f), 930.0f
					);
					currentSubButton.setInactiveFillColor(gs::Color::White); 
					currentSubButton.setScaleModifiers(1.0f); 

					if (subButtonTextures[subButtonIndex].loadFromFile(
						"assets/button" + std::to_string(subButtonIndex)
							+ ".png"
					))
						currentSubButton.setTexture(subButtonTextures[subButtonIndex]); 

					subMenu.add(&currentSubButton); 
				}

				// Preupdate all menus
				orderSlider.setPercentage(20.0f);
				hueStrengthSlider.setPercentage(50.0f); 

				menu.update(); 
				staticMenu.update(); 
				hueShiftMenu.update(); 
				imageMenu.update(); 
				subMenu.update(); 
			}

			void updateUI() {
				menu.update(); 
				subMenu.update(); 

				switch (renderingStyle) {
				case RenderingStyle::Static:
					staticMenu.update(); 

					curveHue = hueSlider.getPercentage(360.0f); 
					curveSaturation = saturationSlider.getPercentage(100.0f); 

					hueSlider.button.setOutlineColor(
						hsvToRgb(curveHue, 70.0f, 100.0f));
					saturationSlider.button.setOutlineColor(
						hsvToRgb(curveHue, curveSaturation, 100.0f));

					break; 
				case RenderingStyle::HueShift:
					hueShiftMenu.update();

					curveBaseHue = hueShiftSlider.getPercentage(360.0f); 
					curveHueStretch = hueStrengthSlider.getPercentage(2.0f); 

					{
						const float hueStretchRecipricol = curveHueStretch != 0
							? 1.0f / curveHueStretch : 1.0f;

						hueShiftSlider.button.setOutlineColor(
							hsvToRgb(curveBaseHue, 70.0f, 100.0f));
						hueStrengthSlider.button.setOutlineColor(
							hsvToRgb(curveBaseHue + (360.0f / hueStretchRecipricol),
								70.0f, 100.0f));
					}

					break; 
				case RenderingStyle::Image:
					imageMenu.update();

					if (changeImageButton.isSelected &&
							changeImageButton.isClickedOn) 
						gotoNextImage();

					break; 
				}

				curveOrder = 1.0f + orderSlider.getPercentage(
					BaseCurve::maxNumOfOrders - 1.0f
				); 
				curveThickness = 1.0f + thicknessSlider.getPercentage(49.0f); 
				
				for (int colorButtonIndex = 0; colorButtonIndex < 3;
						colorButtonIndex++) {
					gs::Button& currentColorButton = 
						colorButtons[colorButtonIndex]; 

					if (currentColorButton.isSelected &&
							currentColorButton.isClickedOn) {
						renderingStyle = static_cast<RenderingStyle>(
							colorButtonIndex
						); 
						ticks -= ticks % 90; 
					}

					if (colorButtonIndex == static_cast<int>(renderingStyle)) {
						currentColorButton.setOutlineColor(gs::Color(
							0, 255, 255, 
							180.0f + (std::sin(gs::util::toRadians(
								static_cast<float>(ticks*4.0f))) * 75.0f)
						));
					}
					else
						currentColorButton.setOutlineColor(gs::Color::White); 
				}

				if (framerateButton.isSelected && framerateButton.isClickedOn)
					window::renderingFramerate =
						window::renderingFramerate == 30 ? 60 : 30; 

				if (subButtons[0].isSelected && subButtons[0].isClickedOn) {
					curvePercentage = 0.0f;
					paused = false;
				}
				else if (subButtons[1].isSelected && subButtons[1].isClickedOn)
					paused = !paused; 
				else if (subButtons[2].isSelected && subButtons[2].isClickedOn) {
					takeScreenshot();
					shadePercentage = 255.0f; 
				}
				else if (subButtons[3].isSelected && subButtons[3].isClickedOn)
					window::window->close(); 
			}

			void renderText(
				const std::string& string, gs::Vec2f position, float scale, 
				gs::Color color, float outlineThickess,	gs::Color outlineColor
			) {
				text.setString(string); 
				text.setPosition(position); 
				text.setScale(scale, scale); 
				text.setFillColor(color); 
				text.setOutlineThickness(outlineThickess); 
				text.setOutlineColor(outlineColor); 

				window::window->draw(text); 
			}
			void renderUI() {
				window::window->draw(menuBackground); 

				// Title
				renderText("Options", gs::Vec2f(1350.0f, 75.0f), 2.0f); 

				// Curve Selection
				renderText(
					"Curve Selection", gs::Vec2f(1120.0f, 170.0f), 1.4f, 
					subtitleColor
				);
				renderText(
					"Style", gs::Vec2f(1155.0f, 240.0f), 1.0f, labelColor
				);
				renderText(
					"Order", gs::Vec2f(1155.0f, 295.0f), 1.0f, labelColor      
				);
				renderText(
					"Width", gs::Vec2f(1155.0f, 350.0f), 1.0f, labelColor
				);
				
				// Color
				renderText(
					"Color Selection", gs::Vec2f(1120.0f, 410.0f), 1.4f,
					subtitleColor
				);
				renderText(
					"Style", gs::Vec2f(1155.0f, 480.0f), 1.0f, labelColor
				);

				// Misc
				renderText(
					"Misc", gs::Vec2f(1120.0f, 650.0f), 1.4f, subtitleColor
				);
				renderText(
					"Fps", gs::Vec2f(1155.0f, 720.0f), 1.0f, labelColor
				);

				// Submenu
				renderText(
					"Controls", gs::Vec2f(1375.0f, 800.0f), 1.4f, gs::Color::White
				);

				gs::draw(window::window.get(), menu);
				gs::draw(window::window.get(), subMenu); 

				switch (renderingStyle) {
				case RenderingStyle::Static:
					renderText(
						"Hue", gs::Vec2f(1155.0f, 535.0f), 1.0f,
						labelColor
					);
					renderText(
						"Sat", gs::Vec2f(1155.0f, 590.0f), 1.0f,
						labelColor
					);

					gs::draw(window::window.get(), staticMenu);

					renderText(
						std::to_string(static_cast<int>(curveHue)),
						gs::Vec2f(
							hueSlider.button.getCenter().x - 23.0f,
							hueSlider.button.getPosition().y + 2.0f
						), 0.75f
					);
					renderText(
						std::to_string(curveSaturation).substr(0, 4),
						gs::Vec2f(
							saturationSlider.button.getCenter().x - 24.0f,
							saturationSlider.button.getPosition().y + 2.0f
						), 0.75f
					);

					break;
				case RenderingStyle::HueShift:
					renderText(
						"Hue", gs::Vec2f(1155.0f, 535.0f), 1.0f,
						labelColor
					);
					renderText(
						"Spread", gs::Vec2f(1155.0f, 590.0f), 1.0f,
						labelColor
					);

					gs::draw(window::window.get(), hueShiftMenu);

					renderText(
						std::to_string(static_cast<int>(curveBaseHue)),
						gs::Vec2f(
							hueShiftSlider.button.getCenter().x - 23.0f,
							hueShiftSlider.button.getPosition().y + 2.0f
						), 0.75f
					);
					renderText(
						std::to_string(curveHueStretch).substr(0, 4),
						gs::Vec2f(
							hueStrengthSlider.button.getCenter().x - 24.0f,
							hueStrengthSlider.button.getPosition().y + 2.0f
						), 0.75f
					);

					break;
				case RenderingStyle::Image:
					renderText(
						"File", gs::Vec2f(1155.0f, 535.0f), 1.0f, 
						labelColor
					);
					renderText(
						imageName, gs::Vec2f(1305.0f, 535.0f), 1.0f,
						gs::Color::White
					);

					renderLine(
						*window::window,
						sf::Vertex(gs::Vec2f(1750.0f, 560.0f), gs::Color::Transparent),
						sf::Vertex(gs::Vec2f(1790.0f, 560.0f), gs::Color::Black),
						60.0f
					);
					renderLine(
						*window::window,
						sf::Vertex(gs::Vec2f(1790.0f, 560.0f), gs::Color::Black),
						sf::Vertex(gs::Vec2f(1880.0f, 560.0f), gs::Color::Black),
						60.0f
					);
					renderLine(
						*window::window,
						sf::Vertex(gs::Vec2f(1880.0f, 560.0f), backgroundColor),
						sf::Vertex(gs::Vec2f(1920.0f, 560.0f), backgroundColor),
						60.0f
					);

					gs::draw(window::window.get(), imageMenu);

					break;
				}

				renderText(
					std::to_string(curveOrder), gs::Vec2f(
						orderSlider.button.getCenter().x - 10.0f, 
						orderSlider.button.getPosition().y - 3.0f
					), 1.0f
				);
				renderText(
					std::to_string(static_cast<int>(curveThickness)) + "px", 
					gs::Vec2f(
						thicknessSlider.button.getCenter().x - 30.0f,
						thicknessSlider.button.getPosition().y + 2.0f
					), 0.75f
				);
				renderText(
					std::to_string(window::renderingFramerate) + "fps",
					gs::Vec2f(1685.0f, framerateButton.getPosition().y + 2.0f), 
					1.0f
				);

				const float optionsMenuCenter = menuBackground.getPosition().x
					+ (menuBackground.getSize().x / 2.0f); 

				renderLine(
					*window::window,
					sf::Vertex(gs::Vec2f(optionsMenuCenter - 300.0f, 780.0f), 
						gs::Color::Transparent),
					sf::Vertex(gs::Vec2f(optionsMenuCenter - 100.0f, 780.0f), 
						gs::Color::White),
					3.0f
				);
				renderLine(
					*window::window,
					sf::Vertex(gs::Vec2f(optionsMenuCenter - 100.0f, 780.0f),
						gs::Color::White),
					sf::Vertex(gs::Vec2f(optionsMenuCenter + 100.0f, 780.0f),
						gs::Color::White),
					3.0f
				);
				renderLine(
					*window::window,
					sf::Vertex(gs::Vec2f(optionsMenuCenter + 100.0f, 780.0f),
						gs::Color::White),
					sf::Vertex(gs::Vec2f(optionsMenuCenter + 300.0f, 780.0f),
						gs::Color::Transparent),
					3.0f
				);
			}
		}
	}
}