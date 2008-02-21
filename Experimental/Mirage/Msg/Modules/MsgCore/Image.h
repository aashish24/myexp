#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Export.h"

namespace Msg
{
	namespace MsgCore
	{
		class OGE_EXPORT Image : public Referenced
		{
			public:
				Image()
				{
				}

				Image( const Image* image )
				{
				}
		};
	}
}

#endif  __IMAGE_H__
