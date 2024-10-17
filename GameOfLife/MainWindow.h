#pragma once
#include "wx/wx.h"
#include <vector>
#include "DrawingPanel.h"


class MainWindow :public wxFrame
{
 public:
	MainWindow();
	~MainWindow();

private:
	void OnSizeChanged(wxSizeEvent& event);
	wxStatusBar* statusBar = nullptr;
	void initializeGrid();
	void updateStatusBar() const;
	std::vector<wxSize>_sizes;
	std::vector<std::vector<bool>> gameBoard;
	int gridSize = 15;
	DrawingPanel* drawingPanel = nullptr;
	int generationCount; 
	int livingCellsCount; 
	wxBoxSizer* _sizer = nullptr;


	wxDECLARE_EVENT_TABLE();
	

};

