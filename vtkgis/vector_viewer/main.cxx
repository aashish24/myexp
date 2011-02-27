
#include <vtkActor.h>
#include <vtkInteractorStyleRubberBand3D.h>
#include <vtkMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

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
  for (int i=0; i < numberOfBlocks; ++i)
    {
    if(vtkSmartPointer<vtkPolyData> polyData = vtkPolyData::SafeDownCast( mbds->GetBlock(i) ))
      {
      std::cout << "Success " << std::endl;
      vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
      mapper->SetInput(polyData);
      vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);
      actor->GetProperty()->SetColor(1.0, 0.0, 0.0); //(R,G,B)
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
