#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{

private:
	int gridSize = 15;

public:
	
	DrawingPanel(wxFrame* parent);
	~DrawingPanel();
	void OnPaint(wxPaintEvent& event);

	bool operator==(const DrawingPanel& other) const;
};

