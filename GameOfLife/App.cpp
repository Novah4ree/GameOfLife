#include "App.h"
#include "Window.h"
wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	Window* window = new Window();
	window->Show();
	return true;
}