
#include "OsgTools/Core/Export.h"

#include "osg/MatrixTransform"
#include "osg/Texture2D"

namespace OsgTools
{
  namespace Geom
  {
    class OSGTOOLS_EXPORT OsgQuad  : public osg::MatrixTransform
    {
      public:

        typedef osg::ref_ptr< osg::Texture2D >    Texture;
        typedef std::vector< Texture >            Textures;

        enum VAlign{ CENTER = 0, TOP, BOTTOM };

        enum HAlign{ MIDDLE = 0, LEFT, RIGHT };

        OsgQuad();

        OsgQuad( const long double& width, const long double& height, const osg::Vec3f& pos );

        void                                      buildQuad( const long double& width, const long double& height, const osg::Vec3& pos = osg::Vec3( 0.0, 0.0, 0.0  ) );

        void                                      addTexture( osg::Texture2D* texture );

        void                                      setTexture( osg::Texture2D* texture ); 

        void                                      useTexture( const unsigned int& index );        

      protected: 

        virtual ~OsgQuad();

        bool                                      mFixedSize;
        bool                                      mFixedAspect;
        
        float                                     mMargin;
        
        VAlign                                    mVAlign;
        HAlign                                    mHAlign;

        osg::Vec4                                 mColor;

        Textures                                  mTextures;        
     };  
  }
}

