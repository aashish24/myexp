
#include "OgeOsg/OsgCore/OsgParser.h"
#include "OgeOsg/OsgCore/OsgModel.h"

#include "OgeBase/OgeInterfaces/IUnknown.h"

namespace Oge
{
  namespace OgeOsg
  {
    namespace OsgCore
    {
      OgeBase::OgeInterfaces::IUnknown* OsgParser::queryInterface( const unsigned long& iid )
      {
        return 0x00;
      } 


      float OsgParser::convert( const std::string& data )
      {
        std::istringstream iStrStrm;

        iStrStrm.str(  data );

        float value;

        iStrStrm >> value;

        return value;
      }
      

      void OsgParser::parse( const std::string& filename, OgeBase::OgeInterfaces::IModel* model )
      {
        OgeBase::OgeInterfaces::IUnknown::RefPtr unknown= model->queryInterface( OgeBase::OgeInterfaces::IOsgScene::IID );
        if( !unknown.valid() )
        {
          // Print message here. 
          return;
        }

        OgeBase::OgeInterfaces::IOsgScene::RefPtr scene = static_cast< OgeBase::OgeInterfaces::IOsgScene* >( unknown.get() );
        _rootModel = scene->rootModel();


        cppdom::ContextPtr ctx( new cppdom::Context() );
        cppdom::Document doc( ctx );

        try
        {
          doc.loadFile( filename );
        }
        catch( cppdom::Error e )
        {
          std::cout << e.what() << std::endl;
        } 

        cppdom::NodePtr np = doc.getChild( "scene" );
        if( np.get() )
        {
          cppdom::NodeList nl = np->getChildren();
          cppdom::NodeListIterator itr = nl.begin();

          while( itr != nl.end() )
          {
            std::string name = ( *itr )->getName();      
            try
            {
              if( name == "light_group" )
              {               
                osg::ref_ptr< osg::Group > gr( new osg::Group() );
                _rootModel->addChild( gr.get() );
                parseLight( gr.get(), nl, itr ); 
              }        
            }
            catch( cppdom::Error e )
            {
            }

            ++itr;
          }
        }
      }

    
      void OsgParser::parseLight( osg::ref_ptr< osg::Group > lightGroup, cppdom::NodeList& nl, cppdom::NodeListIterator& itr )
      { 
        cppdom::NodeList lnl = ( *itr )->getChildren();
        cppdom::NodeListIterator litr = lnl.begin();

        // Lets loop thru the light group first. 
        while( litr != lnl.end() )
        {
          std::string name = ( *litr )->getName();
          
          if( name == "id" ) 
          {
            lightGroup->setName( ( *litr )->getCdata() );            
          }
          else if( name == "parent" )
          {
            // Find the parent and attach this node to the parent. 
          }
          else if( name == "light_source" )
          {
            osg::ref_ptr< osg::LightSource > lightSource( new osg::LightSource() );
            lightGroup->addChild( lightSource.get() );
            parseLightSource( lightSource.get(), lnl, litr );
          }
          else
          {
          }

          ++litr;
        }
      }


      void OsgParser::parseLightSource( osg::ref_ptr< osg::LightSource > lightSource, cppdom::NodeList& nl, cppdom::NodeListIterator& itr )
      {        
        cppdom::NodeList cnl = ( *itr )->getChildren();
        cppdom::NodeListIterator citr = cnl.begin();

        while( citr != cnl.end() )
        {
          std::string name = ( *citr )->getName();
          
          if( name == "id" )
          {
            lightSource->setName( ( *citr )->getCdata() );
          }
          else if( name == "parent" )
          {
            // This would be used to the set the stateset.  
          }
          else if( name == "light" )
          {
            osg::ref_ptr< osg::Light > light( new osg::Light() );
            lightSource->setLight( light.get() );

            parseLightElement( light.get(), cnl, citr );
          }
          else
          {
          }

          ++citr;
        }
      }


      void OsgParser::parseLightElement( osg::ref_ptr< osg::Light > light, cppdom::NodeList& nl, cppdom::NodeListIterator& itr )
      {
        cppdom::NodeList cnl = ( *itr )->getChildren();
        cppdom::NodeListIterator citr = cnl.begin();

        while( citr != cnl.end() )
        {
          std::string name = ( *citr )->getName();

          if( name == "id" )
          {
            light->setName( ( *citr )->getCdata() );
          }
          else if( name == "parent" )
          {
            //
          }
          else if( name == "number" )
          {
            light->setLightNum( convert( ( *citr )->getCdata() ) );
          }
          else if( name == "ambient" )
          {
            cppdom::NodeList anl = ( *citr )->getChildren();
            cppdom::NodeListIterator aitr = anl.begin();
            osg::Vec4f ambient;
            unsigned int i = 0;
            while( aitr != anl.end() )
            {
              ambient[ i ] = convert( ( *aitr )->getCdata() );
              ++aitr;
              ++i;
            }
            light->setAmbient( ambient );
          }
          else if( name == "diffuse" )
          {
            cppdom::NodeList dnl = ( *citr )->getChildren();
            cppdom::NodeListIterator ditr = dnl.begin();
            osg::Vec4f diffuse;
            unsigned int i = 0;
            while( ditr != dnl.end() )
            {
              diffuse[ i ] = convert( ( *ditr )->getCdata() );
              ++ditr;
              ++i;
            }

            light->setDiffuse( diffuse );
          }
          else if( name == "specular" )
          {
            cppdom::NodeList snl = ( *citr )->getChildren();
            cppdom::NodeListIterator sitr = snl.begin();
            osg::Vec4f specualr;
            unsigned int i = 0;
            while( sitr != snl.end() )
            {
              specualr[ i ] = convert( ( *sitr )->getCdata() );
              ++sitr;
              ++i;
            }

            light->setSpecular( specualr );
          }
          else
          {
          }

          ++citr;
        }
      }
    }
  }
}