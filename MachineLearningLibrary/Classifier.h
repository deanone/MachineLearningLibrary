#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <string>

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class Classifier
			{
			protected:
				std::string trainDataFilename;
				std::string testDataFilename;
			public:
				Classifier(std::string trainDataFilename_, std::string testDataFilename_);
				~Classifier();

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

#endif	//	!CLASSIFIER_H