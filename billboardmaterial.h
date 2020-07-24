#ifndef BILLBOARDMATERIAL_H
#define BILLBOARDMATERIAL_H

#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QParameter>
#include <Qt3DRender/QEffect>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QFilterKey>

class BillboardMaterial : public Qt3DRender::QMaterial
{
public:
    BillboardMaterial();

private:
    Qt3DRender::QTexture2D *texture;
    Qt3DRender::QTextureImage *textureImage;
    Qt3DRender::QParameter *billboardParam1;
    Qt3DRender::QParameter *billboardParam2;
    Qt3DRender::QParameter *billboardParam3;
    Qt3DRender::QEffect *billboardEffect;
    Qt3DRender::QTechnique *billboardTechnique;
    Qt3DRender::QRenderPass *billboardRenderPass;
    Qt3DRender::QShaderProgram *billboardShaderProgram;
    Qt3DRender::QFilterKey *filterKey;
};

#endif // BILLBOARDMATERIAL_H
