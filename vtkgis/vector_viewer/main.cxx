
#include <vtkActor.h>
#include <vtkInteractorStyleRubberBand3D.h>
#include <vtkMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataWriter.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <vtkTriangleFilter.h>
#include <vtkPolyDataNormals.h>

#include "vtkOGRReader.h"

int main(int argc, char **argv)
{
  if(argc < 2)
    {
    std::cerr << "Arguments are: shapefile_viewer input_shape_file" << std::endl;
    return 1;
    }

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleRubberBand3D> isRubberBand3D =
      vtkSmartPointer<vtkInteractorStyleRubberBand3D>::New();
  renderWindowInteractor->SetInteractorStyle(isRubberBand3D);

  vtkSmartPointer<vtkOGRReader> reader =
    vtkSmartPointer<vtkOGRReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  std::cout << "Number of layers " << reader->GetNumberOfLayers() << std::endl;

  vtkSmartPointer<vtkMultiBlockDataSet> mbds = reader->GetOutput();

  int numberOfBlocks = mbds->GetNumberOfBlocks();
  std::cout << "Number of blocks: " << numberOfBlocks << std::endl;
  int j = 0;
  for (int i=0; i < numberOfBlocks; ++i)
    {
//    if (i > 10)
//      {
//      break;
//      }
    if(vtkSmartPointer<vtkPolyData> polyData = vtkPolyData::SafeDownCast( mbds->GetBlock(i) ))
      {
      std::cout << "Success " << std::endl;
      std::cout << reader->GetFeatureCount() << std::endl;

      vtkSmartPointer<vtkTriangleFilter> tf (vtkSmartPointer<vtkTriangleFilter>::New());
      tf->SetInput(polyData);
      tf->Update();

      std::cout << polyData->GetNumberOfCells() << std::endl;

      // Writing data to file as well.
      vtkSmartPointer<vtkPolyDataWriter> writer (vtkSmartPointer<vtkPolyDataWriter>::New());
      writer->SetFileName("ShapeVTK.vtk");
      writer->SetInput(polyData);
      writer->Write();

      vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
      mapper->SetInput(tf->GetOutput());
      vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);

      if(j == 0)
        {
        actor->GetProperty()->SetColor(0.8, 0.3, 0.3); //(R,G,B)
        }
      if(j == 1)
        {
        actor->GetProperty()->SetColor(0.3, 0.8, 0.3); //(R,G,B)
        }
      if(j == 2)
        {
        actor->GetProperty()->SetColor(0.0, 0.3, 0.8); //(R,G,B)
        }
      if(j == 3)
        {
        actor->GetProperty()->SetColor(0.2, 0.6, 0.6); //(R,G,B)
        }
      if(j == 4)
        {
        actor->GetProperty()->SetColor(0.2, 0.6, 0.6); //(R,G,B)
        }
      if(j == 5)
        {
        actor->GetProperty()->SetColor(0.2, 0.0, 0.6); //(R,G,B)
        }
      if(j == 6)
        {
        actor->GetProperty()->SetColor(0.6, 0.5, 0.1); //(R,G,B)
        }
      if(j == 7)
        {
        actor->GetProperty()->SetColor(0.6, 0.5, 0.5); //(R,G,B)
        }
      if(j == 8)
        {
        actor->GetProperty()->SetColor(0.1, 0.33, 0.22); //(R,G,B)
        }
      if(j == 9)
        {
        actor->GetProperty()->SetColor(0, 0.5, 0.1); //(R,G,B)
        }
      if(j == 10)
        {
        actor->GetProperty()->SetColor(0.9, 0.5, 0.1); //(R,G,B)
        }
      if(j == 11)
        {
        actor->GetProperty()->SetColor(0.6, 0.2, 0.1); //(R,G,B)
        }
      if(j == 12)
        {
        actor->GetProperty()->SetColor(0.1, 0.1, 0.1); //(R,G,B)
        }
      if(j == 13)
        {
        actor->GetProperty()->SetColor(0.25, 0.25, 0.1); //(R,G,B)
        }
      if(j == 14)
        {
        actor->GetProperty()->SetColor(0.61, 0.35, 1.0); //(R,G,B)
        }
      if(j == 15)
        {
        actor->GetProperty()->SetColor(0.1, 0.9, 0.1); //(R,G,B)
        }
      if(j == 16)
        {
        actor->GetProperty()->SetColor(0.71, 0.19, 0.71); //(R,G,B)
        }
      if(j == 17)
        {
        actor->GetProperty()->SetColor(0.21, 0.29, 0.21); //(R,G,B)
        }
      if(j == 18)
        {
        actor->GetProperty()->SetColor(0.71, 0.19, 0.91); //(R,G,B)
        }
      if(j == 19)
        {
        actor->GetProperty()->SetColor(0.11, 0.89, 0.81); //(R,G,B)
        }
      if(j == 20)
        {
        actor->GetProperty()->SetColor(0.21, 0.59, 0.51); //(R,G,B)
        }
      if(j == 21)
        {
        actor->GetProperty()->SetColor(0.11, 0.89, 0.21); //(R,G,B)
        }
      if(j == 22)
        {
        actor->GetProperty()->SetColor(0.21, 0.339, 0.221); //(R,G,B)
        }
      if(j == 23)
        {
        actor->GetProperty()->SetColor(0.71, 0.229, 0.21); //(R,G,B)
        }
      if(j == 24)
        {
        actor->GetProperty()->SetColor(0.23, 0.23, 0.3); //(R,G,B)
        }
      if(j == 25)
        {
        actor->GetProperty()->SetColor(0.123, 0.923, 0.321); //(R,G,B)
        }
      if(j == 26)
        {
        actor->GetProperty()->SetColor(0.5, 0.1, 0.1); //(R,G,B)
        }
      if(j == 27)
        {
        actor->GetProperty()->SetColor(0.68, 0.66, 0.2); //(R,G,B)
        }
      if(j == 28)
        {
        actor->GetProperty()->SetColor(0.16, 1.0, 0.2); //(R,G,B)
        }
      if(j == 29)
        {
        actor->GetProperty()->SetColor(0.11, 0.4, 0.21); //(R,G,B)
        }
      if(j == 30)
        {
        actor->GetProperty()->SetColor(0.14, 0.6, 0.1); //(R,G,B)
        j = -1;
        }

      ++j;
      renderer->AddActor(actor);
      }
    }

  //Add the actor to the scene
  renderer->SetBackground(1,1,1); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
