#ifndef STARFIELD_H
#define STARFIELD_H

#include "glwidget.h"

class Starfield : public GLWidget
{
	Q_OBJECT

public:
	Starfield()
	{
		files["vertex"] = ":/shaders/vertex.vs";
		files["fragment"] = ":/shaders/starfield.fs";
	}
};

#endif // STARFIELD_H
