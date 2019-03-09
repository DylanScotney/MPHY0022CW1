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

public:
	pairdd FitData(vecPairdd data) override;
};

} // end namespace mphy

#endif