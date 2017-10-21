#include "stdafx.h"
#include "Kmeans.h"
#include "PropertiesParser.h"
#include "MathFunc.h"

//bool less_f(const std::pair<int, int>& pair_a, const std::pair<int, int>& pair_b)
//{
//	return pair_a.second<pair_b.second;
//}

/*! 
 * Constructor.
 */
MLL::UL::Clustering::Kmeans::Kmeans(std::string datasetFilename, std::string propertiesFileName)
{
	MLL::UTIL::PropertiesParser pp(propertiesFileName);
	dimension = pp.GetPropertyAsIntOrDefaultTo("dimension", 4);
	k = pp.GetPropertyAsIntOrDefaultTo("k", 200);
	numOfIterations = pp.GetPropertyAsIntOrDefaultTo("numOfIterations", 1000);
	distanceMetric = pp.GetPropertyAsIntOrDefaultTo("distanceMetric", 1);
	std::string dataline;
	std::ifstream in;
	in.open(datasetFilename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (getline(ss, item, ','))
				items.push_back(item);
			int ID = std::stoi(items[0]);
			Point point;
			point.SetID(ID);
			for (size_t i = 1; i < items.size(); ++i)
				point.AddValue(std::stod(items[i]));
			items.clear();
			points.push_back(point);
		}
		in.close();
	}
	else
		std::cout << "Cannot open file.\n";
}

/*! 
 * Constructor 2. 
 */
MLL::UL::Clustering::Kmeans::Kmeans(std::string datasetFilename, int d, int numOfClusters, int numIt, int distMetric) :
	dimension(d), k(numOfClusters), numOfIterations(numIt), distanceMetric(distMetric)
{
	std::string dataline;
	std::ifstream in;
	in.open(datasetFilename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
		{
			std::stringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (getline(ss, item, ','))
				items.push_back(item);
			int ID = std::stoi(items[0]);
			Point point;
			point.SetID(ID);
			for (size_t i = 1; i < items.size(); ++i)
				point.AddValue(std::stod(items[i]));
			items.clear();
			points.push_back(point);
		}
		in.close();
	}
	else
		std::cout << "Cannot open file.\n";

}

/*! 
 * Destructor. 
 */
MLL::UL::Clustering::Kmeans::~Kmeans()
{
	if (!points.empty()) points.clear();
	if (!initialClusters.empty()) initialClusters.clear();
	if (!finalClusters.empty()) finalClusters.clear();
	if (!pointIDClusterIDAllocation.empty()) pointIDClusterIDAllocation.clear();
	if (!clusterIDPointsOfClusterIDsAllocation.empty()) clusterIDPointsOfClusterIDsAllocation.clear();
}

/*! 
 * Sets the dimension of the points of the dataset. 
 * @param
 */
void MLL::UL::Clustering::Kmeans::SetDimension(int dimension)
{
	this->dimension = dimension;
}

/*! 
 * Gets the dimension. 
 * @return
 */
int MLL::UL::Clustering::Kmeans::GetDimension() const
{
	return dimension;
}

/*! 
 * Sets the number of clusters.
 * @param
 */
void MLL::UL::Clustering::Kmeans::SetK(int k)
{
	this->k = k;
}

/*! 
 * Gets the number of clusters. 
 * @return
 */
int  MLL::UL::Clustering::Kmeans::GetK() const
{
	return k;
}

/*! 
 * Creates the initial clusters by choosing k random Points from the dataset. 
 */
void MLL::UL::Clustering::Kmeans::SetInitialClustersRandomly()
{
	srand(static_cast<size_t>(time(NULL)));
	for (int i = 0; i < k; ++i)
	{
		int index = rand() % points.size();
		Cluster cl(points[index/*i*/], i);
		initialClusters.push_back(cl);
	}
}

/*! 
 * Creates the initial clusters by choosing the first k Points from the dataset. 
 */
void MLL::UL::Clustering::Kmeans::SetInitialClustersByInitialPoints()
{
	for (int i = 0; i < k; ++i)
	{
		Cluster cl(points[i], i);
		initialClusters.push_back(cl);
	}
}

