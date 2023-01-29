#include "../hdr/ui.hpp"

// Globals

int ticks = 0;
engine::Hilbert hilbert; 

void updateEvents() {
	engine::render::window::update(); 

	if (!engine::render::window::window->hasFocus())
		return; 

	engine::render::ui::updateUI(); 

	// Animates the curve if not paused.
	if (!engine::render::paused)
		engine::render::curvePercentage += 0.2f 
			* (engine::BaseCurve::maxNumOfOrders 
				- engine::render::curveOrder + 1); 

	// Fades the shade effect after a screenshot is taken. 
	gs::util::approach(&engine::render::shadePercentage, 0.0f, 15.0f); 
}
void updateGraphics() {
	engine::render::window::begin(engine::render::backgroundColor);  
	engine::render::imageRenderingArea.clear(gs::Color()); 
 
	engine::BaseCurve* currentCurve = &hilbert; 

	engine::render::renderCurve(currentCurve, engine::render::curveOrder);
	engine::render::renderImageRenderingArea(); 
	engine::render::ui::renderUI(); 

	engine::render::window::end(); 
}

int main() {
	gs::util::Clock timer; 
	
	HWND hwnd = GetConsoleWindow();
	// Hides console window. 
	ShowWindow(hwnd, 0);

	engine::render::window::create(true); 
	engine::render::loadAssets(); 
	engine::render::ui::loadAssets(); 

	hilbert.generateOrders(); 
	engine::updateImageFileDirectory(); 
	engine::gotoNextImage(); 

	while (engine::render::window::window->isOpen()) {
		timer.begin(); 
		
		updateEvents(); 

		if (engine::render::window::renderingFramerate !=
				engine::render::window::eventFramerate) {
			if (ticks % (engine::render::window::eventFramerate /
					engine::render::window::renderingFramerate) == 0)
				updateGraphics();
		}
		else
			updateGraphics(); 

		timer.end(); 
		timer.wait(engine::render::window::eventFramerate); 
		ticks++; 
	}

	return 0; 
}