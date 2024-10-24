#pragma once
#include "wx/wx.h"
#include <vector>
#include "GameSettings.h"

//new class called DrawingPanel which should inherit from the wxPanel class
class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>&gameBoard);
	~DrawingPanel();
	void SetSettings(GameSettings* settings);
	void SetShowNeighbors(bool show);
	void OnPaint(wxPaintEvent& event);

	void SetSize(const wxSize& size);
	void SetGridSize(int size);
	void OnMouseUp(wxMouseEvent& event);
	
private:
	bool showNeighbors;
	GameSettings* _settings;
	int gridSize;
	std::vector<std::vector<bool>>&gameBoard;
	std::vector<std::vector<int>>neighborCounts;
	wxDECLARE_EVENT_TABLE();
};

