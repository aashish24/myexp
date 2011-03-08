#include "vtkOGRReader.h"

#include "vtkCellData.h"
#include "vtkCellType.h"
#include "vtkDoubleArray.h"
#include "vtkCellArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkIntArray.h"
#include "vtkMultiBlockDataSet.h"
#include "vtkObjectFactory.h"
#include "vtkStringArray.h"
#include "vtkPolyData.h"

#include <ogrsf_frmts.h>

#include <vtkstd/vector>

vtkStandardNewMacro(vtkOGRReader);
vtkCxxRevisionMacro(vtkOGRReader,"");

int vtkOGRReader::OGRRegistered = 0;

// -----------------------------------------------------------------------------
class vtkOGRReader::Internal
{
public:
  Internal( const char* srcName, int srcMode )
    {
    this->Source = OGRSFDriverRegistrar::Open( srcName, srcMode, &this->Driver );
    if ( ! this->Source )
      {
      this->LastError = CPLGetLastErrorMsg();
      }
    else
      {
      this->LastError = 0;
      }
    }
  ~Internal()
    {
    if ( this->Source )
      {
      OGRDataSource::DestroyDataSource( this->Source );
      }
    }

  bool ReadLayer( OGRLayer* layer, vtkMultiBlockDataSet* mbds )
    {
    int nTotPoly;
    OGRFeature* feat;
    static int layerIdx = 0;
    while ( ( feat = layer->GetNextFeature() ) )
      {
      vtkPolyData* pd = vtkPolyData::New();
      mbds->SetBlock( layerIdx, pd );
      ++layerIdx;
      pd->FastDelete();

      vtkPoints* pts = pd->GetPoints();
      if ( ! pts )
        {
        pts = vtkPoints::New();
        pd->SetPoints( pts );
        pts->FastDelete();
        }

      OGRFeatureDefn* fdef = layer->GetLayerDefn();
      int numFields = fdef->GetFieldCount();
      vtkstd::vector<vtkAbstractArray*> fields;
      vtkAbstractArray* arr;
      int f;
      for ( f = 0; f < numFields; ++f )
        {
        OGRFieldDefn* ffdef = fdef->GetFieldDefn( f );
        switch( ffdef->GetType() )
          {
        case OFTInteger:
          arr = vtkIntArray::New();
          break;
        case OFTReal:
          arr = vtkDoubleArray::New();
          break;
        case OFTString:
        default: // When in doubt, it's a string!
          arr = vtkStringArray::New();
          break;
          }
        arr->SetName( ffdef->GetNameRef() );
        fields.push_back( arr );
        pd->GetCellData()->AddArray( arr );
        arr->FastDelete();
        }

      vtkIdType nTotPoly = 0;
      vtkCellArray* lines (vtkCellArray::New());
      vtkCellArray* verts (vtkCellArray::New());

      pd->SetPolys(lines);
      pd->SetVerts(verts);

      lines->FastDelete();
      verts->FastDelete();

      // Insert points and lines to represent the geometry of each feature.
      OGRGeometry* geom = feat->GetGeometryRef();
      vtkIdType nPoly = this->insertGeometryRecursive( geom, pd, pts, lines, verts );
      if ( ! nPoly )
        {
        continue;
        }

//      double *firstPoint = pts->GetPoint(0);
//      double *lastPoint  = pts->GetPoint(pts->GetNumberOfPoints() - 1);

//      if(firstPoint[0] == lastPoint[0] &&
//         firstPoint[1] == lastPoint[1] &&
//         firstPoint[2] == lastPoint[2])
//        {
//        pts->SetNumberOfPoints(pts->GetNumberOfPoints() - 1);
//        }


      nTotPoly += nPoly;

      // Now insert the field values for this geometry once for each cell created
      // (We have to copy the values when there are multiple polygons or polygons
      //  with inner rings.)
      vtkIdType i;
      int ival;
      double rval;
      const char* sval;
      vtkIntArray* iarr;
      vtkDoubleArray* rarr;
      vtkStringArray* sarr;
      for ( f = 0; f < numFields; ++f )
        {
        OGRFieldDefn* ffdef = fdef->GetFieldDefn( f );
        switch ( ffdef->GetType() )
          {
        case OFTInteger:
          iarr = vtkIntArray::SafeDownCast( fields[f] );
          ival = feat->GetFieldAsInteger( f );
          for ( i = 0; i < nPoly; ++i )
            {
            iarr->InsertNextValue( ival );
            }
          break;
        case OFTReal:
          rarr = vtkDoubleArray::SafeDownCast( fields[f] );
          rval = feat->GetFieldAsDouble( f );
          for ( i = 0; i < nPoly; ++i )
            {
            rarr->InsertNextValue( rval );
            }
          break;
        case OFTString:
        default:
          sarr = vtkStringArray::SafeDownCast( fields[f] );
          sval = feat->GetFieldAsString( f );
          for ( i = 0; i < nPoly; ++i )
            {
            sarr->InsertNextValue( sval );
            }
          }
        }
      }

    return nTotPoly ? true : false;
    }

