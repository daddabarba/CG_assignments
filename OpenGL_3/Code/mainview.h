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
#include <QElapsedTimer>
#include <QVector3D>
#include <memory>

#include "geoms.h"
#include "transform.h"
#include "solid_mesh.h"
#include "animation.h"
#include "parametricanimations.h"

#include "shaderwrapper.h"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    public:
        enum ShadingMode : GLuint
        {
            PHONG = 0, NORMAL, GOURAUD, WAVE
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
        void updateAnimations();
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
        solid_mesh cat;
        solid_mesh earth;
        solid_mesh moon;
        solid_mesh box;
        solid_mesh skybox;
        solid_mesh bouncybox;
        solid_mesh wave;

        shaderWrapper shaderProgram_Normal;
        shaderWrapper shaderProgram_Gouraud;
        shaderWrapper shaderProgram_Phong;
        shaderWrapper shaderProgram_Wave;

        void initAnimations();
        ellipse sphere_orbit;
        ellipse cube_orbit;

        vertex lightSource;

        shaderWrapper *getShader();
        ShadingMode currentShader;

        QOpenGLDebugLogger *debugLogger;
        QTimer timer; // timer used for updating
        QElapsedTimer elapsedTime; //timer used for bounce animation

        QMatrix4x4 transformProjection; //Matrix for projection transformation
        TurntableTransform transformView;

        void createShaderProgram();

        void setBuffer(solid_mesh *mesh);
        void setTexture(solid_mesh *mesh, const char *path);

        void renderBuffer(solid_mesh *mesh);

        void destroyMesh(solid_mesh *mesh);

        QVector<quint8> imageToBytes(QImage image);

};

#endif // MAINVIEW_H
