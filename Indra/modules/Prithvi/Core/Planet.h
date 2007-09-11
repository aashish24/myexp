
#ifndef __PRITHVI_CORE_PLANET_H__
#define __PRITHVI_CORE_PLANET_H__

// This should be the first include. 
#include "Prithvi/PrithviConfig.h"

// Adding this fixes the ossim::min ossim::max problem.
#ifdef _WIN32
# include <windows.h>
# ifdef max
#   undef max
# endif
# ifdef min
#   undef min
# endif
#endif

#ifdef HAVE_OSSIM
# include "ossimPlanet/ossimPlanet.h"
# include "ossimPlanet/ossimPlanetDatabasePager.h"
# include "ossimPlanet/ossimPlanetLand.h"
# include "ossimPlanet/ossimPlanetLatLonHud.h"
# include "ossimPlanet/ossimPlanetManipulator.h"
# include "ossimPlanet/ossimPlanetOssimImageLayer.h"
# include "ossimPlanet/ossimPlanetTextureLayerGroup.h"
# include "ossimPlanet/ossimPlanetAction.h"
# include "ossimPlanet/ossimPlanetTextureLayerRegistry.h"
# include "ossim/base/ossimArgumentParser.h"
# include "ossim/init/ossimInit.h"
# ifndef OSGPLANET_WITHOUT_WMS
#   include "wms/wms.h"
# endif /* #ifndef OSGPLANET_WITHOUT_WMS */
# include "ossimPlanet/io/sg_socket.h"
# include "ossimPlanet/io/netChannel.h"
# include "ossimPlanet/io/netMonitor.h"
# include "ossimPlanet/ossimPlanetServerThread.h"
# include "ossimPlanet/ossimPlanetServerMessageHandler.h"
# include "ossimPlanet/ossimPlanetActionRouter.h"
#endif

#include "osg/Group"

#include "Prithvi/Export.h"

#include "Neiv/Base/Referenced.h"
#include "Neiv/Pointer/Pointer.h"
#include "Neiv/Pointer/SmartPointer.h"

namespace Prithvi
{
  namespace Core
  {
    class PRITHVI_EXPORT Planet : public Neiv::Base::Referenced
    {
      public: 
        
        NEIV_DELCARE_SMART_PTR( Planet );

        Planet();

        virtual osg::Group*                           root();

        virtual int                                   addLayer( const std::string& file );

        virtual bool                                  removeLayer( const unsigned int& id );

        virtual bool                                  hasLayer( const unsigned int& id ) const;

#ifdef HAVE_OSSIM
        virtual void                                  readKwl( const std::string& kwl );

        virtual int                                   addLayer( ossimPlanetTextureLayer* layer );

        virtual bool                                  removeLayer( ossimPlanetTextureLayer* layer );

        virtual bool                                  hasLayer( ossimPlanetTextureLayer* layer ) const;

        virtual ossimPlanetTextureLayer*              getLayer( const unsigned int& id ) const; 
#endif
       
      protected:
       
        virtual void init();

        virtual ~Planet(); 

      private:  
        
        bool                                          mEnableElevation;
        bool                                          mEnableHud;
        bool                                          mEnableEphemeris;
        bool                                          mEnableMipMap;

        float                                         mElevationScale;
        int                                           mElevationEstimate;
        int                                           mLevelDetail;
        float                                         mSplitMetricRatio;

#ifdef HAVE_OSSIM
        ossimPlanetLandType                           mLandType;
        ossimFilename                                 mElevationCache;
        ossimFilename                                 mBindsFile;

        osg::ref_ptr< ossimPlanet >                   mPlanet;
        osg::ref_ptr < ossimPlanetTextureLayerGroup > mTextureLayerGroup;
#endif
     
    };
  }
}

#endif // __PRITHVI_CORE_PLANET_H__
