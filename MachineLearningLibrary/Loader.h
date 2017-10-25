#ifndef MACHINE_LEARNING_LIBRARY_UTILITIES_LOADER_H
#define MACHINE_LEARNING_LIBRARY_UTILITIES_LOADER_H

#include <string>
#include <armadillo>

namespace MLL
{
	namespace UTIL
	{
		class Loader
		{
			std::string filename;
		public:
			Loader();
			Loader(const std::string& filename_);
			~Loader();

			void SetFilename(const std::string& filename);
			std::string GetFilename() const;

			// TODO: Change to template functions.
			void Load(std::vector<std::vector<double> >& predictors, std::vector<double>& labels);
			void Load(std::vector<std::vector<double> >& predictors);
			void Load(arma::Mat<double>& predictors, arma::Col<double>& labels);
			void Load(arma::Mat<double>& predictors);
		};
	}
}




#endif	//	!MACHINE_LEARNING_LIBRARY_UTILITIES_LOADER_H