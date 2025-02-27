#pragma once

namespace Sunset
{
	using MsgList = std::vector<std::string>;
	struct Logger
	{
		static void AddLog(const std::string& msg);
		static MsgList& Get();
	};

	struct Mesure
	{
		explicit Mesure(const std::string& text);
		~Mesure();
	private:
		std::chrono::time_point<std::chrono::steady_clock> time;
		std::string txt;
	};
}

#define LOG(x, ...) Logger::AddLog(std::format(x, ##__VA_ARGS__));
#define SCOPE_PROFILING(x, ...) Mesure _az(std::format(x, ##__VA_ARGS__));