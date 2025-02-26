#include "Logger.h"

namespace
{
	Sunset::MsgList messages;
}

namespace Sunset
{
	void Logger::AddLog(const std::string& msg)
	{
		messages.emplace_back(msg);
	}

	MsgList& Logger::Get()
	{
		return messages;
	}
	
}