/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyFileLoaderDataCreator.h"
#include "vectorPairTypes.h"
#include <fstream>
#include <iostream>

namespace mphy {

vecPairdd mphy::dataLoadFile::GetData(){
	std::ifstream infile(filename);

	if (!infile) {
		throw std::runtime_error("File not found");
	}

	double x, y;
	while (infile >> x >> y) {
		loaded_data.push_back(std::make_pair(x, y));
	}
	
	return loaded_data;
}

}