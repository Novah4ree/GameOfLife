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
	wxMenuItem* FiniteItem;
	wxMenuItem* ToroidalItem;
	wxMenuItem* OnNeighborCountsItem;
	
	wxToolBar* toolBar;
	wxStatusBar* statusBar = nullptr;
	wxBoxSizer* _sizer = nullptr;
	DrawingPanel* drawingPanel = nullptr;
	wxTimer* timer ;
	GameSettings settings; 
	int time;

	

	//std::vector<std::vector<icon>> Icon;
	std::vector<std::vector<bool>> matrix;
	std::vector<std::vector<int>> neighborCounts;
	std::vector<std::vector<bool>> gameBoard;
	
	int countLivingNeighbor(int neighborX, int neighborY) const;
	int generationCount; 
	int livingCellsCount;
	int gridSize;
	wxString saveFileName;
	

	void LoadGameBoard(const wxString& filePath);
	void SaveGameBoard(const wxString& filePath);
	void NextGenerationCount();
	void TimerOn(wxTimerEvent& event);
	void initializeGrid();
	void updateStatusBar() const;
	void RandomizeGrid(unsigned int seed);


	void OnSizeChanged(wxSizeEvent& event);
	void OnFinite(wxCommandEvent& event);
	void OnToroidal(wxCommandEvent& event);
	void OnPlayButtonClick(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnRandomize(wxCommandEvent& event);
	void RandomizeWithSeed(wxCommandEvent& event);

	void Play(wxCommandEvent& event);
	void Pause(wxCommandEvent& event);
	void Next(wxCommandEvent& event);
	void Clear(wxCommandEvent& event);
	void Settings(wxCommandEvent& event);
	void OnNeighborCount(wxCommandEvent& event);
	void OnShowNeighborCounts(wxCommandEvent& event);
	bool isToroidal() const;
	void SetToroidal(bool toroidal);
	wxDECLARE_EVENT_TABLE();
	

};

