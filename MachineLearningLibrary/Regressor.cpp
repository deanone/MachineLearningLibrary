#include "stdafx.h"
#include "Regressor.h"

MLL::SL::Regression::Regressor::Regressor(std::string trainDataFilename_, std::string testDataFilename_)
	: trainDataFilename(trainDataFilename_), testDataFilename(testDataFilename_)
{
}

MLL::SL::Regression::Regressor::~Regressor()
{
}

void MLL::SL::Regression::Regressor::SetTrainDataFilename(const std::string& trainDataFilename)
{
	this->trainDataFilename = trainDataFilename;
}

void MLL::SL::Regression::Regressor::SetTestDataFilename(const std::string& testDataFilename)
{
	this->testDataFilename = testDataFilename;
}

std::string MLL::SL::Regression::Regressor::GetTrainDataFilename() const
{
	return trainDataFilename;
}

std::string MLL::SL::Regression::Regressor::GetTestDataFilename() const
{
	return testDataFilename;
}

void MLL::SL::Regression::Regressor::Fit()
{
}

void MLL::SL::Regression::Regressor::Print()
{
}

void MLL::SL::Regression::Regressor::Run()
{
}