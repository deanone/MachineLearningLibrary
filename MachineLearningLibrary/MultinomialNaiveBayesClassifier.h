#ifndef MULTINOMIAL_NAIVE_BAYES_CLASSIFIER
#define MULTINOMIAL_NAIVE_BAYES_CLASSIFIER

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
				MultinomialNaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
					unsigned int numOfFeatures_, unsigned int numOfClasses_);
				~MultinomialNaiveBayesClassifier();
				void Load(std::vector<std::vector<double> >& data, std::vector<int>& labels, bool training = true);
				void Fit();
				void Print();
				void Run();
			};
		}
	}
}

#endif	//	!MULTINOMIAL_NAIVE_BAYES_CLASSIFIER