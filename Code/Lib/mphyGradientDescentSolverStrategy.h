/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyGradientDescentSolverStrategy_h
#define mphyGradientDescentSolverStrategy_h

#include "mphyLinearModelSolverStrategyI.h"
#include "vectorPairTypes.h"
#include <Eigen\Dense>


namespace mphy {

class gradDesSolver : public dataSolverI {
private:
	double eta;
	int maxIter;
	Eigen::Matrix<double, Eigen::Dynamic, 2> copyXtoEigen(vecPairdd data);
	Eigen::VectorXd copyYtoEigen(vecPairdd data);
	pairdd theta_best;

public:
	gradDesSolver() {
		eta = 0.1;
		maxIter = 1000;
	}
	gradDesSolver(double Eta, int maxIterations){
		eta = Eta;
		maxIter = maxIterations;
	}

	pairdd FitData(vecPairdd data) override;
	pairdd getThetaBest() { return theta_best; }
};

} // end namespace mphy

#endif


