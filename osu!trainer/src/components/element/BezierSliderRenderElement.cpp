#include "BezierSliderRenderElement.h"
#include <OsuSettings.h>

OsuTrainer::BezierSliderRenderElement::BezierSliderRenderElement(std::vector<float>& xcp, std::vector<float>& ycp, float circleRadius) :
	xControlPoints(xcp), yControlPoints(ycp)
{
	/*	bezier curve point equation for 4 control points:
		(1-t)^3 * P1 + 3 * (1-t)^2 * t * P2 + 3 * (1-t) * t^2 * P3 + t^3 * P4
		same deal with more control points
	*/

	// calculate the coefficient
	std::queue<int> coefQueue;
	coefQueue.push(1);
	coefQueue.push(1);
	coefficient = RecursiveCoefficient(xcp.size() - 1, coefQueue);

	// calculate vertices
	std::vector<float> center;
	float smoothstep = OsuTrainer::settings["bezier"]["step"];
	for (float i = 0.0f; i <= 1.0f; i += smoothstep)
	{
		center.push_back(CalcCenter(coefficient, xcp, i));
		center.push_back(CalcCenter(coefficient, ycp, i));
	}

	// temporary for now
	vertices = center;

	// generate buffers
	vl = new Echo::VertexLayout();
	vb = new Echo::VertexBuffer(vertices.data(), vertices.size() * sizeof(float));
	va = new Echo::VertexArray();
	vl->Push<float>(2);
	va->AddBuffer(*vl, *vb);
}

float OsuTrainer::BezierSliderRenderElement::CalcCenter(std::vector<int>& coef, std::vector<float>& cp, float inc)
{
	float val = 0;
	for (int i = 0; i < coef.size(); i++)
	{
		val += coef[i] * cp[i] * pow(1 - inc, cp.size() - 1 - i) * pow(inc, i);
	}
	return val;
}

std::vector<int> OsuTrainer::BezierSliderRenderElement::RecursiveCoefficient(int coef, std::queue<int>& coefQueue)
{
	// last coefficent to take care of, return the coef queue as a vector
	if (coef == 1)
	{
		std::vector<int> coefVec;
		while (!coefQueue.empty())
		{
			coefVec.push_back(coefQueue.front());
			coefQueue.pop();
		}
		return coefVec;
	}
	// else, continue calculating the next coef
	else
	{
		int size = coefQueue.size();

		// push the first (and also last) value (always 1) into the queue
		coefQueue.push(1);

		// push the remaining values
		for (int i = 0; i < size - 1; i++)
		{
			int val = coefQueue.front();
			coefQueue.pop();
			coefQueue.push(val + coefQueue.front());
		}
		coefQueue.pop();	// delete the remaining 1 from the back from the previous queue

		coefQueue.push(1);

		// recursive call
		return RecursiveCoefficient(coef - 1, coefQueue);
	}
}

std::pair<float, float> OsuTrainer::BezierSliderRenderElement::CalcVertices(float x1, float y1, float x2, float y2, float size, bool direction)
{
	float a = (x1 - x2) / (y2 - y1);	// coefficient of the perpendicular line
	float b = y1 - a * x1;				// constant of the perpendicular line

	// calculate the vertex
	return { a,b };
}

float OsuTrainer::BezierSliderRenderElement::GetX(float time)
{
	return CalcCenter(coefficient, xControlPoints, time);
}

float OsuTrainer::BezierSliderRenderElement::GetY(float time)
{
	return CalcCenter(coefficient, yControlPoints, time);
}

OsuTrainer::BezierSliderRenderElement::~BezierSliderRenderElement()
{
	delete va;
	delete vb;
	delete vl;
}