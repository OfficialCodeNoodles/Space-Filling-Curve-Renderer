#include "../hdr/curves.hpp"

namespace engine {
    Hilbert::Hilbert() {
    }
	Hilbert::~Hilbert() {
	}

	void Hilbert::generateOrder(int order) {
        // Points along a normalized, 1st order hilbert curve. 
        static const sf::Vertex points[4] = {
            sf::Vertex(gs::Vec2f(0.0f, 0.0f)), 
            sf::Vertex(gs::Vec2f(0.0f, 1.0f)), 
            sf::Vertex(gs::Vec2f(1.0f, 1.0f)), 
            sf::Vertex(gs::Vec2f(1.0f, 0.0f))
        }; 
        const int numOfLines = getNumOfLines(order); 
		const int numOfVerticies = numOfLines + 1; 

		Order& currentOrder = orders[order-1]; 
	
		currentOrder.allocate(numOfLines); 

        sf::Vertex vertex; 
        int i, index;

		for (int vertexIndex = 0; vertexIndex < numOfVerticies; vertexIndex++) {
            i = vertexIndex; 

            index = i & 3;
            vertex = points[index];

            for (int orderIndex = 1; orderIndex < order; orderIndex++) {
                float segmentLength = std::pow(2, orderIndex);
                float temp;

                i >>= 2;
                index = i & 3;

                switch (index) {
                case 0:
                    std::swap(vertex.position.x, vertex.position.y); 
                    break;
                case 1:
                    vertex.position.y += segmentLength;
                    break;
                case 2:
                    vertex.position.x += segmentLength;
                    vertex.position.y += segmentLength;
                    break;
                case 3:
                    temp = segmentLength - 1.0f - vertex.position.x;
                    vertex.position.x = segmentLength - 1.0f - vertex.position.y;
                    vertex.position.y = temp;
                    vertex.position.x += segmentLength;
                    break;
                }
            }

            currentOrder.setVertex(vertex, vertexIndex);
		}
	}

	int Hilbert::getNumOfLines(int order) const {
		return std::pow(std::pow(2, order), 2) - 1;
	}
    gs::Vec2f Hilbert::denormalizePoint(
            gs::Vec2f position, int order, gs::Vec2i resolution) const {
        const float scaler = static_cast<float>(1000.0f / std::pow(2, order)); 
        return (position * scaler) + gs::Vec2f(scaler / 2.0f, scaler / 2.0f);
    }
}