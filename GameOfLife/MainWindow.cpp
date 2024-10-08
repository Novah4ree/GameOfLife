#include "MainWindow.h"
#include "DrawingPanel.h"

MainWindow::~MainWindow()
{
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0,0), wxSize(200, 200)) {
   
  drawingPanel = new DrawingPanel(this);
}
