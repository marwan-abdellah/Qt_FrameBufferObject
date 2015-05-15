/*
 *  Copyrights (c) Marwan Abdellah <abdellah.marwan@gmail.com>
 *  2015
 */

#include "glwidget.h"

/**
 * @brief GLWidget::GLWidget
 * @param parent
 */
GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    // Create the framebuffer object - make sure to have a current
    // context before creating it.
    makeCurrent();

    // Create a new FBO.
    fbo = new QGLFramebufferObject(512, 512);

    // Set window title.
    setWindowTitle(tr("OpenGL FBO Minimalistic Example"));
}

/**
 * @brief GLWidget::~GLWidget
 */
GLWidget::~GLWidget()
{
    delete fbo;
}

/**
 * @brief GLWidget::initializeGL
 */
void GLWidget::initializeGL()
{
    glClearColor(0, 0, 0, 0);

}

/**
 * @brief drawToFBO
 */
void drawToFBO()

{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.5, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0.5, 0, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.5, 0);
    glEnd();
}

/**
 * @brief GLWidget::resizeGL
 * @param w
 * @param h
 */
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = w/(float)(h ? h : 1);
    glFrustum(-aspect, aspect, -1, 1, 10, 100);

}

/**
 * @brief GLWidget::paintGL
 */
void GLWidget::paintGL()
{

    // Push the projection matrix and the entire GL state before
    // doing any rendering into our framebuffer object
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glViewport(0, 0, fbo->size().width(), fbo->size().height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -99, 99);
    glMatrixMode(GL_MODELVIEW);

    // Render to the framebuffer object
    fbo->bind();
    drawToFBO();
    fbo->release();

    // Pop the projection matrix and GL state back for rendering
    // to the actual widget
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the background
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // Enable the texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, fbo->texture());

    // Save the state.
    glPushMatrix();

    // Draw a textured quad and stick the image onto it.
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1.f, -1.f, 0.f);
    glTexCoord2f(0, 1); glVertex3f(-1.f,  1.f, 0.f);
    glTexCoord2f(1, 1); glVertex3f( 1.f,  1.f, 0.f);
    glTexCoord2f(1, 0); glVertex3f( 1.f, -1.f, 0.f);
    glEnd();

    // Restore the state.
    glPopMatrix();

    // Disable 2D texturing
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
