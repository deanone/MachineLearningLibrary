#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_LINEAR_REGRESSOR_H
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_LINEAR_REGRESSOR_H

#include "Regressor.h"
#include <vector>

namespace MLL
{
	namespace SL
	{
		namespace Regression
		{
			class LinearRegressor : public Regressor
			{
				std::vector<double> b;
			public:
				LinearRegressor();
				~LinearRegressor();

				void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<double>& labels);
				void Predict(const std::vector<std::vector<double> >& predictors, std::vector<double>& predictions);
				void Print();
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_LINEAR_REGRESSOR_H