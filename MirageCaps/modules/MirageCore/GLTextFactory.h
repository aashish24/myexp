#ifndef __GL_TEXT_FACTORY_H___
#define __GL_TEXT_FACTORY_H___

#include <map>
#include <string>

namespace MirageCore
{
	class Text;
}

namespace MirageCore
{	
	class GLTextFactory
	{
		public:
			typedef Text* ( *tCreator )();
			typedef std::map< std::string, tCreator > tCreatorMap;
	
			bool tRegister( const std::string& type, tCreator creator );
			Text* create( const std::string& type );	

			static GLTextFactory* instance();

		private:
			GLTextFactory()
			{}

			~GLTextFactory()
			{}

			tCreatorMap mCreators;
	};
}

#endif // __GL_TEXT_FACTORY_H___
