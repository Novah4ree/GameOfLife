
#include "Dialog.h"
#include "GameSettings.h"
#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
//#include "Icon.xpm"
#include "wx/filedlg.h"
#include "wx/numdlg.h"
#include "wx/wx.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)

EVT_SIZE(MainWindow::OnSizeChanged)
EVT_MENU(10001, MainWindow::Play)
EVT_MENU(10002, MainWindow::Pause)
EVT_MENU(10003, MainWindow::Next)
EVT_MENU(10004, MainWindow::Clear)
EVT_TIMER(10005, MainWindow::TimerOn)
EVT_MENU(10006, MainWindow::Settings)
EVT_MENU(10007, MainWindow::OnNeighborCount)
EVT_MENU(10008, MainWindow::OnRandomize)
EVT_MENU(10009, MainWindow::RandomizeWithSeed)
EVT_MENU(10010, MainWindow::OnNew)
EVT_MENU(10011, MainWindow::OnOpen)
EVT_MENU(10012, MainWindow::OnSave)
EVT_MENU(10013, MainWindow::OnSaveAs)
EVT_MENU(10014, MainWindow::OnExit)
EVT_MENU(10015, MainWindow::OnFinite)
EVT_MENU(10016, MainWindow::OnToroidal)
//EVT_MENU(10010, MainWindow::Icon)

wxEND_EVENT_TABLE()


MainWindow::MainWindow()
	: wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100, 100), wxSize(500, 500)), generationCount(0), livingCellsCount(0), time(50) {


	settings.Load();
	_sizer = new wxBoxSizer(wxVERTICAL);
	drawingPanel = new DrawingPanel(this, gameBoard);
	drawingPanel->SetSettings(&settings);
	_sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);
	
	//status Bar

	statusBar = CreateStatusBar();
	statusBar->SetStatusText("Status Text");
	updateStatusBar();
	initializeGrid();
	this->Layout();

	//Icons for Toolbar
	wxBitmap playIcon(play_xpm);
	wxBitmap pauseIcon(pause_xpm);
	wxBitmap nextIcon(next_xpm);
	wxBitmap trashIcon(trash_xpm);
	//wxBitmap iconIcon(Icon_xpm);
	
	//ToolBar created
	wxToolBar* toolBar = CreateToolBar();
    //toolBar->AddTool(10010, "Test", Icon);
	toolBar->AddTool(10001, "Play", playIcon);
	toolBar->AddTool(10002, "Pause", pauseIcon);
	toolBar->AddTool(10003, "Next", nextIcon);
	toolBar->AddTool(10004, "Clear", trashIcon);
	toolBar->Realize();
	//Timer
	timer = new wxTimer(this, 10005);
	timer->Bind(wxEVT_TIMER, &MainWindow::TimerOn,this);
	Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);
	Bind(wxEVT_MENU, &MainWindow::OnNeighborCount, this, 10007);
	Bind(wxEVT_MENU, &MainWindow::OnRandomize, this, 10008);
	Bind(wxEVT_MENU, &MainWindow::RandomizeWithSeed, this, 10009);
	Bind(wxEVT_MENU, &MainWindow::OnNew, this, 10010);
	Bind(wxEVT_MENU, &MainWindow::OnOpen, this, 10011);
	Bind(wxEVT_MENU, &MainWindow::OnSave, this, 10012);
	Bind(wxEVT_MENU, &MainWindow::OnSaveAs, this, 10013);
	Bind(wxEVT_MENU, &MainWindow::OnExit, this, 10014);
	Bind(wxEVT_MENU, &MainWindow::OnFinite, this, 10015);
	Bind(wxEVT_MENU, &MainWindow::OnToroidal, this, 10016);

	matrix.resize(30);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i].resize(30);
	}

	PopulateMatrix();
	SetSizer(_sizer);

	//MenuBar
	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* optionsMenu = new wxMenu();
	wxMenu* viewMenu = new wxMenu();
	wxMenu* fileMenu = new wxMenu();
	menuBar->Append(fileMenu, "&File");
	
	fileMenu->Append(10010,"New");
	fileMenu->Append(10011, "Open");
	fileMenu->Append(10012, "Save As");
	fileMenu->Append(10013, "Exit");

	wxMenuItem* OnNeighborCountsItem = new wxMenuItem(viewMenu, 10007, "Neighbor Count", " ", wxITEM_CHECK);
	wxMenuItem* FiniteItem = new wxMenuItem(viewMenu, 10015, "Finite", " ", wxITEM_CHECK);
	wxMenuItem* ToroidalItem = new wxMenuItem(viewMenu, 10016, "Toroidal", " ", wxITEM_CHECK);

	FiniteItem->SetCheckable(true);
	ToroidalItem->SetCheckable(true);
	OnNeighborCountsItem->SetCheckable(true);
	viewMenu->Append(FiniteItem);
	viewMenu->Append(ToroidalItem);
	viewMenu->Append(OnNeighborCountsItem);

	optionsMenu->Append(10006, "Settings");
	optionsMenu->Append(10009, "Randomize with Seed");
	optionsMenu->Append(10008, "Randomize");
	menuBar->Append(optionsMenu, "Options");
	menuBar->Append(viewMenu, "View");

	SetMenuBar(menuBar);
	FiniteItem->Check(true);
	ToroidalItem->Check(false);

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

