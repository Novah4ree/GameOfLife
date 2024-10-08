#pragma once
#include "wx/wx.h"


class MainWindow :public wxFrame
{
private:
	std::vector<int>* pNumbers;

public:
	MainWindow();
	~MainWindow();

};

