#pragma once
#include "wx/wx.h"


//new class called DrawingPanel which should inherit from the wxPanel class
class DrawingPanel : public wxPanel
{

private:
	int gridSize;
	std::vector<std::vector<bool>>gameBoard;
public:

	~DrawingPanel();
	DrawingPanel(wxFrame* parent); 
	void OnPaint(wxPaintEvent& event);
	void SetSize(const wxSize& size);
	void setGridSize(int size);
};

