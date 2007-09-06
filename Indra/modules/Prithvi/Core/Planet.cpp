
#include "Prithvi/Core/Planet.h"

namespace Prithvi
{
  namespace Core
  {
    Planet::Planet() : Neiv::Base::Referenced(), 
      mEnableElevation    ( false ),
      mEnableHud          ( false ),
      mEnableEphemeris    ( false ), 
      mEnableMipMap       ( true ), 
      mElevationScale     ( 1.0 ), 
      mElevationEstimate  ( 16.0 ), 
      mLevelDetail        ( 16.0 ), 
      mSplitMetricRatio   ( 0 ),
#ifdef HAVE_OSSIM
        mLandType( ossimPlanetLandType_NORMALIZED_ELLIPSOID ),
        mElevationCache(""),
        mBindsFile("") 
#endif
    {
      // Lets initialize the planet. 
      init();
    }

    Planet::~Planet()
    {
    }

    void Planet::init()
    {
#ifdef HAVE_OSSIM
      try
      {
        mPlanet = new ossimPlanet();
        mTextureLayerGroup =  new ossimPlanetTextureLayerGroup();

        mPlanet->getLand()->setLandType( mLandType );
        mPlanet->getLand()->setElevationEnabledFlag( mEnableElevation );
        mPlanet->getLand()->setHeightExag( mElevationScale );
        mPlanet->getLand()->setElevationPatchSize( mElevationEstimate );
        mPlanet->getLand()->setMaxLevelDetail( mLevelDetail );
        mPlanet->getLand()->setElevationCacheDir( mElevationCache );
        
        if ( mSplitMetricRatio != 0 )
        {
	        mPlanet->getLand()->setSplitMetricRatio( mSplitMetricRatio );
        }

        mPlanet->getLand()->setMipMappingFlag( mEnableMipMap );        
        mPlanet->setEnableHudFlag( mEnableHud );        
      }
      catch( ... )
      {
        std::cerr << "Error: " << std::endl;
      }
#endif // HAVE_OSSIM
    }

    osg::Group* Planet::root()
    {
#ifdef HAVE_OSSIM
      return mPlanet.get();
#else
      throw "Null pointer exception";
#endif // HAVE_OSSIM
    }


    int Planet::addLayer( const std::string& file )
    {
#ifdef HAVE_OSSIM
      osg::ref_ptr< ossimPlanetTextureLayer > layer( ossimPlanetTextureLayerRegistry::instance()->createLayer( file.c_str() ) );
      return this->addLayer( layer.get() );
#else
      return -1;
#endif // HAVE_OSSIM
    }

    
#ifdef HAVE_OSSIM
    void Planet::readKwl( const std::string& file )
    {
      ossimKeywordlist kwl( file.c_str() );
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

    ossimPlanetTextureLayer* Planet::getLayer( const unsigned int& id ) const
    {
      return ( mTextureLayerGroup->getLayer( id ) ).get();
    }

#endif // HAVE_OSSIM

  }
}

