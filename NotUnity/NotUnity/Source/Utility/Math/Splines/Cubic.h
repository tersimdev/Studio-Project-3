#ifndef SPLINE_CUBIC_H
#define SPLINE_CUBIC_H

#include <vector>

#include "../Vector3.h"
#include "../Spline.h"

class SplineCubic : public Spline
{
public:
	SplineCubic();
	~SplineCubic();

	virtual float Fn(float x);
	virtual Vector3 Normal(float x);
};

#endif
