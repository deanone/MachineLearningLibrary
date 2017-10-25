#ifndef MACHINE_LEARNING_LIBRARY_ARTIFICIAL_NEURAL_NETWORKS_NEURON_H
#define MACHINE_LEARNING_LIBRARY_ARTIFICIAL_NEURAL_NETWORKS_NEURON_H

#include <vector>

namespace MLL
{
	namespace ANN
	{
		class Neuron
		{
			std::vector<double> input;
			std::vector<double> weights;
			std::vector<double> weightsUpdates;
			double activation;
			double output;
			double outputDeriv;
			int numOfWeights;
			int activationFuncType;
		public:
			Neuron(int numOfWeights_, int activationFuncType_);
			~Neuron();
			void SetInput(const std::vector<double>& input_);
			void ComputeActivation();
			void ComputeOutput();
			void ComputeOutputDeriv();
			double GetOutput() const { return output; }
			double GetWeight(int weightId) const;
			double GetInput(int inputId) const;
			int GetNumOfWeights() const { return numOfWeights; }
			void AddWeightUpdate(int weightId, double weightUpdate);
			void UpdateWeights();
			void Clear();
			void PrintWeights();
		};
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_ARTIFICIAL_NEURAL_NETWORKS_NEURON_H