/*! 
 * Assigns Points to Clusters. 
 */
void MLL::UL::Clustering::Kmeans::SetPointsToClusters()
{
	double dist = 0.0;
	double minDist = 100000000.0;
	int minID;
	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = 0; j < initialClusters.size(); j++)
		{
			Point center = initialClusters[j].GetCenter();
			switch (distanceMetric)
			{
				case 1:
					dist = MLL::UTIL::mfnc::ComputeEuclideanDistance(points[i].GetValues(), center.GetValues());
					break;
				case 2:
					dist = MLL::UTIL::mfnc::ComputeEuclideanDistanceSquare(points[i].GetValues(), center.GetValues());
					break;
				case 3:
					dist = MLL::UTIL::mfnc::ComputeManhattanDistance(points[i].GetValues(), center.GetValues());
					break;
				case 4:
					dist = MLL::UTIL::mfnc::ComputeChebysevDistance(points[i].GetValues(), center.GetValues());
					break;
				case 5:
					dist = MLL::UTIL::mfnc::ComputeBrayCurtisDistance(points[i].GetValues(), center.GetValues());
					break;
				case 6:
					dist = MLL::UTIL::mfnc::ComputeCanberraDistance(points[i].GetValues(), center.GetValues());
					break;
				case 7:
					dist = MLL::UTIL::mfnc::ComputeCosineSimilarity(points[i].GetValues(), center.GetValues());
					break;
				case 8:
					dist = MLL::UTIL::mfnc::ComputePearsonCorrelation(points[i].GetValues(), center.GetValues());
					break;
				default:
					break;
			}
			if (dist < minDist)
			{
				minDist = dist;
				minID = j;
			}
		}
		initialClusters[minID].SetPointsToCluster(&points[i]);
		minDist = 100000000.0;
	}
}

/*! 
 * Makes the final clusters of the iteration n-1 initial clusters for the iteration n.
 */
void MLL::UL::Clustering::Kmeans::SetFinalClusters()
{
	int n;
	for (int i = 0; i < k; ++i)
	{
		Point new_centroid;
		new_centroid.SetID(i);
		for (int l = 0; l < dimension; ++l)
			new_centroid.AddValue(0.0);
		n = initialClusters[i].GetNumOfPointsInCluster();
		if (n != 0)
		{
			for (int j = 0; j < n; ++j)
				new_centroid = new_centroid + (*(initialClusters[i].GetPointOfCluster(j)));
			new_centroid = new_centroid / n;
			Cluster cl(new_centroid, i);
			for (int m = 0; m < n; ++m)
				cl.SetPointsToCluster(initialClusters[i].GetPointOfCluster(m));
			finalClusters.push_back(cl);
		}
		else
			finalClusters.push_back(initialClusters[i]);
	}
}

/*! 
 * Checks if the algorithm converged. 
 */
bool MLL::UL::Clustering::Kmeans::isOver()
{
	for (int i = 0; i < k; ++i)
		if (!(initialClusters[i].GetCenter() == finalClusters[i].GetCenter())) return false;
	return true;
}

void MLL::UL::Clustering::Kmeans::Initialize()
{
	initialClusters.clear();
	for (int i = 0; i < k; ++i)
	{
		finalClusters[i].ClearPointsOfCluster();
		initialClusters.push_back(finalClusters[i]);
	}
	finalClusters.clear();
}

/*! 
 * Runs the k-means routine. 
 */
void MLL::UL::Clustering::Kmeans::RunKmeans()
{
	// First iteration
	int it = 1;
	//setInitialClustersRandomly();
	SetInitialClustersByInitialPoints();
	SetPointsToClusters();
	SetFinalClusters();
	// Next iterations
	while ((!isOver()) && (it <= numOfIterations))
	{
		it++;
		Initialize();
		SetPointsToClusters();
		SetFinalClusters();
	}
}

