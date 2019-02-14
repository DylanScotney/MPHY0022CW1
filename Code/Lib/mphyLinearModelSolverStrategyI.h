/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <vector>

typedef std::vector<std::pair<double, double>> vecPairdd;

namespace mphy {

class dataSolverI {
public:
	virtual std::pair<double, double> FitData(vecPairdd) = 0;
};

} // end namespace mphy