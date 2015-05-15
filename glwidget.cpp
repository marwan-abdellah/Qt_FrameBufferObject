/****************************************************************************
 **
 ** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

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
