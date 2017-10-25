#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_CLASSIFIER_H
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_CLASSIFIER_H

#include <string>

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class Classifier
			{
			public:
				Classifier();
				~Classifier();
				
				virtual void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels) = 0;
				virtual void Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions) = 0;
				virtual void Print() = 0;
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_CLASSIFIER_H