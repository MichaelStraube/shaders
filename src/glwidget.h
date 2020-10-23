#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QTimer>
#include <QElapsedTimer>
#include <QOpenGLTexture>

// base class for effects

class GLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLWidget();
	~GLWidget();

	QMap<QString, QString> files;

private:
	QOpenGLShader *vShader;
	QOpenGLShader *fShader;
	QOpenGLShaderProgram *program;
	QTimer *timer;
	QElapsedTimer *elapsedTimer;
	QOpenGLTexture *texture0;
	QOpenGLTexture *texture1;
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	void loadShaders();
	void loadTextures();

private slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
};

#endif // GLWIDGET_H
