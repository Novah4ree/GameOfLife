
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
EVT_MENU(10006, MainWindow::Settings)
EVT_MENU(10007, MainWindow::OnNeighborCount)
EVT_TIMER(10005, MainWindow::TimerOn)

wxEND_EVENT_TABLE()


MainWindow::MainWindow()
	: wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(500, 500)), generationCount(0), livingCellsCount(0), time(50) {



	_sizer = new wxBoxSizer(wxVERTICAL);
	drawingPanel = new DrawingPanel(this, gameBoard);
	drawingPanel->SetSettings(&settings);
	_sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);

	//status Bar
	statusBar = CreateStatusBar();
	updateStatusBar();
	initializeGrid();
	this->Layout();

	//Icons for Toolbar
	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);
	//ToolBar created
	toolBar = CreateToolBar();
	toolBar->AddTool(10001, "Play", playIcon);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	toolBar->AddTool(10003, "Next", nextIcon);
	toolBar->AddTool(10004, "Clear", trashIcon);
	toolBar->Realize();

	//Timer
	timer = new wxTimer(this, 10005);
	timer->Bind(wxEVT_TIMER, &MainWindow::TimerOn, this);
	Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);
	Bind(wxEVT_MENU, &MainWindow::OnNeighborCount, this, 10007);
	SetSizer(_sizer);

    //MenuBar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* optionsMenu = new wxMenu();
	wxMenu* viewMenu = new wxMenu();

	wxMenuItem* OnNeighborCountsItem = new wxMenuItem(viewMenu, 10007, "Neighbor Count", " ", wxITEM_CHECK);
	
	OnNeighborCountsItem-> SetCheckable(true);
	viewMenu->Append(OnNeighborCountsItem);
	menuBar->Append(viewMenu, "View");
	optionsMenu->Append(10006, "Settings");
	menuBar->Append(optionsMenu, "Options");

	SetMenuBar(menuBar);



}
//Resize 
void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	wxSize newSize = event.GetSize();
	drawingPanel->SetSize(event.GetSize());
	drawingPanel->Refresh();

	event.Skip();
}
//Grid
void MainWindow::initializeGrid() {
	gameBoard.resize(settings.gridSize);
	//store neighbor counts
	neighborCounts.resize(settings.gridSize, std::vector<int>
		(settings.gridSize, 0));
	for (int i = 0; i < settings.gridSize; ++i) {
		gameBoard[i].resize(settings.gridSize, false); // makes cells (dead)

	}
	drawingPanel->SetGridSize(settings.gridSize);
}

//Status bar 
void MainWindow::updateStatusBar() const
{
	wxString status = wxString::Format("Generation : %d Living Cells : %d", generationCount, livingCellsCount);
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
void MainWindow::Settings(wxCommandEvent& event)
{
	SettingsDialog* dialog = new SettingsDialog(this, &settings);
	GameSettings oldSettings = settings;
	
	//opens SettingsDialog

	if (dialog->ShowModal() == wxID_OK) { //check for ok
		drawingPanel->SetSettings(&settings);
		
		initializeGrid();
		drawingPanel->SetBackgroundColour(settings.GetBackgroundColor());


		drawingPanel->Refresh();
		settings.Save();


	}
	else {
		
		settings = oldSettings;
		drawingPanel->SetSettings(&settings);
		initializeGrid();
		updateStatusBar();
		drawingPanel->SetBackgroundColour(settings.GetBackgroundColor());
		drawingPanel->Refresh();
	}
	delete dialog;

}
void MainWindow::OnNeighborCount(wxCommandEvent& event)
{
}
void MainWindow::OnShowNeighborCounts(wxCommandEvent& event)
{
	bool showNeighborCounts = event.IsChecked();
	drawingPanel->SetShowNeighbors(showNeighborCounts);
	
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

				if (gameBoard[newNeighborX][newNeighborY]) {

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
					++newLivingCellsCount;
				}

			}
			else {

				if (LivingNeighbor == 3) {
					sandbox[row][col] = true;
					++newLivingCellsCount;
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

void MainWindow::TimerOn(wxTimerEvent& event)
{
	NextGenerationCount();
}