
//#include "boost/bind.hpp"

// First file that should be included. 




#include "i3dea/vrj/glut/GlutWrapper.h"

#include "GlutApp.h"

#include <functional>

#if 0
class Test
{
public:
	void  display2( void );
};

void Test::display2( void )
	{
	
    glBegin( GL_QUADS );
        glVertex3f( 0.0, 0.0, 0.0 );
          glVertex3f( 10.0, 0.0, 0.0 );
          glVertex3f( 10.0, 10.0, 0.0 );
          glVertex3f( 0.0, 10.0, 0.0 );
      glEnd();
		return ;
	}

void display()
{
	std::cout << "Display:" << std::endl;
}

int main()
{
	Test testApp;
			
  i3dea::vrj::glut::glutDisplayFunc( boost::bind( &Test::display2, &testApp ) );
  
  i3dea::vrj::glut::glutMainLoop();	
}
#endif // #if 0

int main()
{
  torus_select(RED_PLASTIC);
  teapot_select(BRASS);
  ico_select(EMERALD);

  i3dea::vrj::glut::glutDisplayFunc( &display );

  i3dea::vrj::glut::glutContextInitFunc( &init );

  i3dea::vrj::glut::glutMainLoop();
}



