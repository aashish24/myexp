#include <QApplication>
#include <QMainWindow>
#include <QFileInfo>
#include <QDateTime>

#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <vtkGeoView.h>
#include <vtkJPEGReader.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QMainWindow mainWindow;

  QVTKWidget *qvtk=new QVTKWidget();

  vtkGeoView* view=vtkGeoView::New();

  vtkJPEGReader* reader=vtkJPEGReader::New();
  reader->SetFileName("/home/aashish/tools/vtk/data.git/Data/Infovis/Images/NE2_ps_bath.jpg");
  reader->Update();
  view->AddDefaultImageRepresentation(reader->GetOutput());
  view->ResetCamera();

  //comment these 2 for separate window
  view->SetInteractor(qvtk->GetInteractor());
  qvtk->SetRenderWindow(view->GetRenderWindow());

  //uncomment these 3 for separate window
  //view->Render();
  //view->GetInteractor()->Initialize();
  //view->GetInteractor()->Start();

  mainWindow.setCentralWidget(qvtk);
  mainWindow.resize(600,600);
  mainWindow.show();

  return app.exec();
}
