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

pairdd gradDesSolver::FitData(vecPairdd data){	
	double numData = data.size();
	double convergetol = 1e-10;
	double divergencetol = 1.0;
	
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
			if (i == maxIter - 1) {
				throw "Gradient descent reached max iterations without convergence.";
			}
			if (((theta - thetaPrev).norm() / (theta.norm())) > divergencetol) {
				throw "Gradient descent method diverging";
			}
			thetaPrev = theta;
		}

	}
	theta_best = std::make_pair(theta(0), theta(1));
	
	return theta_best;
}

} // end namespace mphy
