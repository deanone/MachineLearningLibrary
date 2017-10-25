#include "stdafx.h"
#include "NaiveBayesClassifier.h"

MLL::SL::Classification::NaiveBayesClassifier::NaiveBayesClassifier(unsigned int numOfFeatures_, unsigned int numOfClasses_) 
	: numOfFeatures(numOfFeatures_), numOfClasses(numOfClasses_)
{
	classProbs.assign(numOfClasses, 0.0);
}

MLL::SL::Classification::NaiveBayesClassifier::~NaiveBayesClassifier()
{
}

size_t MLL::SL::Classification::NaiveBayesClassifier::GetNumOfFeatures() const
{ 
	return numOfFeatures; 
}

size_t MLL::SL::Classification::NaiveBayesClassifier::GetNumOfClasses() const
{ 
	return numOfClasses;
}

void MLL::SL::Classification::NaiveBayesClassifier::Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels)
{
}

void MLL::SL::Classification::NaiveBayesClassifier::Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions)
{
}

void MLL::SL::Classification::NaiveBayesClassifier::Print()
{
}