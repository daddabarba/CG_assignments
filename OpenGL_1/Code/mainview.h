#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <memory>

#include "geoms.h"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgram;

    cube *solidCube;

    public:
        enum ShadingMode : GLuint
        {
            PHONG = 0, NORMAL, GOURAUD
        };

        MainView(QWidget *parent = 0);
        ~MainView();

        // Functions for widget input events
        void setRotation(int rotateX, int rotateY, int rotateZ);
        void setScale(int scale);
        void setShadingMode(ShadingMode shading);

        QMatrix4x4 transformCube;
        QMatrix4x4 transformPyramid;

        QMatrix4x4 transformProjection;

        GLint uniformModel;
        GLint uniformProjection;

    protected:
        void initializeGL();
        void resizeGL(int newWidth, int newHeight);
        void paintGL();

        // Functions for keyboard input events
        void keyPressEvent(QKeyEvent *ev);
        void keyReleaseEvent(QKeyEvent *ev);

        // Function for mouse input events
        void mouseDoubleClickEvent(QMouseEvent *ev);
        void mouseMoveEvent(QMouseEvent *ev);
        void mousePressEvent(QMouseEvent *ev);
        void mouseReleaseEvent(QMouseEvent *ev);
        void wheelEvent(QWheelEvent *ev);

    private slots:
        void onMessageLogged( QOpenGLDebugMessage Message );

    private:
        cube figure_a;
        pyramid figure_b;

        GLuint VBO_a, VBO_b;
        GLuint VAO_a, VAO_b;

        void createShaderProgram();

};

#endif // MAINVIEW_H
