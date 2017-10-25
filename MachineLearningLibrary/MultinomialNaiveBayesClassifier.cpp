#include "stdafx.h"
#include "MultinomialNaiveBayesClassifier.h"

MLL::SL::Classification::MultinomialNaiveBayesClassifier::MultinomialNaiveBayesClassifier(unsigned int numOfFeatures_, unsigned int numOfClasses_)
	: NaiveBayesClassifier(numOfFeatures_, numOfClasses_)
{
}

MLL::SL::Classification::MultinomialNaiveBayesClassifier::~MultinomialNaiveBayesClassifier()
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels)
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions)
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Print()
{
}