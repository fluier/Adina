#pragma once

#define defaultColorValue 0

typedef unsigned char GLubyte;

namespace Adina{
	struct Position
	{
		float x;
		float y;
	};

	struct ColorRGBA8{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
		ColorRGBA8() : 
			r(defaultColorValue),
			g(defaultColorValue),
			b(defaultColorValue),
			a(defaultColorValue){
			/* Empty */ 
		}
		ColorRGBA8(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) :
			r(_r),g(_g),b(_b),a(_a)
		{ /* Empty */ }
	};
	struct UV{
		float u;
		float v;
	};
	struct Vertex{
		Position position; ///
		ColorRGBA8 color;       /// 4 bytes for R G B A color
		UV uv;             /// UV texture coordinates

		/// Some Helper Function
		void setPosition(float x, float y){
			position.x = x;
			position.y = y;
		}
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		void setUV(float u, float v){
			uv.u = u;
			uv.v = v;
		}
	};
}