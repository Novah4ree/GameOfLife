#include "MainWindow.h"
#include "DrawingPanel.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

EVT_SIZE(MainWindow::OnSizeChanged)

wxEND_EVENT_TABLE()


MainWindow::MainWindow() 
 : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100,100), wxSize(500, 500)), gameBoard(gridSize, std::vector<bool>(gridSize, false)), generationCount(0), livingCellsCount(0) {
   
	

  _sizer = new wxBoxSizer(wxVERTICAL);
  
  drawingPanel = new DrawingPanel(this, gameBoard);

  _sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
  SetSizer(_sizer);
  statusBar = CreateStatusBar();
  updateStatusBar();
  initializeGrid();
  this->Layout();
}



void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	wxSize newSize = event.GetSize();
	if (drawingPanel != nullptr) {

		drawingPanel->SetSize(newSize);
	}
	
	event.Skip();
}

void MainWindow::initializeGrid() {
	gameBoard.resize(gridSize);
	for (int i = 0; i < gridSize; ++i) {
		gameBoard[i].resize(gridSize, false); // makes cells (dead)

	}
	drawingPanel->setGridSize(gridSize);
}

void MainWindow::updateStatusBar() const

{
}
MainWindow::~MainWindow()
{
}
void Layout()
{

}
