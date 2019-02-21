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
#include "mphyGradientDescentSolverStrategy.h"
#include "vectorPairTypes.h"
#include <iostream>
 

namespace mphy {

TEST_CASE("Instansiation of linDataCreator", "linDataCreator") {
	std::unique_ptr<linDataCreator> dataComm(new linDataCreator);

	REQUIRE(dataComm);
}

TEST_CASE("Exception thrown for empty mock_data", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator());

	bool caught = false;
	try {
		data->getMockData();
	}
	catch (std::exception& e) {
		caught = true;
	}

	REQUIRE(caught);
}

TEST_CASE("Correct member values for paramaterised constructor", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator(5, 4, 0, 20, 1, 9999));
	double tol = 0.00000001;

	REQUIRE(fabs(data->getXCoeff() - 5.0) < tol);
	REQUIRE(fabs(data->getIntercept() - 4.0) < tol);
	REQUIRE(fabs(data->getXMin() - 0.0) < tol);
	REQUIRE(fabs(data->getXMax() - 20.0) < tol);
	REQUIRE(fabs(data->getNoise() - 1.0) < tol);
	REQUIRE(fabs(data->getNumData() - 9999.0) < tol);
	
}

TEST_CASE("Size of mock dataset", "linDataCreator") {
	std::unique_ptr<linDataCreator> data(new linDataCreator());
	vecPairdd mockData;

	mockData = data->GetData();

	REQUIRE(static_cast<int>(mockData.size()) == data->getNumData());
}

TEST_CASE("Distribution of mock dataset", "linDataCreator") {
	/*Simple test for uniform distribution by comparing the average 
	value of numData datapoints with the expected value from range*/

	std::unique_ptr<linDataCreator> data(new linDataCreator());
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

TEST_CASE("Normal Eqn Solution with non-rand data", "Norm Eqn Solver") {
	double tol = 0.000001; //tolerance 
	std::unique_ptr<normSolver> solver(new normSolver);

	vecPairdd mockData = { { 1,2 },{ 2,2 },{ 5,7 },{ 3,7 } };
	pairdd expectedSoln(1.428571428571428, 0.571428571428573);

	REQUIRE((fabs(solver->FitData(mockData).first 
			- expectedSoln.first) 
			/ fabs(expectedSoln.first))
			< tol);

	REQUIRE((fabs(solver->FitData(mockData).second
		- expectedSoln.second)
		/ fabs(expectedSoln.second))
		< tol);	
	
}

TEST_CASE("Normal Eqn Solution with zero noise", "Norm Eqn Solver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 10000));
	std::unique_ptr<normSolver> solver(new normSolver());
	
	pairdd theta_best;

	vecPairdd mockData = lineardata->GetData();
	theta_best = solver->FitData(mockData);

	REQUIRE(fabs(theta_best.first - 4.0) < tol);
	REQUIRE(fabs(theta_best.second - 7.0) < tol);
}

TEST_CASE("Gradient Descent Solution with zero noise", "gradDesSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 100));
	std::unique_ptr<gradDesSolver> solver(new gradDesSolver());

	vecPairdd mockData = lineardata->GetData();

	pairdd theta_best = solver->FitData(mockData);

	REQUIRE(fabs(theta_best.first - 4.0) < tol);
	REQUIRE(fabs(theta_best.second - 7.0) < tol);
}

TEST_CASE("Convergence error thrown", "gradDesSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 100));
	std::unique_ptr<gradDesSolver> solver(new gradDesSolver(1, 10000));

	vecPairdd mockData = lineardata->GetData();

	bool caught = false;
	try {
		pairdd theta_best = solver->FitData(mockData);
	}
	catch (std::exception& e) {
		caught = true;
	}

	REQUIRE(caught);

}


} // end namespace mphy