#ifndef STARFIELD_H
#define STARFIELD_H

#include "glwidget.h"

class Starfield : public GLWidget
{
	Q_OBJECT

public:
	Starfield()
	{
		files["vertex"] = ":/shaders/vertex.vert";
		files["fragment"] = ":/shaders/starfield.frag";
	}
};

#endif // STARFIELD_H
