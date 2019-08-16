#ifndef SPLINE_LOGARITHM_H
#define SPLINE_LOGARITHM_H

#include <vector>

#include "../Vector3.h"
#include "../Spline.h"

class SplineLogarithm : public Spline
{
public:
	SplineLogarithm();
	~SplineLogarithm();

	virtual float Fn(float x);
	virtual Vector3 Normal(float x);
};

#endif
