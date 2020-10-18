#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWheelEvent>
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	void setEffect();

	enum {MATRIX, STARFIELD, DIGITALRAIN, NumEffects};
	int effect;

private:
	void wheelEvent(QWheelEvent *event) override;
};

#endif // MAINWINDOW_H
