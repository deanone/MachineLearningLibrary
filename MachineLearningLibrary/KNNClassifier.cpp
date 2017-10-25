#include "stdafx.h"
#include "KNNClassifier.h"
#include "MathFunc.h"

template <typename T1, typename T2>
bool cmp(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2)
{
	return p1.second > p2.second;
}

MLL::SL::Classification::KNNClassifier::KNNClassifier(size_t numOfNeighbors_) : numOfNeighbors(numOfNeighbors_)
{
}

MLL::SL::Classification::KNNClassifier::~KNNClassifier()
{
	if (!trainPredictors.empty()) trainPredictors.clear();
	if (!trainLabels.empty()) trainLabels.clear();
}

void MLL::SL::Classification::KNNClassifier::Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels)
{
}

void MLL::SL::Classification::KNNClassifier::Print()
{
}

void MLL::SL::Classification::KNNClassifier::Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions)
{
	for (size_t inputInstanceId = 0; inputInstanceId < predictors.size(); ++inputInstanceId)
	{
		std::vector<double> inputInstance;
		for (size_t featureId = 0; featureId < predictors[inputInstanceId].size(); ++featureId)
			inputInstance.push_back(predictors[inputInstanceId][featureId]);

		std::vector<std::pair<int, double> > distances;
		for (size_t trainingInstanceId = 0; trainingInstanceId < trainPredictors.size(); ++trainingInstanceId)
		{
			std::vector<double> trainingInstance;
			for (size_t featureId = 0; featureId < trainPredictors[trainingInstanceId].size(); ++featureId)
				trainingInstance.push_back(trainPredictors[trainingInstanceId][featureId]);

			double distance = MLL::UTIL::mfnc::ComputeEuclideanDistance(inputInstance, trainingInstance);
			trainingInstance.clear();
			distances.push_back(std::make_pair(trainingInstanceId, distance));
		}

		std::sort(distances.begin(), distances.end(), cmp<int, double>);
		std::vector<int> predictedClasses;
		for (size_t i = 0; i < numOfNeighbors; ++i)
			predictedClasses.push_back(trainLabels[distances[i].first]);
		distances.clear();
		std::vector<std::pair<int, int> > numOfOccurencesOfValues;
		MLL::UTIL::mfnc::FindNumOfOccurencesOfValues(predictedClasses, numOfOccurencesOfValues);
		predictedClasses.clear();
		std::sort(numOfOccurencesOfValues.begin(), numOfOccurencesOfValues.end(), cmp<int, int>);
		int predictedClass = numOfOccurencesOfValues.begin()->first;
		numOfOccurencesOfValues.clear();
		predictions.push_back(predictedClass);
	}
}