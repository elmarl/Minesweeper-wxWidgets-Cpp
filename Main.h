#pragma once

#include "wx/wx.h"

class Main : public wxFrame
{
public:
	Main();
	~Main();

private:
	// fields
	int gridWidth = 10;
	int gridHeight = 10;
	wxButton** btn;
	int* mineGrid = nullptr;
	bool bFirstClick = true;

	// methods
	void onButtonClicked(wxCommandEvent &evnt);
	void onRightButtonClicked(wxMouseEvent& evnt);
	// reset game
	void resetGame();
	// generate the game grid with the first click as a parameter, since it will only ever be generated after the first click
	void generateGrid(int& x, int& y);
	// count surrounding mines in 3x3 matrix
	int countMines(int& x, int& y);
	void clearCells(int x, int y);

	wxDECLARE_EVENT_TABLE();
};

