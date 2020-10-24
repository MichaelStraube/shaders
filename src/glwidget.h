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
	QVector<QOpenGLTexture *> textures;
	static constexpr int numTextures = 4; // iChannel0..3
	QVector4D mousePos;
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
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
};

#endif // GLWIDGET_H
