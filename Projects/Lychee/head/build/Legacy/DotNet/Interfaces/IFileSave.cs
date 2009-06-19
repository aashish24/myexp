
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Arizona State University
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//  Created by: Adam Kubach
//
///////////////////////////////////////////////////////////////////////////////

namespace CadKit.Interfaces
{
  public interface IFileSave : IReferenced
  {
    void save(object caller);
    void saveAs(string filename, object caller);
  }
}
