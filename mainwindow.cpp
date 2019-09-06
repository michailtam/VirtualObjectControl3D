#include "mainwindow.h"

const int INTERVAL = 1000;


// Constructor
MainWindow::MainWindow()
{
	// Setup the user interface
	ui.setupUi(this);
	
	// Create the central child window and set it as central 
	mCentralChildWindow = new CentralChildWindow(this);
	setCentralWidget(mCentralChildWindow);
}


// Destructor
MainWindow::~MainWindow()
{
	if (mCentralChildWindow !=0)
		delete mCentralChildWindow;
}