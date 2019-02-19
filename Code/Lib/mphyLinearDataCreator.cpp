/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyLinearDataCreator.h"
#include <random>
#include <iostream>

namespace mphy {
	
vecPairdd linDataCreator::GetData()
{
	/*returns a 2 x num dataset of randomly distributed (y, x) points*/
	// y = c1*x + c2 + noise
	double c1, c2, x;

	c1 = 2; 
	c2 = 1;

	int seed = 1;
	std::mt19937 mt(seed);
	std::uniform_real_distribution<double> xdist(xRange[0], xRange[1]);
	std::uniform_real_distribution<double> noiseDist(-noise, noise);


	for (int i = 0; i < numData; i++) {
		x = xdist(mt);
		mock_data.push_back(std::make_pair(x, c1*x + c2 + noiseDist(mt)));
	}

	return mock_data;
}

} // end namespace mphy
