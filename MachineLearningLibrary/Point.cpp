#include "stdafx.h"
#include "Point.h"

/*! 
 * Constructor. 
 */
MLL::UL::Clustering::Point::Point() : id(-1)
{
}

/*! 
 * Destructor. 
 */
MLL::UL::Clustering::Point::~Point()
{
	if (!values.empty()) values.clear();
}

/*! 
 * Sets the ID of the point. 
 */
void MLL::UL::Clustering::Point::SetID(const int id)
{
	this->id = id;
}

/* 
 * Returns the ID of the point.
 * @return
 */
int MLL::UL::Clustering::Point::GetID() const
{
	return id;
}

/*! 
 * Add value to the values vector of the point. 
 * @param
 */
void MLL::UL::Clustering::Point::AddValue(const double value)
{
	values.push_back(value);
}

/*! 
 * Get a value from the values vector of the point, for a specific index. 
 * @param
 * @return
 */
double MLL::UL::Clustering::Point::GetValue(const size_t index)
{
	return (index >= 0 && index < values.size()) ? values[index] : -1.0;	// -1.0 error indicator
}

/*! 
 * Get the size of the values vector of the point. 
 * @return
 */
size_t MLL::UL::Clustering::Point::GetValuesSize()
{
	return values.size();
}

/*! 
 * Change a value of the values vector of the point, at a specific index. 
 * @param
 * @param
 */
void MLL::UL::Clustering::Point::ChangeValue(const size_t index, const double newValue)
{
	if (index >= 0 && index < values.size())
		values[index] = newValue;
}

std::vector<double> MLL::UL::Clustering::Point::GetValues()
{
	return values;
}

MLL::UL::Clustering::Point MLL::UL::Clustering::Point::operator+(const Point &p)
{
	if (values.size() == p.values.size())
	{
		for (size_t i = 0; i < values.size(); ++i)
			values[i] += p.values[i];
	}
	return *this;
}

MLL::UL::Clustering::Point MLL::UL::Clustering::Point::operator/(size_t m)
{
	for (size_t i = 0; i < values.size(); ++i)
		values[i] /= m;
	return *this;
}

MLL::UL::Clustering::Point MLL::UL::Clustering::Point::operator=(const Point &p)
{
	if (values.size() == 0)
	{
		for (size_t i = 0; i < p.values.size(); ++i)
			values.push_back(p.values[i]);
	}
	else
	{
		for (size_t i = 0; i < p.values.size(); ++i)
			values[i] = p.values[i];
	}
	return *this;
}

bool MLL::UL::Clustering::Point::operator==(const Point &p)
{
	size_t s1 = values.size();
	size_t s2 = p.values.size();
	size_t s = s1 < s2 ? s1 : s2;
	for (int i = 0; i < s; ++i)
		if (values[i] != p.values[i]) return false;
	return true;
}

bool MLL::UL::Clustering::Point::operator<(const Point &p)
{
	if (values.size() == p.values.size())
	{
		for (size_t i = 0; i < values.size(); ++i)
			if (values[i] >= p.values[i]) return false;
		return true;
	}
	else
		return false;
}

/*! 
 * Prints the values of the point in console. 
 */
void MLL::UL::Clustering::Point::PrintValuesToConsole()
{
	for (size_t i = 0; i < values.size(); ++i)
		std::cout << " " << values[i];
}

/*! 
 * Prints the values of the point in a file. 
 */
void MLL::UL::Clustering::Point::WriteValuesToFile(std::ostream &out)
{
	for (size_t i = 0; i < values.size(); ++i)
		out << " " << values[i];
}