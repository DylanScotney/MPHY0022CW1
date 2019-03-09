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
#include "mphyFileLoaderDataCreator.h"
#include "vectorPairTypes.h"
#include <iostream>
#include <fstream>
#include <string>
 

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

TEST_CASE("Copy vector pair data to Eigen", "dataSolverI") {
	/*
	Tests protected methods, copyXtoEigen and copyYtoEigen from solver interface
	by declaring a new inherited class
	*/

	class testdataSolver : public dataSolverI {
	private:
		vecPairdd mockData;
		Eigen::Matrix<double, 4, 2> expectedXData;
		Eigen::Vector4d expectedYData;

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
			testdataSolver() {
			mockData = { { 1,2 },{ 2,2 },{ 5,7 },{ 3,7 } };
			expectedXData << 1, 1, 1, 2, 1, 5, 1, 3;
			expectedYData << 2, 2, 7, 7;
		}

		void testcopyXtoEigen() {
			Eigen::Matrix<double, 4, 2> zeros;
			zeros << 0, 0, 0, 0, 0, 0, 0, 0;

			Eigen::MatrixX2d Xdata = copyXtoEigen(mockData);
			REQUIRE(expectedXData - Xdata == zeros);
		}

		void testcopyYtoEigen() {
			Eigen::Vector4d zeros;
			zeros << 0, 0, 0, 0;

			Eigen::VectorXd Ydata = copyYtoEigen(mockData);
			REQUIRE(expectedYData - Ydata == zeros);

		}

		// not concerned about definition of FitData for this test
		virtual pairdd FitData(vecPairdd data) { return pairdd(0, 0); }

	};

	std::unique_ptr<testdataSolver> tester(new testdataSolver);
	tester->testcopyXtoEigen();
	tester->testcopyYtoEigen();
}

TEST_CASE("Instansiation of normSolver", "normSolver") {
	std::unique_ptr<normSolver> solver(new normSolver);

	REQUIRE(solver);
}

TEST_CASE("Normal Eqn Solution with non-rand data", "normSolver") {
	double tol = 1e-6; 
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

TEST_CASE("Normal Eqn Solution with zero noise", "normSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 10000));
	std::unique_ptr<normSolver> solver(new normSolver());
	
	pairdd theta_best;

	vecPairdd mockData = lineardata->GetData();
	theta_best = solver->FitData(mockData);

	REQUIRE(fabs(theta_best.first - 7.0) < tol);
	REQUIRE(fabs(theta_best.second - 4.0) < tol);
}

TEST_CASE("Gradient Descent Solution with zero noise", "gradDesSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 100));
	std::unique_ptr<gradDesSolver> solver(new gradDesSolver(0.005, 10000));

	vecPairdd mockData = lineardata->GetData();

	pairdd theta_best = solver->FitData(mockData);

	REQUIRE(fabs(theta_best.first - 7.0) < tol);
	REQUIRE(fabs(theta_best.second - 4.0) < tol);
}

TEST_CASE("Divergence error thrown", "gradDesSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 100));
	std::unique_ptr<gradDesSolver> solver(new gradDesSolver(2, 100));

	vecPairdd mockData = lineardata->GetData();

	try {
		pairdd theta_best = solver->FitData(mockData);
	}
	catch (const char* msg) {
		REQUIRE(std::string(msg).compare("Gradient descent method diverging") == 0);
	}

}

TEST_CASE("max iterations error thrown", "gradDesSolver") {

	double tol = 1e-6;

	std::unique_ptr<linDataCreator> lineardata(new linDataCreator(4, 7, 0, 20, 0, 100));
	std::unique_ptr<gradDesSolver> solver(new gradDesSolver(0.005, 100));

	vecPairdd mockData = lineardata->GetData();

	try {
		pairdd theta_best = solver->FitData(mockData);
	}
	catch (const char* msg) {
		REQUIRE(std::string(msg).compare("Gradient descent reached max iterations without convergence.") == 0);
	}

}

TEST_CASE("Throwing exception when file not found", "dataLoadFile") {
	std::string filename = "not a real file";

	std::unique_ptr<dataLoadFile> dataLoader(new dataLoadFile(filename));
	bool caught = false;
	try {
		dataLoader->checkFile(filename);
	}
	catch (std::exception &e) {
		caught = true;
	}
	
	REQUIRE(caught);
}


} // end namespace mphy