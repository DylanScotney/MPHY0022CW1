/*=============================================================================

MPHYG0022CW1: CW1, 2019: Linear Regression.

Copyright (c) University College London (UCL). All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "mphyFileLoaderDataCreator.h"
#include "mphyNormalEquationSolverStrategy.h"
#include "vectorPairTypes.h"
#include <iostream>
#include <string>
#include <memory>


static void show_usage(std::string name) {
	std::cerr << "Usage:\t" << name << " <data filename>.txt "
		<< "<solvetype>\n"
		<< "Options:\n"
		<< "\t-h,--help\t\tShow help message\n"
		<< "Solve Types:\n"
		<< "\t-n,--normSolve\t\tFit data using normal equation\n"
		<< "\t-g,--gradDescent\tFit data using gradient descent\n"
		<< std::endl;
}

static void show_help(char** argv, std::string helpWith) {

	if (helpWith == "General") {
		std::cerr << "\nGENERAL HELP:\n" 
			<< "Linearly fit data using:\n"
			<< argv[0] << " <datafilename>.txt "
			<< "<solvetype>\n\n"
			<< "NOTE:\n"
			<< "<filename> must be .txt type\n"
			<< "Data must be a set of x and y points and is loaded assuming 2 "
			<< "values per line.\n\n"
			<< "Optional Arguments:\n"
			<< "Either -n, --normSolve or -g,--gradDescent must be used "
			<< "for the 3rd argument as solve types.\n"
			<< std::endl;
	}

	if (helpWith == "Grad Descent") {
		std::cout << "Grad Descent Help" << std::endl;
	}


}

int main(int argc, char** argv) {

	mphy::pairdd theta_best;

	/////////////////////// NO ARGS PARSED ///////////////////////// 
	// show_usage() if no args parsed
	if (argc < 2) {
		show_usage(argv[0]);
		return 0;
	}

	// Show general help if first argument is -h, --help
	if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
		show_help(argv, "General");
		return 0;
	}
	else {

		/////////////////////// PARSING FILE ///////////////////////// 
		// Check first argument is .txt file here
		std::unique_ptr<mphy::dataLoadFile> dataLoader(new mphy::dataLoadFile(argv[1]));
		// Look for file and loads data if found
		try {
			dataLoader->GetData();
		}
		catch (std::exception &e) {
			std::cerr << "\nFile not found.\n"
				<< "Ensure data file is first argument and correct path is used.\n"
				<< std::endl;
			show_usage(argv[0]);
			return 0;
		}
		
		///////////////////// PARSING SOLN METHOD ///////////////////////// 
		// No method Chosen
		if (!argv[2]) {
			std::cout << "\nThird argument must be solve type. Use -n or -g.\n" << std::endl;
			show_usage(argv[0]);
			return 0;
		}
		// Solving via Normal Equation
		else if (std::string(argv[2]) == "-n" || std::string(argv[2]) == "--normSolver") {
			// Show general help since no extra args for norm soln
			if (!argv[3]) {
				std::unique_ptr<mphy::normSolver> solver(new mphy::normSolver());
				theta_best = solver->FitData(dataLoader->getLoadedData());
				std::cerr << "Fitting linear data y = c1*x + c2:\n"
					<< "c1: " << theta_best.first << "\n"
					<< "c2 " << theta_best.second << "\n"
					<< std::endl;
			}
			else {
				show_help(argv, "General");
				std::cerr << "There is no 3rd arg for Normal Solution, -n."
					<< std::endl;				
			}
			
		}
		// Sovling via Gradient Descent
		else if (std::string(argv[2]) == "-g" || std::string(argv[2]) == "--gradDescent") {
			std::cout << "Soving with grad descent" << std::endl;
		}
		// Incorrect third argument type
		else {
			show_usage(argv[0]);
			std::cout << "\nThird argument must be solve type. Use -n or -g.\n" << std::endl;
			
			return 0;
		}
	}


	return 0;
}
