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
    cat(":/models/cat.obj", set_point(0.0,-2.0,-10.0), 10.0f, set_color(1.0f,1.0f,1.0f), set_material(0.2f,1.0f,1.0f, 4)),
    shaderProgram_Normal(),
    shaderProgram_Gouraud(),
    shaderProgram_Phong()
{
    qDebug() << "MainView constructor";

    //Setting light source (position and color)
    lightSource = set_vertex(set_point(5.0,5.0,5.0), set_color(1.0,1.0,1.0));

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    qDebug() << "Connected";
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

    QImage im_cat(":/textures/cat_diff.png");
    if (im_cat.isNull()) qDebug() << "Failed to load texture";
    QVector<quint8> diff_cat = imageToBytes(im_cat);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, diff_cat.data());

    qDebug() << "Uploading cat";

    //SETTING CAT FIGURE ON GPU
    setBuffer(&cat);
    qDebug() << "cat mesh uploaded";

    //SETTING PROJECTION TRANSFORMATION MATRIX
    transformProjection.perspective(60, 1, 0.1f, 100.0);

}


void MainView::createShaderProgram()
{
    qDebug() << "Loading normal shader";
    shaderProgram_Normal.create(":/shaders/vertshader_normal.glsl", ":/shaders/fragshader_normal.glsl");

    qDebug() << "Loading gouraud shader";
    shaderProgram_Gouraud.create(":/shaders/vertshader_gouraud.glsl", ":/shaders/fragshader_gouraud.glsl");

    qDebug() << "Loading phong shader";
    shaderProgram_Phong.create(":/shaders/vertshader_phong.glsl", ":/shaders/fragshader_phong.glsl");
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

    getShader()->bind();

    // Draw here

    //Setting PROJECTION transformation matrix (in shader's uniform)
    glUniformMatrix4fv(getShader()->uniformProjection, 1, GL_FALSE, transformProjection.data());

    if((getShader()->uniformLightCol)>=0 && (getShader()->uniformLightPos)>=0 ){
        //qDebug()<<"sent light";
        glUniform3f(getShader()->uniformLightPos, (lightSource.position).x, (lightSource.position).y, (lightSource.position).z);
        glUniform3f(getShader()->uniformLightCol, (lightSource.color).r, (lightSource.color).g, (lightSource.color).b);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    //RENDERING CAT
    renderBuffer(&cat);

    getShader()->release();
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
    transformProjection.perspective(60, (float)newWidth / newHeight, 0.1f, 100);

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
    currentShader = shading;
    qDebug() << "Changed shading to" << shading;
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
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(point)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)(sizeof(point) * 2));

}

void MainView::renderBuffer(solid_mesh *mesh){

    //Setting model transformation uniform to solid transformation
    glUniformMatrix4fv(getShader()->uniformModel, 1, GL_FALSE, (mesh->transformation).getMatrix().data());
    glUniformMatrix3fv(getShader()->uniformNormal, 1, GL_FALSE, (mesh->getNormalMatrix()).data());

    if((getShader()->uniformMaterial)>=0 && (getShader()->uniformObjCol)>=0){
        //qDebug()<<"sent object";
        glUniform4f(getShader()->uniformMaterial,(mesh->material).a,(mesh->material).d,(mesh->material).s,(mesh->material).e);
        glUniform3f(getShader()->uniformObjCol,(mesh->color).r,(mesh->color).g,(mesh->color).b);
    }

    //Binding buffer containing solid
    glBindVertexArray(mesh->VAO);
    //drawing solid from buffer
    glDrawArrays(GL_TRIANGLES, 0, mesh->size_solid);
}

void MainView::destroyMesh(solid_mesh *mesh){
    glDeleteBuffers(1, &(mesh->VBO));
    glDeleteVertexArrays(1, &(mesh->VAO));
}

shaderWrapper *MainView::getShader(){
    switch (currentShader) {
    case NORMAL:
        return &shaderProgram_Normal;
        break;
    case GOURAUD:
        return &shaderProgram_Gouraud;
    case PHONG:
        return &shaderProgram_Phong;
    default:
        return &shaderProgram_Normal;
        break;
    }
}

// Had to put this here, otherwise I got an unresolved external error
QVector<quint8> MainView::imageToBytes(QImage image) {
    // needed since (0,0) is bottom left in OpenGL
    QImage im = image.mirrored();
    QVector<quint8> pixelData;
    pixelData.reserve(im.width()*im.height()*4);

    for (int i = 0; i != im.height(); ++i) {
        for (int j = 0; j != im.width(); ++j) {
            QRgb pixel = im.pixel(j,i);

            // pixel is of format #AARRGGBB (in hexadecimal notation)
            // so with bitshifting and binary AND you can get
            // the values of the different components
            quint8 r = (quint8)((pixel >> 16) & 0xFF); // Red component
            quint8 g = (quint8)((pixel >> 8) & 0xFF); // Green component
            quint8 b = (quint8)(pixel & 0xFF); // Blue component
            quint8 a = (quint8)((pixel >> 24) & 0xFF); // Alpha component

            // Add them to the Vector
            pixelData.append(r);
            pixelData.append(g);
            pixelData.append(b);
            pixelData.append(a);
        }
    }
    return pixelData;
}
