#include "stdafx.h"
#include "GenericFunc.h"

/*!
*Function that returns the path of the project's executable.
*@return the path of the project's executable.
*/
std::string MLL::UTIL::gnfnc::GetExecutablePath()
{
	std::vector<char> executablePath(MAX_PATH);

	// Try to get the executable path with a buffer of MAX_PATH characters.
	DWORD result = ::GetModuleFileNameA(
		NULL, &executablePath[0], static_cast<DWORD>(executablePath.size())
	);

	// As long the function returns the buffer size, it is indicating that the buffer
	// was too small. Keep enlarging the buffer by a factor of 2 until it fits.
	while (result == executablePath.size()) {
		executablePath.resize(executablePath.size() * 2);
		result = ::GetModuleFileNameA(
			NULL, &executablePath[0], static_cast<DWORD>(executablePath.size())
		);
	}

	// If the function returned 0, something went wrong
	if (result == 0) {
		throw std::runtime_error("GetModuleFileName() failed");
	}

	// We've got the path, construct a standard string from it
	return std::string(executablePath.begin(), executablePath.begin() + result);
}

/*!
*Function that concatenates the path of the project's executable with a filename.
*@return the concatenation of the path of the project's executable with a filename.
*/
std::string MLL::UTIL::gnfnc::GetExecutablePathAndMatchItWithFilename(std::string filename)
{
	std::string execPath = GetExecutablePath();
	size_t found = execPath.find_last_of("\\");
	execPath = execPath.substr(0, found);
	std::stringstream ss;
	ss << execPath << "\\" << filename;
	return ss.str();
}

int MLL::UTIL::gnfnc::CountNumberOfLinesInFile(std::string filename)
{
	int numberOfLines = 0;
	std::string dataline = "";
	std::ifstream in(filename);
	if (in.is_open())
	{
		while (std::getline(in, dataline))
			numberOfLines++;
		in.close();
	}
	return numberOfLines;
}