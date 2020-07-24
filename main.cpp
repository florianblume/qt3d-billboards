// Includes for framegraph
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QFrameGraphNode>
#include <Qt3DRender/QRenderSurfaceSelector>
#include <Qt3DRender/QViewport>
#include <Qt3DRender/QCameraSelector>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QClearBuffers>
#include <Qt3DExtras/QForwardRenderer>

#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DInput/QInputSettings>

#include <Qt3DCore/QEntity>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DRender/QGraphicsApiFilter>
#include <Qt3DExtras/QTextureMaterial>

#include <QSurfaceFormat>

#include <QVector3D>
#include <QColor>

#include <QGuiApplication>

#include "billboardgeometry.h"
#include "billboardmaterial.h"

#include "testmaterial.h"

#include <QOpenGLContext>

Qt3DExtras::QFirstPersonCameraController * cameraController;

int windowWidth = 1600;
int windowHeight = 800;

Qt3DCore::QEntity *createScene() {
    Qt3DCore::QEntity *root = new Qt3DCore::QEntity();

    cameraController = new Qt3DExtras::QFirstPersonCameraController(root);

    // Add plane
    Qt3DCore::QEntity *planeEntity = new Qt3DCore::QEntity(root);
    Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh(planeEntity);
    planeMesh->setWidth(20);
    planeMesh->setHeight(20);
    Qt3DExtras::QPhongMaterial *planeMaterial = new Qt3DExtras::QPhongMaterial(planeEntity);
    planeMaterial->setAmbient(QColor(0, 0, 0.7 * 255, 0.1 * 255));
    planeEntity->addComponent(planeMesh);
    planeEntity->addComponent(planeMaterial);

    // Add sphere
    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(root);
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh(sphereEntity);
    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial(sphereEntity);
    sphereMaterial->setAmbient(Qt::red);
    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform(sphereEntity);
    sphereTransform->setTranslation(QVector3D(0., 5., 0.));
    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(sphereMaterial);
    sphereEntity->addComponent(sphereTransform);

    // Add cube
    Qt3DCore::QEntity *cubeEntity = new Qt3DCore::QEntity(root);
    Qt3DExtras::QCuboidMesh *cubeMesh = new Qt3DExtras::QCuboidMesh(cubeEntity);
    Qt3DExtras::QPhongMaterial *cubeMaterial = new Qt3DExtras::QPhongMaterial(cubeEntity);
    cubeMaterial->setAmbient(Qt::gray);
    Qt3DCore::QTransform *cubeTransform = new Qt3DCore::QTransform();
    cubeTransform->setTranslation(QVector3D(2., 2., 5.));
    cubeEntity->addComponent(cubeMesh);
    cubeEntity->addComponent(cubeMaterial);
    cubeEntity->addComponent(cubeTransform);

    // Add Billboard
    Qt3DCore::QEntity *billboardEntity = new Qt3DCore::QEntity(root);

    // Create billboard geometry
    QVector<QVector3D> pos;
    pos << QVector3D(1, 1, 0);
    pos << QVector3D(-1, 2, 8);
    pos << QVector3D(1, 1, 7);
    pos << QVector3D(0, 0, 4);
    BillboardGeometry *billboardGeometry = new BillboardGeometry(billboardEntity);
    billboardGeometry->setPoints(pos);
    Qt3DRender::QGeometryRenderer *billboardRenderer = new Qt3DRender::QGeometryRenderer(billboardEntity);
    billboardRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Points);
    billboardRenderer->setGeometry(billboardGeometry);
    billboardRenderer->setVertexCount(billboardGeometry->count());

    Qt3DCore::QTransform *billboardTransform = new Qt3DCore::QTransform(billboardEntity);
    billboardTransform->setTranslation(QVector3D(0., 1.5, 0.));

    // Billboard material
    BillboardMaterial *billboardMaterial = new BillboardMaterial();

    billboardEntity->addComponent(billboardRenderer);
    billboardEntity->addComponent(billboardMaterial);
    billboardEntity->addComponent(billboardTransform);

    return root;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    Qt3DExtras::Qt3DWindow view;
    view.resize(windowWidth, windowHeight);
    Qt3DExtras::QForwardRenderer *renderer = (Qt3DExtras::QForwardRenderer *)view.activeFrameGraph();
    renderer->setClearColor("black");

    Qt3DRender::QCamera *camera = view.camera();
    camera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    camera->setFieldOfView(45);
    // Cast to float to ensure float division
    camera->setAspectRatio(windowWidth / (float) windowHeight);
    camera->setNearPlane(0.1f);
    camera->setFarPlane(100.f);
    camera->setPosition(QVector3D(0., 10., 20.));
    camera->setViewCenter(QVector3D(0., 0., 0.));
    camera->setUpVector(QVector3D(0., 1., 0.));

    Qt3DCore::QEntity *root = createScene();
    view.setRootEntity(root);
    cameraController->setCamera(camera);

    view.setTitle("Billboards");
    view.show();

    return app.exec();
}
