#ifndef MACHINE_LEARNING_LIBRARY_UNSUPERVISED_LEARNING_CLUSTERING_POINT_H
#define MACHINE_LEARNING_LIBRARY_UNSUPERVISED_LEARNING_CLUSTERING_POINT_H

#include <vector>

namespace MLL
{
	namespace UL
	{
		namespace Clustering
		{
			class Point
			{
				int id;
				std::vector<double> values;
			public:
				Point();
				~Point();
				void SetID(const int id);
				int GetID() const;
				void AddValue(const double value);
				double GetValue(const size_t index);
				size_t GetValuesSize();
				void ChangeValue(const size_t index, const double newValue);
				std::vector<double> GetValues();
				Point operator+(const Point &p);
				Point operator=(const Point &p);
				bool operator==(const Point &p);
				bool operator<(const Point &p);
				Point operator/(size_t m);				
				void PrintValuesToConsole();
				void WriteValuesToFile(std::ostream &out);

			};
		}
	}
}

#endif	//	!POINT_H