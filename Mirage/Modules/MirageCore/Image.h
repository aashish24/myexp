#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Export.h"

namespace Mirage
{
	namespace MirageCore
	{
		class MSG_EXPORT Image : public Referenced
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
