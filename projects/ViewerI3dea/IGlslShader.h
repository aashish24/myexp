
#ifndef __I_GLSL_SHADERS_H__
#define __I_GLSL_SHADERS_H__

namespace I3deaApp
{
	struct IGlslShaders
	{
		virtual osg::Program*	program() = 0;
		virtual void			init()	= 0;
		virtual void			applyShaders( osg::Node* node ) = 0;
		virtual void			disableShaders( osg::Node* node ) = 0;
	};
}

#endif // __I_GLSL_SHADERS_H__