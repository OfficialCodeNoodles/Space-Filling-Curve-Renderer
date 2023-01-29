#include "../hdr/render.hpp"

namespace engine {
	namespace render {
		namespace window {
			const gs::Vec2i windowSize = gs::Vec2i(1920, 1080); 
			const int eventFramerate = 60;

			std::unique_ptr<sf::RenderWindow> window = nullptr;
			bool isFullscreen;
			int renderingFramerate = 30;
			sf::Image icon;

			void create(bool fullscreen) {
				auto getStyle = [](bool fullscreen) {
					return fullscreen ? sf::Style::Fullscreen 
						: sf::Style::Default; 
				}; 

				isFullscreen = fullscreen; 

				if (window == nullptr) {
					window = std::make_unique<sf::RenderWindow>(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Space Filling Curve Renderer", 
						getStyle(isFullscreen)
					); 

					icon.loadFromFile("assets/icon.png"); 
				}
				else {
					window->create(
						sf::VideoMode(windowSize.x, windowSize.y),
						"Space Filling Curve Renderer",
						getStyle(isFullscreen)
					); 
				}

				initWindowStates(); 
			}
			void initWindowStates() {
				gs::input::setWindow(window.get()); 

				// Resizes window to match the monitor size. 

				const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode(); 

				window->setSize(gs::Vec2u(
					desktopMode.width, desktopMode.height
				)); 

				// Sets the window icon.
				if (icon.getSize().x > 0)
					window->setIcon(
						icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()
					); 
			}
			void update() {
				sf::Event event; 

				gs::input::updateInputs(); 

				while (window->pollEvent(event)) {
					gs::input::updateEvents(event); 

					switch (event.type) {
					case sf::Event::Closed:
						window->close(); 
						break; 
					case sf::Event::KeyPressed:
						switch (event.key.code) {
						case sf::Keyboard::Escape:
							window->close(); 
							break;
						case sf::Keyboard::F11:
							create(!isFullscreen); 
							break;
						}
						break; 
					}
				}
			}

			void begin(gs::Color backgroundColor) {
				window->clear(backgroundColor); 
			}
			void end() {
				window->display(); 
			}
		}

		const gs::Color backgroundColor = gs::Color(20, 25, 30); 
		const gs::Vec2i imageRenderingAreaSize = gs::Vec2i(1000, 1000);
		const gs::Vec2i imageRenderingAreaOffset = gs::Vec2i(40, 40);

		sf::RenderTexture imageRenderingArea;
		sf::Sprite imageRenderingAreaSprite;
		sf::RectangleShape imageRenderingAreaOutline;
		sf::RectangleShape imageRenderingAreaShade;
		float shadePercentage = 0.0f; 
		RenderingStyle renderingStyle = RenderingStyle::Static; 
		float curvePercentage = 0.0f; 
		int curveOrder = 0; 
		float curveThickness = 1.0f; 
		float curveHue = 0; 
		float curveSaturation = 100.0f;
		int curveBaseHue = 0;
		float curveHueStretch = 1.0f;
		bool paused = false; 

		void loadAssets() {

			handleAssets();
		}
		void handleAssets() {
			// Image rendering area stuffs
			imageRenderingArea.create(
				imageRenderingAreaSize.x, imageRenderingAreaSize.y);

			imageRenderingAreaSprite.setTexture(
				imageRenderingArea.getTexture()); 
			imageRenderingAreaSprite.setPosition(
				imageRenderingAreaOffset.x, imageRenderingAreaOffset.y);

			imageRenderingAreaOutline.setSize(gs::Vec2f(
				imageRenderingAreaSize.x, imageRenderingAreaSize.y)); 
			imageRenderingAreaOutline.setPosition(
				imageRenderingAreaSprite.getPosition()); 
			imageRenderingAreaOutline.setFillColor(gs::Color::Transparent); 
			imageRenderingAreaOutline.setOutlineThickness(3.0f);

			imageRenderingAreaShade.setSize(gs::Vec2f(
				imageRenderingAreaSize.x, imageRenderingAreaSize.y));
			imageRenderingAreaShade.setPosition(
				imageRenderingAreaSprite.getPosition());
			imageRenderingAreaShade.setFillColor(gs::Color::White); 
		}

