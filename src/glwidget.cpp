#include "glwidget.h"
#include <QOpenGLFunctions_3_3_Core>

GLWidget::GLWidget()
	: timer(new QTimer(this))
	, elapsedTimer(new QElapsedTimer)
{
	connect(timer, &QTimer::timeout, this, &GLWidget::onTimeout);

	timer->start();
	elapsedTimer->start();
}

GLWidget::~GLWidget()
{
	QOpenGLFunctions_3_3_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

	// Make sure the context is current before deleting resources
	makeCurrent();

	delete vShader;
	delete fShader;
	delete program;

	/* is this needed ??

	delete texture0;
	delete texture1;
	*/

	f->glDeleteVertexArrays(1, &vao);
	f->glDeleteBuffers(1, &vbo);
	f->glDeleteBuffers(1, &ebo);

	doneCurrent();

	delete elapsedTimer;
}

void GLWidget::loadShaders()
{
	// build and compile our shader program

	vShader = new QOpenGLShader(QOpenGLShader::Vertex);
	vShader->compileSourceFile(files.value("vertex"));

	fShader = new QOpenGLShader(QOpenGLShader::Fragment);
	fShader->compileSourceFile(files.value("fragment"));

	program = new QOpenGLShaderProgram;
	program->addShader(vShader);
	program->addShader(fShader);
	program->link();
	program->bind();
}

void GLWidget::loadTextures()
{
	texture0 = new QOpenGLTexture(QImage(files.value("texture0")).mirrored());
	texture0->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture0->setMagnificationFilter(QOpenGLTexture::Linear);
	texture0->setWrapMode(QOpenGLTexture::Repeat);

	texture1 = new QOpenGLTexture(QImage(files.value("texture1")).mirrored());
	texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture1->setMagnificationFilter(QOpenGLTexture::Linear);
	texture1->setWrapMode(QOpenGLTexture::Repeat);

	program->setUniformValue("iChannel0", 0);
	program->setUniformValue("iChannel1", 1);

	program->setUniformValue("iChannelResolution[0]", texture0->width(), texture0->height(), 0.0);
	program->setUniformValue("iChannelResolution[1]", texture1->width(), texture1->height(), 0.0);
}

void GLWidget::initializeGL()
{
	// Load shaders, initialize vertex data, etc.

	QOpenGLFunctions_3_3_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

	loadShaders();

	float vertices[] = {
		// positions          // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	f->glGenVertexArrays(1, &vao);
	f->glGenBuffers(1, &vbo);
	f->glGenBuffers(1, &ebo);

	f->glBindVertexArray(vao);

	f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
	f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	f->glEnableVertexAttribArray(0);

	// texture coord attribute
	f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	f->glEnableVertexAttribArray(1);

	loadTextures();
}

void GLWidget::resizeGL(int w, int h)
{
	Q_UNUSED(w);
	Q_UNUSED(h);

	// Do nothing
}

void GLWidget::paintGL()
{
	// Draw the scene

	QOpenGLFunctions_3_3_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

	program->setUniformValue("iResolution", this->width(), this->height());

	GLfloat elapsed = elapsedTimer->elapsed();
	program->setUniformValue("iTime", elapsed / 1000);

	f->glActiveTexture(GL_TEXTURE0);
	texture0->bind();

	f->glActiveTexture(GL_TEXTURE1);
	texture1->bind();

	f->glBindVertexArray(vao);
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// SLOTS

void GLWidget::onTimeout()
{
	update();
}
