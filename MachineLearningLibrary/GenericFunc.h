#ifndef MACHINE_LEARNING_LIBRARY_UTILITIES_GENERIC_FUNC_H
#define MACHINE_LEARNING_LIBRARY_UTILITIES_GENERIC_FUNC_H

/*!
* GenericFunc.h : interface of the gnfnc namespace.
*/

#include <string>

namespace MLL
{
	namespace UTIL
	{
		namespace gnfnc
		{
			std::string GetExecutablePath();
			std::string GetExecutablePathAndMatchItWithFilename(const std::string& filename);
			size_t CountNumberOfRowsInFile(const std::string& filename);
			size_t CountNumberOfColsInFile(const std::string& filename);
		}
	}
}

#endif	//	!MACHINE_LEARNING_LIBRARY_UTILITIES_GENERIC_FUNC_H