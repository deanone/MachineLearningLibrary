#include "stdafx.h"
#include "Neuron.h"
#include "MathFunc.h"

MLL::ANN::Neuron::Neuron(int numOfWeights_, int activationFuncType_) : numOfWeights(numOfWeights_), activationFuncType(activationFuncType_), activation(-1.0), output(-1.0), outputDeriv(-1.0)
{
	weights.assign(numOfWeights, MLL::UTIL::mfnc::CreateRandomNumber(0, 1));	// the initial value of the weights is the same for all the weights
	weightsUpdates.assign(numOfWeights, 0.0);
	input.assign(numOfWeights, 0.0);
}

MLL::ANN::Neuron::~Neuron()
{
	if (!weights.empty()) weights.clear();
	if (!weightsUpdates.empty()) weightsUpdates.clear();
	if (!input.empty()) input.clear();
}

void MLL::ANN::Neuron::SetInput(const std::vector<double>& input_)
{
	for (size_t i = 0; i < input_.size(); i++)
		input[i] = input_[i];
}

void MLL::ANN::Neuron::ComputeActivation()
{
	activation = std::inner_product(std::begin(weights), std::end(weights), std::begin(input), 0.0);
}

void MLL::ANN::Neuron::ComputeOutput()
{
	switch (activationFuncType)
	{
	case 1:
		output = MLL::UTIL::mfnc::Sigmoid(activation);
		break;
	case 2:
		output = tanh(activation);
		break;
	case 3:
		output = MLL::UTIL::mfnc::Relu(activation);
		break;
	case 4:
		output = MLL::UTIL::mfnc::Identity(activation);
		break;
	default:
		break;
	}
}

void MLL::ANN::Neuron::ComputeOutputDeriv()
{
	switch (activationFuncType)
	{
	case 1:
		outputDeriv = MLL::UTIL::mfnc::SigmoidDeriv(activation);
		break;
	case 2:
		outputDeriv = MLL::UTIL::mfnc::TanhDeriv(activation);
		break;
	case 3:
		outputDeriv = MLL::UTIL::mfnc::ReluDeriv(activation);
		break;
	case 4:
		outputDeriv = MLL::UTIL::mfnc::IdentityDeriv(activation);
		break;
	default:
		break;
	}
}

double MLL::ANN::Neuron::GetWeight(int weightId) const
{
	return (weightId >= 0 && weightId < numOfWeights) ? weights[weightId] : -1.0;
}

double MLL::ANN::Neuron::GetInput(int inputId) const
{
	return (inputId >= 0 && inputId < numOfWeights) ? input[inputId] : -1.0;
}

void MLL::ANN::Neuron::AddWeightUpdate(int weightId, double weightUpdate)
{
	if (weightId >= 0 && weightId < numOfWeights)
		weightsUpdates[weightId] = weightUpdate;
}

void MLL::ANN::Neuron::UpdateWeights()
{
	int weightId = 0;
	for (; weightId < numOfWeights; ++weightId)
		weights[weightId] += weightsUpdates[weightId];
}

void MLL::ANN::Neuron::Clear()
{
	int weightId = 0;
	for (; weightId < numOfWeights; ++weightId)
	{
		weightsUpdates[weightId] = 0.0;
		input[weightId] = 0.0;
	}

	activation = -1.0;
	output = -1.0;
	outputDeriv = -1.0;
}

void MLL::ANN::Neuron::PrintWeights()
{
	int weightId = 0;
	for (; weightId < numOfWeights; ++weightId)
	{
		std::cout << weights[weightId];
		if (weightId != (numOfWeights - 1))
			std::cout << ",";
	}
	std::cout << std::endl;
}