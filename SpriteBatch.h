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
		Glyph();
		Glyph(const glm::vec4& DestRect, const glm::vec4& UVRect, GLuint Texture, float Depth, const ColorRGBA8& Color);
		Glyph(const glm::vec4& DestRect, const glm::vec4& UVRect, GLuint Texture, float Depth, const ColorRGBA8& Color,float angle);
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
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
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color,float angle);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

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

