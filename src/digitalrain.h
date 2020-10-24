#ifndef DIGITALRAIN_H
#define DIGITALRAIN_H

#include "glwidget.h"

class DigitalRain : public GLWidget
{
	Q_OBJECT

public:
	DigitalRain()
	{
		files["vertex"] = ":/shaders/vertex.vert";
		files["fragment"] = ":/shaders/digitalrain.frag";
		files["texture0"] = ":/images/digitalrain/0.png";
		files["texture1"] = ":/images/digitalrain/1.png";
	}
};

#endif // DIGITALRAIN_H
