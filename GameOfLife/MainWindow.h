#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"


class MainWindow :public wxFrame
{
private:
	std::vector<int>* pNumbers;
	DrawingPanel* drawingPanel = nullptr;
	wxBoxSizer* _sizer = nullptr;
	void OnSizeChanged(wxSizeEvent& event);
public:
	MainWindow();
	~MainWindow();
};

