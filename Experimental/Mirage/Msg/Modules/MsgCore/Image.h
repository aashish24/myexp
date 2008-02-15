#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <oge/Export.h>

namespace oge
{
	namespace core
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