  vtkIdType insertGeometryRecursive( OGRGeometry* geom, vtkPolyData* pd, vtkPoints* pts, vtkCellArray* lines, vtkCellArray* verts )
    {
    if ( ! geom )
      {
      return 0;
      }

    vtkstd::vector<vtkIdType> ptIds;
    OGRPoint* gpt;
    OGRLineString* gls;
    OGRLinearRing* grng;
    OGRPolygon* gpl;
    OGRGeometryCollection* gcol;
    //OGRMultiPolygon* gmpl;
    //OGRMultiLineString* gmls;
    //OGRMultiPoint* gmpt;
    int num;
    vtkIdType i;
    vtkIdType nCells = 0;

    switch ( geom->getGeometryType() )
      {
    case wkbUnknown:
      return 0;
      break;
    case wkbPoint:
    case wkbPoint25D:
      gpt = (OGRPoint*) geom;
      ptIds.push_back( pts->InsertNextPoint( gpt->getX(), gpt->getY(), gpt->getZ() ) );
      verts->InsertNextCell(1);
      ++nCells;
      break;
    case wkbLinearRing: // NB. OGR docs imply that wkbLinearRing may not inherit wkbLineString in the future.
    case wkbLineString:
    case wkbLineString25D:
      gls = (OGRLineString*) geom;
      for ( int p = 0; p < gls->getNumPoints(); ++p )
        {
        // insert ring points
        ptIds.push_back( pts->InsertNextPoint( gls->getX( p ), gls->getY( p ), gls->getZ( p ) ) );
        }
      // insert ring line segments
      lines->InsertNextCell( (int) ptIds.size(), &(ptIds[0]) );
      ++nCells;
      break;
    case wkbPolygon:
    case wkbPolygon25D:
      gpl = (OGRPolygon*) geom;
      grng = gpl->getExteriorRing();
      nCells += this->insertGeometryRecursive( grng, pd, pts, lines, verts );
      num = gpl->getNumInteriorRings();
      for ( i = 0 ; i < num; ++i )
        {
        grng = gpl->getInteriorRing( i );
        nCells += this->insertGeometryRecursive( grng, pd, pts, lines, verts );
        }
      break;
    case wkbMultiPoint:
    case wkbMultiPoint25D:
    case wkbMultiLineString:
    case wkbMultiLineString25D:
    case wkbMultiPolygon:
    case wkbMultiPolygon25D:
    case wkbGeometryCollection:
    case wkbGeometryCollection25D:
      gcol = (OGRGeometryCollection*) geom;
      num = gcol->getNumGeometries();
      for ( i = 0 ; i < num; ++i )
        {
        nCells += this->insertGeometryRecursive( gcol->getGeometryRef( i ), pd, pts, lines, verts );
        }
      break;
    case wkbNone:
      return 0;
      break;
      }

    return nCells;
    }

  OGRDataSource* Source;
  OGRSFDriver* Driver;
  const char* LastError;
};

// -----------------------------------------------------------------------------
vtkOGRReader::vtkOGRReader()
{
  this->FileName = 0;
  this->P = 0;

  this->SetNumberOfInputPorts( 0 );

  if ( ! vtkOGRReader::OGRRegistered )
    {
    vtkOGRReader::OGRRegistered = 1;
    OGRRegisterAll();
    }
}

// -----------------------------------------------------------------------------
vtkOGRReader::~vtkOGRReader()
{
  this->SetFileName( 0 );
  if ( this->P )
    {
    delete this->P;
    }
}

