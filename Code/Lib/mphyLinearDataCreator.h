/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyLinearDataCreator_h
#define mphyLinearDataCreator_h

#include "mphyDataCreatorI.h"
#include "vectorPairTypes.h"

namespace mphy {

class linDataCreator : public dataInterface {
private:
	vecPairdd mock_data;
public:
	linDataCreator() {};
	~linDataCreator() {};
	vecPairdd GetData() override;
};

} // end namespace mphy

#endif
