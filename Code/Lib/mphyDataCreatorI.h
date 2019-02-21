/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/
#ifndef mphyDataCreatorI_h
#define mphyDataCreatorI_h

#include <vector>
#include "vectorPairTypes.h"

namespace mphy {

class dataInterface {
public:

	virtual vecPairdd GetData() = 0;
};

} // end namespace mphy

#endif
