#pragma once
#include "wx/wx.h"
#include <vector>
#include "DrawingPanel.h"
#include "GameSettings.h"


class MainWindow :public wxFrame
{
 public:
	MainWindow();
	~MainWindow();

private:

	wxToolBar* toolBar = nullptr;
	wxStatusBar* statusBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	DrawingPanel* drawingPanel = nullptr;
	wxTimer* timer = nullptr;
	GameSettings settings;

	std::vector<wxSize>_sizes;
	std::vector<std::vector<bool>> gameBoard;

	int countLivingNeighbor(int neighborX, int neighborY) const;
	int generationCount; 
	int livingCellsCount;
	int time;
	
	void NextGenerationCount();
	void OnPlayButtonClick(wxCommandEvent& event);
	void timerOn(wxTimerEvent& event);
	void initializeGrid();
	void OnSizeChanged(wxSizeEvent& event);
	void updateStatusBar() const;
	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Clear(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
	

};

