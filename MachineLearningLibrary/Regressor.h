#ifndef REGRESSOR_H
#define REGRESSOR_H

#include <string>

namespace MLL
{
	namespace SL
	{
		namespace Regression
		{
			class Regressor
			{
			protected:
				std::string trainDataFilename;
				std::string testDataFilename;
			public:
				Regressor(std::string trainDataFilename_, std::string testDataFilename_);
				~Regressor();
				void SetTrainDataFilename(const std::string& trainDataFilename);
				std::string GetTrainDataFilename() const;
				void SetTestDataFilename(const std::string& testDataFilename);
				std::string GetTestDataFilename() const;

				virtual void Fit();
				virtual void Print();
				virtual void Run();
			};
		}
	}
}

#endif	//	!REGRESSOR_H