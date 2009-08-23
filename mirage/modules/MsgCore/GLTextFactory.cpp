
#include <glCore/GLTextFactory>

#include <map>

using namespace glCore;

typedef GLTextFactory::tCreatorMap::value_type vt;

bool GLTextFactory::tRegister( const std::string& type, tCreator creator )
{
	return mCreators.insert( vt( type, creator ) ).second;	
}

GLTextFactory* GLTextFactory::instance()
{
	static GLTextFactory* sGLTextFactory;
	if( sGLTextFactory )
	{
		return sGLTextFactory;
	}
	else
	{
		sGLTextFactory = new GLTextFactory();
		return sGLTextFactory;
	}
}

Text* GLTextFactory::create( const std::string& type )
{
	tCreatorMap::iterator itr;

	for( itr = mCreators.begin(); itr != mCreators.end(); ++itr )
	{
		if( itr->first == type )
		{
			return itr->second();
		}
	}
}