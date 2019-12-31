#include "CircleElement.h"
#include <Settings.h>
using namespace std;

#define PI 3.14

CircleRenderElement::CircleRenderElement(float circleRadius, float circleThickness, glm::vec4 circleColor) :
	RenderElement(circleColor)
{
	// caculate the vertices coordinate
	float innerRadius = circleRadius - circleThickness;
	for (double i = 0; i < 2 * PI; i += 2 * PI / settings["circle"]["vertices"]) {
		vertices.push_back(cos(i) * circleRadius);
		vertices.push_back(sin(i) * circleRadius);

		vertices.push_back(cos(i) * innerRadius);
		vertices.push_back(sin(i) * innerRadius);
	}
	vertices.insert(vertices.end(), { circleRadius, 0.0f, innerRadius, 0.0f });

	// create buffers
	vl = new VertexLayout();		// vl
	vl->Push<float>(2);
	vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(float), GL_DYNAMIC_DRAW);	// vb
	va = new VertexArray(*vl, *vb);	// va
}
