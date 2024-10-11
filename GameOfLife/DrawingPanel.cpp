#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0))
{
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->SetDoubleBuffered(true);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	
}

DrawingPanel::~DrawingPanel(){}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	// Create a wxGraphicsContext from the wxAutoBufferedPaintDC
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context)
	{
		return;
	}
	//used the wxgrahicscontext to draw
	context->SetPen(*wxBLACK_PEN);
	context->SetBrush(*wxTRANSPARENT_BRUSH);

	// size of panel
	int pWidth; int pHeight;// this is the panel Height/width

	int cellSize = 10;
	GetClientSize(&pWidth, &pHeight);

	// cell size calculated
	int cellWidth = pWidth / gridSize; //helps resize the cells width with the panel seperate
	int cellHeight = pHeight / gridSize;//helps resize the cells height with the panel seperate
	 
	//draws the grid
	for (int row = 0; row < gridSize; ++row) { //loop for roow
		for (int col = 0; col < gridSize; ++col) {// loop for column
			int x = col * cellWidth;
			int y = row * cellHeight;
			context->DrawRectangle(x, y, cellWidth, cellHeight);
		}
	}
	// CLean up
	delete context;

}
void DrawingPanel::SetSize(const wxSize& size)
{
	wxPanel::SetSize(size);
	Refresh(); //repaint
}


