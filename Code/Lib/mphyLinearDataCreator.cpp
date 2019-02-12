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
	
const std::vector<std::pair<double, double>> linDataCreator::GetData()
{
	return std::vector<std::pair<double, double>>(0);
}

const std::vector<std::pair<double, double>> linDataCreator::getMockData(int num)
{
	/*returns a 2 x num dataset of randomly distributed (y, x) points*/

	int seed = 1;
	std::mt19937 mt(seed);
	std::uniform_real_distribution<double> xdist(0, 99);
	std::uniform_real_distribution<double> ydist(0, 99);

	for (int i = 0; i < num; i++) {
		mock_data.push_back(std::make_pair(xdist(mt), ydist(mt)));
	}
	
	return mock_data;
}


} // end namespace mphy
