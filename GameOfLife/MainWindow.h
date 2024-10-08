#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"


class MainWindow :public wxFrame
{
private:
	std::vector<int>* pNumbers;

public:
	DrawingPanel *drawingPanel;
	MainWindow();
	~MainWindow();

};

