#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "matrix.h"
#include "starfield.h"
#include "digitalrain.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, effect(0)
{
	ui->setupUi(this);

	setEffect();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setEffect()
{
	switch (effect) {
	case MATRIX:
		setCentralWidget(new Matrix);
		break;
	case STARFIELD:
		setCentralWidget(new Starfield);
		break;
	case DIGITALRAIN:
		setCentralWidget(new DigitalRain);
		break;
	default:
		break;
	}
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	Q_UNUSED(event);

	effect++;
	effect %= NumEffects;
	setEffect();
}
