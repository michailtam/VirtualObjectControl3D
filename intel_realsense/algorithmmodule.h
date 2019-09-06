/************************************************************************************/
/*																					*/
/*		File:			algorithmmodule.h											*/
/*		Description:	This file is the base class of all the algorithm modules	*/
/*						like face tracking, hand tracking etc. which is provided	*/
/*						by the Intel RealSense SDK									*/
/*		Creation date:	19.02.2016													*/
/*																					*/
/*		Developer:		Michael Tamvakeras											*/
/*		Field of study:	PLH40														*/
/*		Associate																	*/
/*		Professor:		PhD Anagnostopoulos Christos								*/
/*																					*/
/************************************************************************************/

#pragma once
#include "pxcsensemanager.h"


class AlgorithmModule
{
protected:
	AlgorithmModule();	// NO CONSTRUCTION FROM OUTSIDE ALLOWED
	~AlgorithmModule();

	virtual bool init() = 0;

	PXCSenseManager* mSenseManager;
	bool mInitStatus;
};

