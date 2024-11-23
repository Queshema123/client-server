#include "logger.h"
#include <fstream>
#include <iostream>
#include <ctime>

std::string Logger::getTagName(Tag name) const
{
	switch (name)
	{
	case Logger::Tag::Message:
		return "message";
	case Logger::Tag::Error:
		return "error";
	default:
		return "unknown_tag";
	}
}

std::string Logger::getXMLToken(const std::string& type, const std::string& content) const
{
	time_t stamp;
	time(&stamp);
	return '<' + type + " Time=\"" + ctime(&stamp) + '\"' + '>' + content + '<' + type + "/>";
}

void Logger::log(const std::string& text, Tag name) const
{
	std::ofstream out(path+file_name, std::ios_base::out);
	if (!out.is_open())
	{
		std::cerr << "Can't open file to log - " << getTagName(name) << '\n';
		return;
	}
	out << getXMLToken(getTagName(name), text) << '\n';
	out.close();
}
