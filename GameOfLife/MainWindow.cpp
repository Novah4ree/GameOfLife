#define TOOLBAR_PLAY_ICON 10001
#include "Dialog.h"
#include "GameSettings.h"
#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "Dialog.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

EVT_SIZE(MainWindow::OnSizeChanged)
EVT_MENU(10001, MainWindow::Play)
EVT_MENU(10002, MainWindow::Pause)
EVT_MENU(10003, MainWindow::Next)
EVT_MENU(10004, MainWindow::Clear)
EVT_TIMER(10005, MainWindow::timerOn)

wxEND_EVENT_TABLE()


MainWindow::MainWindow()
	: wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(500, 500)), generationCount(0), livingCellsCount(0), time(50) {



	_sizer = new wxBoxSizer(wxVERTICAL);
	drawingPanel = new DrawingPanel(this, gameBoard);
	drawingPanel->SetSettings(&settings);
	_sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
	
	statusBar = CreateStatusBar();
	updateStatusBar();
	initializeGrid();
	this->Layout();

	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);

	toolBar = CreateToolBar();
	toolBar->AddTool(TOOLBAR_PLAY_ICON, "Play", playIcon);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	toolBar->AddTool(10003, "Next", nextIcon);
	toolBar->AddTool(10004, "Clear", trashIcon);
	toolBar->Realize();

	timer = new wxTimer(this, 10005);
	timer->Bind(wxEVT_TIMER, &MainWindow::timerOn, this);
	Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);

	SetSizer(_sizer);
}
void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	wxSize newSize = event.GetSize();
	drawingPanel->SetSize(event.GetSize());
	drawingPanel->Refresh();

	event.Skip();
}
void MainWindow::initializeGrid() {
	gameBoard.resize(settings.gridSize);
	for (int i = 0; i < settings.gridSize; ++i) {
		gameBoard[i].resize(settings.gridSize, false); // makes cells (dead)

	}
	drawingPanel->setGridSize(settings.gridSize);
}
void MainWindow::updateStatusBar() const
{
	wxString status = wxString::Format("Generation :   %d Living Cells : %d", generationCount, livingCellsCount);
		statusBar->SetStatusText(status);
}
void MainWindow::Play(wxCommandEvent& event)
{
	timer->Start(settings.interval);
}
void MainWindow::Pause(wxCommandEvent& event)
{
	timer->Stop();
}

void MainWindow::Next(wxCommandEvent& event)
{
	NextGenerationCount();
}

void MainWindow::Clear(wxCommandEvent& event)
{
	for (int row = 0; row < settings.gridSize; ++row) {
		for (int col = 0; col < settings.gridSize; ++col) {
			gameBoard[row][col] = false;
		}
	}
	generationCount = 0; 
	livingCellsCount = 0;
	updateStatusBar(); 
	drawingPanel->Refresh();
}
int MainWindow::countLivingNeighbor(int neighborX, int neighborY) const {
	int LivingNeighbor = 0;
	for (int row = -1; row <= 1; row++) {

		for (int col = -1; col <= 1; ++col)
		{
			if (row == 0 && col == 0)
				continue;
			int newNeighborX = neighborX + row;
			int newNeighborY = neighborY + col;
			if (newNeighborX >= 0 && newNeighborX < settings.gridSize && newNeighborY >= 0 && newNeighborY < settings.gridSize) {

				if (gameBoard[neighborX][neighborY]) {

					LivingNeighbor++;
				}
			}
		}
	}


	return LivingNeighbor;
}

void MainWindow::NextGenerationCount() {
	std::vector<std::vector<bool>>sandbox = gameBoard;
	int newLivingCellsCount = 0;
	for (int row = 0; row < settings.gridSize; row++) {

		for (int col = 0; col < settings.gridSize; col++) {

			int LivingNeighbor = countLivingNeighbor(row, col);

			if (gameBoard[row][col]) {

				if (LivingNeighbor < 2 || LivingNeighbor > 3) {
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
	livingCellsCount = newLivingCellsCount;
	++generationCount;
	updateStatusBar();
	drawingPanel->Refresh();

}
MainWindow::~MainWindow()
{
	delete timer;
}
void Layout()
{
}

void MainWindow::OnPlayButtonClick(wxCommandEvent& event) {
	SettingsDialog* dialog = new SettingsDialog (this, &settings);
	dialog->ShowModal();
	delete dialog;
}

void MainWindow::timerOn(wxTimerEvent& event)
{
	NextGenerationCount();
}