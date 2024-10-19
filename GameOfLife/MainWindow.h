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

	DrawingPanel* drawingPanel = nullptr;
	wxToolBar* toolBar;
	wxStatusBar* statusBar = nullptr;
	wxBoxSizer* _sizer = nullptr;

	std::vector<wxSize>_sizes;
	std::vector<std::vector<bool>> gameBoard;

	int countLivingNeighbor(int neighborX, int neighborY) const;
	int generationCount; 
	int livingCellsCount;
	int gridSize = 15;

	void initializeGrid();
	void OnSizeChanged(wxSizeEvent& event);
	void GenerationCount();
	void updateStatusBar() const;
	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Clear(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
	

};

