

#include "Model.h"
#include "View.h"

#include "Controller.h"

#include <GL/glut.h>

DigitalInput mouseKey1;
DigitalInput mouseKey2;
DigitalInput mouseKey3;

void
reshape(int w, int h)
{
  /* Because Gil specified "screen coordinates" (presumably with an
     upper-left origin), this short bit of code sets up the coordinate
     system to correspond to actual window coodrinates.  This code
     wouldn't be required if you chose a (more typical in 3D) abstract
     coordinate system. */

  glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
  glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
  glLoadIdentity();             /* Reset project matrix. */
  glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
  glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
  glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
}

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0);  /* blue */
    glVertex2i(0, 0);
    glColor3f(0.0, 1.0, 0.0);  /* green */
    glVertex2i(200, 200);
    glColor3f(1.0, 0.0, 0.0);  /* red */
    glVertex2i(20, 200);
  glEnd();
  glFlush();  /* Single buffered, so needs a flush. */
}


void mouse( int button, int state, int x, int y )
{ 
  if( state == GLUT_DOWN )
  {
    if( button == GLUT_LEFT_BUTTON )
    {
      mouseKey1.execute();
    }
  }
}

int
main(int argc, char **argv)
{ 

  PrintCommand  pCommand;
  PrintCommand2 pCommand2;

  mouseKey1.addFunctorOnClick( new InputFunctor< PrintCommand > ( &pCommand, &PrintCommand::execute ) );
  mouseKey1.addFunctorOnClick( new InputFunctor< PrintCommand2 > ( &pCommand2, &PrintCommand2::execute ) );

  mouseKey2.addFunctorOnClick( new InputFunctor< PrintCommand > ( &pCommand, &PrintCommand::execute ) );
  mouseKey3.addFunctorOnClick( new InputFunctor< PrintCommand > ( &pCommand, &PrintCommand::execute ) );

  glutInit( &argc, argv );
  glutCreateWindow( "single triangle" );
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutMouseFunc( mouse );
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


//int main()
//{
//  Model* model = new Model();
//
//  View* view = new View( model );
//
//  view->render();
//}