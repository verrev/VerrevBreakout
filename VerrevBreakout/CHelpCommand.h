#pragma once

#include "CConsoleCommand.h"

class CHelpCommand : public CConsoleCommand
{
public:
	CHelpCommand(std::wstring command, std::wstring usageHelp = L"") { addAlias(command); usageInstructions = usageHelp; }
	~CHelpCommand() {}
	std::wstring carryOut(std::wstring command) override
	{
		std::wstring result = L"";
		result += L"\nThis is a shell for executing various commands. What follows is a list of possible\ncalls one can make.\n";
		result += L"---help : displays this text\n";
		result += L"---clr : clears the screen\n";
		result += L"---load [filename], $[mode] : loads a file, filename - path to file, mode (optional) binary\nor ASCII\n";
		result += L"---time : displays current time and date";
		return result;
	}
};