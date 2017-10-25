#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_REGRESSOR_H
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_REGRESSOR_H

#include <string>

namespace MLL
{
	namespace SL
	{
		namespace Regression
		{
			class Regressor
			{
			public:
				Regressor();
				~Regressor();

				virtual void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<double>& labels) = 0;
				virtual void Predict(const std::vector<std::vector<double> >& predictors, std::vector<double>& predictions) = 0;
				virtual void Print() = 0;
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_REGRESSION_REGRESSOR_H