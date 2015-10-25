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
		for (int i = 0; i < m_glyph.size(); i++) {
			delete m_glyph[i];
		}
		m_glyph.clear();
	}
	void SpriteBatch::end(){
		sortGlyphs();
		createRenderBatches();
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color){
		Glyph* newGlyph = new Glyph;
		newGlyph->texture = texture;
		newGlyph->depth = depth;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x +uvRect.z, uvRect.y);

		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		m_glyph.push_back(newGlyph);
	}

	void SpriteBatch::renderBatch(){
		// Bind our VAO. This sets up the opengl state we need, including the 
		// vertex attribute pointers and it binds the VBO
		glBindVertexArray(m_vao);

		for (int i = 0; i < m_renderBatches.size(); i++){
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
		vertices.resize(m_glyph.size() * 6);

		if (m_glyph.empty()){
			return;
		}
		int offset = 0;
		int cv = 0; // current vertex
		//RenderBatch newBatch(0, 6, m_glyph[0]->texture);
		//m_renderBatches.emplace_back(newBatch);
		//Add the first batch
		m_renderBatches.emplace_back(offset, 6, m_glyph[0]->texture);
		vertices[cv++] = m_glyph[0]->topLeft;
		vertices[cv++] = m_glyph[0]->bottomLeft;
		vertices[cv++] = m_glyph[0]->bottomRight;
		vertices[cv++] = m_glyph[0]->bottomRight;
		vertices[cv++] = m_glyph[0]->topRight;
		vertices[cv++] = m_glyph[0]->topLeft;
		offset += 6;
		for (int cg = 1; cg < m_glyph.size(); cg++){// current glyph
			// Check if this glyph can be part of the current batch
			if (m_glyph[cg]->texture != m_glyph[cg - 1]->texture){
				// Make a new batch
				m_renderBatches.emplace_back(offset, 6, m_glyph[cg]->texture);
			}
			else{
				// If its part of the current batch, just increase numVertices
				m_renderBatches.back().numVertices += 6;
			}
			vertices[cv++] = m_glyph[cg]->topLeft;
			vertices[cv++] = m_glyph[cg]->bottomLeft;
			vertices[cv++] = m_glyph[cg]->bottomRight;
			vertices[cv++] = m_glyph[cg]->bottomRight;
			vertices[cv++] = m_glyph[cg]->topRight;
			vertices[cv++] = m_glyph[cg]->topLeft;
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
			
			std::stable_sort(m_glyph.begin(), m_glyph.end(), compareFrontToBack);

			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyph.begin(), m_glyph.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyph.begin(), m_glyph.end(), compareTexture);
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