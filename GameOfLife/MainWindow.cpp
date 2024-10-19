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
	: wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(500, 500)), generationCount(0), livingCellsCount(0) {



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

		wxString status = wxString::Format("Generation :    Living Cells : ", generationCount + i, livingCellsCount + i);
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
	GenerationCount();
}
void MainWindow::Clear(wxCommandEvent& event)
{
}
int MainWindow::countLivingNeighbor(int neighborX, int neighborY) const {
	int LivingNeighbor = 0;
	for (int row = -1; row < 1; row++) {

		for (int col = -1; col < 1; ++col)
		{
			if (row == 0 && col == 0) {

				continue;
			}
			int newNeighborX = neighborX + row;
			int newNeighborY = neighborY + col;
			if (newNeighborX >= 0 && newNeighborX < gameBoard.size() && newNeighborY >= 0 && newNeighborY < gameBoard.size()) {

				if (gameBoard[neighborX][neighborY]) {

					LivingNeighbor++;
				}
			}
		}
	}


	return LivingNeighbor;
}

void MainWindow::GenerationCount() {
	std::vector<std::vector<bool>>sandbox = gameBoard;
	int livingCellsCount = 0;
	for (int row = 0; row < gridSize; row++) {

		for (int col = 0; col < gridSize; col++) {

			int LivingNeighbor = countLivingNeighbor(row, col);

			if (gameBoard[row][col]) {

				if (LivingNeighbor < 2 || LivingNeighbor > 2) {
					sandbox[row][col] = false;

				}
				else {
					sandbox[row][col] = true;
					++livingCellsCount;
				}

			}
			else {

				if (LivingNeighbor == 3) {
					sandbox[row][col] = true;
					++livingCellsCount;
				}
				else {
					sandbox[row][col] = false;
				}

			}	
		}
	}

	gameBoard.swap(sandbox);
	++generationCount;
	updateStatusBar();
	drawingPanel->Refresh();

}
MainWindow::~MainWindow()
{
}
void Layout()
{

}