#ifndef MACHINE_LEARNING_LIBRARY_UTILITIES_MATH_FUNC_H
#define MACHINE_LEARNING_LIBRARY_UTILITIES_MATH_FUNC_H

namespace MLL
{
	namespace UTIL
	{ 
		namespace mfnc
		{
			constexpr double alpha = 1e-08;
			constexpr double PI = 3.141592653589793238463;

			template <typename T>
			double ComputeEuclideanDistance(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeEuclideanDistanceSquare(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeManhattanDistance(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeChebysevDistance(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeCosineSimilarity(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeMean(const std::vector<T>& v);

			template <typename T>
			double ComputeStd(const std::vector<T>& v);

			template <typename T>
			double ComputePearsonCorrelation(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeBrayCurtisDistance(const std::vector<T>& v1, const std::vector<T>& v2);

			template <typename T>
			double ComputeCanberraDistance(const std::vector<T>& v1, const std::vector<T>& v2);

			double Sigmoid(const double& x);
			double Relu(const double& x);
			double Identity(const double& x);
			double SigmoidDeriv(const double& x);
			double ReluDeriv(const double& x);
			double IdentityDeriv(const double& x);
			double TanhDeriv(const double& x);
			double GaussianPdf(const double& mean, const double& variance, const double& val);
			double CreateRandomNumber(const double& dMin, const double& dMax);
			int CountOccurences(const std::vector<int>& v, const int& val);
			void FindUniqueValues(const std::vector<int>& v, std::vector<int>& vUnique);
			void FindNumOfOccurencesOfValues(const std::vector<int>& v, std::vector<std::pair<int, int> >& numOfOccurencesOfValues);
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_UTILITIES_MATH_FUNC_H