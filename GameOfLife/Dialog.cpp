#include "Dialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::Ok)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::Cancel)
wxEND_EVENT_TABLE()

//Settings Dialog UI
SettingsDialog::SettingsDialog(wxWindow *parent, GameSettings *settings): wxDialog(parent, wxID_ANY, "Settings", wxPoint(100,150), wxSize(400,250)), _settings(settings)
{    
	//Spinner
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(sizer);

	wxBoxSizer* SpinnerSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* ColorSizer = new wxBoxSizer(wxHORIZONTAL);

	_Spinner = new wxSpinCtrl(this, wxID_ANY);
	_ColorPick = new wxColourPickerCtrl(this, wxID_ANY);
	wxStaticText* spinnerLabel = new wxStaticText(this, wxID_ANY, "Number");
	spinnerLabel->SetMinSize(wxSize(100, 50));

	wxStaticText* ColorLabel = new wxStaticText(this, wxID_ANY, " Color");
	ColorLabel->SetMinSize(wxSize(100, 50));

	SpinnerSizer->Add(spinnerLabel);
	SpinnerSizer->Add(_Spinner);
	
	ColorSizer->Add(ColorLabel);
	ColorSizer->Add(_ColorPick);
	sizer->Add(SpinnerSizer);
	sizer->Add(ColorSizer);




	//grid
	wxBoxSizer* mainBoxSizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);

	gridSizeSizer->Add(new wxStaticText(this, wxID_ANY, "Grid Size: "), 0, wxALL);

    _gridSizeCtrl = new wxSpinCtrl(this, wxID_ANY);

	_gridSizeCtrl->SetValue(_settings->gridSize);

	gridSizeSizer->Add(_gridSizeCtrl, 1, wxALL);


	//interval
	wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);

	intervalSizer->Add(new wxStaticText(this, wxID_ANY, "Interval: "), 0, wxALL);
  
	_intervalCtrl = new wxSpinCtrl(this, wxID_ANY);

	_intervalCtrl->SetValue(_settings->interval);

	intervalSizer->Add(_intervalCtrl, 1, wxALL);

	mainBoxSizer->Add(intervalSizer, 0, wxEXPAND | wxALL);

	//LCC
	wxBoxSizer* LivingCellColorSizer = new wxBoxSizer(wxHORIZONTAL);

	LivingCellColorSizer->Add(new wxStaticText(this, wxID_ANY, "Living Cell Color: "), 0, wxALL);

	_LivingCellColorsPick = new wxColourPickerCtrl(this, wxID_ANY, _settings->GetLivingCellColors());

	LivingCellColorSizer->Add(_LivingCellColorsPick, 1, wxALL);

	mainBoxSizer->Add(LivingCellColorSizer, 0, wxEXPAND | wxALL);

	//DCC
	wxBoxSizer* DeadCellColorSizer = new wxBoxSizer(wxHORIZONTAL);

	DeadCellColorSizer->Add(new wxStaticText(this, wxID_ANY, "Dead Cell Color: "), 0, wxALL);

	_DeadCellColorsPick = new wxColourPickerCtrl(this, wxID_ANY, _settings->GetLivingCellColors());

	DeadCellColorSizer->Add(_DeadCellColorsPick, 1, wxALL);

	mainBoxSizer->Add(DeadCellColorSizer, 0, wxEXPAND | wxALL);

	//background
	wxBoxSizer* BackgroundColorSizer = new wxBoxSizer(wxHORIZONTAL);

	BackgroundColorSizer->Add(new wxStaticText(this, wxID_ANY, "Background Color: "), 0, wxALL);

	_BackgroundColorPick = new wxColourPickerCtrl(this, wxID_ANY, _settings->GetLivingCellColors());

	BackgroundColorSizer->Add(_BackgroundColorPick, 1, wxALL);

	mainBoxSizer->Add(BackgroundColorSizer, 0, wxEXPAND | wxALL);

	//ok
	mainBoxSizer->Add(CreateButtonSizer(wxOK));

	//cancel
	mainBoxSizer->Add(CreateButtonSizer(wxCANCEL));

	SetSizer(mainBoxSizer);
	
}
//Settings Dialog UI
void SettingsDialog::Ok(wxCommandEvent& event)
{ // makes sure that any changes in grid size or color are visible after clicking ok from settings
	_settings->gridSize = _gridSizeCtrl->GetValue();

	_settings->gridSize = _intervalCtrl->GetValue();
	_settings->SetLivingCellColor(_LivingCellColorsPick->GetColour());
	_settings->SetDeadCellColor(_DeadCellColorsPick->GetColour());
	_settings->SetBackgroundColor(_BackgroundColorPick->GetColour());
	//close the dialog wit ok
	EndModal(wxID_OK);
}

void SettingsDialog::Cancel(wxCommandEvent& event)
{

	EndModal(wxID_CANCEL);
}
