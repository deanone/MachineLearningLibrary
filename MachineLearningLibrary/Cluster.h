#ifndef CLUSTER_H
#define CLUSTER_H

#include "Point.h"

namespace MLL
{
	namespace UL
	{
		namespace Clustering
		{
			class Cluster
			{
				int id;
			public:
				std::vector<Point*> pointsOfCluster;
				Point center;
			public:
				Cluster(Point center_, int id_);
				~Cluster();
				void SetID(const int id);
				int GetID() const;
				void SetCenter(Point& center);
				Point GetCenter();
				void SetPointsToCluster(Point *p);
				size_t GetNumOfPointsInCluster();
				Point* GetPointOfCluster(const size_t index);
				void ClearPointsOfCluster();
				bool operator==(Cluster &c);
				bool operator<(Cluster &c);
				void PrintCentroidInConsole();
				void PrintAllocationInConsole();
				void WriteCentroidToFile(std::ostream &out);
				void WriteAllocationToFile(std::ostream &out);
			};
		}
	}
}

#endif	//	!CLUSTER_H