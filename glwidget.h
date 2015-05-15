/*
 *  Copyrights (c) Marwan Abdellah <abdellah.marwan@gmail.com>
 *  2015
 */

#include <QtOpenGL>

class GLWidget : public QGLWidget
{
public:
    /**
     * @brief GLWidget
     * @param parent
     */
    GLWidget(QWidget *parent);
    ~GLWidget();

    /**
     * @brief initializeGL
     */
    void initializeGL();

    /**
     * @brief resizeGL
     * @param w
     * @param h
     */
    void resizeGL(int w, int h);

    /**
     * @brief paintGL
     */
    void paintGL();
    void timerEvent(QTimerEvent *) { update(); }

    /**
     * @brief drawCube
     * @param i
     * @param z
     * @param ri
     * @param jmp
     * @param amp
     */
    void drawCube(int i, GLfloat z, GLfloat ri, GLfloat jmp, GLfloat amp);

private:
    QGLFramebufferObject *fbo;
};
