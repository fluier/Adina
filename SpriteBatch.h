#pragma once

#include<GL\glew.h>
#include<glm\glm.hpp>

#include<vector>

#include"Vertex.h"

namespace Adina{
	enum class GlyphSortType{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};
	class Glyph{
	public:
		GLuint	texture;
		float depth;
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
		Glyph(){}
		Glyph(const glm::vec4& DestRect, const glm::vec4& UVRect, GLuint Texture, float Depth, const ColorRGBA8& Color):
			texture(Texture),
			depth(Depth)
		{

			topLeft.color = Color;
			topLeft.setPosition(DestRect.x, DestRect.y + DestRect.w);
			topLeft.setUV(UVRect.x, UVRect.y + UVRect.w);

			bottomLeft.color = Color;
			bottomLeft.setPosition(DestRect.x, DestRect.y);
			bottomLeft.setUV(UVRect.x, UVRect.y);

			bottomRight.color = Color;
			bottomRight.setPosition(DestRect.x + DestRect.z, DestRect.y);
			bottomRight.setUV(UVRect.x + UVRect.z, UVRect.y);

			topRight.color = Color;
			topRight.setPosition(DestRect.x + DestRect.z, DestRect.y + DestRect.w);
			topRight.setUV(UVRect.x + UVRect.z, UVRect.y + UVRect.w);
		}
	};
	class RenderBatch{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture):
			offset(Offset),
			numVertices(NumVertices),
			texture(Texture){
		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};
	class SpriteBatch
	{
	private:
		GLuint m_vbo;
		GLuint m_vao;
		GlyphSortType m_sortType;

		std::vector<Glyph> m_glyph;          /// < this are the actual glyphs
		std::vector<Glyph*> m_glyphPointers; /// < this is for sorting

		std::vector<RenderBatch> m_renderBatches;
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

		void renderBatch();
	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};
}/*Adina*/

