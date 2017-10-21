#include "stdafx.h"
#include "Cluster.h"

/*! 
 * Constructor. 
 * @param
 * @param
 */
MLL::UL::Clustering::Cluster::Cluster(Point center_, int id_) : center(center_), id(id_)
{
}

/*! 
 * Destructor. 
 */
MLL::UL::Clustering::Cluster::~Cluster()
{
	if (!pointsOfCluster.empty()) pointsOfCluster.clear();
}

/*! 
 * Sets the ID of the cluster. 
 * @param
 */
void MLL::UL::Clustering::Cluster::SetID(const int id)
{
	this->id = id;
}

/*! 
 * Returns the ID of the cluster. 
 * @return
 */
int MLL::UL::Clustering::Cluster::GetID() const
{
	return id;
}

/*! 
 * Sets the center of the cluster.
 * @param
 */
void MLL::UL::Clustering::Cluster::SetCenter(Point &center)
{
	this->center = center;
}

/*! 
 * Returns center of the cluster.
 * @return
 */
MLL::UL::Clustering::Point MLL::UL::Clustering::Cluster::GetCenter()
{
	return center;
}

/*! 
 * Adds point to the set of the points consisting the cluster.
 * @param
 */
void MLL::UL::Clustering::Cluster::SetPointsToCluster(Point *p)
{
	pointsOfCluster.push_back(p);
}

/*! 
 * Returns the number of points in this cluster. 
 * @return
 */
size_t MLL::UL::Clustering::Cluster::GetNumOfPointsInCluster()
{
	return pointsOfCluster.size();
}

/*! 
 * Returns a point of the cluster for the specific index. 
 * @param
 */
MLL::UL::Clustering::Point* MLL::UL::Clustering::Cluster::GetPointOfCluster(const size_t index)
{
	return (index >= 0 && index < pointsOfCluster.size()) ? pointsOfCluster[index] : nullptr;
}

/*! 
 * Delete points of cluster. 
 */
void MLL::UL::Clustering::Cluster::ClearPointsOfCluster()
{
	pointsOfCluster.clear();
}

bool MLL::UL::Clustering::Cluster::operator==(Cluster &c)
{
	return (center == c.center) ? true : false;
}

bool MLL::UL::Clustering::Cluster::operator<(Cluster &c)
{
	return (center < c.center) ? true : false;
}

/*! 
 * Prints the centroid of the cluster to console. 
 */
void MLL::UL::Clustering::Cluster::PrintCentroidInConsole()
{
	std::cout << id;
	center.PrintValuesToConsole();
}

/*! 
 * Prints the ids of the points of cluster to console. 
 */
void MLL::UL::Clustering::Cluster::PrintAllocationInConsole()
{
	for (size_t i = 0; i < pointsOfCluster.size(); ++i)
		std::cout << pointsOfCluster[i]->GetID() << " " << id << std::endl;
}

/*!
 * Writes the centroid of the cluster to file. 
 */
void MLL::UL::Clustering::Cluster::WriteCentroidToFile(std::ostream &out)
{
	out << id;
	center.WriteValuesToFile(out);
}

/*! 
 * Writes the ids of the points of cluster to file.
 */
void MLL::UL::Clustering::Cluster::WriteAllocationToFile(std::ostream &out)
{
	for (size_t i = 0; i < pointsOfCluster.size(); ++i)
		out << pointsOfCluster[i]->GetID() << " " << id << std::endl;
}