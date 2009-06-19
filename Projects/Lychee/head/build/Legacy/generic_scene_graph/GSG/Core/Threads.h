
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Threading model.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _GENERIC_SCENE_GRAPH_CORE_THREADING_MODEL_H_
#define _GENERIC_SCENE_GRAPH_CORE_THREADING_MODEL_H_


namespace GSG {
namespace Detail {


///////////////////////////////////////////////////////////////////////////////
//
//  Single-threaded class.
//
///////////////////////////////////////////////////////////////////////////////

struct SingleThreaded
{
  template < class T > SingleThreaded ( const T *t )
  {
  }
};


}; // namespace Detail
}; // namespace GSG


#endif // _GENERIC_SCENE_GRAPH_CORE_THREADING_MODEL_H_
