/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "testmaterial.h"

#include <Qt3DRender/qfilterkey.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qshaderprogram.h>
#include <Qt3DRender/qparameter.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qgraphicsapifilter.h>
#include <QtCore/QUrl>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

TwiceReflectingMaterial::TwiceReflectingMaterial(Qt3DCore::QNode *parent)
    : m_phongEffect(new Qt3DRender::QEffect())
    , m_phongGL3Technique(new Qt3DRender::QTechnique())
    , m_phongGL3RenderPass(new Qt3DRender::QRenderPass())
    , m_phongGL3Shader(new Qt3DRender::QShaderProgram())
    , m_filterKey(new Qt3DRender::QFilterKey)
{
    init();
}

void TwiceReflectingMaterial::init()
{
    m_phongGL3Shader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/billboards.vert"))));
    //m_phongGL3Shader->setGeometryShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/billboards.geom"))));
    m_phongGL3Shader->setFragmentShaderCode(Qt3DRender::QShaderProgram::loadSource(QUrl(QStringLiteral("qrc:/shaders/billboards.frag"))));

    m_phongGL3RenderPass->setShaderProgram(m_phongGL3Shader);

    m_phongGL3Technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    m_phongGL3Technique->graphicsApiFilter()->setMajorVersion(3);
    m_phongGL3Technique->graphicsApiFilter()->setMinorVersion(1);
    m_phongGL3Technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);

    m_phongGL3Technique->addRenderPass(m_phongGL3RenderPass);

    m_filterKey->setParent(this);
    m_filterKey->setName(QStringLiteral("renderingStyle"));
    m_filterKey->setValue(QStringLiteral("forward"));

    m_phongGL3Technique->addFilterKey(m_filterKey);

    m_phongEffect->addTechnique(m_phongGL3Technique);

    this->setEffect(m_phongEffect);
}

/*!
    \class Qt3DExtras::QPhongMaterial
    \brief The QPhongMaterial class provides a default implementation of the phong lighting effect.
    \inmodule Qt3DExtras
    \since 5.7
    \inherits Qt3DRender::QMaterial
    \deprecated
    This class is deprecated; use QDiffuseSpecularMaterial instead.
    The phong lighting effect is based on the combination of 3 lighting components ambient, diffuse
    and specular. The relative strengths of these components are controlled by means of their
    reflectivity coefficients which are modelled as RGB triplets:
    \list
    \li Ambient is the color that is emitted by an object without any other light source.
    \li Diffuse is the color that is emitted for rought surface reflections with the lights.
    \li Specular is the color emitted for shiny surface reflections with the lights.
    \li The shininess of a surface is controlled by a float property.
    \endlist
    This material uses an effect with a single render pass approach and performs per fragment
    lighting. Techniques are provided for OpenGL 2, OpenGL 3 or above as well as OpenGL ES 2.
*/

/*!
   Destroys the QPhongMaterial.
*/
TwiceReflectingMaterial::~TwiceReflectingMaterial()
{
}
