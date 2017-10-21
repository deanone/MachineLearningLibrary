#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <map>
#include <vector>
#include "Layer.h"

namespace MLL
{
	namespace ANN
	{
		class NeuralNetwork
		{
			std::vector<Layer*> layers;
			double learningRate;
			double target;
			int numOfLayers;
			int numberOfIntermediateHiddenLayers;
			int	numberOfNeuronsPerLayer;
			int	numberOfInputs;
			int activationFuncTypeHiddenLayers;
			int activationFuncTypeOuputLayer;
		public:
			NeuralNetwork(std::string nnConfigFilename);
			~NeuralNetwork();
			Layer* GetLayer(int layerId);
			double ComputeDelta(int layerId, int neuronId, int weightId);
			double ComputeWeightUpdate(int layerId, int neuronId, int weightId);
			void Build();
			void Train(std::string trainDataFilename);
			void Run(std::string testDataFilename);
			void PrintWeights();
		};
	}
}

#endif	//	!NEURAL_NETWORK_H