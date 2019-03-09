#include "mphyLinearModelSolverStrategyI.h"
#include "vectorPairTypes.h"

namespace mphy {

	Eigen::Matrix<double, Eigen::Dynamic, 2> dataSolverI::copyXtoEigen(vecPairdd data) {
		/*
		Input: data of vector of pairs (x, y) of arbitary length N

		Output: 2 x N matrix of every element in first coloumn = 1 and second
		coloum contains (x0,..., xN)
		*/

		int iterCnt = 0;

		Eigen::MatrixX2d Xdata;
		Xdata.resize(data.size(), 2);

		for (vecPairdd::iterator i = data.begin(); i != data.end(); ++i) {
			Xdata(iterCnt, 0) = 1;
			Xdata(iterCnt, 1) = i->first;
			iterCnt++;
		}
		return Xdata;
	}

	Eigen::VectorXd dataSolverI::copyYtoEigen(vecPairdd data) {
		/*
		Input: data of vector of pairs (x, y) of arbitary length N

		Output: Vector of length N containing (y0,..., yN)
		*/
		int iterCnt = 0;

		Eigen::VectorXd Ydata;
		Ydata.resize(data.size());

		for (vecPairdd::iterator i = data.begin(); i != data.end(); ++i) {
			Ydata(iterCnt) = i->second;
			iterCnt++;
		}

		return Ydata;
	}
} // end namespace mphy