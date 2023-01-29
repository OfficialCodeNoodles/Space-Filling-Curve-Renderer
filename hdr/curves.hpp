#pragma once

// Dependencies
#include "baseCurve.hpp"

namespace engine {
	class Hilbert : public BaseCurve {
	public:
		Hilbert(); 
		~Hilbert(); 

		void generateOrder(int order) override;

		int getNumOfLines(int order) const override;	
		gs::Vec2f denormalizePoint(
			gs::Vec2f position, int order, gs::Vec2i resolution) const override; 
	private:
	};
}