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
#include "mphyNormalEquationSolverStrategy.h"
#include <iostream>


namespace mphy {

TEST_CASE("Instansiation of linDataCreator", "linDataCreator") {
	std::unique_ptr<linDataCreator> dataComm(new linDataCreator);

	REQUIRE(dataComm);
}

TEST_CASE("Size of dataset", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator);
	std::vector<std::pair<double, double>> mockData;
	int numData = 10000;
	mockData = data->GetData();

	REQUIRE(static_cast<int>(mockData.size()) == numData);
}

TEST_CASE("Distribution of dataset", "linDataCreator") {
	/*Simple test for uniform distribution by comparing the average 
	value of numData datapoints with the expected value from range*/

	typedef std::vector<std::pair<double, double>> vecPairdd;

	std::unique_ptr<dataInterface> data(new linDataCreator());
	vecPairdd mockData;

	const double tol = 1; // tolerence for expected value
	const double xExpct = (data->xRange[1] - data->xRange[0]) / 2; 
	const double yExpct = (data->yRange[1] - data->yRange[0]) / 2; 
	
	mockData = data->GetData();

	double yAvrge = 0;
	double xAvrge = 0;

	for (vecPairdd::iterator i = mockData.begin(); i != mockData.end(); i++) {
		xAvrge += i->first;
		yAvrge += i->second;
	}

	xAvrge = xAvrge / (data->numData);
	yAvrge = yAvrge / (data->numData);

	REQUIRE(fabs(xAvrge - xExpct) < tol);
	REQUIRE(fabs(yAvrge - yExpct) < tol);
}

TEST_CASE("Instansiation of normSolver", "linDataCreator") {
	std::unique_ptr<normSolver> solver(new normSolver);

	REQUIRE(solver);
}

} // end namespace mphy