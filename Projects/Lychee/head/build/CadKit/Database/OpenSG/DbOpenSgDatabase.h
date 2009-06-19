
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  DbOsgDatabase: OpenSceneGraph database wrapper class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CADKIT_DATABASE_OPEN_SG_LIBRARY_DATABASE_H_
#define _CADKIT_DATABASE_OPEN_SG_LIBRARY_DATABASE_H_

#include "DbOpenSgApi.h"

#include "Database/Base/DbBaseTarget.h"

#include "Interfaces/IEntityNotify.h"
#include "Interfaces/IInstanceQuery.h"
#include "Interfaces/IFileExtension.h"
#include "Interfaces/IDataWrite.h"
#include "Interfaces/IOutputAttribute.h"

#include "Standard/SlStack.h"
#include "Standard/SlErrorPolicy.h"

#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGNode.h>

namespace CadKit
{
class DB_OPENSG_API DbOpenSgDatabase : public DbBaseTarget,
                                       public IAssemblyNotify,
                                       public IPartNotify,
                                       public IInstanceNotify,
                                       public ILodNotify,
                                       public IShapeNotify,
                                       public ISetNotify,
                                       public IFileExtension,
                                       public IDataWrite,
                                       public IOutputAttribute
{
public:

  DbOpenSgDatabase();
  
protected:

  virtual ~DbOpenSgDatabase();

public:
  
  // IUnknown interface.
  CADKIT_DECLARE_IUNKNOWN_MEMBERS;
  
  /////////////////////////////////////////////////////////////////////////////
  //
  //  IDataTarget interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // Tell the target it is about to receive data.
  virtual bool            dataTransferStart ( IUnknown *caller );

  // Tell the target it is done receiving data.
  virtual bool            dataTransferEnd ( IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IFormatAttribute interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // Does the format have the attribute?
  virtual bool            isAttributeSupported ( const FormatAttribute &attribute ) const;

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IAssemblyNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the assembly.
  virtual bool            endEntity ( AssemblyHandle assembly, IUnknown *caller );

  // Start the assembly.
  virtual bool            startEntity ( AssemblyHandle assembly, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IPartNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the part.
  virtual bool            endEntity ( PartHandle assembly, IUnknown *caller );

  // Start the part.
  virtual bool            startEntity ( PartHandle assembly, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IInstanceNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the instance.
  virtual bool            endEntity ( InstanceHandle assembly, IUnknown *caller );

  // Start the instance.
  virtual bool            startEntity ( InstanceHandle assembly, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  ILodNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the lod.
  virtual bool            endEntity ( LodHandle lod, IUnknown *caller );

  // Start the lod.
  virtual bool            startEntity ( LodHandle lod, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IShapeNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the shape.
  virtual bool            endEntity ( ShapeHandle shape, IUnknown *caller );

  // Start the shape.
  virtual bool            startEntity ( ShapeHandle shape, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  ISetNotify interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // End the set.
  virtual bool            endEntity ( SetHandle set, IUnknown *caller );

  // Start the set.
  virtual bool            startEntity ( SetHandle set, IUnknown *caller );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IFileExtension interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // Get the file extension.
  virtual std::string     getFileExtension() const;

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IDataWrite interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // Write the data.
  virtual bool            writeData ( const std::string &filename );

  /////////////////////////////////////////////////////////////////////////////
  //
  //  IOutputAttribute interface.
  //
  /////////////////////////////////////////////////////////////////////////////

  // Set the output attribute.
  virtual bool            setOutputAttribute ( const FormatAttribute &attribute );

private:

  bool                    _addAttributes ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );
  bool                    _addDataSets   ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );
  bool                    _addVertices   ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );
  bool                    _addNormals    ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );
  bool                    _addColors     ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );
  bool                    _addTexCoords  ( IUnknown *caller, ShapeHandle shape, osg::GeometryPtr geometry );

  void                    _clearGroupStack();

  osg::NodePtr            _findGroup ( InstanceHandle instance, IInstanceQueryFloat *query ) const;

  osg::NodePtr            _getRoot() const;

  bool                    _hasColorAttribute ( IUnknown *caller, ShapeHandle shape ) const;

  void                    _pushGroup ( osg::NodePtr group );
  void                    _popGroup();

  void                    _setLodParameters ( osg::NodePtr lod ) const;
  
  typedef CadKit::ErrorPolicy::Throw < std::out_of_range > StackErrorPolicy;
  typedef SlStack < osg::NodePtr, StackErrorPolicy > GroupStack;
  std::auto_ptr<GroupStack> _groupStack;

  SL_DECLARE_REFERENCE_POINTER ( DbOpenSgDatabase );
  SL_DECLARE_DYNAMIC_CLASS ( DbOpenSgDatabase, 1778405428 );
};

} // namespace CadKit


#endif // _CADKIT_DATABASE_OPEN_SG_LIBRARY_DATABASE_H_
