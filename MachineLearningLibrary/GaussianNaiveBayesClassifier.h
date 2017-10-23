#ifndef GAUSSIAN_NAIVE_BAYES_CLASSIFIER
#define GAUSSIAN_NAIVE_BAYES_CLASSIFIER

#include "NaiveBayesClassifier.h"

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class GaussianNaiveBayesClassifier : public NaiveBayesClassifier
			{
			private:
				std::vector<std::vector<int> > counts;
				std::vector<std::vector<double> > means;
				std::vector<std::vector<double> > variances;
			public:
				GaussianNaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
					unsigned int numOfFeatures_, unsigned int numOfClasses_);
				~GaussianNaiveBayesClassifier();
				void Load(std::vector<std::vector<double> >& data, std::vector<int>& labels, bool training = true);
				void Fit();
				void Print();
				void Run();
			};
		}
	}
}

#endif	//	!GAUSSIAN_NAIVE_BAYES_CLASSIFIER
