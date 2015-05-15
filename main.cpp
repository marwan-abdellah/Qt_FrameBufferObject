/*
 *  Copyrights (c) Marwan Abdellah <abdellah.marwan@gmail.com>
 *  2015
 */

#include <QApplication>
#include <QMessageBox>
#include "glwidget.h"

int main(int argc, char **argv)
{

    QApplication a(argc, argv);
    if (!QGLFormat::hasOpenGL() || !QGLFramebufferObject::hasOpenGLFramebufferObjects()) {
        QMessageBox::information(0, "OpenGL Qt Example to render to FBO",
                                 "This system does not support OpenGL/framebuffer objects.");
        return -1;
    }

    GLWidget widget(0);
    widget.resize(500, 500);
    widget.show();
    return a.exec();
}
