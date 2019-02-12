/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "mphyCatchMain.h"
#include "mphyLinearDataCreator.h"
#include <iostream>

namespace mphy {

TEST_CASE("Instansiation of linDataCreator", "linDataCreator") {
	std::unique_ptr<linDataCreator> dataComm(new linDataCreator);

	REQUIRE(dataComm);
}

TEST_CASE("Random data gen", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator);
	std::vector<std::pair<double, double>> mockData;

	int numData = 10;
	mockData = data->getMockData(numData);

	REQUIRE(static_cast<int>(mockData.size()) == numData);


	/*for (auto i = mockData.begin(); i != mockData.end(); i++) {
		std::cout << i->first << " " << i->second << std::endl;
	}*/

}

} // end namespace mphy