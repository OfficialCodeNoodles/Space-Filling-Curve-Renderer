#pragma once

// Dependencies
#include "files.hpp"

namespace engine {
	class Order {
	public:
		Order();
		~Order() = default;

		void allocate(int numOfLines); 
		
		void setVertex(sf::Vertex vertex, int index); 

		std::pair<sf::Vertex, sf::Vertex> getLine(int index) const;
		int getNumberOfLines() const; 
	private:
		// Each point along the curve. 
		std::vector<sf::Vertex> verticies;
		// Number of line segments. Note: The line count is one less than the 
		// number of verticies. 
		int lineCount; 
	};

	class BaseCurve {
	public:
		BaseCurve() = default; 
		~BaseCurve() = default; 

		virtual void generateOrder(int order) = 0; 
		void generateOrders(); 

		virtual int getNumOfLines(int order) const = 0;
		// Scales point on curve to match up with a given resolution. 
		virtual gs::Vec2f denormalizePoint(
			gs::Vec2f position, int order, gs::Vec2i resolution) const = 0;
		const Order& getOrder(int order) const; 

		// The highest order automatically generated. 
		static constexpr int maxNumOfOrders = 10;
	protected:
		Order orders[maxNumOfOrders + 1]; 
	};
}