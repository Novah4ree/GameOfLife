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
	void PopulateMatrix();
private:

	wxToolBar* toolBar;
	wxStatusBar* statusBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	DrawingPanel* drawingPanel = nullptr;
	wxTimer* timer ;
	GameSettings settings;
	int time;
	
	std::vector<std::vector<bool>> matrix;
	std::vector<std::vector<int>> neighborCounts;
	std::vector<std::vector<bool>> gameBoard;
	
	int countLivingNeighbor(int neighborX, int neighborY) const;
	int generationCount; 
	int livingCellsCount;
	

	
	void NextGenerationCount();
	void OnPlayButtonClick(wxCommandEvent& event);
	void TimerOn(wxTimerEvent& event);
	void initializeGrid();
	void OnSizeChanged(wxSizeEvent& event);
	void updateStatusBar() const;
	
	void RandomizeGrid(unsigned int seed);
	void OnRandomize(wxCommandEvent& event);
	void RandomizeWithSeed(wxCommandEvent& event);
	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Clear(wxCommandEvent& event);
	void Settings(wxCommandEvent& event);
	void OnNeighborCount(wxCommandEvent& event);
	void OnShowNeighborCounts(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
	

};

