#pragma once

#include <tinyxml.h>
#include "forms.hpp"

namespace Parser
{
	const std::vector<Forms::Form*> &ReadSVGFile();

	const char *GCodeCreator(const std::vector<Forms::Form*> forms);
}
