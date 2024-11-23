#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>

class Logger
{
	std::string path, file_name;
public:
	Logger(const std::string& path = "", const std::string& fname) : path{ path }, file_name{ fname + ".xml"} { }
	~Logger() = default;

	enum class Tag{ Message, Error };
	std::string getTagName(Tag name) const;
	std::string getXMLToken(const std::string& type, const std::string& content) const;
	void log(const std::string& text, Tag name) const;
	
	inline std::string getPathToFile() const { return path; }
	inline void setPathToFile(const std::string& file) { this->path = path; }
};

#endif // !_LOGGER_H_
