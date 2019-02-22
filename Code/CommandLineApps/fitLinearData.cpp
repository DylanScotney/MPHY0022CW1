/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <iostream>
#include <string>

static void show_usage(std::string name) {
	std::cerr << "Usage:\t" << name << " <data filename>.txt\n"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow help message\n"
		<< "\t-n,--normSolve\t\tFit data using normal equation\n"
		<< "\t-g,--gradDescent\tFit data using gradient descent\n"
		<< std::endl;
}

static void show_help(char** argv, std::string helpWith) {

	if (helpWith == "General") {
		std::cerr << "\nLinearly fit data using:\n"
			<< argv[0] << " <datafilename>.txt\n\n"
			<< "NOTE:\n"
			<< "<filename> must be .txt type\n"
			<< "Data must be a set of x and y points and is loaded assuming 2 "
			<< "values per line.\n\n"
			<< "Optional Arguments:\n"
			<< "Either -n, --normSolve or -g,--gradDescent must be used.\n"
			<< std::endl;
	}

	if (helpWith == "Norm Solver") {
		std::cout << "Norm Solver Help" << std::endl;
	}

	if (helpWith == "Grad Descent") {
		std::cout << "Grad Descent Help" << std::endl;
	}


}

int main(int argc, char** argv) {

	if (argc < 2) {
		// show_usage when only .exe run
		show_usage(argv[0]);
		return 0;
	}

	// Show general help if first argument is -h, --help
	if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
		show_help(argv, "General");
		return 0;
	}
	

	return 0;
}