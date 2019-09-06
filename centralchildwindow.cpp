#include "centralchildwindow.h"
#include <QtWidgets\qdesktopwidget.h>

const int STRETCH_FACTOR = 6;

// Constructor
CentralChildWindow::CentralChildWindow(QWidget* parent)
{
	// Setup the user interface
	ui.setupUi(this);	

	// Gets the screen size 
	QRect rec = QApplication::desktop()->screenGeometry();

	// Creates the two child windows
	mInformationWindow = new InformationWindow(this);
	mRenderWindow = new RenderWindow(rec.width(), rec.height(), mInformationWindow, this);

	// Creates the layout and add the windows in a two dimensional grid
	mHBoxLayout = new QHBoxLayout;

	// Set Size policy of the render window (left) and add it to the layout
	QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spLeft.setHorizontalStretch(STRETCH_FACTOR);	// Stretch-factor: 6
	mRenderWindow->setSizePolicy(spLeft);
	mHBoxLayout->addWidget(mRenderWindow);			

	// Set Size policy of the information window (right) and add it to the layout
	QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
	spRight.setHorizontalStretch(STRETCH_FACTOR / STRETCH_FACTOR);	// Stretch-factor: 1
	mInformationWindow->setSizePolicy(spRight);
	mHBoxLayout->addWidget(mInformationWindow);
	
	// Add the HBoxLayout to the central child window
	this->setLayout(mHBoxLayout);

}

// Destructor
CentralChildWindow::~CentralChildWindow()
{
}
