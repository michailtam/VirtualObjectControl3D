/************************************************************************************/
/*																					*/
/*		File:			intelrsthread.h												*/
/*		Description:	This file contains the thread in which the capture loop		*/
/*						will run separately											*/		
/*		Creation date:	02.03.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include "QtCore\qthread.h"


class IntelRSThread : public QThread
{
public:
	IntelRSThread();
	
	void run();
};

