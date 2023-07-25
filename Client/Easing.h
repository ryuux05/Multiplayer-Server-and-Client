//#include "..\[Server]\Common.h"

struct Easing {
	double time;
	double startPos;
	double change;
	double duration;
};

static double EasingLinear(Easing e)
{
	return e.change * e.time / e.duration + e.startPos;
}
static double EaseInQuad(Easing e)
{
	e.time /= e.duration;
	return e.change * e.time * e.time + e.startPos;
}
static double EaseOutQuad(Easing e)
{
	e.time /= e.duration;
	return -e.change * e.time * (e.time - 2) + e.startPos;
}
static double EaseInOutQuad(Easing e)
{
	e.time /= e.duration / 2;
	if (e.time < 1)
	{
		return e.change / 2 * e.time * e.time + e.startPos;
	}

	return -e.change / 2 * ((--e.time) * (e.time - 2) - 1) + e.startPos;
};

