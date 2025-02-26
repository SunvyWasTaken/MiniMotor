#pragma once

namespace Sunset
{
	using MsgList = std::vector<std::string>;
	struct Logger
	{
		static void AddLog(const std::string& msg);
		static MsgList& Get();
	};
}

#define LOG(x) Logger::AddLog(x);