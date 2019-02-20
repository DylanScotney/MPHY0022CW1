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
#include <iostream>
#include <math.h>
#include <Eigen/StdVector>
#include <Eigen/Dense>
#include <map>


namespace mphy {

pairdd normSolver::FitData(vecPairdd data)
{
	/* 
	Finds optimal theta using the Normal Equation. 
	theta_best = inv(X^T . X) . X^T . y, where:

	data:		a vector of pairs (x, y)
	X:			a 2xnumData matrix of (1, x0; 1, x1; 1, x2...)
	 */

	vecd xdata, ydata; 
	vecPairdd::iterator it1, it2;
	
	//storing xdata
	xdata.reserve(std::distance(it1, it2));
	std::transform(it1,
				   it2,
			       std::back_inserter(xdata),
				   [](const std::pair<double, int>& p) {return p.first; });

	//storing ydata
	ydata.reserve(std::distance(it1, it2));
	std::transform(it1,
				   it2,
				   std::back_inserter(ydata),
				   [](const std::pair<double, int>& p) {return p.first; });



	return pairdd(0, 0);
}

} // end namespace mphy