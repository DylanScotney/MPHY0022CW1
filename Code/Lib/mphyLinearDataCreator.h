/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyDataCreatorI.h"

namespace mphy {

class linDataCreator : public dataInterface {
private:
	std::vector< std::pair<double, double> > mock_data;
public:
	const std::vector< std::pair<double, double> > GetData() override;
	const std::vector < std::pair<double, double> > getMockData(const int num, const double xRange[2], const double yRange[2]);
};

} // end namespace mphy

