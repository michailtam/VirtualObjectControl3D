/************************************************************************************/
/*																					*/
/*		File:			informationwindow.h											*/
/*		Description:	This class represents the information window in which we	*/
/*						will display the information like current operation,		*/
/*						coordinates etc.											*/
/*		Creation date:	12.02.2016													*/
/*																					*/
/*		Developer:		Michail Tamvakeras											*/
/*																					*/
/************************************************************************************/

#pragma once
#include "QtWidgets\qwidget.h"
#include "ui_informationwindow.h"


class InformationWindow : public QWidget
{
	Q_OBJECT

public:
	InformationWindow(QWidget* parent = 0);
	~InformationWindow();

	Ui::InformationWindowUI getUIRef() { return ui; }

private:
	Ui::InformationWindowUI ui;		// User interface reference

// Signals and Slots
signals:

private slots :
};

