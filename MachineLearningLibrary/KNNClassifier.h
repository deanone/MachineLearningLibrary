#ifndef MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_KNN_CLASSIFIER_H
#define MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_KNN_CLASSIFIER_H

#include "Classifier.h"
#include <vector>

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class KNNClassifier : public Classifier
			{
				size_t numOfNeighbors;
				std::vector<std::vector<double> > trainPredictors;
				std::vector<int> trainLabels;
			public:
				KNNClassifier(size_t numOfNeighbors_);
				~KNNClassifier();

				void Fit(const std::vector<std::vector<double> >& predictors, const std::vector<int>& labels);
				void Predict(const std::vector<std::vector<double> >& predictors, std::vector<int>& predictions);
				void Print();
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_SUPERVISED_LEARNING_CLASSIFICATION_KNN_CLASSIFIER_H