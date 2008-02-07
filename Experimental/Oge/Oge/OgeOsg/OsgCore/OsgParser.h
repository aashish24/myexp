
#ifndef __OSG_CORE_OSG_PARSER_H__
#define __OSG_CORE_OSG_PARSER_H__

#include "cppdom/cppdom.h"

#include "Oge/Export.h"

#include "Oge/OgeBase/OgeInterfaces/IParser.h"

#include "Oge/OgeBase/OgeCore/Referenced.h"

#include "osg/Group"
#include "osg/Light"
#include "osg/LightSource"

#include <string>

namespace Oge
{
  // Forward declarations. 
  namespace OgeBase
  {
    namespace OgeInterfaces
    {
      class IModel;
    }
  }

  namespace OgeOsg
  {
    namespace OsgCore
    {
      class OGE_EXPORT OsgParser : public OgeBase::OgeInterfaces::IParser, 
                                   public OgeBase::OgeCore::Referenced
      {
        public: 

          OGE_DELCARE_SMART_PTR( OsgParser );

          IMPLEMENT_IUNKNOWN_MEMBERS( OsgParser, OgeBase::OgeCore::Referenced );

          virtual OgeBase::OgeInterfaces::IUnknown* queryInterface( const unsigned long& iid );

          float convert( const std::string& str );

          virtual void parse( const std::string& filename, OgeBase::OgeInterfaces::IModel* model );        

          virtual void parseLight( osg::ref_ptr< osg::Group > lightGroup, cppdom::NodeList& nl, cppdom::NodeListIterator& itr );

          virtual void parseLightSource( osg::ref_ptr< osg::LightSource > lightSource, cppdom::NodeList& nl, cppdom::NodeListIterator& itr );

          virtual void parseLightElement( osg::ref_ptr< osg::Light > light, cppdom::NodeList& nl, cppdom::NodeListIterator& itr );

        private:

          osg::ref_ptr< osg::Group > _rootModel;
      };
    }
  }
}

#endif // __OSG_CORE_OSG_PARSER_H__
