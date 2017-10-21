#include "stdafx.h"
#include "Layer.h"

MLL::ANN::Layer::Layer(int numOfNeurons_, int numOfWeights_, int activationFuncType_) : numOfNeurons(numOfNeurons_)
{
	int i = 0;
	for (; i < numOfNeurons; ++i)
	{
		Neuron* ptr(new Neuron(numOfWeights_, activationFuncType_));
		neurons.push_back(ptr);
	}
}

MLL::ANN::Layer::~Layer()
{
	if (!neurons.empty())
	{
		size_t i = 0;
		for (; i < neurons.size(); ++i)
			delete neurons[i];
		neurons.clear();
	}
}

void MLL::ANN::Layer::ForwardPass(std::vector<double>& input)
{
	std::vector<double> output;
	output.push_back(1.0);	// for bias
	size_t i = 0;
	for (; i < neurons.size(); ++i)
	{
		neurons[i]->SetInput(input);
		neurons[i]->ComputeActivation();
		neurons[i]->ComputeOutput();
		neurons[i]->ComputeOutputDeriv();
		output.push_back(neurons[i]->GetOutput());
	}

	input.clear();

	i = 0;
	for (; i < output.size(); ++i)
		input.push_back(output[i]);

	output.clear();
}

MLL::ANN::Neuron* MLL::ANN::Layer::GetNeuron(int neuronId)
{
	return (neuronId >= 0 && neuronId < numOfNeurons) ? neurons[neuronId] : nullptr;
}