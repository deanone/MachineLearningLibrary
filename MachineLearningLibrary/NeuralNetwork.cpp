#include "stdafx.h"
#include "NeuralNetwork.h"
#include "PropertiesParser.h"

MLL::ANN::NeuralNetwork::NeuralNetwork(std::string nnConfigFilename) : target(-1.0)
{
	MLL::UTIL::PropertiesParser pp(nnConfigFilename);
	numberOfIntermediateHiddenLayers = pp.GetPropertyAsInt("numberOfIntermediateHiddenLayers");
	numberOfNeuronsPerLayer = pp.GetPropertyAsInt("numberOfNeuronsPerLayer");
	numberOfInputs = pp.GetPropertyAsInt("numberOfInputs");
	learningRate = pp.GetPropertyAsDouble("learningRate");
	activationFuncTypeHiddenLayers = pp.GetPropertyAsInt("activationFuncTypeHiddenLayers");
	activationFuncTypeOuputLayer = pp.GetPropertyAsInt("activationFuncTypeOuputLayer");
	numOfLayers = numberOfIntermediateHiddenLayers + 2;	// number of inermediate hidden layers + first hidden layer + 1 output layer
}

MLL::ANN::NeuralNetwork::~NeuralNetwork()
{
	if (!layers.empty())
	{
		size_t i = 0;
		for (; i < layers.size(); ++i)
			delete layers[i];
		layers.clear();
	}
}

void MLL::ANN::NeuralNetwork::Build()
{
	// First hidden layer
	Layer* layerPtr = new Layer(numberOfNeuronsPerLayer, numberOfInputs + 1, activationFuncTypeHiddenLayers);
	layers.push_back(layerPtr);

	// Intermediate hidden layers
	int i = 0;
	for (; i < numberOfIntermediateHiddenLayers; ++i)
	{
		Layer* layerPtr = new Layer(numberOfNeuronsPerLayer, numberOfNeuronsPerLayer + 1, activationFuncTypeHiddenLayers);
		layers.push_back(layerPtr);
	}

	// Output layer
	Layer* outputlayerPtr = new Layer(1, numberOfNeuronsPerLayer + 1, activationFuncTypeOuputLayer);
	layers.push_back(outputlayerPtr);

}

MLL::ANN::Layer* MLL::ANN::NeuralNetwork::GetLayer(int layerId)
{
	return (layerId >= 0 && layerId < numOfLayers) ? layers[layerId] : nullptr;
}

double MLL::ANN::NeuralNetwork::ComputeDelta(int layerId, int neuronId, int weightId)
{
	double delta = -1.0;
	if (layerId == (numOfLayers - 1))	// for output neurons
	{
		double output = GetLayer(layerId)->GetNeuron(neuronId)->GetOutput();
		delta = (output - static_cast<double>(target)) * output * (1 - output);
	}
	else // for hidden neurons
	{
		delta = 0.0;
		auto neurons = GetLayer(layerId + 1)->GetNeurons();
		size_t i = 0;
		for (; i < neurons->size(); ++i)
			delta += ComputeDelta(layerId + 1, i, weightId) * neurons->at(i)->GetWeight(weightId);
	}
	return delta;
}

double MLL::ANN::NeuralNetwork::ComputeWeightUpdate(int layerId, int neuronId, int weightId)
{
	double delta = ComputeDelta(layerId, neuronId, weightId);
	double input = GetLayer(layerId)->GetNeuron(neuronId)->GetInput(weightId);
	double weightUpdate = (-1.0) * learningRate * input * delta;
	return weightUpdate;
}

void MLL::ANN::NeuralNetwork::Train(std::string trainDataFilename)
{
	std::string dataline = "";
	std::ifstream in(trainDataFilename);
	if (in.is_open())
	{
		//std::cout << "Training the neural network...\n";
		while (std::getline(in, dataline))	// for each observation
		{
			//std::cout << "Constructing training vector...\n";
			// Read line
			std::istringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (std::getline(ss, item, ','))
				items.push_back(item);

			// Transform string line to double training vector
			std::vector<double> trainingVector;
			trainingVector.push_back(1.0);	// bias input
			size_t i = 0;
			for (; i < (items.size() - 1); ++i)
				trainingVector.push_back(stod(items[i]));
			target = stod(items[items.size() - 1]);
			items.clear();

			//############################################################################# Training ###############################################################################################

			// forward pass
			//std::cout << "Forward pass...\n";
			int layerId = 0;
			for (; layerId < numOfLayers; ++layerId)
				layers[layerId]->ForwardPass(trainingVector);

			// backwards pass
			//std::cout << "Backwards pass...\n";
			layerId = (numOfLayers - 1);
			for (; layerId >= 0; --layerId)
			{
				Layer* layer = GetLayer(layerId);
				int numOfNeuronsInLayer = layer->GetNumOfNeurons();
				int neuronId = 0;
				for (; neuronId < numOfNeuronsInLayer; ++neuronId)
				{
					Neuron* neuron = layer->GetNeuron(neuronId);
					int numOfWeights = neuron->GetNumOfWeights();
					int weightId = 0;
					for (; weightId < numOfWeights; ++weightId)
					{
						double weightUpdate = ComputeWeightUpdate(layerId, neuronId, weightId);
						neuron->AddWeightUpdate(weightId, weightUpdate);
					}
				}
			}

			// update weights and clear input and weightsUpdates vectors to be ready for the next observation
			//std::cout << "Updating weights...\n";
			layerId = 0;
			for (; layerId < numOfLayers; ++layerId)
			{
				Layer* layer = GetLayer(layerId);
				int numOfNeuronsInLayer = layer->GetNumOfNeurons();
				int neuronId = 0;
				for (; neuronId < numOfNeuronsInLayer; ++neuronId)
				{
					Neuron* neuron = layer->GetNeuron(neuronId);
					neuron->UpdateWeights();
					neuron->Clear();
				}
			}

			//############################################################################# End of Training ###############################################################################################
		}
		in.close();
		//std::cout << "Neural network trained.\n";
	}
}

void MLL::ANN::NeuralNetwork::PrintWeights()
{
	int layerId = 0;
	for (; layerId < numOfLayers; ++layerId)
	{
		Layer* layer = GetLayer(layerId);
		int numOfNeuronsInLayer = layer->GetNumOfNeurons();
		int neuronId = 0;
		for (; neuronId < numOfNeuronsInLayer; ++neuronId)
		{
			std::cout << layerId << "," << neuronId << ",";
			Neuron* neuron = layer->GetNeuron(neuronId);
			neuron->PrintWeights();
		}
	}
}

void MLL::ANN::NeuralNetwork::Run(std::string testDataFilename)
{
	std::string dataline = "";
	std::ifstream in(testDataFilename);
	if (in.is_open())
	{
		//std::cout << "Predicting...\n";
		while (std::getline(in, dataline))	// for each observation
		{
			// Read line
			std::istringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (std::getline(ss, item, ','))
				items.push_back(item);

			// Transform string line to double test vector
			std::vector<double> testVector;
			testVector.push_back(1.0);
			size_t i = 0;
			for (; i < (items.size() - 1); ++i)
				testVector.push_back(stod(items[i]));
			target = stod(items[items.size() - 1]);
			items.clear();

			int layerId = 0;
			for (; layerId < numOfLayers; ++layerId)
				layers[layerId]->ForwardPass(testVector);

			double output = GetLayer(numOfLayers - 1)->GetNeuron(0)->GetOutput();
			std::cout << target << " " << output << std::endl;
		}
		in.close();
	}
}