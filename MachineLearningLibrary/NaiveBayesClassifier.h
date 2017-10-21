#ifndef NAIVE_BAYES_CLASSIFIER
#define NAIVE_BAYES_CLASSIFIER

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
				NaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
					unsigned int numOfFeatures_, unsigned int numOfClasses_);
				~NaiveBayesClassifier();
				size_t GetNumOfFeatures() const;
				size_t GetNumOfClasses() const;
				void Fit();
				void Print();
				void Run();
			};
		}
	}
}

#endif	//	!NAIVE_BAYES_CLASSIFIER