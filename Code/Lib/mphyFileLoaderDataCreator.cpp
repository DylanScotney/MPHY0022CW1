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


bool dataLoadFile::checkFile(std::string filename)
{
	std::ifstream infile(filename);
	if (infile) return true;

	if (!infile) {
		throw std::runtime_error("File not found");
	}
}


vecPairdd mphy::dataLoadFile::GetData(){
	checkFile(filename);
	std::ifstream infile(filename);
	
	double x, y;
	while (infile >> x >> y) {
		loaded_data.push_back(std::make_pair(x, y));
	}
	
	return loaded_data;
}


}
