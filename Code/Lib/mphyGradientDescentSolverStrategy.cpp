/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyGradientDescentSolverStrategy.h"
#include "vectorPairTypes.h"
#include <iostream>

namespace mphy {

Eigen::Matrix<double, Eigen::Dynamic, 2> gradDesSolver::copyXtoEigen(vecPairdd data) {
	/*
	Input: data of vector of pairs (x, y) of arbitary length N

	Output: 2 x N matrix of every element in first coloumn = 1 and second
	coloum contains (x0,..., xN)
	*/

	int iterCnt = 0;

	Eigen::MatrixX2d Xdata;
	Xdata.resize(data.size(), 2);

	for (vecPairdd::iterator i = data.begin(); i != data.end(); ++i) {
		Xdata(iterCnt, 0) = 1;
		Xdata(iterCnt, 1) = i->first;
		iterCnt++;
	}
	return Xdata;
}

Eigen::VectorXd gradDesSolver::copyYtoEigen(vecPairdd data) {
	/*
	Input: data of vector of pairs (x, y) of arbitary length N

	Output: Vector of length N containing (y0,..., yN)
	*/
	int iterCnt = 0;

	Eigen::VectorXd Ydata;
	Ydata.resize(data.size());

	for (vecPairdd::iterator i = data.begin(); i != data.end(); ++i) {
		Ydata(iterCnt) = i->second;
		iterCnt++;
	}

	return Ydata;
}

pairdd gradDesSolver::FitData(vecPairdd data){	
	double numData = data.size();
	double convergetol = 1e-10;
	
	Eigen::MatrixX2d xdata = copyXtoEigen(data);
	Eigen::VectorXd ydata = copyYtoEigen(data);
	Eigen::VectorXd gradients;
	Eigen::Vector2d theta{ 1, 1 };
	Eigen::Vector2d thetaPrev{ 0, 0 };

	for (int i = 0; i < maxIter; ++i) {
		gradients = (2.0 / numData) * xdata.transpose() *(xdata*theta - ydata);
		theta = theta - eta * gradients;
		
		if (((theta - thetaPrev).norm() / (theta.norm())) < convergetol) {
			break;
		}
		else {
			thetaPrev = theta;
			if (i == maxIter - 1) {
				throw std::runtime_error("Gradient descent reached max"
										 "iterations without convergence.");
			}
		}

	}
	
	return pairdd(theta(0), theta(1));
}

} // end namespace mphy
