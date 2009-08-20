
#ifndef __GLSL_SHADERS_H__
#define __GLSL_SHADERS_H__

#include <osg/Program>
#include <osg/Shader>
#include <osg/Uniform>

#include <osgDB/FileUtils>

#include "IGlslShader.h"

namespace I3deaApp
{
	// Global function. 
	void loadShaderSource( osg::Shader* shader, const std::string& fileName )
	{
		std::string fqFileName = osgDB::findDataFile(fileName);
		if( fqFileName.length() != 0 )
		{
			shader->loadShaderSourceFromFile( fqFileName.c_str() );
		}
		else
		{
			osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
		}
	}	

	class GlslShaders  : public IGlslShaders, public osg::Referenced
	{
		public:
			GlslShaders()
			{
				init();
			}

			osg::Program*					program();

			void							init();
	
			void							applyShaders( osg::Node* node );

			void							disableShaders( osg::Node* node );

	  private:
			
		  virtual ~GlslShaders()
		  {
		  }

		  // Disallow copy. 
		  GlslShaders( const GlslShaders& from, const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY ) : osg::Referenced( from )
		  {
		  }

		  // Disallow assignment. s
		  GlslShaders& operator = ( const GlslShaders& ) { return *this; }

		  osg::ref_ptr< osg::Program >		mProgram;
		  osg::ref_ptr< osg::Shader	 >		mPerPixelVertShader;
		  osg::ref_ptr< osg::Shader	 >		mPerPixelFragShader;
	};

	inline osg::Program* GlslShaders::program()
	{
		return mProgram.get();
	}

	inline void GlslShaders::init()
	{
		mProgram			= new osg::Program();
		mPerPixelVertShader = new osg::Shader( osg::Shader::VERTEX );
		mPerPixelFragShader = new osg::Shader( osg::Shader::FRAGMENT );

		loadShaderSource( mPerPixelVertShader.get(), "shaders/phong.vert" );
		loadShaderSource( mPerPixelFragShader.get(), "shaders/phong.frag" );	

		mProgram->addShader( mPerPixelVertShader.get() );
		mProgram->addShader( mPerPixelFragShader.get() );
	}

	inline void GlslShaders::applyShaders( osg::Node* node )
	{
		osg::ref_ptr< osg::StateSet > ss( node->getOrCreateStateSet() );
		if( !ss.valid() )
		{
			return;
		}
		
		ss->setAttributeAndModes( mProgram.get(), osg::StateAttribute::ON );
	}

	inline void GlslShaders::disableShaders( osg::Node* node )
	{
		osg::ref_ptr< osg::StateSet > ss( node->getOrCreateStateSet() );
		if( !ss.valid() )
		{
			return;
		}
		
		ss->setAttributeAndModes( new osg::Program(), osg::StateAttribute::ON );
	}
}

#endif // __GLSL_SHADERS_H__

