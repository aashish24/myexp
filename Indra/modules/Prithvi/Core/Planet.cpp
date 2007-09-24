
#if define HAVE_OSSIM

#include "Prithvi/Core/Planet.h"

namespace Prithvi
{
  namespace Core
  {
    Planet::Planet() : Neiv::Base::Referenced(), 
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

    Planet::~Planet()
    {
    }

    void Planet::init()
    {
      try
      {
        ossimInit::instance()->initialize();

        mDatabasePager = new ossimPlanetDatabasePager();
        osgDB::Registry::instance()->setDatabasePager( mDatabasePager.get() );

        mOssimPlanet = new ossimPlanet();
        mTextureLayerGroup =  new ossimPlanetTextureLayerGroup();

        mOssimPlanet->getLand()->setLandType( mLandType );
        mOssimPlanet->getLand()->setElevationEnabledFlag( mEnableElevation );
        mOssimPlanet->getLand()->setHeightExag( mElevationScale );
        mOssimPlanet->getLand()->setElevationPatchSize( mElevationEstimate );
        mOssimPlanet->getLand()->setMaxLevelDetail( mLevelDetail );
        mOssimPlanet->getLand()->setElevationCacheDir( mElevationCache );
        
        if ( mSplitMetricRatio != 0 )
        {
	        mOssimPlanet->getLand()->setSplitMetricRatio( mSplitMetricRatio );
        }

        mOssimPlanet->getLand()->setMipMappingFlag( mEnableMipMap );        
        mOssimPlanet->setEnableHudFlag( mEnableHud );     

        // Add texture layers. 
        mOssimPlanet->getLand()->setTextureLayer( mTextureLayerGroup.get(), 0 );

        mDatabasePager->setExpiryDelay( 0 );
      }
      catch( ... )
      {
        std::cerr << "Error: " << std::endl;
      }
    }

    osg::Group* Planet::root()
    {
      return mOssimPlanet.release();
    }


    int Planet::addLayer( const std::string& file )
    {
      osg::ref_ptr< ossimPlanetTextureLayer > layer( ossimPlanetTextureLayerRegistry::instance()->createLayer( file.c_str() ) );
      return this->addLayer( layer.get() );
    }


    bool Planet::removeLayer( const unsigned int &id ) 
    {
      if( mTextureLayerGroup->removeLayer( id ).valid() )
        return true;
      else
        return false;
    }
    

    bool Planet::hasLayer( const  unsigned int& id ) const 
    {
      return mTextureLayerGroup->containsLayer( this->getLayer( id ) );
    }

    void Planet::readKwl( char* file )
    {
      ossimKeywordlist kwl( file );
      osg::ref_ptr< ossimPlanetTextureLayer > layer = ossimPlanetTextureLayerRegistry::instance()->createLayer( kwl.toString() );
      if( layer.valid() )
      {
        this->addLayer( layer.get() );
      }
    }

    int Planet::addLayer( ossimPlanetTextureLayer* layer )
    {
      int index = -1;

      if( 0x00 != layer )
      {
        mTextureLayerGroup->addTop( layer );
        index = mTextureLayerGroup->findLayerIndex( layer );
        return index;
      }

      return index;
    }

    bool Planet::removeLayer( ossimPlanetTextureLayer* layer )
    {
      if( 0x00 != layer )
      {
        return mTextureLayerGroup->removeLayer( layer );
      }
      
      return false;
    }

    ossimPlanetTextureLayer* Planet::getLayer( const unsigned int& id ) const
    {
      return ( mTextureLayerGroup->getLayer( id ) ).get();
    }

    bool Planet::hasLayer( ossimPlanetTextureLayer* layer ) const 
    {
      return mTextureLayerGroup->containsLayer( layer );
    }

    void Planet::setElevationScale( const float& scale )
    {
      mOssimPlanet->getLand()->setHeightExag( scale );
    }

    float Planet::getElevationScale() 
    {
      return mOssimPlanet->getLand()->getHeightExag();
    }
  }
}

#endif // HAVE_OSSIM


