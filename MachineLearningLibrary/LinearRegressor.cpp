#include "stdafx.h"
#include "LinearRegressor.h"
#include <armadillo>

using namespace arma;

MLL::SL::Regression::LinearRegressor::LinearRegressor()
{
}

MLL::SL::Regression::LinearRegressor::LinearRegressor::~LinearRegressor()
{
	if (!b.empty()) b.clear();
}

void MLL::SL::Regression::LinearRegressor::Fit(const std::vector<std::vector<double> >& predictors, const std::vector<double>& labels)
{
	size_t numOfObservations = predictors.size();
	size_t numOfFeatures = predictors[0].size();
	b.assign(numOfFeatures, 0.0);

	// Pass X matrix to a data structure of type arma::Mat
	// TODO: Change X from std::vector<std::vector<double> > to arma::Mat to avoid this data transfer
	arma::Mat<double> Xmat(numOfObservations, numOfFeatures, fill::zeros);
	size_t i = 0;
	size_t j = 0;
	for (; i < numOfObservations; ++i)
	{
		j = 0;
		for (; j < numOfFeatures; ++j)
			Xmat(i, j) = predictors[i][j];
	}

	// Pass y to a data structure of type arma::Vec
	// TODO: Change y from std::vector<double> to arma::Vec to avoid this data transfer
	arma::Col<double> yvec(labels.size(), fill::zeros);
	i = 0;
	for (; i < numOfObservations; ++i)
		yvec(i) = labels[i];

	arma::Mat<double> U;
	arma::Col<double> s;
	arma::Mat<double> V;

	// Perform the SVD decomposition
	svd(U, s, V, Xmat);
	Xmat.clear();

	// Find the estimation of the parameters based in the formula in
	// https://en.wikipedia.org/wiki/Linear_least_squares_(mathematics)
	// Computation->Orthogonal Decomposition Methods
	// at the method that uses the SVD

	arma::Mat<double> S(numOfObservations, numOfFeatures, fill::zeros);
	i = 0;
	for (; i < numOfObservations; ++i)
	{
		j = 0;
		for (; j < numOfFeatures; ++j)
			if (i == j)
				S(i, j) = 1.0 / s[j];
	}
	
	arma::Mat<double> invS = S.t();

	arma::Col<double> bvec = ((V * invS) * U.t()) * yvec;
	U.clear();
	s.clear();
	V.clear();

	// Pass the estimated parameters from the arma::Vec data structure to a std::vector<double>
	j = 0;
	for (; j < numOfFeatures; j++)
		b[j] = bvec(j);
}

void MLL::SL::Regression::LinearRegressor::Print()
{
	size_t i = 0;
	size_t numOfWeights = b.size();
	for (; i < numOfWeights; ++i)
	{
		std::cout << b[i];
		if (i != (numOfWeights - 1))
			std::cout << " ";
	}
	std::cout << std::endl;
}

void MLL::SL::Regression::LinearRegressor::Predict(const std::vector<std::vector<double> >& predictors, std::vector<double>& predictions)
{
	size_t i = 0;
	size_t numOfObservations = predictors.size();
	for (; i < numOfObservations; ++i)
	{
		double prediction = std::inner_product(predictors[i].begin(), predictors[i].end(), b.begin(), 0.0);
		predictions.push_back(prediction);
	}
}