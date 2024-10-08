#pragma once
#include "wx/wx.h"

class Window : public wxFrame
{
private:
    wxButton* buttonIncreaseX = nullptr;
    wxButton* buttonDecreaseX= nullptr;
    wxButton* buttonIncreaseY= nullptr;
    wxButton* buttonDecreaseY = nullptr;


public:
    Window();
    wxDECLARE_EVENT_TABLE();
    void OnButtonClick(wxCommandEvent& event);
};

