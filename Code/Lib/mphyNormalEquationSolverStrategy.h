/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyLinearModelSolverStrategyI.h"

namespace mphy {

class normSolver : public dataSolverI {	

public:
	std::pair<double, double> FitData(std::vector<std::pair<double, double> >) override;
};

} // end namespace mphy