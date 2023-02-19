#pragma once

class CommandLineParser
{
public:
	void Parse();
	
	CPoint GetLeftTop();
	CSize GetFrameSize();
	int GetLineThickness();

private:
	bool m_wasParsed = false;
	CPoint m_leftTop;
	CSize m_frameSize;
	int m_lineThickness;
};
