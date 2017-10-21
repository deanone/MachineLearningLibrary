#include "stdafx.h"
#include "Classifier.h"

MLL::SL::Classification::Classifier::Classifier(std::string trainDataFilename_, std::string testDataFilename_)
	: trainDataFilename(trainDataFilename_), testDataFilename(testDataFilename_)
{
}

MLL::SL::Classification::Classifier::~Classifier()
{
}

void MLL::SL::Classification::Classifier::SetTrainDataFilename(const std::string& trainDataFilename)
{
	this->trainDataFilename = trainDataFilename; 
}

void MLL::SL::Classification::Classifier::SetTestDataFilename(const std::string& testDataFilename)
{ 
	this->testDataFilename = testDataFilename; 
}

std::string MLL::SL::Classification::Classifier::GetTrainDataFilename() const
{
	return trainDataFilename;
}

std::string MLL::SL::Classification::Classifier::GetTestDataFilename() const
{
	return testDataFilename;
}

void MLL::SL::Classification::Classifier::Fit()
{
}

void MLL::SL::Classification::Classifier::Print()
{
}

void MLL::SL::Classification::Classifier::Run()
{
}