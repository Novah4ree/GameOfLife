#pragma once
#include "wx/wx.h"
#include <vector>


//new class called DrawingPanel which should inherit from the wxPanel class
class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>&gameBoard);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);
	void SetSize(const wxSize& size);
	void setGridSize(int size);
	void OnMouseUp(wxMouseEvent& event);
	
private:
	int gridSize;
	std::vector<std::vector<bool>>&gameBoard;
	wxDECLARE_EVENT_TABLE();
};

