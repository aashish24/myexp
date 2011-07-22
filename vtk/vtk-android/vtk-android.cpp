
#include <vtkCellArray.h>
#include <vtkOBJReader.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

// GL includes.
#include "OpenGL.h"

// Library includes.
#include"OpenGLSLHelper.h"

// C++ includes.
#include <iostream>

// GLM includes.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLSlang objects.
GLhandleARB gPhongShader;
GLuint oneBuffer;
GLuint modelTransformUniform;
GLuint viewTransformUniform;

// Global variables.
int numberOfIndices;

//-----------------------------------------------------------------------------
vtkSmartPointer<vtkPolyData> readFile(const std::string& filename)
{
  vtkSmartPointer<vtkOBJReader> objReader (vtkSmartPointer<vtkOBJReader>::New());
  objReader->SetFileName(filename.c_str());
  objReader->Update();

  vtkSmartPointer<vtkPolyData> polyData (vtkSmartPointer<vtkPolyData>::New());
  polyData->ShallowCopy( objReader->GetOutput() );

  return polyData.GetPointer();
}

//-----------------------------------------------------------------------------
void printHelp()
{
  std::cout << "executable fiilename [obj]" << std::endl;
}

//-----------------------------------------------------------------------------
void Resize(int width, int height)
{
  glViewport(0, 0, width, height);

//  gluPerspective(45, width/height, 1.0, 1000.0);
  glm::mat4 viewMatrix = glm::perspective(45.0f, (float)width/height, 1.0f, 1000.0f);
  glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

//-----------------------------------------------------------------------------
bool InitializeApp(vtkSmartPointer<vtkPolyData>& polyData)
{
  if(!polyData)
    {
    return false;
    }

  vtkPoints* points   = polyData->GetPoints();
  vtkCellArray* polys = polyData->GetPolys();
  int numberOfCells   = polys->GetNumberOfCells();

  double* positions   = new double[numberOfCells * 3 * 3 + 1];

  vtkIdList *pointIds = vtkIdList::New();

  for(int i=0; i < numberOfCells; ++i)
  {
    polys->GetNextCell(pointIds);

    int numberOfIds = pointIds->GetNumberOfIds();
    for(int j=0; j < numberOfIds; ++j)
    {
      double temp[3];
      points->GetPoint(pointIds->GetId(j), temp);
      positions[i * 9 + j * 3 + 0] = temp[0];
      positions[i * 9 + j * 3 + 1] = temp[1];
      positions[i * 9 + j * 3 + 2] = temp[2];
    }
  }

  numberOfIndices = numberOfCells * 3.0;

  pointIds->Delete();

  // Load shaders and object.
  // Load shaders.
  if(!CreateGLSLShader("/home/aashish/tools/mywork/src.git/vtk/vtk-android/per_pixel_phong_shader_vs.glsl",
                      "/home/aashish/tools/mywork/src.git/vtk/vtk-android/per_pixel_phong_shader_ps.glsl", gPhongShader))
   {
    return false;
   }

  // glBindAttribLocation requires call before glLinkProgram. Since in our code this is not
  // entirely possible we are getting attribute location and using the locations to glVertexAttribPointer.
  GLuint positionsLoc   = glGetAttribLocation(gPhongShader, "positions");

  modelTransformUniform = glGetUniformLocation(gPhongShader, "modelMatrix");
  viewTransformUniform  = glGetUniformLocation(gPhongShader, "viewMatrix");

  glGenBuffers(1, &oneBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, oneBuffer);

//  std::cout << "size of positions " << sizeof(positions) << std::endl;

  glBufferData(GL_ARRAY_BUFFER, sizeof(double) * numberOfIndices * 3, positions, GL_STATIC_DRAW);
  glVertexAttribPointer(positionsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0);
  glEnableVertexAttribArray(positionsLoc);

  // Swith back to normal operations.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glUseProgram(gPhongShader);

  return true;
}

// Render scene.
//-----------------------------------------------------------------------------
void RenderScene()
{
  glClearColor(0, 0, 0.2, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glm::mat4 modelMatrix(1.0f);
  modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -10.0));
  glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  glBindBuffer(GL_ARRAY_BUFFER, oneBuffer);
  glDrawArrays(GL_TRIANGLES, 0, numberOfIndices);

  glutSwapBuffers();
  glutPostRedisplay();
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
  if(argc < 2)
  {
    printHelp();
    return 1;
  }

  vtkSmartPointer<vtkPolyData> polyData ( readFile( std::string(argv[1]) ) ) ;

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);

  glutCreateWindow("OpenGL VBO");
  glutDisplayFunc(RenderScene);
  glutReshapeFunc(Resize);

  if(InitializeApp(polyData) == true)
     glutMainLoop();
  else
     std::cerr << "Error in InitializeApp()!\n\n";

  return 1;
}

