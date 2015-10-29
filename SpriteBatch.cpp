#include "SpriteBatch.h"

#include<algorithm>

namespace Adina{

	SpriteBatch::SpriteBatch():
		m_vao(0),
		m_vbo(0){
	}


	SpriteBatch::~SpriteBatch(){
	}

	void SpriteBatch::init(){
		createVertexArray();
	}
	void SpriteBatch::begin(GlyphSortType sortType){
		m_sortType = sortType;
		m_renderBatches.clear();
		// Have to delete any glyphs that remain so we don't have memory leaks!
		m_glyph.clear();
	}
	void SpriteBatch::end(){
		/// set up all pointers for fast sorthing
		m_glyphPointers.resize(m_glyph.size());
		for (unsigned i = 0; i < m_glyph.size(); i++){
			m_glyphPointers[i] = &m_glyph[i];
		}
		sortGlyphs();
		createRenderBatches();
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	{		
		m_glyph.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::renderBatch(){
		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray(m_vao);

		for (unsigned i = 0; i < m_renderBatches.size(); i++){
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}
	void SpriteBatch::createRenderBatches(){
		// This will store all the vertices that we need to upload
		std::vector<Vertex>vertices;
		// Resize the buffer to the exact size we need so we can treat
		// it like an array
		vertices.resize(m_glyphPointers.size() * 6);

		if (m_glyphPointers.empty()){
			return;
		}
		int offset = 0;
		int cv = 0; // current vertex
		//RenderBatch newBatch(0, 6, m_glyph[0]->texture);
		//m_renderBatches.emplace_back(newBatch);
		//Add the first batch
		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->topRight;
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		offset += 6;
		for (unsigned cg = 1; cg < m_glyph.size(); cg++){// current glyph
			// Check if this glyph can be part of the current batch
			if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture){
				// Make a new batch
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
			}
			else{
				// If its part of the current batch, just increase numVertices
				m_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->topRight;
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			offset += 6;
		}
		// Bind our VBO
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// Orphan the buffer (for speed)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		// Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void SpriteBatch::createVertexArray(){
		// Generate the VAO if it isn't already generated
		if (m_vao == 0){
			glGenVertexArrays(1, &m_vao);
		}
		// Bind the VAO. All subsequent opengl calls will modify it's state.
		glBindVertexArray(m_vao);
		
		//Generate the VBO if it isn't already generated
		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo); 
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		//Tell opengl what attribute arrays we need
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs(){
		switch (m_sortType){
		case GlyphSortType::BACK_TO_FRONT:
			
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);

			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
		default:;
		}
	}
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){
		return (a->texture < b->texture);
	}
}/*Adina*/