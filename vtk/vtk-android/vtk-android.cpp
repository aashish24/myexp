
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkOBJReader.h>
#include <vtkPointData.h>
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

GLuint positionBuffer;
GLuint normalBuffer;

GLuint modelTransformUniform;
GLuint viewTransformUniform;

GLuint positionsLoc;
GLuint normalsLoc;

// Global variables.
int numberOfIndices;
double offset[3];
double bounds[6];

//-----------------------------------------------------------------------------
vtkSmartPointer<vtkPolyData> LoadData(const std::string& filename)
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
  glm::mat4 viewMatrix = glm::perspective(45.0f, (float)width/height, 0.1f, 1000.0f);
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

  int sizeOfPositions = numberOfCells * 3 * 3;
  int dataSize        = sizeOfPositions * sizeof(double);

  double* positions   = new double[sizeOfPositions];
  vtkIdList *pointIds = vtkIdList::New();

  vtkDataArray *polyNormals = polyData->GetPointData()->GetNormals();
  double *normals;
  if(polyNormals)
    {
     normals = new double[sizeOfPositions];
    }


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

      if(polyNormals)
        {
        double *normal;
        normal = polyNormals->GetTuple3(pointIds->GetId(j));
        normals[i * 9 + j * 3 + 0] = normal[0];
        normals[i * 9 + j * 3 + 1] = normal[1];
        normals[i * 9 + j * 3 + 2] = normal[2];
        }
    }
  }

  numberOfIndices = numberOfCells * 3;

  if(polyNormals)
    {
    for(int i=0; i < sizeOfPositions / 3; ++i)
      {
      std::cout << "normals "  << i << " " << normals[i * 3 + 0] << " " << normals[i * 3 + 1] << " " << normals[i * 3 + 2] << std::endl;
      }
    }

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
  positionsLoc   = glGetAttribLocation(gPhongShader, "positions");
  normalsLoc     = glGetAttribLocation(gPhongShader, "normals");

  modelTransformUniform = glGetUniformLocation(gPhongShader, "modelMatrix");
  viewTransformUniform  = glGetUniformLocation(gPhongShader, "viewMatrix");

  glGenBuffers(1, &positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, dataSize * 2, NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, positions);
  glBufferSubData(GL_ARRAY_BUFFER, dataSize, dataSize, normals);

  glVertexAttribPointer(positionsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0);

  glVertexAttribPointer(normalsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *) (dataSize));

//  glGenBuffers(1, &normalBuffer);
//  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(double) * numberOfIndices * 3, normals, GL_STATIC_DRAW);
//  glVertexAttribPointer(normalsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0);
//  glEnableVertexAttribArray(normalsLoc);

  // Swith back to normal operations.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glUseProgram(gPhongShader);

  polyData->GetBounds(bounds);

  offset[0] = (bounds[1] + bounds[0]) / 2.0;
  offset[1] = (bounds[3] + bounds[2]) / 2.0;
  offset[2] = (bounds[5] + bounds[4]);

  return true;
}

// Render scene.
//-----------------------------------------------------------------------------
void RenderScene()
{
  glClearColor(1.0, 1.0, 1.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glm::mat4 modelMatrix(1.0f);
  modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-offset[0], -offset[1], -offset[2]));
  glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glEnableVertexAttribArray(positionsLoc);
  glEnableVertexAttribArray(normalsLoc);

//  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

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

  vtkSmartPointer<vtkPolyData> polyData ( LoadData( std::string(argv[1]) ) ) ;

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

