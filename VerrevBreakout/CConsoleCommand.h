#pragma once

#include <string>
#include <vector>
#include <sstream>

class CConsoleCommand
{
public:
	CConsoleCommand() {}
	virtual ~CConsoleCommand() {}
	inline std::wstring hit(const std::wstring &command)
	{
		for (auto s : commandAliases) if (command.find(s) != std::wstring::npos) return carryOut(command);
		return L"";
	}

	inline void addAlias(std::wstring command) { commandAliases.push_back(command); }

	inline void parseArguments(std::wstring command)
	{
		replaceAll(command, L" ", L"");
		std::vector<std::string> args = split(std::string(command.begin(), command.end()), '-');
		args.erase(args.begin());
		std::vector<std::wstring> retArgs;
		for (auto a : args) retArgs.push_back(std::wstring(a.begin(), a.end()));
		arguments = retArgs;
	}

	inline bool containsArgument(std::wstring arg)
	{
		for (auto a : arguments) if (a == arg) return true;
		return false;
	}

	virtual std::wstring carryOut(std::wstring command) = 0;
protected:
	std::vector<std::wstring> commandAliases;
	std::vector<std::wstring> arguments;
	std::wstring usageInstructions;
private:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}
	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	void replaceAll(std::wstring &s, const std::wstring &search, const std::wstring &replace) {
		for (size_t pos = 0; ; pos += replace.length()) {
			pos = s.find(search, pos);
			if (pos == std::wstring::npos) break;
			s.erase(pos, search.length());
			s.insert(pos, replace);
		}
	}
};