void MainWindow::OnRandomize(wxCommandEvent& event)
{
	RandomizeGrid((unsigned int)time_t(NULL));
}
void MainWindow::RandomizeWithSeed(wxCommandEvent& event)
{
	long seed = wxGetNumberFromUser("Enter seed number", "Seed:  ", "Randomize with Seed", 0, LONG_MIN, LONG_MAX, this);
	if (seed != -1) {
		RandomizeGrid(seed);
	}

}
void MainWindow::RandomizeGrid(unsigned int seed)
{
	srand(seed);
	for (int row = 0; row < settings.gridSize; ++row) {
		for (int col = 0; col < settings.gridSize; ++col) {
			gameBoard[row][col] = rand() % 2 == 0;
		}
	}
	drawingPanel->Refresh();
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
void MainWindow::OnPlayButtonClick(wxCommandEvent& event) {
	SettingsDialog* dialog = new SettingsDialog(this, &settings);
	dialog->ShowModal();
	delete dialog;
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
		settings.Load();
		drawingPanel->Refresh();
	}
	delete dialog;

}
void MainWindow::OnShowNeighborCounts(wxCommandEvent& event)
{
	settings.Load();
	bool showNeighborCounts = event.IsChecked();
	drawingPanel->SetShowNeighbors(showNeighborCounts);
	settings.Save();
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
			if (settings.Universe == "Toroidal") {
				newNeighborX = (newNeighborX + settings.gridSize) % settings.gridSize;
				newNeighborY = (newNeighborY + settings.gridSize) % settings.gridSize;
	
			}
			if (newNeighborX >= 0 && newNeighborX < settings.gridSize && newNeighborY >= 0 && newNeighborY < settings.gridSize) {

				if (gameBoard[newNeighborX][newNeighborY]) {

					LivingNeighbor++;
				}
			}
		}
	}


	return LivingNeighbor;
}
void MainWindow::OnNeighborCount(wxCommandEvent& event)
{
	settings.Load();
	bool showNeightborCounts = event.IsChecked();
	drawingPanel->SetShowNeighbors(showNeightborCounts);
	settings.Save();
	if (showNeightborCounts) {
		for (int row = 0; row < settings.gridSize; row++) {
			for (int col = 0; col < settings.gridSize; col++) {
				neighborCounts[row][col] = countLivingNeighbor(row, col);
			}

		}
	}

	drawingPanel->Refresh();
}

void MainWindow::LoadGameBoard(const wxString& filePath)
{
}

void MainWindow::SaveGameBoard(const wxString& filePath)
{
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
void MainWindow::PopulateMatrix()
{
	unsigned int seed = (time_t(NULL));
	srand(seed);

	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix[row].size(); col++) {
			int num = rand();
			if (num % 100 < 45) {
				matrix[row][col] = true;
			}
			else {
				matrix[row][col] = false;
			}
		}
	}


}
void Layout()
{
}
bool MainWindow::isToroidal() const
{
	return settings.Universe == "Toroidal";
}
void MainWindow::SetToroidal(bool toroidal)
{
	if (toroidal) {
		settings.Universe = "Toroidal";
	}
	else {
		settings.Universe = "Finite";
	}
	settings.Save();
}

void MainWindow::OnFinite(wxCommandEvent& event)
{
	FiniteItem->Check(true);
	ToroidalItem->Check(false);
	settings.Universe = "Finite";
	settings.Save();
}

void MainWindow::OnToroidal(wxCommandEvent& event)
{
	FiniteItem->Check(false);
	ToroidalItem->Check(true);
	settings.Universe = "Toroidal";
	settings.Save();
}


void MainWindow::TimerOn(wxTimerEvent& event)
{
	NextGenerationCount();
}


void MainWindow::OnNew(wxCommandEvent& event)
{
	gameBoard.clear();
	gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
	saveFileName.clear();
	drawingPanel->Refresh();

}

void MainWindow::OnOpen(wxCommandEvent& event)
{
	wxFileDialog
		openFileDialog(this, _("Open .cells file"), "", "",
			"Cells files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	LoadGameBoard(openFileDialog.GetPath());
}

void MainWindow::OnSave(wxCommandEvent& event)
{
	if (saveFileName.empty()) {
		OnSaveAs(event);
	}
	else {
		SaveGameBoard(saveFileName);
	}
}

void MainWindow::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog
		saveFileDialog(this, _("Save .cells file"), "", "",
			"Cells files (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	saveFileDialog.GetPath();
	SaveGameBoard(saveFileName);
}

void MainWindow::OnExit(wxCommandEvent& event)
{

	Close(true);
}