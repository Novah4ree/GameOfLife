#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include "GameSettings.h"

class SettingsDialog : public wxDialog
{
public:
    SettingsDialog(wxWindow *parent, GameSettings *settings);

private:
    GameSettings* _settings;
    wxSpinCtrl* _Spinner =  nullptr;
    wxSpinCtrl* _gridSizeCtrl = nullptr;
    wxSpinCtrl* _intervalCtrl = nullptr;
    wxColourPickerCtrl* _ColorPick = nullptr;
    wxColourPickerCtrl* _LivingCellColorsPick = nullptr;
    wxColourPickerCtrl* _DeadCellColorsPick = nullptr;

    void Ok(wxCommandEvent& event);
    void Cancel(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
