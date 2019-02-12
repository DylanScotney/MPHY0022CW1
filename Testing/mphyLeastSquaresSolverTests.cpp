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

TEST_CASE("Size of dataset", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator);
	std::vector<std::pair<double, double>> mockData;

	int numData = 10;
	mockData = data->getMockData(numData);

	REQUIRE(static_cast<int>(mockData.size()) == numData);

}

TEST_CASE("Distribution of dataset", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator);
	std::vector<std::pair<double, double>> mockData;

	const int numData = 10000;
	const double tol = 1; // tolerence for expected value
	const double xRange[2] = { 0, 100 };
	const double xExpct = (xRange[1] - xRange[0]) / 2; // expected x val
	const double yRange[2] = { 0, 100 };
	const double yExpct = (yRange[0] - yRange[1]) / 2; // expected y val
	
	mockData = data->getMockData(numData, xRange, yRange);

	double yAvrge = 0;
	double xAvrge = 0;

	for (auto i = mockData.begin(); i != mockData.end(); i++) {
		xAvrge += i->first;
		yAvrge += i->second;
	}

	xAvrge = xAvrge / numData;
	yAvrge = yAvrge / numData;

	REQUIRE(fabs(xAvrge - xExpct) < tol);
	REQUIRE(fabs(yAvrge - yExpct) < tol);
}

} // end namespace mphy