		gs::Color hsvToRgb(float h, float s, float v) {
			// This function is inspired by this website page. 
			// https://www.codespeedy.com/hsv-to-rgb-in-cpp/

			gs::Color color;

			h = gs::util::mod(h, 360.0f);

			s /= 100.0f;
			v /= 100.0f;

			float C = s * v;
			float X = C * (1.0f - abs(std::fmod(h / 60.0, 2.0f) - 1.0f));
			float m = v - C;
			float r, g, b;

			if (h >= 0.0f && h < 60.0f)
				r = C, g = X, b = 0.0f;
			else if (h >= 60.0f && h < 120.0f)
				r = X, g = C, b = 0.0f;
			else if (h >= 120.0f && h < 180.0f)
				r = 0, g = C, b = X;
			else if (h >= 180.0f && h < 240.0f)
				r = 0, g = X, b = C;
			else if (h >= 240 && h < 300.0f)
				r = X, g = 0.0f, b = C;
			else
				r = C, g = 0.0f, b = X;

			color.r = (r + m) * 255;
			color.g = (g + m) * 255;
			color.b = (b + m) * 255;

			return color;
		}

		void renderLine(
			sf::RenderTarget& target, sf::Vertex vertex1, sf::Vertex vertex2,
			float thickness
		) {
			static sf::VertexArray quads(sf::Quads, 4); 

			// Angle perpendicular to the lines length. 
			const float angle = (gs::util::PI / 2.0f) + gs::util::angleBetween(
				vertex1.position, vertex2.position, false
			); 
			// Offset from the ends to create line thickness. 
			const gs::Vec2f offsetVector = gs::Vec2f(
				std::cos(angle) * (thickness / 2.0f),
				std::sin(angle) * (thickness / 2.0f)
			); 

			// Corners of the quad. 
			quads[0].position = vertex1.position - offsetVector; 
			quads[1].position = vertex2.position - offsetVector; 
			quads[2].position = vertex2.position + offsetVector; 
			quads[3].position = vertex1.position + offsetVector; 

			// Use the same colors on the same side of the line. 
			quads[0].color = quads[3].color = vertex1.color;
			quads[1].color = quads[2].color = vertex2.color;

			target.draw(quads); 
		}
		void renderCurve(const BaseCurve* curve, int order) {
			const int numOfLines = curve->getNumOfLines(order); 
			// Number of lines to be rendered. Creates the illusion of the 
			// curve being generated in real time. 
			const int numOfRenderableLines = static_cast<float>(numOfLines) 
				* (curvePercentage / 100.0f);
			// How large of an area on the curve should be faded.
			const int spread = std::max(numOfLines / 30, 1); 

			for (int lineIndex = 0; lineIndex < 
					std::min(numOfRenderableLines, numOfLines); lineIndex++) {
				std::pair<sf::Vertex, sf::Vertex> line = 
					curve->getOrder(order).getLine(lineIndex); 

				// Scales points to match the size of the window. 
				line.first.position = curve->denormalizePoint(
					line.first.position, order, window::windowSize);
				line.second.position = curve->denormalizePoint(
					line.second.position, order, window::windowSize);

				switch (renderingStyle) {
				case RenderingStyle::Static:
					line.first.color = line.second.color = 
						hsvToRgb(curveHue, curveSaturation, 100.0f);
					break; 
				case RenderingStyle::HueShift:
					line.first.color = hsvToRgb(
						curveBaseHue + (lineIndex 
							/ static_cast<float>(numOfLines)) * 360.0f 
								* curveHueStretch, 100.0f, 100.0f
					); 
					line.second.color = hsvToRgb(
						curveBaseHue + ((lineIndex + 1) 
							/ static_cast<float>(numOfLines)) * 360.0f
								* curveHueStretch, 100.0f, 100.0f
					);
					break; 
				case RenderingStyle::Image:
					line.first.color = getPixel(
						line.first.position, imageRenderingAreaSize
					); 
					line.second.color = getPixel(
						line.second.position, imageRenderingAreaSize
					); 
					break; 
				}

				// Creates the fading in animation. 
				line.first.color.a = 255 - ((255 / spread) 
					* (spread - std::min(numOfRenderableLines - lineIndex, spread)));
				line.second.color.a = 255 - ((255 / spread)
					* (spread - std::min(numOfRenderableLines - lineIndex - 1, spread)));

				renderLine(
					imageRenderingArea, line.first, line.second, 
					std::floor(curveThickness)
				); 
			}
		}
		void renderImageRenderingArea() {
			imageRenderingAreaShade.setFillColor(gs::Color(
				255, 255, 255, shadePercentage
			));

			imageRenderingArea.display(); 

			window::window->draw(imageRenderingAreaSprite); 
			window::window->draw(imageRenderingAreaOutline); 
			window::window->draw(imageRenderingAreaShade); 
		}
	}
}