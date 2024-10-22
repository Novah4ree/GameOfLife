#pragma once
#include <wx/colour.h>
#include <fstream>

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

	//extra --background color setup
	unsigned int backgroundRed = 255;
	unsigned int backgroundGreen = 255;
	unsigned int backgroundBlue = 255;
	unsigned int backgroundAlpha = 255;

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

	//getter for background color
	wxColor GetBackgroundColor() const {
		return wxColor(backgroundRed, backgroundBlue, backgroundGreen, backgroundAlpha);
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
	// extra setter for Background
	void SetBackgroundColor(const wxColor& color) {
		
		backgroundRed = color.GetRed();
		backgroundGreen = color.GetGreen();
		backgroundBlue = color.GetBlue();
		backgroundAlpha = color.GetAlpha();
	}
	void Save() const 
	{ std::ofstream file("settings.bin", std::ios::out | std::ios::binary); 
	 file.write((char*)this, sizeof(GameSettings));
	 file.close();

	}

	void Load() 
	{
		std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
		if (file.is_open()) {
			file.read((char*)this, sizeof(GameSettings));
			file.close();
		}
	}
};