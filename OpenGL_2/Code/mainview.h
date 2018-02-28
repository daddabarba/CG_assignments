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
#include "transform.h"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram shaderProgram;

    //cube *solidCube;

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
        Transform transformCube;     //Cube transformation matrix (rotation, scaling, translation)
        Transform transformPyramid;  //Pyramid transformation matrix (rotation, scaling, translation)
        Transform transformSphere;   //Sphere transformation matrix (rotation, scaling, translation)

        QMatrix4x4 transformProjection; //Matrix for projection transformation

        GLint uniformModel;          //model transform (rotate, scale, translate) uniform's location in shader
        GLint uniformProjection;     //projection transform uniform's location in shader

        int size_sphere;             //Number of sphere's mesh vertices

        GLuint VBO_cube, VBO_pyramid, VBO_sphere;  //VBO's for cube, pyramid and sphere
        GLuint VAO_cube, VAO_pyramid, VAO_sphere;  //VAO's for cube, pyramid and sphere

        void createShaderProgram();

};

#endif // MAINVIEW_H
