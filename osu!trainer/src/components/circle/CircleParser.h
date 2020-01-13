#pragma once

#include <components/element/CircleRenderElement.h>
#include "CircleComponent.h"
#include "Circle.h"

class CircleParser
{
public:
	// circle parsing function
	static ObjectComponent* CircleParserFunc(std::stringstream& ss);
};

ObjectComponent* CircleParser::CircleParserFunc(std::stringstream& ss)
{
	ObjectComponent* object = new CircleComponent();
	object->SetSize(settings["metadata"]["scaleCS"] / (float)settings["metadata"]["cs"]);

	// create circle
	std::string x = "0.0f", y = "0.0f", beat = "0";
	if (!ss.eof()) ss >> x;
	if (!ss.eof()) ss >> y;
	if (!ss.eof()) ss >> beat;
	object->AddObject(new Circle(stof(x), stof(y), stoi(beat)));

	// add render element
	RenderElement* element = new CircleRenderElement(object->GetSize());
	object->AddElement("circle", element);

	return object;
}