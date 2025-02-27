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
		std::cerr << msg << std::endl;
	}

	MsgList& Logger::Get()
	{
		return messages;
	}
	
	Mesure::Mesure(const std::string& text)
		: time(std::chrono::steady_clock::now())
		, txt(text)
	{
		LOG("Start : {}", txt);
	}

	Mesure::~Mesure()
	{
		std::chrono::duration<float> delta = std::chrono::steady_clock::now() - time;
		LOG("End : {} -> {}s", txt, delta.count());
	}
}