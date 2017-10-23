#include "stdafx.h"
#include "NaiveBayesClassifier.h"

MLL::SL::Classification::NaiveBayesClassifier::NaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
	unsigned int numOfFeatures_, unsigned int numOfClasses_) 
	: Classifier(trainDataFilename_, testDataFilename_) , numOfFeatures(numOfFeatures_), numOfClasses(numOfClasses_)
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

void MLL::SL::Classification::NaiveBayesClassifier::Load(std::vector<std::vector<double> >& data, std::vector<int>& labels, bool training /*= true*/)
{
}

void MLL::SL::Classification::NaiveBayesClassifier::Fit()
{
}

void MLL::SL::Classification::NaiveBayesClassifier::Print()
{
}

void MLL::SL::Classification::NaiveBayesClassifier::Run()
{
}