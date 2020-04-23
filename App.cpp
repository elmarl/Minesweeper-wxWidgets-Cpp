#include "App.h"

// generate main
wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	my_frame1 = new Main();
	my_frame1->Show();

	return true;
}
