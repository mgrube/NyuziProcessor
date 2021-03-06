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

#ifndef __RENDER_CONTEXT_H
#define __RENDER_CONTEXT_H

#include "RenderTarget.h"
#include "VertexShader.h"
#include "PixelShader.h"

namespace render
{

class RenderContext
{
public:
	RenderContext(RenderTarget *target);
	void renderFrame();
	void bindShader(VertexShader *vertexShader, PixelShader *pixelShader);
	void bindGeometry(const float *vertices, int numVertices, const int *indices, int numIndices);
	void bindUniforms(const void *uniforms);
		
private:
	struct Triangle 
	{
		float x0, y0, z0, x1, y1, z1, x2, y2, z2;
		int x0Rast, y0Rast, x1Rast, y1Rast, x2Rast, y2Rast;
		bool visible;
		int bbLeft, bbTop, bbRight, bbBottom;
		int offset0, offset1, offset2;
	};

	void shadeVertices(int index, int, int);
	void setUpTriangle(int triangleIndex, int, int);
	void fillTile(int x, int y, int);
	static void _shadeVertices(void *_castToContext, int x, int y, int z);
	static void _setUpTriangle(void *_castToContext, int x, int y, int z);
	static void _fillTile(void *_castToContext, int x, int y, int z);
	
	float *fVertexParams;
	Triangle *fTriangles;
	RenderTarget *fRenderTarget;
	const float *fVertices;
	int fNumVertices;
	const int *fIndices;
	int fNumIndices;
	const void *fUniforms;
	int fNumVertexParams;
	VertexShader *fVertexShader;	
	PixelShader *fPixelShader;
	int fFbWidth;
	int fFbHeight;
};

}

#endif
