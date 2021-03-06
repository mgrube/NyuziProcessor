// 
// Copyright (C) 2011-2014 Jeff Bush
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
// 
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
// Boston, MA  02110-1301, USA.
// 


#include <math.h>
#include <schedule.h>
#include <stdlib.h>
#include <Matrix.h>
#include <Rasterizer.h>
#include <RenderTarget.h>
#include <RenderContext.h>
#include "PhongShader.h"
#include "teapot.h"

using namespace render;

const int kFbWidth = 640;
const int kFbHeight = 480;

void *operator new(size_t size, void *p)
{
	return p;
}
	
int main()
{
	RenderTarget *renderTarget = new RenderTarget();
	Surface *colorBuffer = new (memalign(64, sizeof(Surface))) Surface(kFbWidth, kFbHeight, (void*) 0x200000);
	Surface *zBuffer = new (memalign(64, sizeof(Surface))) Surface(kFbWidth, kFbHeight);
	renderTarget->setColorBuffer(colorBuffer);
	renderTarget->setZBuffer(zBuffer);
	RenderContext *context = new RenderContext(renderTarget);
	
	VertexShader *vertexShader = new (memalign(64, sizeof(PhongVertexShader))) PhongVertexShader();
	PixelShader *pixelShader = new PhongPixelShader(renderTarget);

	pixelShader->enableZBuffer(true);
	context->bindShader(vertexShader, pixelShader);

	PhongUniforms *uniforms = new PhongUniforms;
	uniforms->fLightVector[0] = 0.7071067811f;
	uniforms->fLightVector[1] = 0.7071067811f; 
	uniforms->fLightVector[2] = 0.0f;
	uniforms->fDirectional = 0.6f;		
	uniforms->fAmbient = 0.2f;

	context->bindUniforms(uniforms);

	Matrix projectionMatrix = Matrix::getProjectionMatrix(kFbWidth, kFbHeight);
	Matrix modelViewMatrix;
	Matrix rotationMatrix;
	context->bindGeometry(kTeapotVertices, kNumTeapotVertices, kTeapotIndices, kNumTeapotIndices);
	modelViewMatrix = Matrix::getTranslationMatrix(0.0f, 0.1f, 0.25f);
	modelViewMatrix = modelViewMatrix * Matrix::getRotationMatrix(M_PI, -1.0f, 0.0f, 0.0f);
	
	rotationMatrix = Matrix::getRotationMatrix(M_PI / 8, 0.707f, 0.707f, 0.0f);

	for (int frame = 0; frame < 1; frame++)
	{
		uniforms->fMVPMatrix = projectionMatrix * modelViewMatrix;
		uniforms->fNormalMatrix = modelViewMatrix.upper3x3();
		context->renderFrame();
		modelViewMatrix = modelViewMatrix * rotationMatrix;
	}
	
	return 0;
}
