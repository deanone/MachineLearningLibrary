#ifndef LINEAR_REGRESSOR_H
#define LINEAR_REGRESSOR_H

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
				std::vector<std::vector<double> > X;
				std::vector<double> y;
				std::vector<double> b;
			public:
				LinearRegressor(std::string trainDataFilename_, std::string testDataFilename_);
				~LinearRegressor();

				void Load(bool training = true);
				void Fit();
				void Print();
				void Run();
			};
		}
	}
}

#endif	//	!LINEAR_REGRESSOR_H