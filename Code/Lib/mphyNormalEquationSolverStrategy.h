/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyNormalEquationSolverStrategy_h
#define mphyNormalEquationSolverStrategy_h

#include "mphyLinearModelSolverStrategyI.h"
#include "vectorPairTypes.h"
#include <Eigen/Dense>

namespace mphy {

class normSolver : public dataSolverI {	

private: 
	Eigen::Matrix<double, Eigen::Dynamic, 2> copyXtoEigen(vecPairdd data);
	Eigen::VectorXd copyYtoEigen(vecPairdd data);

public:
	pairdd FitData(vecPairdd data) override;

	////// For unit tests of private methods. DO NOT USE. //////
	Eigen::VectorXd _testcopyYtoEigen(vecPairdd data);
	Eigen::Matrix<double, Eigen::Dynamic, 2> _testcopyXtoEigen(vecPairdd data);
};

} // end namespace mphy

#endif