#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_AppLogger;

void Logger::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%"); // this sets the pattern of the logger 
	// in the above brackets it states in the following order - PC
	//  color, name of logger, timestamp, message -PC
	s_AppLogger = spdlog::stdout_color_mt("RTCD_LOGGER");
	s_AppLogger->set_level(spdlog::level::trace);
}
