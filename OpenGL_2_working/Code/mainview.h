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
#include "solid_mesh.h"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT


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
        solid_mesh sphere;
        solid_mesh cat;

        QOpenGLDebugLogger *debugLogger;
        QTimer timer; // timer used for animation

        QOpenGLShaderProgram shaderProgram;

        Transform transformCube;     //Cube transformation matrix (rotation, scaling, translation)
        Transform transformPyramid;  //Pyramid transformation matrix (rotation, scaling, translation)

        QMatrix4x4 transformProjection; //Matrix for projection transformation

        GLint uniformModel;          //model transform (rotate, scale, translate) uniform's location in shader
        GLint uniformProjection;     //projection transform uniform's location in shader
        GLint uniformNormal;

        GLuint VBO_cube, VBO_pyramid;  //VBO's for cube, pyramid and sphere
        GLuint VAO_cube, VAO_pyramid;  //VAO's for cube, pyramid and sphere

        void createShaderProgram();

        void setBuffer(solid_mesh *mesh, point position, float scale);
        void renderBuffer(solid_mesh *mesh, GLint transform_uniform, GLint normal_uniform);

};

#endif // MAINVIEW_H
