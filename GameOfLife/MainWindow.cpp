#include "MainWindow.h"
#include "DrawingPanel.h"

MainWindow::~MainWindow() {}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(100,100), wxSize(500, 500)) {
   
  drawingPanel = new DrawingPanel(this);
  
  _sizer = new wxBoxSizer(wxVERTICAL);
  
  _sizer->Add(drawingPanel, 1, wxEXPAND | wxALL);

  this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChanged, this);

  SetSizer(_sizer);
}

void MainWindow::OnSizeChanged(wxSizeEvent& event) {
	wxSize newSize = event.GetSize();
	event.Skip();
	drawingPanel->SetSize(newSize);
	drawingPanel->Refresh();
}