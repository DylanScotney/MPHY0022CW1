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
#include "vectorPairTypes.h"
#include <iostream>
 

namespace mphy {

TEST_CASE("Instansiation of linDataCreator", "linDataCreator") {
	std::unique_ptr<linDataCreator> dataComm(new linDataCreator);

	REQUIRE(dataComm);
}

TEST_CASE("Size of dataset", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator);
	vecPairdd mockData;
	int numData = 10000;
	mockData = data->GetData();

	REQUIRE(static_cast<int>(mockData.size()) == numData);
}

TEST_CASE("Distribution of dataset", "linDataCreator") {
	/*Simple test for uniform distribution by comparing the average 
	value of numData datapoints with the expected value from range*/

	std::unique_ptr<dataInterface> data(new linDataCreator());
	vecPairdd mockData;

	const double tol = 1; // tolerence for expected value
	const double xExpct = (data->getXMax() - data->getXMin()) / 2; 
	
	mockData = data->GetData();
	double xAvrge = 0;

	for (vecPairdd::iterator i = mockData.begin(); i != mockData.end(); ++i) {
		xAvrge += i->first;
	}

	xAvrge = xAvrge / (data->getNumData());

	REQUIRE(fabs(xAvrge - xExpct) < tol);
}

TEST_CASE("Instansiation of normSolver", "Norm Eqn Solver") {
	std::unique_ptr<normSolver> solver(new normSolver);

	REQUIRE(solver);
}

TEST_CASE("Copy vector pair data to Eigen", "Norm Eqn Solver") {
	/*
	Tests copyXtoEigen and copyYtoEigen. 
	*/

	std::unique_ptr<normSolver> solver(new normSolver);

	vecPairdd mockData = { {1,2}, {2,2}, {5,7}, {3,7} };

	Eigen::MatrixX2d Xdata;
	Eigen::VectorXd Ydata;
	Eigen::Matrix<double, 4, 2> expectedXdata;
	Eigen::Vector4d expectedYdata;
	Eigen::Matrix<double, 4, 2> zerosMx;
	Eigen::Vector4d zerosVy;

	expectedXdata << 1, 1, 1, 2, 1, 5, 1, 3;
	expectedYdata << 2, 2, 7, 7;
	zerosMx << 0, 0, 0, 0, 0, 0, 0, 0;
	zerosVy << 0, 0, 0, 0; 

	Xdata = solver->_testcopyXtoEigen(mockData);	
	Ydata = solver->_testcopyYtoEigen(mockData);

	REQUIRE(expectedXdata - Xdata == zerosMx);
	REQUIRE(expectedYdata - Ydata == zerosVy);

}

TEST_CASE("Normal Eqn Solution", "Norm Eqn Solver") {
	/*
	Tests copyXtoEigen and copyYtoEigen.
	*/
	double tol = 0.000001; //tolerance 
	std::unique_ptr<normSolver> solver(new normSolver);

	vecPairdd mockData = { { 1,2 },{ 2,2 },{ 5,7 },{ 3,7 } };
	pairdd expectedSoln(0.571428571428573, 1.428571428571428);

	REQUIRE((fabs(solver->FitData(mockData).first 
			- expectedSoln.first) 
			/ fabs(expectedSoln.first))
			< tol);

	REQUIRE((fabs(solver->FitData(mockData).second
		- expectedSoln.second)
		/ fabs(expectedSoln.second))
		< tol);	
	
}


} // end namespace mphy