
#ifndef _OPENSGVECTORINPUT_H_
#define _OPENSGVECTORINPUT_H_

// OpenSG includes
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGVector.h>

// std library includes
#include <iosfwd>

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
std::istream &
    operator >>(std::istream       &inStream,
                Color3<ValueTypeT> &color    );
                
template <class ValueTypeT,
          class StorageInterfaceT>
std::istream &
    operator >>(std::istream                     &inStream,
                PointInterface<ValueTypeT,
                               StorageInterfaceT> &obj      );
                               
template <class ValueTypeT,
          class StorageInterfaceT>
std::istream &
    operator >>(std::istream                       &inStream,
                VectorInterface<ValueTypeT,
                                StorageInterfaceT> &obj      );

OSG_END_NAMESPACE

#include "OpenSGVectorInput.inl"

#endif // _OPENSGVECTORINPUT_H_
