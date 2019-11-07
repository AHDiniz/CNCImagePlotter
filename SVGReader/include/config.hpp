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

	inline void SetWidth(const int width)
	{
		this->width = width;
	}

	inline void SetHeight(const int height)
	{
		this->height = height;
	}

	inline const std::string GetFilename() { return svgFilename; }
	inline const std::string GetPort() { return arduinoPort; }

	inline const int GetWidth() { return width; }
	inline const int GetHeight() { return height; }

private:
	std::string svgFilename;
	std::string arduinoPort;
	int width = 0, height = 0;
};
