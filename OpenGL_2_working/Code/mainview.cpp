#include "mainview.h"
#include "math.h"

#include "geoms.h"
#include "colors.h"

#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) :
    QOpenGLWidget(parent),
    sphere(":/models/sphere.obj"),
    cat(":/models/cat.obj")
{
    qDebug() << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();
    glDeleteBuffers(1, &VBO_cube);
    glDeleteBuffers(1, &VBO_pyramid);
    glDeleteVertexArrays(1, &VAO_cube);
    glDeleteVertexArrays(1, &VAO_pyramid);
    qDebug() << "MainView destructor";
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glEnable(GL_CULL_FACE);

    // Default is GL_LESS
    glDepthFunc(GL_LEQUAL);

    // Set the color of the screen to be black on clear (new frame)
    glClearColor(0.2f, 0.5f, 0.7f, 0.0f);

    createShaderProgram();



    //SETTING CUBE FIGURE ON GPU

    //Computing vertices
    cube figure_cube = set_cube(2, red, green, blue, brown , yellow, light_blue, white, black);

    //Starting VAO and VBO
    glGenBuffers(1, &VBO_cube);
    glGenVertexArrays(1, &VAO_cube);

    glBindVertexArray(VAO_cube);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);

    //Sending cube to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), &figure_cube, GL_STATIC_DRAW);

    //Defining attributes (position and color)
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(point)) );

    //Setting cube's model transformation (translation)
    transformCube.setPosition(2.0f, 0.0f, -6.0f);



    //SETTING PYRAMID FIGURE ON GPU

    //Computing vertices
     pyramid figure_pyramid = set_pyramid(2, 2, red, green, blue, white, black);

    //Staring VAO and VBO
    glGenBuffers(1, &VBO_pyramid);
    glGenVertexArrays(1, &VAO_pyramid);

    glBindVertexArray(VAO_pyramid);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_pyramid);

    //Sending pyramid to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid), &figure_pyramid, GL_STATIC_DRAW);

    //Defining attributes (position and color)
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(point)) );

    //Setting pyramid's model transformation (translation)
    transformPyramid.setPosition(-2, 0, -6);

    //SETTING SPHERE FIGURE ON GPU
    setBuffer(&sphere, set_point(0.0,0.0,-10.0),0.04f);

    //setBuffer(&cat, set_point(0.0,-1.0,-4.0),2.0f);
    //SETTING PROJECTION TRANSFORMATION MATRIX
    transformProjection.perspective(60, 1, 2, 10);

}

void MainView::createShaderProgram()
{
    // Create shader program
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader.glsl");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader.glsl");
    shaderProgram.link();

    //Getting shader's locations for model and projection's uniforms
    uniformModel = shaderProgram.uniformLocation("modelTransform");
    uniformProjection = shaderProgram.uniformLocation("projection");
    uniformNormal = shaderProgram.uniformLocation("normalMatrix");

    qDebug() << uniformNormal;
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.bind();

    // Draw here

    //Setting PROJECTION transformation matrix (in shader's uniform)
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, transformProjection.data());
    /*
    //RENDERING CUBE

    //Setting model transformation uniform to cube transformation
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, transformCube.getMatrix().data());

    //Binding buffer containing cube
    glBindVertexArray(VAO_cube);
    //drawing cube from buffer
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //RENDERING PYRAMID

    //Setting model transformation uniform to pyramid transformation
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, transformPyramid.getMatrix().data());

    //Binding buffer containing pyramid
    glBindVertexArray(VAO_pyramid);
    //drawing pyramid from buffer
    glDrawArrays(GL_TRIANGLES, 0, 18);

    */

    //RENDERING SPHERE
    renderBuffer(&sphere, uniformModel, uniformNormal);
    //renderBuffer(&cat, uniformModel, uniformNormal);

    shaderProgram.release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight) 
{
    //Re-setting matrix, otherwise both projection (old and new) transformation are applied consecutively
    transformProjection.setToIdentity();
    //Updating projection matrix (according to new window ratio)
    transformProjection.perspective(60, (float)newWidth / newHeight, 2, 10);

}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    //Change solid's rotation value
    transformCube.setRotation(rotateX, rotateY, rotateZ);
    transformPyramid.setRotation(rotateX, rotateY, rotateZ);
    sphere.transformation.setRotation(rotateX, rotateY, rotateZ);
    cat.transformation.setRotation(rotateX, rotateY, rotateZ);

    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    //Q_UNIMPLEMENTED();
    update();
}

void MainView::setScale(int scale)
{
    //Change solid's (uniform) scaling value
    transformCube.setScale(scale / 100.0f);
    transformPyramid.setScale(scale / 100.0f);
    sphere.transformation.setScale(scale / 100.0f * 0.04f);
    cat.transformation.setScale(scale / 100.0f*2.0f);

    qDebug() << "Scale changed to " << scale;
    //Q_UNIMPLEMENTED();
    update();
}

void MainView::setShadingMode(ShadingMode shading)
{
    qDebug() << "Changed shading to" << shading;
    Q_UNIMPLEMENTED();
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}

void MainView::setBuffer(solid_mesh *mesh, point position, float scale){
    //Starting VAO and VBO
    glGenBuffers(1, &(mesh->VBO));
    glGenVertexArrays(1, &(mesh->VAO));

    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    //Sending solid to VBO
    glBufferData(GL_ARRAY_BUFFER, (mesh->size_solid)*sizeof(vertex), mesh->figure_solid, GL_STATIC_DRAW);
    mesh->discard_vertices();

    //Defining attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(point)) );

    //Setting solid's model transformation (translation and scaling)
    (mesh->transformation).setPosition(position.x, position.y, position.z);
    (mesh->transformation).setScale(scale);

}

void MainView::renderBuffer(solid_mesh *mesh, GLint transform_uniform, GLint normal_uniform){

    //Setting model transformation uniform to solid transformation
    glUniformMatrix4fv(transform_uniform, 1, GL_FALSE, (mesh->transformation).getMatrix().data());
    glUniformMatrix3fv(normal_uniform, 1, GL_FALSE, (mesh->getNormalMatrix()).data());

    //Binding buffer containing solid
    glBindVertexArray(mesh->VAO);
    //drawing solid from buffer
    glDrawArrays(GL_TRIANGLES, 0, mesh->size_solid);
}
