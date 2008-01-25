
#ifdef HAVE_OSSIM

#include "Oge/OgePrithvi/PrithviCore/Planet.h"

namespace Oge
{
  namespace OgePrithvi
  {
    namespace PrithviCore
    {
      ///////////////////////////////////////////////////////////////////////////
      //
      // Constructor.
      //
      ///////////////////////////////////////////////////////////////////////////
      
      Planet::Planet() : OgeBase::OgeCore::Referenced(), 
        mEnableElevation    ( true ),
        mEnableHud          ( false ),
        mEnableEphemeris    ( false ), 
        mEnableMipMap       ( true ), 
        mElevationScale     ( 1.0 ), 
        mElevationEstimate  ( 16.0 ), 
        mLevelDetail        ( 16.0 ), 
        mSplitMetricRatio   ( 0 ),
        mLandType( ossimPlanetLandType_NORMALIZED_ELLIPSOID ),
        mElevationCache(""),
        mBindsFile("") 
      {
        // Lets initialize the planet. 
        init();
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Destructor.
      //
      ///////////////////////////////////////////////////////////////////////////
      
      Planet::~Planet()
      {
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Initializations.
      //
      ///////////////////////////////////////////////////////////////////////////
      
      void Planet::init()
      {
        try
        {
          ossimInit::instance()->initialize();

          mDatabasePager = new ossimPlanetDatabasePager();
          osgDB::Registry::instance()->setDatabasePager( mDatabasePager.get() );

          mOssimPlanet = new ossimPlanet();
          mOssimPlanet->setupDefaults();

          mTextureLayerGroup =  new ossimPlanetTextureLayerGroup();

          //mOssimPlanet->land()->setLandType( mLandType );
          mOssimPlanet->land()->setElevationEnabledFlag( mEnableElevation );
          mOssimPlanet->land()->setHeightExag( mElevationScale );
          mOssimPlanet->land()->setElevationPatchSize( mElevationEstimate );
          mOssimPlanet->land()->setMaxLevelDetail( mLevelDetail );
          mOssimPlanet->land()->setElevationCacheDir( mElevationCache );
          
          if ( mSplitMetricRatio != 0 )
          {
	          mOssimPlanet->land()->setSplitMetricRatio( mSplitMetricRatio );
          }

          mOssimPlanet->land()->setMipMappingFlag( mEnableMipMap );        
          //mOssimPlanet->setEnableHudFlag( mEnableHud );     

          // Add texture layers. 
          // As the API has changed we cannot add the texture layer group. 
          // So this is the work around for this for time being. 
          addLayersToPlanet();

          mDatabasePager->setExpiryDelay( 0 );
        }
        catch( ... )
        {
          std::cerr << "Error: " << std::endl;
        }
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Return the root of the scene. 
      //
      ///////////////////////////////////////////////////////////////////////////

      osg::Group* Planet::root()
      {
        return mOssimPlanet.release();
      }


      void Planet::initShaders()
      {
        if( mOssimPlanet.valid() )
        {
          mOssimPlanet->land()->initShaders();
        }
      }

      ///////////////////////////////////////////////////////////////////////////
      //
      // Add texture layer. 
      //
      ///////////////////////////////////////////////////////////////////////////

      int Planet::addLayer( const std::string& file )
      {
        osg::ref_ptr< ossimPlanetTextureLayer > layer( ossimPlanetTextureLayerRegistry::instance()->createLayer( file.c_str() ) );
        return this->addLayer( layer.get() );
      }

      
      ///////////////////////////////////////////////////////////////////////////
      //
      // Add texture layer.
      //
      ///////////////////////////////////////////////////////////////////////////

      int Planet::addLayer( ossimPlanetTextureLayer* layer )
      {
        int index = -1;

        if( 0x00 != layer )
        {
          // Add ref to local group. 
          mTextureLayerGroup->addTop( layer );

          // Now actually add it to the planet. 
          mOssimPlanet->land()->referenceLayer()->addTop( layer );

          index = mTextureLayerGroup->findLayerIndex( layer );
          return index;
        }

        return index;
      }

      
      ///////////////////////////////////////////////////////////////////////////
      //
      // Remove a texture layer with given id.
      //
      ///////////////////////////////////////////////////////////////////////////
     
      bool Planet::removeLayer( const unsigned int &id ) 
      {
        if( mTextureLayerGroup->removeLayer( id ).valid() )
          return true;
        else
          return false;
      }
     

      ///////////////////////////////////////////////////////////////////////////
      //
      // Remove a texture layer.
      //
      ///////////////////////////////////////////////////////////////////////////

      bool Planet::removeLayer( ossimPlanetTextureLayer* layer )
      {
        if( 0x00 != layer )
        {
          return mTextureLayerGroup->removeLayer( layer );
        }

        return false;
      }
   

      ///////////////////////////////////////////////////////////////////////////
      //
      // Check if layer already exists.  
      //
      ///////////////////////////////////////////////////////////////////////////
      
      bool Planet::hasLayer( const  unsigned int& id ) const 
      {
        return mTextureLayerGroup->containsLayer( this->getLayer( id ) );
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Check if the layer already exists.
      //
      ///////////////////////////////////////////////////////////////////////////

      bool Planet::hasLayer( ossimPlanetTextureLayer* layer ) const
      {
        return mTextureLayerGroup->containsLayer( layer );
      }

   
      ///////////////////////////////////////////////////////////////////////////
      //
      // Get a texture layer with given id. 
      //
      ///////////////////////////////////////////////////////////////////////////

      ossimPlanetTextureLayer* Planet::getLayer( const unsigned int& id ) const
      {
        return ( mTextureLayerGroup->layer( id ) ).get();
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Read KWL file.
      //
      ///////////////////////////////////////////////////////////////////////////

      void Planet::readKwl( const std::string&  kwlFile )
      {
        ossimKeywordlist kwl( kwlFile.c_str() );
        osg::ref_ptr< ossimPlanetTextureLayer > layer = ossimPlanetTextureLayerRegistry::instance()->createLayer( kwl.toString() );
        if( layer.valid() )
        {
          this->addLayer( layer.get() );
        }
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Set elevation exaggeration.
      //
      ///////////////////////////////////////////////////////////////////////////

      void Planet::setElevationScale( const float& scale )
      {
        mOssimPlanet->land()->setHeightExag( scale );
      }


      ///////////////////////////////////////////////////////////////////////////
      //
      // Get elevation exaggeration.
      //
      ///////////////////////////////////////////////////////////////////////////

      float Planet::getElevationScale() 
      {
        return mOssimPlanet->land()->getHeightExag();
      }


      void Planet::addLayersToPlanet()
      {
        size_t count = ( size_t )( mTextureLayerGroup->numberOfLayers() );
        for( size_t i = 0; i < count; ++i )
        {
          mOssimPlanet->land()->referenceLayer()->addTop( mTextureLayerGroup->layer( i ) );
        }
      }
    }
  }
}

#endif // HAVE_OSSIM


