/*!
*PropertiesParser.cpp: implementation of the PropertiesParser class.
*/

#include "stdafx.h"
#include "PropertiesParser.h"

/*!
* Constructor. Initializes the parser parsing the properties file and
* reading all properties in the \c propMap.
*
* @param propertiesFilename the filename of the properties file.
*/
MLL::UTIL::PropertiesParser::PropertiesParser(std::string propertiesFilename)
{
	AddPropertiesFile(propertiesFilename);
}

/*!
* Destructor. Destroys the map object propMap of the class and frees the corresponding memory.
*/
MLL::UTIL::PropertiesParser::~PropertiesParser()
{
	propMap.clear();
}

/*!
* Parses a properties file and reads all properties in the \c propMap.
* It may be used consecutively to parse multiple properties files.
*
* @param propertiesFilename the filename of the properties file.
*/
void MLL::UTIL::PropertiesParser::AddPropertiesFile(std::string propertiesFilename)
{
	std::ifstream propertiesFileStream(propertiesFilename);
	std::string line;
	if (propertiesFileStream.is_open())
	{
		if (propertiesFileStream.good())
		{
			while (propertiesFileStream.eof() == false)
			{
				line.clear();
				std::getline(propertiesFileStream, line);
				if (line.length() > 0 && line[0] != '#')	/*! line is not a comment line*/
				{
					std::string propertyName;
					std::string propertyValue;
					std::stringstream ss(line);
					char c;//c used to eat the '=' character
					ss >> propertyName >> c >> propertyValue;
					propMap[propertyName] = propertyValue;
				}
			}
		}
		propertiesFileStream.close();
	}
}

/*!
* Checks if a property exists.
*
* @param propertyName the name of the property to be checked.
* @return \c true if property exists, \c false otherwise.
*/
bool MLL::UTIL::PropertiesParser::PropertyExists(std::string propertyName)
{
	return (!(propMap.find(propertyName) == propMap.end()));
}

/*!
* Returns the string value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a string value for the property.
*/
std::string MLL::UTIL::PropertiesParser::GetPropertyAsString(std::string propertyName)
{
	return propMap[propertyName];
}

/*!
* Returns the integer value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return an integer value for the property.
*/
int MLL::UTIL::PropertiesParser::GetPropertyAsInt(std::string propertyName)
{
	int propertyValue = 0;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the boolean value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a boolean value for the property.
*/
bool MLL::UTIL::PropertiesParser::GetPropertyAsBool(std::string propertyName)
{
	bool propertyValue = true;
	propertyValue = (propMap[propertyName] == "true");
	return propertyValue;
}

/*!
* Returns the float value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a float value for the property.
*/
float MLL::UTIL::PropertiesParser::GetPropertyAsFloat(std::string propertyName)
{
	float propertyValue = 0.0f;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the double value of a property.
*
* @param propertyName the name of the property of which the value is returned.
* @return a double value for the property.
*/
double MLL::UTIL::PropertiesParser::GetPropertyAsDouble(std::string propertyName)
{
	double propertyValue = 0.0;
	std::stringstream strStream(propMap[propertyName]);
	strStream >> propertyValue;
	return propertyValue;
}

/*!
* Returns the string value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a string value for the property.
*/
std::string MLL::UTIL::PropertiesParser::GetPropertyAsStringOrDefaultTo(std::string propertyName, std::string defaultPropertyValue)
{
	return PropertyExists(propertyName) ? GetPropertyAsString(propertyName) : defaultPropertyValue;
}

/*!
* Returns the integer value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return an integer value for the property.
*/
int MLL::UTIL::PropertiesParser::GetPropertyAsIntOrDefaultTo(std::string propertyName, int defaultPropertyValue)
{
	return PropertyExists(propertyName) ? GetPropertyAsInt(propertyName) : defaultPropertyValue;
}

/*!
* Returns the boolean value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a boolean value for the property.
*/
bool MLL::UTIL::PropertiesParser::GetPropertyAsBoolOrDefaultTo(std::string propertyName, bool defaultPropertyValue)
{
	return PropertyExists(propertyName) ? GetPropertyAsBool(propertyName) : defaultPropertyValue;
}

/*!
* Returns the float value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a float value for the property.
*/
float MLL::UTIL::PropertiesParser::GetPropertyAsFloatOrDefaultTo(std::string propertyName, float defaultPropertyValue)
{
	return PropertyExists(propertyName) ? GetPropertyAsFloat(propertyName) : defaultPropertyValue;
}

/*!
* Returns the double value of a property, if it exists, or a default value if
* the property does not exist.
*
* @param propertyName the name of the property of which the value is returned.
* @param defaultPropertyValue the default property value.
* @return a double value for the property.
*/
double MLL::UTIL::PropertiesParser::GetPropertyAsDoubleOrDefaultTo(std::string propertyName, double defaultPropertyValue)
{
	return PropertyExists(propertyName) ? GetPropertyAsDouble(propertyName) : defaultPropertyValue;
}