void MLL::UL::Clustering::Kmeans::WriteCentroidsToFile(std::string centroidsFilename)
{
	std::ofstream out(centroidsFilename.c_str());
	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		finalClusters[i].WriteCentroidToFile(out);
		out << std::endl;
	}
	out.close();
}

void MLL::UL::Clustering::Kmeans::CreatePointIDClusterIDAllocation()
{
	for (size_t i = 0; i < finalClusters.size(); i++)
	{
		for (size_t j = 0; j < finalClusters[i].GetNumOfPointsInCluster(); j++)
			pointIDClusterIDAllocation.insert(std::make_pair(finalClusters[i].GetPointOfCluster(j)->GetID(), finalClusters[i].GetID())); // (PointID,ClusterID)
	}
}

void MLL::UL::Clustering::Kmeans::CreateClusterIDPointsOfClusterIDsAllocation()
{
	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		std::vector<int> pointsOfClusterIDs;
		for (size_t j = 0; j < finalClusters[i].GetNumOfPointsInCluster(); ++j)
			pointsOfClusterIDs.push_back(finalClusters[i].GetPointOfCluster(j)->GetID());
		clusterIDPointsOfClusterIDsAllocation.insert(std::make_pair(finalClusters[i].GetID(), pointsOfClusterIDs));
		pointsOfClusterIDs.clear();
	}
}

void MLL::UL::Clustering::Kmeans::WriteClusterIDPointsOfClusterIDsAllocationToFile(std::string allocationFilename1)
{
	std::ofstream out;
	out.open(allocationFilename1.c_str());
	for (auto it = clusterIDPointsOfClusterIDsAllocation.begin(); it != clusterIDPointsOfClusterIDsAllocation.end(); ++it)
	{
		int clusterID = it->first;
		std::vector<int> pointsOfClusterIDs = it->second;
		out << clusterID;
		for (size_t i = 0; i < pointsOfClusterIDs.size(); ++i)
			out << " " << pointsOfClusterIDs[i];
		out << std::endl;
		pointsOfClusterIDs.clear();
	}
	out.close();
}

void MLL::UL::Clustering::Kmeans::WritePointIDClusterIDAllocationToFile(std::string allocationFilename2)
{
	std::ofstream out;
	out.open(allocationFilename2.c_str());
	for (auto it = pointIDClusterIDAllocation.begin(); it != pointIDClusterIDAllocation.end(); ++it)
	{
		int pointID = it->first;
		int clusterID = it->second;
		out << pointID << " " << clusterID << std::endl;
	}
	out.close();
}

/*! 
 * Calculates the Silhouette metric. 
 * https://en.wikipedia.org/wiki/Silhouette_(clustering)
 * @return
 */
double MLL::UL::Clustering::Kmeans::CalculateSilhouette()
{
	std::vector<double> silhouettes;
	for (size_t i = 0; i < points.size(); ++i)
	{
		double a_for_point, final_b_for_point, temp_b, silhouetteForPoint;
		//	std::cout << "Calculating the average dissimilarity of point " << points[i].getID() << " of all other data within the same cluster..." << "\n";
		a_for_point = 0;
		int clusterID = -1;
		auto it = pointIDClusterIDAllocation.find(points[i].GetID());
		if (it != pointIDClusterIDAllocation.end())
			clusterID = it->second;

		for (size_t j = 0; j < finalClusters[clusterID].GetNumOfPointsInCluster(); ++j)
		{
			Point* pointOfCluster = finalClusters[clusterID].GetPointOfCluster(j);
			a_for_point += MLL::UTIL::mfnc::ComputeEuclideanDistance(points[i].GetValues(), pointOfCluster->GetValues());
		}
		a_for_point /= finalClusters[clusterID].GetNumOfPointsInCluster();

		//	std::cout << "Calculating the lowest average dissimilarity of point " << points[i].getID() << " of all other data of all other clusters..." << "\n";
		std::vector<double> b_for_point;
		for (size_t j = 0; j < finalClusters.size(); ++j)
		{
			if (finalClusters[j].GetID() != clusterID)
			{
				temp_b = 0;
				for (size_t k = 0; k < finalClusters[j].GetNumOfPointsInCluster(); ++k)
				{
					Point* pointOfCluster = finalClusters[j].GetPointOfCluster(k);
					temp_b += MLL::UTIL::mfnc::ComputeEuclideanDistance(points[i].GetValues(), pointOfCluster->GetValues());
				}
				temp_b /= finalClusters[j].pointsOfCluster.size();
				b_for_point.push_back(temp_b);
			}
		}
		final_b_for_point = *std::min_element(b_for_point.begin(), b_for_point.end());
		b_for_point.clear();

		//	std::cout << "Calculating the silhouette of point " << points[i].getID() <<"\n";
		silhouetteForPoint = (final_b_for_point - a_for_point) / max(a_for_point, final_b_for_point);
		silhouettes.push_back(silhouetteForPoint);
	}

	double silhouette = 0.0;
	for (size_t i = 0; i < silhouettes.size(); ++i)
		silhouette += silhouettes[i];
	silhouette /= (double)silhouettes.size();

	return silhouette;
}

