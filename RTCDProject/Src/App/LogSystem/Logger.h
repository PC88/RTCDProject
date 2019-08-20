#pragma once
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging - the logging system im using -PC
// This example was Constructed from SpdLog, examples and Yan Chernikov tutorials

class Logger
{
public:

	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
private:

	static std::shared_ptr<spdlog::logger> s_AppLogger;
};

