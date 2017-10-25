#include "stdafx.h"
#include "Loader.h"

MLL::UTIL::Loader::Loader() : filename("")
{
}

MLL::UTIL::Loader::Loader(const std::string& filename_) : filename(filename_)
{
}

MLL::UTIL::Loader::~Loader()
{
}

void MLL::UTIL::Loader::SetFilename(const std::string& filename)
{
	this->filename = filename;
}

std::string MLL::UTIL::Loader::GetFilename() const
{
	return filename;
}

void MLL::UTIL::Loader::Load(std::vector<std::vector<double> >& predictors, std::vector<double>& labels)
{
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

			std::vector<double> predictorsVector;
			predictorsVector.push_back(1.0);	//	intercept
			size_t i = 0;
			size_t numOfInputPredictors = (items.size() - 1);
			for (; i < numOfInputPredictors; ++i)
				predictorsVector.push_back(stod(items[i]));
			predictors.push_back(predictorsVector);
			predictorsVector.clear();
			labels.push_back(stod(items[numOfInputPredictors]));	//	value of the dependent variable is the last value of each row
		}
		in.close();
	}
}

void MLL::UTIL::Loader::Load(std::vector<std::vector<double> >& predictors)
{
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

			std::vector<double> predictorsVector;
			predictorsVector.push_back(1.0);	//	intercept
			size_t i = 0;
			size_t numOfInputPredictors = (items.size() - 1);
			for (; i < numOfInputPredictors; ++i)
				predictorsVector.push_back(stod(items[i]));
			predictors.push_back(predictorsVector);
			predictorsVector.clear();
		}
		in.close();
	}
}

void MLL::UTIL::Loader::Load(arma::Mat<double>& predictors, arma::Col<double>& labels)
{
	size_t rowIndex = 0;
	size_t colIndex = 0;
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

			size_t numOfInputPredictors = (items.size() - 1);
			predictors(rowIndex, colIndex) = 1.0;	// intercept
			for (; colIndex < numOfInputPredictors; ++colIndex)
				predictors(rowIndex, colIndex + 1) = stod(items[colIndex]);
			labels(rowIndex) = stod(items[numOfInputPredictors]);
		}
		in.close();
	}
}

void MLL::UTIL::Loader::Load(arma::Mat<double>& predictors)
{
	size_t rowIndex = 0;
	size_t colIndex = 0;
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

			size_t numOfInputPredictors = (items.size() - 1);
			predictors(rowIndex, colIndex) = 1.0;	// intercept
			for (; colIndex < numOfInputPredictors; ++colIndex)
				predictors(rowIndex, colIndex + 1) = stod(items[colIndex]);
		}
		in.close();
	}
}