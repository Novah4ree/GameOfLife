#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"


DrawingPanel::DrawingPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 200))
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
	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context)
	{
		return;
	}

	context->SetPen(*wxBLACK_PEN);
	context->SetBrush(*wxTRANSPARENT_BRUSH);

	int cellSize = 10;

	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			int x = col * cellSize;
			int y = row * cellSize;
			context->DrawRectangle(x, y, cellSize, cellSize);
		}
	}
	
	delete context;

}

bool DrawingPanel::operator==(const DrawingPanel& other) const
{
	return false;
}
