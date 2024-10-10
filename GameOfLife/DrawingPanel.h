#pragma once
#include "wx/wx.h"


//new class called DrawingPanel which should inherit from the wxPanel class
class DrawingPanel : public wxPanel
{

private:
	int gridSize = 15;

public:

	DrawingPanel(wxFrame* parent);
	//empty destructor
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);

	bool operator==(const DrawingPanel& other) const;
};

