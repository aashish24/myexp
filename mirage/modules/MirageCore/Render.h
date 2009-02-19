
#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Msg
{
	namespace MsgCore
	{
		class MSG_EXPORT Renderer
		{
			virtual void draw() = 0;
		};
	}
}

#endif // __RENDERER_H__

