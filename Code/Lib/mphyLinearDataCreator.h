/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyLinearDataCreator_h
#define mphyLinearDataCreator_h

#include "mphyDataCreatorI.h"
#include "vectorPairTypes.h"

namespace mphy {

class linDataCreator : public dataInterface {
private:
	double c1, c2;  //y = c1 * x + c2 + noise
	double xRange[2], noise;
	int numData;
	vecPairdd mock_data;
public:

	linDataCreator() {
		xRange[0] = 0;
		xRange[1] = 100;
		noise = 5;
		numData = 10000;
		c1 = 2;
		c2 = 1;
	};

	linDataCreator(double xCoefficient, double intercept, double x0, double xf, double Noise, int n) {
		xRange[0] = x0;
		xRange[1] = xf;
		noise = Noise;
		numData = n; 
		c1 = xCoefficient;
		c2 = intercept;
	};

	~linDataCreator() {};

	vecPairdd GetData() override;

	double getXMin() { return xRange[0]; }
	double getXMax() { return xRange[1]; }
	double getNoise() { return noise; }
	int getNumData() { return numData; }
};

} // end namespace mphy

#endif
