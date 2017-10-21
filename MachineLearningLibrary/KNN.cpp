#include "stdafx.h"
#include "KNN.h"
#include "MathFunc.h"

template <typename T1, typename T2>
bool cmp(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
	return p1.second > p2.second;
}

MLL::SL::Classification::KNN::KNN(std::string trainDataFilename_, std::string testDataFilename_, size_t numOfNeighbors_)
	: Classifier(trainDataFilename_, testDataFilename_), numOfNeighbors(numOfNeighbors_)
{
}

MLL::SL::Classification::KNN::~KNN()
{
	if (!trainingInstances.empty()) trainingInstances.clear();
}

void MLL::SL::Classification::KNN::Fit()
{
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
			trainingInstances.push_back(temp);
			trainingClasses.push_back(stoi(items[items.size() - 1]));
		}
		in.close();
	}
}

void MLL::SL::Classification::KNN::Print()
{
}

void MLL::SL::Classification::KNN::Run()
{
	std::vector<std::vector<double> > inputInstances;
	std::vector<int> inputClasses;
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
			inputInstances.push_back(temp);
			inputClasses.push_back(stoi(items[items.size() - 1]));
		}
		in.close();
	}


	for (size_t inputInstanceId = 0; inputInstanceId < inputInstances.size(); ++inputInstanceId)
	{
		std::vector<double> inputInstance;
		for (size_t featureId = 0; featureId < inputInstances[inputInstanceId].size(); ++featureId)
			inputInstance.push_back(inputInstances[inputInstanceId][featureId]);

		std::vector<std::pair<int, double> > distances;
		for (size_t trainingInstanceId = 0; trainingInstanceId < trainingInstances.size(); ++trainingInstanceId)
		{
			std::vector<double> trainingInstance;
			for (size_t featureId = 0; featureId < trainingInstances[trainingInstanceId].size(); ++featureId)
				trainingInstance.push_back(trainingInstances[trainingInstanceId][featureId]);

			double distance = MLL::UTIL::mfnc::ComputeEuclideanDistance(inputInstance, trainingInstance);
			trainingInstance.clear();
			distances.push_back(std::make_pair(trainingInstanceId, distance));
		}

		std::sort(distances.begin(), distances.end(), cmp<int, double>);
		std::vector<int> predictedClasses;
		for (size_t i = 0; i < numOfNeighbors; ++i)
			predictedClasses.push_back(trainingClasses[distances[i].first]);
		distances.clear();
		std::vector<std::pair<int, int> > numOfOccurencesOfValues;
		MLL::UTIL::mfnc::FindNumOfOccurencesOfValues(predictedClasses, numOfOccurencesOfValues);
		predictedClasses.clear();
		std::sort(numOfOccurencesOfValues.begin(), numOfOccurencesOfValues.end(), cmp<int, int>);
		int predictedClass = numOfOccurencesOfValues.begin()->first;
		numOfOccurencesOfValues.clear();
		std::cout << inputClasses[inputInstanceId] << "," << predictedClass << std::endl;
	}
}