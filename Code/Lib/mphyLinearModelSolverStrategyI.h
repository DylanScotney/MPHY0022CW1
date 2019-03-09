/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyLinearModelSolverStrategy_h
#define mphyLinearModelSolverStrategy_h


#include <vector>
#include <Eigen/Dense>
#include "vectorPairTypes.h"


namespace mphy {

class dataSolverI {
protected:
	Eigen::Matrix<double, Eigen::Dynamic, 2> copyXtoEigen(vecPairdd data);
	Eigen::VectorXd copyYtoEigen(vecPairdd data);

public:
	virtual pairdd FitData(vecPairdd) = 0;
};

} // end namespace mphy

#endif