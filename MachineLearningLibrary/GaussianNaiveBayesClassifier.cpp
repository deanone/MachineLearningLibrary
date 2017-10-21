#include "stdafx.h"
#include "GaussianNaiveBayesClassifier.h"
#include "MathFunc.h"

MLL::SL::Classification::GaussianNaiveBayesClassifier::GaussianNaiveBayesClassifier(std::string trainDataFilename_, std::string testDataFilename_, 
	unsigned int numOfFeatures_, unsigned int numOfClasses_) :
	NaiveBayesClassifier(trainDataFilename_, testDataFilename_, numOfFeatures_, numOfClasses_)
{
	size_t i = 0;
	for (; i < numOfClasses; ++i)
	{
		std::vector<double> temp;
		temp.assign(numOfFeatures, 0.0);	// here 0.0 initialization value
		means.push_back(temp);
		variances.push_back(temp);
		temp.clear();	// not exactly necessary because temp vector is destroyed due to scope
	}

	i = 0;
	for (; i < numOfClasses; ++i)
	{
		std::vector<int> temp;
		temp.assign(numOfFeatures, 0);	// here 0 initialization value
		counts.push_back(temp);
		temp.clear();
	}
}

MLL::SL::Classification::GaussianNaiveBayesClassifier::~GaussianNaiveBayesClassifier()
{
	if (!means.empty()) means.clear();
	if (!variances.empty()) variances.clear();
	if (!counts.empty()) counts.clear();
}

void MLL::SL::Classification::GaussianNaiveBayesClassifier::Fit()
{
	// Load all data into memory.
	// TODO: Change this to iteratively read training instances from disk in
	// order to reduce the memory limitations.
	std::vector<std::vector<double> > data;
	std::vector<int> classes;
	std::string line;
	std::ifstream in(trainDataFilename);
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
			classes.push_back(stoi(items[items.size() - 1]));
		}
		in.close();
	}

	// Find counts of instances per class per feature and mean of values per class per feature
	size_t numOfTrainingInstances = data.size();
	for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
	{
		for (size_t trainingInstanceId = 0; trainingInstanceId < numOfTrainingInstances; ++trainingInstanceId)
		{
			int classId = classes[trainingInstanceId];
			classProbs[classId]++;
			counts[classId][featureId]++;
			means[classId][featureId] += data[trainingInstanceId][featureId];
		}
	}

	for (size_t classId = 0; classId < numOfClasses; ++classId)
		for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
			means[classId][featureId] /= counts[classId][featureId];

	// Find variances per class per feature
	for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
	{
		for (size_t trainingInstanceId = 0; trainingInstanceId < numOfTrainingInstances; ++trainingInstanceId)
		{
			int classId = classes[trainingInstanceId];
			variances[classId][featureId] += std::pow(data[trainingInstanceId][featureId] - means[classId][featureId], 2);
		}
	}

	for (size_t classId = 0; classId < numOfClasses; ++classId)
		for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
			variances[classId][featureId] /= (counts[classId][featureId] - 1);	// unbiased sample variance

																				// Find probabilities of classes
	for (size_t classId = 0; classId < numOfClasses; ++classId)
		classProbs.push_back(static_cast<double>(MLL::UTIL::mfnc::CountOccurences(classes, classId)) / static_cast<double>(classes.size()));
}

void MLL::SL::Classification::GaussianNaiveBayesClassifier::Print()
{
	for (size_t classId = 0; classId < numOfClasses; ++classId)
	{
		for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
		{
			std::cout << std::fixed;
			std::cout << counts[classId][featureId] << ',' << means[classId][featureId];
			std::cout << std::scientific;
			std::cout << "," << variances[classId][featureId] << "--";
		}
		std::cout << std::endl;
	}
}

void MLL::SL::Classification::GaussianNaiveBayesClassifier::Run()
{
	// Load all data into memory.
	// TODO: Change this to iteratively read training instances from disk in
	// order to reduce the memory limitations.
	std::vector<std::vector<double> > data;
	std::vector<int> classes;
	std::string line;
	std::ifstream in(testDataFilename);
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
			classes.push_back(stoi(items[items.size() - 1]));
		}
		in.close();
	}

	size_t numOfTrainingInstances = data.size();
	std::cout << "Real, Predicted\n";
	for (size_t trainingInstanceId = 0; trainingInstanceId < numOfTrainingInstances; ++trainingInstanceId)
	{
		int predictedClass = -1;
		double maxClassCondProb = -1.0;
		for (size_t classId = 0; classId < numOfClasses; ++classId)
		{
			double classCondProb = 1.0;
			for (size_t featureId = 0; featureId < numOfFeatures; ++featureId)
				classCondProb *= MLL::UTIL::mfnc::GaussianPdf(means[classId][featureId], variances[classId][featureId], data[trainingInstanceId][featureId]);
			classCondProb *= classProbs[classId];
			if (classCondProb > maxClassCondProb)
			{
				maxClassCondProb = classCondProb;
				predictedClass = classId;
			}
		}
		std::cout << classes[trainingInstanceId] << "," << predictedClass << std::endl;
	}
}