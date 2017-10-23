#include "stdafx.h"
#include "MultinomialNaiveBayesClassifier.h"

MLL::SL::Classification::MultinomialNaiveBayesClassifier::MultinomialNaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
	unsigned int numOfFeatures_, unsigned int numOfClasses_)
	: NaiveBayesClassifier(trainDataFilename_, testDataFilename_, numOfFeatures_, numOfClasses_)
{
}

MLL::SL::Classification::MultinomialNaiveBayesClassifier::~MultinomialNaiveBayesClassifier()
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Load(std::vector<std::vector<double> >& data, std::vector<int>& labels, bool training /*= true*/)
{
	// Load all data into memory.
	// TODO: Change this to iteratively read training instances from disk in
	// order to reduce the memory limitations.

	std::string filename = training ? trainDataFilename : testDataFilename;
	std::string line;
	std::ifstream in(filename);
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::istringstream iss(line);
			std::string item;
			std::vector<std::string> items;
			while (std::getline(iss, item, ','))
				items.push_back(item);

			std::vector<double> temp;
			for (size_t i = 0; i < (items.size() - 1); ++i)
				temp.push_back(stod(items[i]));
			data.push_back(temp);
			labels.push_back(stoi(items[items.size() - 1]));
		}
		in.close();
	}
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Fit()
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Print()
{
}

void MLL::SL::Classification::MultinomialNaiveBayesClassifier::Run()
{
}