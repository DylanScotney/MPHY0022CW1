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
#include "mphyGradientDescentSolverStrategy.h"
#include "vectorPairTypes.h"
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>  


static void show_usage(std::string name) {
	std::cerr << "Usage:\n" << name << " <data filename>.txt "
		<< "<solvetype>\n\n"
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
			<< "- <filename> must be .txt type\n"
			<< "- Data must be a set of x and y points and is loaded assuming "
			<< "2 values per line.\n\n"
			<< "Optional Arguments:\n"
			<< "Either -n, --normSolve or -g,--gradDescent must be used "
			<< "for the 3rd argument as solve types.\n"
			<< std::endl;
	}

	if (helpWith == "Grad Descent") {
		std::cerr << "\nGrad Descent Help:" << std::endl;
		std::cerr << "Usage:\t" << argv[0] << " <data filename>.txt "
			<< "<eta> <max iterations>\n"
			<< "- eta must be bound in 0 < eta < 1.\n"
			<< "- Max iterations must be an integer\n"
			<< std::endl;
	}

}

static void output_solution(mphy::pairdd theta) {
	std::cout << std::setprecision(8);
	std::cout << "Fitting linear data y = c0 + c1*x:\n"
		<< "c0: " << theta.first << "\n"
		<< "c1: " << theta.second << "\n"
	    << std::endl;
}

bool hasSuffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
bool ofTypetxt(const std::string &str) {
	if (hasSuffix(str, ".txt")) return true;
	else if (hasSuffix(str, ".TXT")) return true;
	else return false;
}

int main(int argc, char** argv) {
	
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
		//Checking file to be type .txt
		if (!ofTypetxt(argv[1])) {
			show_help(argv, "General");
			std::cerr << "Error: data file must be of type .txt" << std::endl;
			return 0;
		}

		std::unique_ptr<mphy::dataLoadFile> dataLoader(new mphy::dataLoadFile(argv[1]));
		// checks file is found and loads data if so
		try {
			dataLoader->GetData();
		}
		catch (std::exception &e) {
			std::cerr << "\nError: File not found." << std::endl; 
			show_usage(argv[0]);
			std::cerr << "Ensure file is first argument" << std::endl;			
			return 0;
		}
		
		///////////////////// PARSING SOLN METHOD ///////////////////////// 

		// No method Chosen
		if (!argv[2]) {
			std::cerr << "\nError: Third argument must be solve type. "
				<<"Use -n or -g.\n" 
				<< std::endl;
			show_usage(argv[0]);
			return 0;
		}

		/////////////// Solving via Normal Equation ///////////////////////
		else if (std::string(argv[2]) == "-n" || std::string(argv[2]) == "--normSolve") {

			// no extra args for norm solution
			if (!argv[3]) {
				std::cout << "\nSolving via Normal Equation\n" << std::endl;
				std::unique_ptr<mphy::normSolver> solver(new mphy::normSolver());
				mphy::pairdd theta_norm = solver->FitData(dataLoader->getLoadedData());
				output_solution(theta_norm);
			}
			// Show general help since no extra args for norm soln
			else {
				show_help(argv, "General");
				std::cerr << "Error: There is no optional args for Normal Solution, -n."
					<< std::endl;		
				return 0;
			}			
		}

		///////////////// Sovling via Gradient Descent /////////////////////
		else if (std::string(argv[2]) == "-g" || std::string(argv[2]) == "--gradDescent") {
			// Gradient descent with default params
			if (!argv[3]) {
				std::cout << "\nSoving with Gradient Descent:\n" << std::endl;
				std::unique_ptr<mphy::gradDesSolver> solver(new mphy::gradDesSolver());
				mphy::pairdd theta_grad = solver->FitData(dataLoader->getLoadedData());
				output_solution(theta_grad);
			}
			// Gradient descent with input params by user
			else if (argc == 5) {
				// convert strings to double/int
				double eta = atof(argv[3]);
				int maxIters = std::stoi(argv[4]);
				if (eta<0.0 || eta >1.0) {
					show_help(argv, "Grad Descent");
					std::cerr << "Error: 3rd arg eta must be bound by 0 < eta < 1."
						<< std::endl;
					return 0;
				}
				else {
					std::unique_ptr<mphy::gradDesSolver> solver(new mphy::gradDesSolver(eta, maxIters));
					try {
						solver->FitData(dataLoader->getLoadedData());
					}
					catch (const char* msg) {
						show_help(argv, "Grad Descent");
						if (std::string(msg).compare("Gradient descent method diverging") == 0) {
							std::cerr << "Error: "
								<< msg 
								<< " Try reducing eta.\n" << std::endl;
						}
						else { 
							// error: reached max iters before convergence.
							std::cerr << "Error: " 
								<< msg
								<< " Try increasing max iterations.\n" 
								<< std::endl;
						}
						return 0;
					}

					std::cout << "\nSoving with Gradient Descent:\n" << std::endl;
					output_solution(solver->getThetaBest());
				}
			}
			else {
				show_help(argv, "Grad Descent");
				std::cerr << "Error: Incorrect number of optional Arguments."
					<< std::endl;
				return 0;
			}
				
		}
		// Incorrect third argument type
		else {
			show_usage(argv[0]);
			std::cerr << "Error: Third argument must be solve type. Use -n or -g.\n" << std::endl;			
			return 0;
		}
	}


	return 0;
}
