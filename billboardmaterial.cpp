#include "billboardmaterial.h"

#include <Qt3DRender/QGraphicsApiFilter>

BillboardMaterial::BillboardMaterial()
{
    // Image of billboard material
    texture = new Qt3DRender::QTexture2D();
    textureImage = new Qt3DRender::QTextureImage(texture);
    textureImage->setSource(QUrl(QStringLiteral("qrc:/success-kid.png")));
    texture->addTextureImage(textureImage);

    // Parameters of billboard material
    billboardParam1 = new Qt3DRender::QParameter(QStringLiteral("tex0"), texture);
    billboardParam2 = new Qt3DRender::QParameter(QStringLiteral("WIN_SCALE"), QSizeF(1600.0, 800.0));
    billboardParam3 = new Qt3DRender::QParameter(QStringLiteral("BB_SIZE"), QSizeF(100.0, 100.0));
    this->addParameter(billboardParam1);
    this->addParameter(billboardParam2);
    this->addParameter(billboardParam3);

    // Effect of material
    billboardEffect = new Qt3DRender::QEffect();
    billboardTechnique = new Qt3DRender::QTechnique();
    billboardTechnique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    billboardTechnique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);
    billboardTechnique->graphicsApiFilter()->setMajorVersion(3);
    billboardTechnique->graphicsApiFilter()->setMinorVersion(2);
    // You need the filter key because the QForwardRenderer employed as the default framegraph by the Qt3DWindow
    // extends QTechniqueFilter and filters for this key exactly. Without it, the material gets discarded.
    filterKey = new Qt3DRender::QFilterKey(this);
    filterKey->setName(QStringLiteral("renderingStyle"));
    filterKey->setValue(QStringLiteral("forward"));
    billboardTechnique->addFilterKey(filterKey);
    billboardRenderPass = new Qt3DRender::QRenderPass();
    billboardShaderProgram = new Qt3DRender::QShaderProgram();
    billboardShaderProgram->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl("qrc:/shaders/billboards.vert")));
    billboardShaderProgram->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl("qrc:/shaders/billboards.geom")));
    billboardShaderProgram->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl("qrc:/shaders/billboards.frag")));
    billboardRenderPass->setShaderProgram(billboardShaderProgram);
    billboardTechnique->addRenderPass(billboardRenderPass);
    billboardEffect->addTechnique(billboardTechnique);
    this->setEffect(billboardEffect);
}
