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

pairdd normSolver::FitData(vecPairdd data){
	/* 
	Finds optimal theta using the Normal Equation. 
	theta_best = inv(X^T . X) . X^T . y, where:

	data:		a vector of pairs (x, y)
	X:			a 2xnumData matrix of (1, x0; 1, x1; 1, x2...)
	 */
	
	Eigen::Matrix<double, Eigen::Dynamic, 2> xdata; 
	Eigen::VectorXd ydata, theta_best; 

	xdata = copyXtoEigen(data);
	ydata = copyYtoEigen(data);
	
	theta_best = ((xdata.transpose()*xdata).inverse())*xdata.transpose()*ydata;
	

	return pairdd(theta_best(0), theta_best(1));
}

} // end namespace mphy