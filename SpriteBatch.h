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
	struct Glyph{
		GLuint	texture;
		float depth;
		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
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

		std::vector<Glyph*> m_glyph;
		std::vector<RenderBatch> m_renderBatches;
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect,const glm::vec4& uvRect,GLuint texture,float depth,const Color& color);

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

