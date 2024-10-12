#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class MainWindow :public wxFrame
{
private:
	std::vector<int>* pNumbers;
	DrawingPanel* drawingPanel = nullptr;
	wxBoxSizer* _sizer = nullptr;
	void OnSizeChanged(wxSizeEvent& event);
	std::vector<std::vector<bool>> gameBoard;
	int gridSize = 15;
public:
	
	MainWindow();
	~MainWindow();
	void initializeGrid();
};

