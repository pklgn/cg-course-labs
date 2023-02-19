#include "../pch.h"
#include "CommandLineParser.h"

const int ARGUMENTS_NUMBER = 5;

void CommandLineParser::Parse()
{
	if (m_wasParsed)
	{
		return;
	}

	auto cmdLine = GetCommandLine();
	int numArgs;
	auto params = CommandLineToArgvW(cmdLine, &numArgs);

	if (numArgs < ARGUMENTS_NUMBER)
	{
		throw std::invalid_argument(std::format("Wrong number of command line arguments was given ({} needed)", ARGUMENTS_NUMBER));
	}

	m_leftTop = {
		std::stoi(params[1]),
		std::stoi(params[2])
	};

	m_frameSize = {
		std::stoi(params[3]),
		std::stoi(params[4])
	};

	m_lineThickness = std::stoi(params[5]);

	m_wasParsed = true;
}

CPoint CommandLineParser::GetLeftTop()
{
	return m_leftTop;
}

CSize CommandLineParser::GetFrameSize()
{
	return m_frameSize;
}

int CommandLineParser::GetLineThickness()
{
	return m_lineThickness;
}
