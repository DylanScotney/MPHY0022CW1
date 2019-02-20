/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/
#ifndef mphyDataCreatorI_h
#define mphyDataCreatorI_h

#include <vector>
#include "vectorPairTypes.h"

namespace mphy {

class dataInterface {
private:

public:
	double xRange[2], noise;
	int numData;

	dataInterface() {
		xRange[0] = 0;
		xRange[1] = 100;
		noise = 5;
		numData = 10000;
	}
	dataInterface(double x0, double xf, double Noise, int n) {
		xRange[0] = x0;
		xRange[1] = xf;
		noise = Noise;
		numData = n;
	}

	//~dataInterface();
	virtual vecPairdd GetData() = 0;

};

}

#endif
