#ifndef KNN_H
#define KNN_H

#include "Classifier.h"
#include <vector>

namespace MLL
{
	namespace SL
	{
		namespace Classification
		{
			class KNN : public Classifier
			{
				size_t numOfNeighbors;
				std::vector<std::vector<double> > trainingInstances;
				std::vector<int> trainingClasses;
			public:
				KNN(std::string trainDataFilename_, std::string testDataFilename_, size_t numOfNeighbors_);
				~KNN();

				void Fit();
				void Print();
				void Run();
			};
		}
	}
}

#endif	//	!KNN_H