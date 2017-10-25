#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_MULTINOMIAL_NAIVE_BAYES_CLASSIFIER
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_MULTINOMIAL_NAIVE_BAYES_CLASSIFIER

#include "NaiveBayesClassifier.h"

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class MultinomialNaiveBayesClassifier : public NaiveBayesClassifier
			{
			public:
				MultinomialNaiveBayesClassifier(unsigned int numOfFeatures_, unsigned int numOfClasses_);
				~MultinomialNaiveBayesClassifier();

				void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels);
				void Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions);
				void Print();
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_MULTINOMIAL_NAIVE_BAYES_CLASSIFIER