/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef mphyFileLoaderDataCreator_h
#define mphyFileLoaderDataCreator_h

#include "mphyDataCreatorI.h"
#include "vectorPairTypes.h"

namespace mphy {

class dataLoadFile : public dataInterface {
private:
	std::string filename;
	vecPairdd loaded_data;
public:
	dataLoadFile(std::string FILENAME) {
		filename = FILENAME; 
	}
	vecPairdd GetData() override;
};

} // end namespace mphy

#endif