// -----------------------------------------------------------------------------
void vtkOGRReader::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
  os << indent << "FileName: " << ( this->FileName ? this->FileName : "(null)" ) << "\n";
  os << indent << "P: " << this->P << "\n";
}

// -----------------------------------------------------------------------------
int vtkOGRReader::RequestInformation(
  vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector )
{
  (void)request;
  (void)inputVector;
  (void)outputVector;

  return 1;
}

// -----------------------------------------------------------------------------
int vtkOGRReader::RequestData(
  vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector )
{
  (void)request;
  (void)inputVector;

  if ( ! this->FileName )
    {
    //vtkWarningMacro( "No filename specified" );
    return 0;
    }

  vtkMultiBlockDataSet* mbds = 0;
  vtkInformation* oi = outputVector->GetInformationObject( 0 );
  if ( ! oi )
    {
    return 0;
    }
  mbds = vtkMultiBlockDataSet::SafeDownCast( oi->Get( vtkDataObject::DATA_OBJECT() ) );
  if ( ! mbds )
    {
    return 0;
    }

  if(this->InitializeInternal() == VTK_ERROR)
    {
    return 1;
    }

  vtkOGRReader::Internal* p = this->P;

  for ( int layerIdx = 0; layerIdx < p->Source->GetLayerCount(); ++layerIdx )
    {
    OGRLayer* layer = p->Source->GetLayer( layerIdx );
    if ( ! layer )
      {
      continue;
      }

    if(layer->GetSpatialRef())
      {
      char *projStr;
      layer->GetSpatialRef()->exportToWkt(&projStr);
      this->LayerProjectionMap[layerIdx] = std::string(projStr);
      }

    p->ReadLayer( layer, mbds );
    }

  return 1;
}

// -----------------------------------------------------------------------------
int vtkOGRReader::InitializeInternal()
{
  if(!this->FileName)
    {
    vtkErrorMacro(<< "FileName not set or empty:");
    return VTK_ERROR;
    }

  if(!this->P)
    {
    this->P = new vtkOGRReader::Internal( this->FileName, 0 );
    if ( ! this->P || this->P->LastError )
      {
      if ( this->P )
        {
        vtkErrorMacro( << this->P->LastError );
        delete this->P;
        this->P = 0;
        }
      return VTK_ERROR;
      }
    }

  return VTK_OK;
}

// -----------------------------------------------------------------------------
int vtkOGRReader::GetNumberOfLayers()
{
  if(this->InitializeInternal() == VTK_ERROR)
    {
    return -1;
    }

  return this->P->Source->GetLayerCount();
}

// -----------------------------------------------------------------------------
int vtkOGRReader::GetLayerType(int layerIndex)
{
  if(this->InitializeInternal() == VTK_ERROR)
    {
    return -1;
    }

  OGRLayer* layer = this->P->Source->GetLayer( layerIndex );

  if(!layer)
    {
    return -1;
    }

  switch(layer->GetGeomType())
    {
    case wkbUnknown:
      return VTK_EMPTY_CELL;
    case wkbPoint:
    case wkbPoint25D:
      return VTK_VERTEX;
    case wkbLinearRing: // NB. OGR docs imply that wkbLinearRing may not inherit wkbLineString in the future.
    case wkbLineString:
    case wkbLineString25D:
      return VTK_LINE;
    case wkbPolygon:
    case wkbPolygon25D:
      return VTK_POLYGON;
    case wkbMultiPoint:
    case wkbMultiPoint25D:
      return VTK_POLY_VERTEX;
    case wkbMultiLineString:
    case wkbMultiLineString25D:
      return VTK_POLY_LINE;
    case wkbMultiPolygon:
    case wkbMultiPolygon25D:
      return VTK_POLYGON;
    case wkbGeometryCollection:
    case wkbGeometryCollection25D:
      return VTK_NUMBER_OF_CELL_TYPES;
    case wkbNone:
      return -1;
    default:
      return -1;
    }
}

// -----------------------------------------------------------------------------
int vtkOGRReader::GetFeatureCount(int layerIndex)
 {
  if(this->InitializeInternal() == VTK_ERROR)
    {
    return -1;
    }

  OGRLayer* layer = this->P->Source->GetLayer( layerIndex );

  if(!layer)
    {
    return -1;
    }

  return layer->GetFeatureCount();
}
