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
    cat(":/models/cat.obj", set_point(0.0,-1.0,-4.0), 4.0f)
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

    destroyMesh(&cat);

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


    //SETTING CAT FIGURE ON GPU
    setBuffer(&cat);


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

    //RENDERING CAT
    renderBuffer(&cat, uniformModel, uniformNormal);

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
    cat.setRotation(rotateX, rotateY, rotateZ);

    qDebug() << "Rotation changed to (" << rotateX << "," << rotateY << "," << rotateZ << ")";
    //Q_UNIMPLEMENTED();
    update();
}

void MainView::setScale(int scale)
{
    //Change solid's (uniform) scaling value
    cat.setScale(scale / 100.0f);

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

void MainView::setBuffer(solid_mesh *mesh){
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

void MainView::destroyMesh(solid_mesh *mesh){
    glDeleteBuffers(1, &(mesh->VBO));
    glDeleteVertexArrays(1, &(mesh->VAO));
}
