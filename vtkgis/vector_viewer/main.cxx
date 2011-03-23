
// VTK includes.
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkInteractorStyleRubberBand3D.h>
#include <vtkLookupTable.h>
#include <vtkMapper.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkOutlineFilter.h>
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

// C++ includes.
#include <sstream>

// Color table.
double colors[][3] =
{
  {0.9, 0.3, 0.0},
  {0.2, 0.2, 0.8},
  {0.0, 0.9, 0.6},
  {0.5, 0.5, 0.5}
};

// Main program.
int main(int argc, char **argv)
{
  if(argc < 2)
    {
    std::cerr << "Arguments are: shapefile_viewer input_shape_file" << std::endl;
    return 1;
    }

  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkInteractorStyleRubberBand3D> isRubberBand3D =
      vtkSmartPointer<vtkInteractorStyleRubberBand3D>::New();
  renderWindowInteractor->SetInteractorStyle(isRubberBand3D);

  // Create reader to read shape file.
  vtkSmartPointer<vtkOGRReader> reader = vtkSmartPointer<vtkOGRReader>::New();
  reader->SetFileName(argv[1]);
  reader->Update();

  // Dealing with reader output.
  vtkSmartPointer<vtkMultiBlockDataSet> mbds = reader->GetOutput();

  int numberOfBlocks = mbds->GetNumberOfBlocks();
  std::cout << "Number of blocks: " << numberOfBlocks << std::endl;
  std::cout << "Number of layers " << reader->GetNumberOfLayers() << std::endl;

  for (int i=0; i < numberOfBlocks; ++i)
    {
    if(vtkSmartPointer<vtkPolyData> polyData = vtkPolyData::SafeDownCast( mbds->GetBlock(i) ))
      {
      vtkSmartPointer<vtkCellArray> polys = polyData->GetPolys();
      if(polys->GetNumberOfCells() > 1)
        {
        std::cout << "Index is " << i << std::endl;
        std::cout << "Number of cells are " << polys->GetNumberOfCells() << std::endl;
        }

      vtkSmartPointer<vtkPolyData> newPolyData (vtkSmartPointer<vtkPolyData>::New());
      newPolyData->SetPolys(polyData->GetLines());
      newPolyData->SetPoints(polyData->GetPoints());

      vtkSmartPointer<vtkTriangleFilter> tf (vtkSmartPointer<vtkTriangleFilter>::New());
      tf->SetInput(newPolyData);
      tf->Update();

//      // Writing data to file as well.
//      vtkSmartPointer<vtkPolyDataWriter> writer (vtkSmartPointer<vtkPolyDataWriter>::New());
//      std::ostringstream oss;
//      oss << i;
//      std::string fileName = std::string("/home/aashish/Desktop/output") + oss.str() + ".vtk";
//      writer->SetFileName(fileName.c_str());
//      writer->SetInput(tf->GetOutput());
//      writer->Write();

      vtkSmartPointer<vtkPolyDataMapper> mapper =
        vtkSmartPointer<vtkPolyDataMapper>::New();
      mapper->SetInput(tf->GetOutput());
      vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);
      actor->GetProperty()->SetColor(colors[i%4]);

      vtkSmartPointer<vtkPolyDataMapper> lineMapper (vtkSmartPointer<vtkPolyDataMapper>::New());
      vtkSmartPointer<vtkActor> lineActor (vtkSmartPointer<vtkActor>::New());
      lineMapper->SetInput(polyData);
      lineActor->SetMapper(lineMapper);
      lineActor->GetProperty()->SetColor(0.0, 0.0, 0.0);
      lineActor->GetProperty()->SetLineWidth(2.0);

      renderer->AddActor(actor);
      renderer->AddActor(lineActor);
      }
    }

  //Add the actor to the scene
  renderer->SetBackground(1,1,1); // Background color white

  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
