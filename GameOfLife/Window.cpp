#include "Window.h"

Window::Window() : wxFrame(nullptr, wxID_ANY, "COS1 Example", wxPoint(100, 100), wxSize(300, 200)) {

	button1 = new wxButton(this, 1001, "Click Here",wxPoint(25,50), wxSize(75,25));
	button2 = new wxButton(this, 1002, "Better Yet, Click Here", wxPoint(155, 50), wxSize(125, 25));

}