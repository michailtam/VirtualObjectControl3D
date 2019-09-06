/************************************************************************************/
/*																					*/
/*		File:			mainwindow.h												*/
/*		Description:	This class represents the main window which contains the	*/
/*						calibration window and the central child window				*/
/*						(which contains the render and information window)			*/
/*		Creation date:	12.02.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include <QtCore\qtimer.h>
#include "QtWidgets\qmainwindow.h"
#include "ui_mainwindow.h"
#include "centralchildwindow.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private:
	Ui::MainWindowUI ui;	// User interface reference

	CentralChildWindow* mCentralChildWindow;	// The central child window

// Signals and Slots
signals:

private slots :
};

