
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkOBJReader.h>
#include <vtkMath.h>
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
void ResetCamera(double bounds[6], double viewAngle, bool useHorizontalViewAngle,
  double viewAspect[2], double viewPlaneNormal[3], double viewUp[3], double focalPoint[3],
  double position[3], double &parallelScale)
{
  double center[3];
  double distance;

  center[0] = (bounds[0] + bounds[1])/2.0;
  center[1] = (bounds[2] + bounds[3])/2.0;
  center[2] = (bounds[4] + bounds[5])/2.0;

  double w1 = bounds[1] - bounds[0];
  double w2 = bounds[3] - bounds[2];
  double w3 = bounds[5] - bounds[4];

  w1 *= w1;
  w2 *= w2;
  w3 *= w3;
  double radius = w1 + w2 + w3;

  // If we have just a single point, pick a radius of 1.0
  radius = (radius==0)?(1.0):(radius);

  // compute the radius of the enclosing sphere
  radius = sqrt(radius)*0.5;

  // default so that the bounding sphere fits within the view fustrum

  // compute the distance from the intersection of the view frustum with the
  // bounding sphere. Basically in 2D draw a circle representing the bounding
  // sphere in 2D then draw a horizontal line going out from the center of
  // the circle. That is the camera view. Then draw a line from the camera
  // position to the point where it intersects the circle. (it will be tangent
  // to the circle at this point, this is important, only go to the tangent
  // point, do not draw all the way to the view plane). Then draw the radius
  // from the tangent point to the center of the circle. You will note that
  // this forms a right triangle with one side being the radius, another being
  // the target distance for the camera, then just find the target dist using
  // a sin.
  double angle=vtkMath::RadiansFromDegrees(viewAngle);
  parallelScale=radius;

  if(viewAspect[0]>=1.0) // horizontal window, deal with vertical angle|scale
    {
    if(useHorizontalViewAngle)
      {
      angle=2.0*atan(tan(angle*0.5)/viewAspect[0]);
      }
    }
  else // vertical window, deal with horizontal angle|scale
    {
    if(!useHorizontalViewAngle)
      {
      angle=2.0*atan(tan(angle*0.5)*viewAspect[0]);
      }

    parallelScale=parallelScale/viewAspect[0];
    }

  distance =radius/sin(angle*0.5);

  // check view-up vector against view plane normal
  if ( fabs(vtkMath::Dot(viewUp,viewPlaneNormal)) > 0.999 )
    {
    // Resetting view-up since view plane normal is parallel.
    double temp[3] = {viewUp[0], viewUp[1], viewUp[2]};
    viewUp[0] = -temp[2];
    viewUp[1] = temp[0];
    viewUp[2] = temp[1];
    }

  // update the camera
  focalPoint[0] = center[0];
  focalPoint[1] = center[1];
  focalPoint[2] = center[2];

  position[0] = center[0] + distance* viewPlaneNormal[0];
  position[1] = center[1] + distance* viewPlaneNormal[1];
  position[2] = center[2] + distance* viewPlaneNormal[2];
}

//-----------------------------------------------------------------------------
void Resize(int width, int height)
{
  double viewAspect[2] =      {width, height};
  double viewPlaneNormal[3] = {0.0, 0.0, 1.0};
  double viewUp[3] = {0.0, 1.0, 0.0};
  double focalPoint[3] = {0.0, 0.0, 0.0};
  double viewAngle = 45.0;
  double position[3] = {0.0};
  double parallelScale = 1.0;

  glViewport(0, 0, width, height);

  ResetCamera(bounds, viewAngle, false, viewAspect, viewPlaneNormal, viewUp, focalPoint, position, parallelScale);

  glm::mat4 viewMatrix  = glm::perspective( (float)viewAngle, (float)(viewAspect[0]/viewAspect[1]), 0.1f, 1000.0f);
  glm::mat4 modelMatrix = glm::lookAt( glm::vec3(position[0], position[1], position[2]),
    glm::vec3(focalPoint[0], focalPoint[1], focalPoint[2]), glm::vec3(viewUp[0], viewUp[1], viewUp[2]));

  glUniformMatrix4fv(viewTransformUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
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
  glBufferData(GL_ARRAY_BUFFER, dataSize, positions, GL_STATIC_DRAW);
  glVertexAttribPointer(positionsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0);

  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, dataSize, normals, GL_STATIC_DRAW);
  glVertexAttribPointer(normalsLoc, 3, GL_DOUBLE, GL_FALSE, 0, (const GLvoid *)0);

  // Swith back to normal operations.
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glUseProgram(gPhongShader);

  polyData->GetBounds(bounds);

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

  Resize(800, 600);

  glEnableVertexAttribArray(positionsLoc);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

  glEnableVertexAttribArray(normalsLoc);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);

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

  if(InitializeApp(polyData) == true)
     glutMainLoop();
  else
     std::cerr << "Error in InitializeApp()!\n\n";

  return 1;
}

