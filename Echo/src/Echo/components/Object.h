#pragma once

#include <EchoHeader.h>
#include <Core.h>

class ECHO_DLL Object
{
protected:
	Object(float ox, float oy);

	// x and y of the starting point
	float x;
	float y;

	/* difficulty variables:
	* AR: approach rate: how fast the object appears and disappears on the screen
	* OD: how close to the beat the player has to tap to score point
	*/
	static float AR;
	static float OD;

	// use to scale AR
	static int scaleAR;
	int approachTime;

	// timestamps (when the circle appears and disappears)
	int startTime;
	int endTime;

	// score range
	int score300;
	int score100;
	int score50;

	// score range scaling
	static float score300Scaling;
	static float score100Scaling;
	static float score50Scaling;
public:
	// return a score when the user taps
	virtual int GetScore(int time) = 0;

	~Object() = default;
};
