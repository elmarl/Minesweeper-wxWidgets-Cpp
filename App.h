#pragma once

#include "wx/wx.h"
#include "Main.h"

class App : public wxApp
{
public:
		App();
		~App();

private:
	Main* my_frame1 = nullptr;

public:
	virtual bool OnInit();
};