/*! 
 * Calculates Within Cluster Sum of Squares (WCSS). 
 * @return
 */
double MLL::UL::Clustering::Kmeans::CalculateWCSS()
{
	double withinClusterVariance = 0.0;
	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		for (size_t j = 0; j < finalClusters[i].GetNumOfPointsInCluster(); ++j)
		{
			Point* pointOfCluster = finalClusters[i].GetPointOfCluster(j);
			Point center = finalClusters[i].GetCenter();
			withinClusterVariance += MLL::UTIL::mfnc::ComputeEuclideanDistance(pointOfCluster->GetValues(), center.GetValues());
		}
	}
	return withinClusterVariance;
}

/*!
 * Davies-Bouldin index for clustering results internal evaluation.
 * http://en.wikipedia.org/wiki/Cluster_analysis
 * http://en.wikipedia.org/wiki/Davies%E2%80%93Bouldin_index
 * @return
 */
double MLL::UL::Clustering::Kmeans::CalculateDaviesBouldinIndex()
{
	double DaviesDoublinIndex = 0.0;
	std::vector<double> AverageIntraClusterDistances;
	std::vector<std::vector<double> > InterClusterDistances;
	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		double averageIntaClusterDistance = 0.0;
		for (size_t j = 0; j < finalClusters[i].GetNumOfPointsInCluster(); ++j)
		{
			Point* pointOfCluster = finalClusters[i].GetPointOfCluster(j);
			Point center = finalClusters[i].GetCenter();
			averageIntaClusterDistance += MLL::UTIL::mfnc::ComputeEuclideanDistance(pointOfCluster->GetValues(), center.GetValues());
		}
		averageIntaClusterDistance /= finalClusters[i].GetNumOfPointsInCluster();
		AverageIntraClusterDistances.push_back(averageIntaClusterDistance);
	}

	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		std::vector<double> temp;
		double interClusterDistance;
		Point center1 = finalClusters[i].GetCenter();
		for (size_t j = 0; j < finalClusters.size(); ++j)
		{
			Point center2 = finalClusters[j].GetCenter();
			interClusterDistance = MLL::UTIL::mfnc::ComputeEuclideanDistance(center1.GetValues(), center2.GetValues());
			temp.push_back(interClusterDistance);
		}
		InterClusterDistances.push_back(temp);
	}

	for (size_t i = 0; i < finalClusters.size(); ++i)
	{
		double Di = -1.0;
		double maxDi = -1.0;
		for (size_t j = 0; j < finalClusters.size(); ++j)
		{
			if (i != j)
			{
				Di = (AverageIntraClusterDistances[i] + AverageIntraClusterDistances[j]) / InterClusterDistances[i][j];
				if (Di > maxDi) maxDi = Di;
			}
		}
		DaviesDoublinIndex += maxDi;
	}
	DaviesDoublinIndex /= finalClusters.size();

	return DaviesDoublinIndex;
}