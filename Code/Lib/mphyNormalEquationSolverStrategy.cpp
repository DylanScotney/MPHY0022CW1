/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyNormalEquationSolverStrategy.h"
#include "vectorPairTypes.h"
#include <memory>
#include <iostream>
#include <math.h>
#include <Eigen/StdVector>
#include <Eigen/Dense>
#include <map>


namespace mphy {

Eigen::Matrix<double, Eigen::Dynamic, 2> normSolver::copyXtoEigen(vecPairdd data){
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

Eigen::VectorXd normSolver::copyYtoEigen(vecPairdd data){
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


pairdd normSolver::FitData(vecPairdd data){
	/* 
	Finds optimal theta using the Normal Equation. 
	theta_best = inv(X^T . X) . X^T . y, where:

	data:		a vector of pairs (x, y)
	X:			a 2xnumData matrix of (1, x0; 1, x1; 1, x2...)
	 */
	
	int iterCnt = 0;

	Eigen::Matrix<double, Eigen::Dynamic, 2> xdata; 
	Eigen::VectorXd ydata, theta_best; 

	xdata = copyXtoEigen(data);
	ydata = copyYtoEigen(data);
	
	theta_best = ((xdata.transpose()*xdata).inverse())*xdata.transpose()*ydata;
	

	return pairdd(theta_best(0), theta_best(1));
}




//////////// For unit tests of private methods DO NOT USE /////////////////

Eigen::VectorXd normSolver::_testcopyYtoEigen(vecPairdd data)
{
	return copyYtoEigen(data);
}

Eigen::Matrix<double, Eigen::Dynamic, 2> normSolver::_testcopyXtoEigen(vecPairdd data)
{
	return copyXtoEigen(data);
}

} // end namespace mphy