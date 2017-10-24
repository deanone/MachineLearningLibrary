// MachineLearningLibraryApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LinearRegressor.h"


int main()
{
	std::string trainDataFilename = "C:\\Users\\thana\\Desktop\\train.csv";
	std::string testDataFilename = "C:\\Users\\thana\\Desktop\\test.csv";
	MLL::SL::Regression::LinearRegressor lr(trainDataFilename, testDataFilename);
	lr.Fit();	
	lr.Print();
	lr.Run();
    return 0;
}

