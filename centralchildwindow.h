/************************************************************************************/
/*																					*/
/*		File:			centralchildwindow.h										*/
/*		Description:	This class represents the central child window which		*/
/*						contains render window and the information window			*/
/*		Creation date:	12.02.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include "QtWidgets\qwidget.h"
#include "ui_centralchildwindow.h"
#include "renderwindow.h"
#include "informationwindow.h"
#include <QtWidgets\QHBoxLayout>


class CentralChildWindow : public QWidget
{
	Q_OBJECT

public:
	CentralChildWindow(QWidget* parent = 0);
	~CentralChildWindow();

	InformationWindow* getInformationWindowRef() { return mInformationWindow; }

private:
	Ui::CentralChildWindowUI ui;			// User interface reference
	
	RenderWindow* mRenderWindow;			// The render window
	InformationWindow* mInformationWindow;	// The information window
	QHBoxLayout* mHBoxLayout;				// Tha layout for the child windows

// Signals and Slots
signals:

private slots:
};

