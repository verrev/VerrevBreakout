#pragma once

#include "CConsoleCommand.h"
#include <algorithm>
#include <ctime>

class CGetTimeCommand : public CConsoleCommand
{
public:
	CGetTimeCommand(std::wstring command, std::wstring usageHelp = L"") { addAlias(command); usageInstructions = usageHelp; }
	~CGetTimeCommand() {}
	std::wstring carryOut(std::wstring command) override
	{
		parseArguments(command);

		std::wstring result = L"";
		result += L"\nCurrent time is ";

		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);

		if (containsArgument(L"a") || !arguments.size()) {
			result += std::to_wstring(now.tm_year + 1900);
			result += L"/";
			result += std::to_wstring(now.tm_mon + 1);
			result += L"/";
			result += std::to_wstring(now.tm_mday);
			result += L" ";
			result += std::to_wstring(now.tm_hour);
			result += L":";
			result += std::to_wstring(now.tm_min);
			result += L":";
			result += std::to_wstring(now.tm_sec);
		}
		else {
			if (containsArgument(L"y")) {
				result += std::to_wstring(now.tm_year + 1900);
			}
			if (containsArgument(L"m")) {
				result += L"/";
				result += std::to_wstring(now.tm_mon + 1);
			}
			if (containsArgument(L"d")) {
				result += L"/";
				result += std::to_wstring(now.tm_mday);
			}
			if (containsArgument(L"t")) {
				result += std::to_wstring(now.tm_hour);
				result += L":";
				result += std::to_wstring(now.tm_min);
				result += L":";
				result += std::to_wstring(now.tm_sec);
			}
		}

		return result;
	}
};