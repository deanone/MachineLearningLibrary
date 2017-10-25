#ifndef MACHINE_LEARNING_LIBRARY_UNSUPERVISED_LEARNING_CLUSTERING_KMEANS_H
#define MACHINE_LEARNING_LIBRARY_UNSUPERVISED_LEARNING_CLUSTERING_KMEANS_H

#include "Point.h"
#include "Cluster.h"

#include <map>

namespace MLL
{
	namespace UL
	{
		namespace Clustering
		{
			class Kmeans
			{
				int	dimension;
				int k;
				int numOfIterations;
				int distanceMetric;
			public:
				std::vector<Point> points;
				std::vector<Cluster> initialClusters;
				std::vector<Cluster> finalClusters;
				std::map<int, int> pointIDClusterIDAllocation;
				std::map<int, std::vector<int> > clusterIDPointsOfClusterIDsAllocation;

			public:
				Kmeans(std::string datasetFilename, std::string propertiesFileName);
				Kmeans(std::string datasetFilename, int d, int numOfClusters, int numIt, int distMetric);
				~Kmeans();
				void SetDimension(int dimension);
				int GetDimension() const;
				void SetK(int k);
				int GetK() const;
				void SetPointsToClusters();
				void SetInitialClustersRandomly();
				void SetInitialClustersByInitialPoints();
				void SetFinalClusters();
				void Initialize();
				bool isOver();
				void RunKmeans();
				void WriteCentroidsToFile(std::string centroidsFilename);
				void CreatePointIDClusterIDAllocation();
				void CreateClusterIDPointsOfClusterIDsAllocation();
				void WriteClusterIDPointsOfClusterIDsAllocationToFile(std::string allocationFilename1);
				void WritePointIDClusterIDAllocationToFile(std::string allocationFilename2);
				double CalculateSilhouette();
				double CalculateWCSS();
				double CalculateDaviesBouldinIndex();
			};
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_UNSUPERVISED_LEARNING_CLUSTERING_KMEANS_H