#include "stdafx.h"
#include "LinearRegressor.h"
#include <armadillo>

using namespace arma;

MLL::SL::Regression::LinearRegressor::LinearRegressor(std::string trainDataFilename_, std::string testDataFilename_)
	: Regressor(trainDataFilename_, testDataFilename_)
{
}

MLL::SL::Regression::LinearRegressor::LinearRegressor::~LinearRegressor()
{
	if (!X.empty()) X.clear();
	if (!y.empty()) y.clear();
	if (!b.empty()) b.clear();
}

void MLL::SL::Regression::LinearRegressor::Load(bool training /*= true*/)
{
	// Load all data into memory.
	// TODO: Change this to iteratively read training instances from disk in
	// order to reduce the memory limitations.

	std::string filename = training ? trainDataFilename : testDataFilename;
	std::string line;
	std::ifstream in(filename);
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
			temp.push_back(1.0);	//	intercept
			for (size_t i = 0; i < (items.size() - 1); ++i)
				temp.push_back(stod(items[i]));
			X.push_back(temp);
			y.push_back(stod(items[items.size() - 1]));	//	value of the dependent variable is the last value of each row
		}
		in.close();
	}
}

void MLL::SL::Regression::LinearRegressor::Fit()
{
	// Load data
	Load();

	size_t numOfObservations = X.size();
	size_t numOfFeatures = X[0].size();
	b.assign(numOfFeatures, 0.0);

	// Pass X matrix to a data structure of type arma::Mat
	// TODO: Change X from std::vector<std::vector<double> > to arma::Mat to avoid this data transfer
	mat Xmat(numOfObservations, numOfFeatures, fill::zeros);
	size_t i = 0;
	size_t j = 0;
	for (; i < numOfObservations; ++i)
	{
		j = 0;
		for (; j < numOfFeatures; ++j)
			Xmat(i, j) = X[i][j];
	}

	// Pass y to a data structure of type arma::Vec
	// TODO: Change y from std::vector<double> to arma::Vec to avoid this data transfer
	vec yvec(y.size(), fill::zeros);
	i = 0;
	for (; i < numOfObservations; ++i)
		yvec(i) = y[i];

	mat U;
	vec s;
	mat V;

	// Perform the SVD decomposition
	svd(U, s, V, Xmat);
	Xmat.clear();

	// Find the estimation of the parameters based in the formula in
	// https://en.wikipedia.org/wiki/Linear_least_squares_(mathematics)
	// Computation->Orthogonal Decomposition Methods
	// at the method that uses the SVD

	mat S(numOfObservations, numOfFeatures, fill::zeros);
	i = 0;
	for (; i < numOfObservations; ++i)
	{
		j = 0;
		for (; j < numOfFeatures; ++j)
			if (i == j)
				S(i, j) = 1.0 / s[j];
	}
	
	mat invS = S.t();

	vec bvec = ((V.t() * invS) * U.t()) * yvec;
	U.clear();
	s.clear();
	V.clear();

	// Pass the estimated parameters from the arma::Vec data structure to a std::vector<double>
	for (size_t j = 0; j < numOfFeatures; j++)
		b[j] = bvec(j);

	// Clear training data
	X.clear();
	y.clear();
}

void MLL::SL::Regression::LinearRegressor::Print()
{
	size_t i = 0;
	for (; i < b.size(); ++i)
		std::cout << b[i] << std::endl;
}

void MLL::SL::Regression::LinearRegressor::Run()
{
	Load(false);
	size_t numOfObservations = X.size();
	for (size_t i = 0; i < numOfObservations; i++)
	{
		double yHat = std::inner_product(X[i].begin(), X[i].end(), b.begin(), 0.0);
		std::cout << y[i] << " " << yHat << std::endl;
	}
}