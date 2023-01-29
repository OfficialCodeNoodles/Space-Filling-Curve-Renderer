#include "../hdr/baseCurve.hpp"

namespace engine {
	Order::Order() : lineCount(0) {
	}
	void Order::allocate(int numOfLines) {
		const int numOfVerticies = numOfLines + 1;

		verticies.resize(numOfVerticies, sf::Vertex()); 
		lineCount = numOfLines; 
	}

	void Order::setVertex(sf::Vertex vertex, int index) {
		verticies[index] = vertex; 
	}

	std::pair<sf::Vertex, sf::Vertex> Order::getLine(int index) const {
		return std::pair<sf::Vertex, sf::Vertex>(
			verticies[index], verticies[index+1]
		);
	}
	int Order::getNumberOfLines() const {
		return lineCount;
	}

	void BaseCurve::generateOrders() {
		for (int order = 1; order < maxNumOfOrders + 1; order++)
			generateOrder(order);
	}
	const Order& BaseCurve::getOrder(int order) const {
		return orders[order-1]; 
	}
}