#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

EVT_SIZE(MainWindow::OnSizeChanged)

EVT_MENU(10001, MainWindow::Play)
EVT_MENU(10002, MainWindow::Pause)
EVT_MENU(10003, MainWindow::Next)
EVT_MENU(10004, MainWindow::Clear)

wxEND_EVENT_TABLE()


MainWindow::MainWindow()
 : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100,100), wxSize(500, 500)), generationCount(0), livingCellsCount(0){
   
	

  _sizer = new wxBoxSizer(wxVERTICAL);
  drawingPanel = new DrawingPanel(this, gameBoard);
  _sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
  SetSizer(_sizer);


  statusBar = CreateStatusBar();
  updateStatusBar();
  initializeGrid();
  this->Layout();


  toolBar = CreateToolBar();
  wxBitmap playIcon(play_xpm);
  wxBitmap pauseIcon(pause_xpm);
  wxBitmap nextIcon(next_xpm);
  wxBitmap trashIcon(trash_xpm);
  toolBar->AddTool(10001, "Play", playIcon);
  toolBar->AddTool(10002, "Pause", pauseIcon);
  toolBar->AddTool(10003, "Next", nextIcon);
  toolBar->AddTool(10004, "Clear", trashIcon);
  toolBar->Realize();

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
	for (int i = 0; i < 10; ++i) {
	
		wxString status = wxString::Format("Generation :   \n" " Living Cells : \n",generationCount + i, livingCellsCount + i);
		statusBar->SetStatusText(status);
	}
}
void MainWindow::Play(wxCommandEvent& event)
{


}
void MainWindow::Pause(wxCommandEvent& event)
{
}
void MainWindow::Next(wxCommandEvent& event)
{
}
void MainWindow::Clear(wxCommandEvent& event)
{
}
MainWindow::~MainWindow()
{
}
void Layout()
{

}
 