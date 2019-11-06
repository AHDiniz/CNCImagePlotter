#pragma once

#include <string>

/**
 * Program configuration variables class holder
*/

class Config
{
public:
	inline static Config *GetInstance()
	{
		static Config *config = new Config();
		return config;
	}

	inline void SetFilename(const char *filename)
	{
		svgFilename = filename;
	}

	inline void SetPort(const char *port)
	{
		arduinoPort = port;
	}

	inline const std::string GetFilename() { return svgFilename; }
	inline const std::string GetPort() { return arduinoPort; }

private:
	std::string svgFilename;
	std::string arduinoPort;
};
