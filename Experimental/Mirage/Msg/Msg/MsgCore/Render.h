#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace oge
{
	namespace core
	{
		class OGE_EXPORT Renderer
		{
			virtual void draw() = 0;
		};
	}
}

#endif // __RENDERER_H__

