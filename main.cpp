/************************************************************************************/
/*																					*/
/*		File:			main.cpp													*/
/*		Description:	Tis file contains the application object which is the		*/
/*						entrance point of the program and the main window.			*/
/*						We are using for GUI interactions with the user, the cross	*/
/*						platform gui lib Qt (http://www.qt.io/)						*/
/*		Creation date:	15.08.2015													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Tutor:			PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#include <QtWidgets\qapplication.h>
#include "mainwindow.h"

#include "tools\mathlib.h"

// Main program 
int main(int argc, char* argv[]) 
{	
	// The one and only application object
	QApplication app(argc, argv);

	// Creates the main window of the application
	MainWindow mainWindow;
	mainWindow.showMaximized();

	return app.exec();
}