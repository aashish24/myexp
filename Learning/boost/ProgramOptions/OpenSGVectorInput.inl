
#include "OpenSGVectorInput.h"

// std library includes
#include <istream>

OSG_BEGIN_NAMESPACE

template <class ValueTypeT>
inline std::istream &
    operator >>(std::istream       &inStream,
                Color3<ValueTypeT> &color    )
{
    typename Color3<ValueTypeT>::ValueType valR;
    typename Color3<ValueTypeT>::ValueType valG;
    typename Color3<ValueTypeT>::ValueType valB;
    
    inStream >> valR;
    while(inStream.peek() == ' ' || inStream.peek() == ',')
        inStream.ignore();
    inStream >> valG;
    while(inStream.peek() == ' ' || inStream.peek() == ',')
        inStream.ignore();
    inStream >> valB;
    
    color.setValuesRGB(valR, valG, valB);
    
    return inStream;
}
                
template <class ValueTypeT,
          class StorageInterfaceT>
inline std::istream &
    operator >>(std::istream                     &inStream,
                PointInterface<ValueTypeT,
                               StorageInterfaceT> &obj      )
{
    for(UInt32 i = 0; i < StorageInterfaceT::_iSize; ++i)
    {
        inStream >> obj[i];
        
        if(i != StorageInterfaceT::_iSize - 1)
        {
            while(inStream.peek() == ' ' || inStream.peek() == ',')
                inStream.ignore();
        }
    }

    return inStream;
}
                               
template <class ValueTypeT,
          class StorageInterfaceT>
inline std::istream &
    operator >>(std::istream                       &inStream,
                VectorInterface<ValueTypeT,
                                StorageInterfaceT> &obj      )
{
    for(UInt32 i = 0; i < StorageInterfaceT::_iSize; ++i)
    {
        inStream >> obj[i];
         
        if(i != StorageInterfaceT::_iSize - 1)
        {
            while(inStream.peek() == ' ' || inStream.peek() == ',')
                inStream.ignore();
        }
    }
    
    return inStream;
}

OSG_END_NAMESPACE
