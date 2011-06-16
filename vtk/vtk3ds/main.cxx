#include <vtk3DSImporter.h>
#include <vtkLight.h>
#include <vtkMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

int main(int argc, char *argv[])
{
  vtkSmartPointer<vtkRenderWindowInteractor> interactor (vtkSmartPointer<vtkRenderWindowInteractor>::New());
  vtkSmartPointer<vtkRenderWindow> renderWindow (vtkSmartPointer<vtkRenderWindow>::New());

  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtk3DSImporter> importer (vtkSmartPointer<vtk3DSImporter>::New());
  importer->SetFileName("/home/aashish/tools/mywork/src.git/vtk/vtk3ds/assembly_cell_modelT.3ds");
  importer->DebugOn();
  importer->Read();
  renderWindow->AddRenderer(importer->GetRenderer());

  vtkSmartPointer<vtkLight> light (vtkSmartPointer<vtkLight>::New());
  light->SetColor(1, 1, 1);
  light->SetDiffuseColor(1.0, 1.0, 1.0);
  light->SetIntensity(1);
  light->SetAmbientColor(2.0, 2.0, 2.0);
  light->SetLightTypeToHeadlight();
  importer->GetRenderer()->AddLight(light);


  interactor->Initialize();
  interactor->Start();
}
