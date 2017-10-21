#include "stdafx.h"
#include "MathFunc.h"

template <typename T>
double MLL::UTIL::mfnc::ComputeEuclideanDistance(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist = 0.0;
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (size_t i = 0; i < s; ++i)
		dist += std::pow(v1[i] - v2[i], 2.0);
	dist = sqrt(dist);
	return dist;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeEuclideanDistanceSquare(const std::vector<T>& v1, const std::vector<T>& v2)
{
	return std::pow(ComputeEuclideanDistance(v1, v2), 2.0);
}

template <typename T>
double MLL::UTIL::mfnc::ComputeManhattanDistance(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist = 0.0;
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (size_t i = 0; i < s; ++i)
		dist += std::fabs(v1[i] - v2[i]);
	return dist;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeChebysevDistance(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist = std::fabs(v1[0] - v2[0]);
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (size_t i = 1; i < s; ++i)
	{
		double tempDist = std::fabs(v1[i] - v2[i]);
		if (tempDist > dist) dist = tempDist;
	}
	return dist;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeCosineSimilarity(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist, dotProduct, magnitudeVec1, magnitudeVec2;
	dist = dotProduct = -1.0;
	magnitudeVec1 = magnitudeVec2 = 0.0;
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	dotProduct = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
	for (size_t i = 0; i < s; ++i)
	{
		magnitudeVec1 += std::pow(v1[i], 2.0);
		magnitudeVec2 += std::pow(v2[i], 2.0);
	}
	magnitudeVec1 = std::sqrt(magnitudeVec1);
	magnitudeVec2 = std::sqrt(magnitudeVec2);
	dist = 1.0 - (dotProduct / (magnitudeVec1 * magnitudeVec2));
	return dist;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeMean(const std::vector<T>& v)
{
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	return sum / static_cast<double>(v.size());
}

template <typename T>
double MLL::UTIL::mfnc::ComputeStd(const std::vector<T>& v)
{
	double m, s;
	m = s = -1.0;
	m = ComputeMean(v);
	double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
	return std::sqrt(std::abs(sq_sum / static_cast<double>(v.size()) - std::pow(m, 2.0)));
}

template <typename T>
double MLL::UTIL::mfnc::ComputePearsonCorrelation(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double mean1, stDev1, mean2, stDev2, tempMean, pearsonCorrelation;
	mean1 = stDev1 = mean2 = stDev2 = tempMean = pearsonCorrelation = -1.0;
	mean1 = ComputeMean(v1);
	mean2 = ComputeMean(v2);
	stDev1 = ComputeStd(v1);
	stDev2 = ComputeStd(v2);
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	tempMean = 0.0;
	for (size_t i = 0; i < s; ++i)
		tempMean += ((v1[i] - mean1) * (v2[i] - mean2));
	tempMean /= s;
	pearsonCorrelation = 1.0 - (tempMean / (stDev1 * stDev2));
	return pearsonCorrelation;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeBrayCurtisDistance(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist, sum1, sum2;
	dist = sum1 = sum2 = 0.0;
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (size_t i = 0; i < s; ++i)
	{
		sum1 += std::fabs(v1[i] - v2[i]);
		sum2 += std::fabs(v1[i] + v2[i]);
	}
	dist = sum1 / sum2;
	return dist;
}

template <typename T>
double MLL::UTIL::mfnc::ComputeCanberraDistance(const std::vector<T>& v1, const std::vector<T>& v2)
{
	double dist = 0.0;
	size_t s1 = v1.size();
	size_t s2 = v2.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (size_t i = 0; i < s; ++i)
		dist += std::fabs(v1[i] - v2[i]) / (std::fabs(v1[i]) + std::fabs(v2[i]));
	return dist;
}

double MLL::UTIL::mfnc::Sigmoid(const double& x)
{
	double expValue = exp(-alpha * x);
	double sig = 1 / (1 + expValue);
	return sig;
}

double MLL::UTIL::mfnc::SigmoidDeriv(const double& x)
{
	double sig = Sigmoid(x);
	return alpha * sig * (1 - sig);
}

double MLL::UTIL::mfnc::TanhDeriv(const double& x)
{
	double t = tanh(x);
	return 1 - pow(t, 2);
}

double MLL::UTIL::mfnc::Relu(const double& x)
{
	double rel = max(0.0, x);
	return rel;
}

double MLL::UTIL::mfnc::ReluDeriv(const double& x)
{
	return (x < 0.0) ? 0.0 : 1.0;
}

double MLL::UTIL::mfnc::Identity(const double& x)
{
	return x;
}
double MLL::UTIL::mfnc::IdentityDeriv(const double& x)
{
	return 1.0;
}

/* Random double number generator using the old C++ way */
double MLL::UTIL::mfnc::CreateRandomNumber(const double& dMin, const double& dMax)
{
	double f = (double)rand() / RAND_MAX;
	return f * (dMax - dMin) + dMin;
}

int MLL::UTIL::mfnc::CountOccurences(const std::vector<int>& v, const int& val)
{
	return std::count(v.begin(), v.end(), val);
}

double MLL::UTIL::mfnc::GaussianPdf(const double& mean, const double& variance, const double& val)
{
	double denominator = sqrt(2.0 * PI * variance);
	double exponent = (std::pow(val - mean, 2)) / (2.0 * variance);
	double featureCondProb = (1.0 / denominator) * exp(-exponent);
	return featureCondProb;
}

void MLL::UTIL::mfnc::FindUniqueValues(const std::vector<int>& v, std::vector<int>& vUnique)
{
	vUnique = v;
	std::vector<int>::iterator it = std::unique(vUnique.begin(), vUnique.end());
	vUnique.resize(std::distance(vUnique.begin(), it));
}

void MLL::UTIL::mfnc::FindNumOfOccurencesOfValues(const std::vector<int>& v, std::vector<std::pair<int, int> >& numOfOccurencesOfValues)
{
	std::vector<int> vUnique;
	FindUniqueValues(v, vUnique);
	for (size_t i = 0; i < vUnique.size(); ++i)
		numOfOccurencesOfValues.push_back(std::make_pair(vUnique[i], 0));

	for (size_t i = 0; i < v.size(); ++i)
	{
		for (size_t j = 0; j < numOfOccurencesOfValues.size(); ++j)
		{
			if (v[i] == numOfOccurencesOfValues[j].first)
			{
				numOfOccurencesOfValues[j].second++;
				break;
			}
		}
	}
}