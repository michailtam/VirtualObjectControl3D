#include "informationwindow.h"
#include "QtWidgets\QVBoxLayout"

const int MAX_INFO_WINDOW_WIDTH = 400;


InformationWindow::InformationWindow(QWidget* parent)
{
	// Setup the user interface
	ui.setupUi(this);

	// Sets the maximum width of the window
	setMaximumWidth(MAX_INFO_WINDOW_WIDTH);

	// Set the style with the help of CSS (Cascading-Style-Sheets)
	ui.InformationWindowLabel->setStyleSheet("margin-bottom: 5px;");
	ui.InformationWindowLabel->setAlignment(Qt::AlignCenter);
	  
	ui.cameraInfoLabel->setStyleSheet("margin-top: 10px;");
	ui.cameraInfoLabel->setStyleSheet("margin-bottom: 5px;");
	ui.cameraInfoLabel->setAlignment(Qt::AlignLeft);
	  
	ui.deviceName->setStyleSheet("margin-bottom: 5px;");
	ui.deviceModel->setStyleSheet("margin-bottom: 5px;");
	ui.deviceSerial->setStyleSheet("margin-bottom: 5px;");
	ui.deviceLazerProjector->setStyleSheet("margin-bottom: 30px;");
	ui.cameraActionsList->setStyleSheet("margin-bottom: 20px;");

	// Add spacing to 
	ui.cameraLayout->addSpacing(20);

	// Set the fileds to read only status
	ui.deviceName->setReadOnly(true);
	ui.deviceModel->setReadOnly(true);
	ui.deviceSerial->setReadOnly(true);

	// Set all init stream types to not be checked
	ui.deviceColorCam->setChecked(false);
	ui.deviceDepthCam->setChecked(false);
	ui.deviceLazerProjector->setChecked(false);
}


InformationWindow::~InformationWindow()
{
}

