#include "stdafx.h"
#include "LinearRegressor.h"


MLL::SL::Regression::LinearRegressor::LinearRegressor(std::string trainDataFilename_, std::string testDataFilename_)
	: Regressor(trainDataFilename_, testDataFilename_)
{
}

MLL::SL::Regression::LinearRegressor::LinearRegressor::~LinearRegressor()
{
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
			y.push_back(stoi(items[items.size() - 1]));	//	value of the dependent variable is the last value of each row
		}
		in.close();
	}
}

void MLL::SL::Regression::LinearRegressor::Fit()
{

	//mat X = randu<mat>(5, 5);

	//mat U;
	//vec s;
	//mat V;

	//svd(U, s, V, X);
}

void MLL::SL::Regression::LinearRegressor::Print()
{
}

void MLL::SL::Regression::LinearRegressor::Run()
{
}