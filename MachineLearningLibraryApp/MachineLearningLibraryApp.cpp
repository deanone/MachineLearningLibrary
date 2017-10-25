// MachineLearningLibraryApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Loader.h"
#include "LinearRegressor.h"

int main()
{
	std::string trainDataFilename = "C:\\Users\\thana\\Desktop\\train.csv";
	//std::string testDataFilename = "C:\\Users\\thana\\Desktop\\test.csv";
	
	// Define data structures to use
	std::vector<std::vector<double> > predictors;
	std::vector<double> labels;
	std::vector<double> predictions;

	// Load data
	MLL::UTIL::Loader loader(trainDataFilename);
	loader.Load(predictors, labels);

	// Fit and predict using a linear regression model
	MLL::SL::Regression::LinearRegressor linearRegressor;
	linearRegressor.Fit(predictors, labels);
	linearRegressor.Predict(predictors, predictions);

	for (size_t i = 0; i < predictions.size(); ++i)
		std::cout << labels[i] << " " << predictions[i] << std::endl;

	predictors.clear();
	labels.clear();
	predictions.clear();

    return 0;
}

