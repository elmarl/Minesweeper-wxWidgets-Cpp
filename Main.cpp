#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)

wxEND_EVENT_TABLE()

// root window, give null ptr for parent window
Main::Main() : wxFrame(nullptr, wxID_ANY, "Ultimate Minesweeper", wxPoint(30,30), wxSize(317, 340), wxDEFAULT_FRAME_STYLE ^ wxRESIZE_BORDER)
{
	btn = new wxButton * [gridWidth*gridHeight];
	
	mineGrid = new int[gridWidth * gridHeight];
	
	wxFont gameFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			btn[y * gridHeight + x] = new wxButton(this, 10000 + (y * gridHeight + x),"", wxPoint(x*30, y*30), wxSize(30,30));
			btn[y * gridHeight + x]->SetFont(gameFont);
			btn[y * gridHeight + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::onButtonClicked, this);
			btn[y * gridHeight + x]->Bind(wxEVT_RIGHT_DOWN, &Main::onRightButtonClicked, this);
			mineGrid[y * gridHeight + x] = 0;
		}
	}
}

Main::~Main()
{
	// deletion of window and all its children done by the framework
}


void Main::onButtonClicked(wxCommandEvent &evnt) {
	
	int x = (evnt.GetId() - 10000) % gridWidth;
	int y = (evnt.GetId() - 10000) / gridHeight;

	if (btn[y * gridWidth + x]->GetLabel() == "!") {
		evnt.Skip();
		return;
	}

	if (bFirstClick) {
		generateGrid(x, y);
		bFirstClick = false;
	}
	// check for mine hit
	if (mineGrid[y * gridHeight + x] == -1) {
		btn[y * gridHeight + x]->SetLabel("X");
		wxMessageBox("Stepped on a Mine! Game Over");
		// reset gamegrid
		resetGame();
	}
	else {
		clearCells(x, y);
	}
	evnt.Skip();
}

void Main::onRightButtonClicked(wxMouseEvent& evnt)
{
	int x = (evnt.GetId() - 10000) % gridWidth;
	int y = (evnt.GetId() - 10000) / gridHeight;

	(btn[y * gridHeight + x]->GetLabel() == "!") ? btn[y * gridHeight + x]->SetLabel("") : btn[y * gridHeight + x]->SetLabel("!");
}

void Main::resetGame()
{
	bFirstClick = true;
	for (int x = 0; x < gridWidth; x++)
	{
		for (int y = 0; y < gridHeight; y++)
		{
			mineGrid[y * gridHeight + x] = 0;
			btn[y * gridHeight + x]->SetLabel("");
			btn[y * gridHeight + x]->Enable(true);
		}
	}
}

void Main::generateGrid(int& x, int& y)
{
	int mines = 15;

	while (mines)
	{
		int rx = rand() % gridWidth;
		int ry = rand() % gridHeight;

		if (mineGrid[ry * gridHeight + rx] == 0 && rx != x && ry != y) {
			mineGrid[ry * gridHeight + rx] = -1;
			mines--;
		}
	}
}

int Main::countMines(int& x, int& y)
{
	int numberOfMines = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight)
			{
				if (mineGrid[(y + j) * gridHeight + (x + i)] == -1) {
					numberOfMines++;
				}
			}
		}
	}
	return numberOfMines;
}

void Main::clearCells(int x, int y)
{
	if (btn[(y)*gridHeight + (x)]->IsEnabled() && mineGrid[(y)*gridHeight + (x)] != -1) {
		btn[y * gridHeight + x]->Enable(false);
		int numberOfMines = countMines(x, y);
		if (numberOfMines > 0) {
			btn[y * gridHeight + x]->SetLabel(std::to_string(countMines(x, y)));
			return;
		}

		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight)
				{
					clearCells(x+i, y+j);
				}
			}
		}
	}
}

