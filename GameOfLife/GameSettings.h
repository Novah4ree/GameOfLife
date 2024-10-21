#pragma once
#include <wx/colour.h>

struct GameSettings {
	//colors
	unsigned int Red = 255;
	unsigned int Blue = 255;
	unsigned int Green = 255;
	unsigned int Alpha = 255;

	//colors for Living Cell
	unsigned int livingCellRed = 128;
	unsigned int livingCellGreen = 128;
	unsigned int livingCellBlue = 128;
	unsigned int livingCellAlpha = 255;

	//colors for Dead Cell
	unsigned int deadCellRed = 255;
	unsigned int deadCellGreen = 255;
	unsigned int deadCellBlue = 255;
	unsigned int deadCellAlpha = 255;
	//grid size
	int gridSize = 15;
	//interval
	int interval = 50;

	//Methods to get wxColor

	wxColor GetColor() {
		wxColor color(Red, Green, Blue, Alpha);
		return color;
	}
	//Methods to get wxColor for LCC
	wxColor GetLivingCellColors() const {
		return wxColor(livingCellRed, livingCellGreen, livingCellBlue, livingCellAlpha);
	}
	//Methods to get wxColor for DCC
	wxColor GetDeadCellColors() const {
		return wxColor(deadCellRed, deadCellGreen, deadCellBlue, deadCellAlpha);
	}
	// setters for Color
	void SetColor(wxColor color) {
		Red = color.GetRed();
		Green = color.GetGreen();
		Blue = color.GetBlue();
		Alpha = color.GetAlpha();
	}
	// setter for LCC
	void SetLivingCellColor(const wxColor& color)
	{
		livingCellRed = color.GetRed();
		livingCellGreen = color.GetGreen();
		livingCellBlue = color.GetBlue();
		livingCellAlpha = color.GetAlpha();
	}
	// setter for DCC
	void SetDeadCellColor(const wxColor& color)
	{
		deadCellRed = color.GetRed();
		deadCellGreen = color.GetGreen();
		deadCellBlue = color.GetBlue();
		deadCellAlpha = color.GetAlpha();
	}

};