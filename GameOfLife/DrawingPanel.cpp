#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)

EVT_PAINT(DrawingPanel::OnPaint)

EVT_LEFT_UP(DrawingPanel::OnMouseUp)

wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, std::vector<std::vector<bool>>& gameBoard)
	: wxPanel(parent), gameBoard(gameBoard), gridSize(15), _settings(nullptr), showNeighbors(false)
{

	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->SetDoubleBuffered(true);
	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this, 0);
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseUp, this, 0);


}

DrawingPanel::~DrawingPanel() {}

void DrawingPanel::SetSettings(GameSettings* settings) {
	_settings = settings;

}

void DrawingPanel::SetShowNeighbors(bool show) {

	showNeighbors = show;
}
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

	// size of panel

	wxSize boardSize = this->GetSize();


	// cell size calculated
	float cellWidth = boardSize.x / (float)gridSize; //helps resize the cells width with the panel seperate
	float cellHeight = boardSize.y / (float)gridSize;//helps resize the cells height with the panel seperate
	//by change my int to float for cellwidth/ cellheight also added (float) in front of gridSize
	// i was able to eliminate the extra gaps on the side and bottom of my game board.
	//draws the grid
	//used the wxgrahicscontext to draw
	context->SetPen(*wxBLACK_PEN);

	for (int row = 0; row < gridSize; ++row) {//loop for roow

		for (int col = 0; col < gridSize; ++col) {// loop for column
			float x = col * cellWidth;
			float y = row * cellHeight;
			if (gameBoard[row][col]) {
				context->SetBrush(*wxLIGHT_GREY);
			}
			else {
				context->SetBrush(*wxWHITE);
			}

			context->DrawRectangle(x, y, cellWidth, cellHeight);

			context->SetFont(wxFontInfo(16), *wxRED);
			for (int x = 0; x < gridSize; ++x) {

				for (int y = 0; y < gridSize; ++y) {
					if (showNeighbors) {
						int neighborCount = neighborCounts[row][col];

						if (neighborCount > 0) {
							wxString text = wxString::Format("% d", neighborCount);
							double textWidth, textHeight;
							context->GetTextExtent(text, &textWidth, &textHeight);
							context->DrawText(text, x * cellWidth + (cellWidth - textWidth) / 2, y * cellHeight + (cellHeight - textHeight) / 2);

						}
					}
				}
			}
		}
	}

	// CLean up
	delete context;

}
void DrawingPanel::SetSize(const wxSize& size)
{
	wxPanel::SetSize(size);

}

void DrawingPanel::SetGridSize(int size)
{
	int gridSize = size;
	Refresh();
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();


	wxSize boardSize = this->GetSize();


	// cell size calculated
	float cellWidth = boardSize.x / (float)gridSize; //helps resize the cells width with the panel seperate
	float cellHeight = boardSize.y / (float)gridSize;


	int col = x / cellWidth;
	int row = y / cellHeight;

	if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
		gameBoard[row][col] = !gameBoard[row][col];
	}

	Refresh();
}