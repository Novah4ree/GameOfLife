#include "Window.h"
#define BUTTON_INCREASE_X_ID 10001
#define BUTTON_DECREASE_X_ID 10002
#define BUTTON_INCREASE_Y_ID 10003
#define BUTTON_DECREASE_Y_ID 10004

wxBEGIN_EVENT_TABLE(Window, wxFrame)
EVT_BUTTON(BUTTON_INCREASE_X_ID, Window::OnButtonClick)
EVT_BUTTON(BUTTON_DECREASE_X_ID, Window::OnButtonClick)
EVT_BUTTON(BUTTON_INCREASE_Y_ID, Window::OnButtonClick)
EVT_BUTTON(BUTTON_DECREASE_Y_ID, Window::OnButtonClick)
wxEND_EVENT_TABLE()

Window::Window() : wxFrame(nullptr, wxID_ANY, "COS1 Example", wxPoint(100, 100), wxSize(300, 300)) {
	buttonIncreaseX= new wxButton(this, BUTTON_INCREASE_X_ID, "Increase X",wxPoint(50,50), wxSize(75,25));
	buttonDecreaseX = new wxButton(this, BUTTON_DECREASE_X_ID,"Decrease X", wxPoint(150, 50), wxSize(75,25));
	buttonIncreaseY = new wxButton(this, BUTTON_INCREASE_Y_ID, "Increase Y", wxPoint(50, 150), wxSize(75, 25));
	buttonDecreaseY= new wxButton(this, BUTTON_DECREASE_Y_ID, "Decrease Y", wxPoint(150, 50), wxSize(75, 25));
	Bind(wxEVT_BUTTON, &Window::OnButtonClick, this);
}
void Window::OnButtonClick(wxCommandEvent& event) {
	int id = event.GetId();
	switch (id) {
	case BUTTON_INCREASE_X_ID:
		SetSize(wxSize(GetSize().x + 10, GetSize().y + 10));
		break;
	case BUTTON_DECREASE_X_ID:
		SetSize(wxSize(GetSize().x - 10, GetSize().y - 10));
		break;
	case BUTTON_INCREASE_Y_ID:
		SetSize(wxSize(GetSize().x + 10, GetSize().y + 10));
		break;
	case BUTTON_DECREASE_Y_ID:
		SetSize(wxSize(GetSize().x - 10, GetSize().y - 10));
		break;
	}
}
