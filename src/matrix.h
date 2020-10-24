#ifndef MATRIX_H
#define MATRIX_H

#include "glwidget.h"

class Matrix : public GLWidget
{
	Q_OBJECT

public:
	Matrix()
	{
		files["vertex"] = ":/shaders/vertex.vert";
		files["fragment"] = ":/shaders/matrix.frag";
		files["texture0"] = ":/images/matrix/0.png";
	}
};

#endif // MATRIX_H
