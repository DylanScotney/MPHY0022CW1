/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <vector>

typedef std::vector<std::pair<double, double>> vecPairdd;

class dataInterface {
private:

public:
	double xRange[2], yRange[2];
	int numData;

	dataInterface() {
		xRange[0] = 0;
		xRange[1] = 100;
		yRange[0] = 0;
		yRange[1] = 100;
		numData = 10000;
	}
	dataInterface(double x0, double xf, double y0, double yf, int n) {
		xRange[0] = x0;
		xRange[1] = xf;
		yRange[0] = y0;
		yRange[0] = yf;
		numData = n;
	}

	//~dataInterface();
	virtual vecPairdd GetData() = 0;

};
