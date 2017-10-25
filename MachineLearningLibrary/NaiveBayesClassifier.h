#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_NAIVE_BAYES_CLASSIFIER
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_NAIVE_BAYES_CLASSIFIER

#include <vector>
#include "Classifier.h"

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class NaiveBayesClassifier : public Classifier
			{
			protected:
				size_t numOfFeatures;
				size_t numOfClasses;
				std::vector<double> classProbs;
			public:
				NaiveBayesClassifier(unsigned int numOfFeatures_, unsigned int numOfClasses_);
				~NaiveBayesClassifier();

				size_t GetNumOfFeatures() const;
				size_t GetNumOfClasses() const;
				void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels);
				void Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions);
				void Print();
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_NAIVE_BAYES_CLASSIFIER