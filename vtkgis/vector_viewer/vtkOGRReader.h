#ifndef __vtkOGRReader_h
#define __vtkOGRReader_h

#include <vtkMultiBlockDataSetAlgorithm.h>

#include <map> // STL required.

class vtkOGRReader : public vtkMultiBlockDataSetAlgorithm
{
public:
  static vtkOGRReader* New();
  virtual void PrintSelf( ostream& os, vtkIndent indent );
  vtkTypeRevisionMacro(vtkOGRReader,vtkMultiBlockDataSetAlgorithm);

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Return number of layers.
  int GetNumberOfLayers();

  // Description:
  // Given a index return layer type (eg point, line, polygon).
  int GetLayerType(int layerIndex=0);

  // Description:
  // Given a layer index return number of features (shapes).
  int GetFeatureCount(int layerIndex=0);

  // Description:
  // Return the active layer type (eg point, line, polygon).
  int GetActiveLayerType( ){return GetLayerType(ActiveLayer);}

  // Description:
  // Return the number of features in the active layer (shapes).
  int GetActiveLayerFeatureCount( ){return GetFeatureCount(ActiveLayer);}

  // Description:
  // Set and Get the active layer
  vtkSetMacro(ActiveLayer,int);
  vtkGetMacro(ActiveLayer,int);

  // Description:
  // Return projection string belong to each layer.
  std::map<int, std::string> GetLayersProjection()
    {
    return this->LayersProjection;
    }

protected:
  vtkOGRReader();
  virtual ~vtkOGRReader();

  int RequestInformation( vtkInformation*, vtkInformationVector**, vtkInformationVector* );
  int RequestData( vtkInformation*, vtkInformationVector**, vtkInformationVector* );

  int InitializeInternal();

  /// The name of the file that will be opened on the next call to RequestData()
  char* FileName;

  int ActiveLayer;

  //BTX
  class Internal;

  /// Private per-file metadata
  vtkOGRReader::Internal* P;

  /// Global variable indicating whether the OGR library has been registered yet or not.
  static int OGRRegistered;

  /// Mapping of layer to projection.
  std::map<int, std::string> LayersProjection;
  //ETX
};

#endif // __vtkOGRReader_h
