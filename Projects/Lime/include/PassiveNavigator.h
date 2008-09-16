
#ifndef _PASSIVENAVIGATOR_H_
#define _PASSIVENAVIGATOR_H_

#include <NavigatorBase.h>

// gmtl includes
#include <gmtl/EulerAngle.h>
#include <gmtl/Point.h>
#include <gmtl/Vec.h>

class PassiveNavigator : public NavigatorBase
{
  public:
    typedef NavigatorBase    Inherited;
    typedef PassiveNavigator Self;
    
    /*=======================================================================*/
    /* Construction/Destruction                                              */
    
             PassiveNavigator(vrj::App *pApp);
    virtual ~PassiveNavigator(void);
    
    /*=======================================================================*/
    /* Initialization                                                        */
    
    virtual void initialize(void);
    
    /*=======================================================================*/
    /* Navigation                                                            */
    
    void                     setTranslation(gmtl::Point3f const &       pos  );
    gmtl::Point3f const &    getTranslation(void) const;
    void                     setRotation   (gmtl::EulerAngleXYZf const &rot  );
    gmtl::EulerAngleXYZf const &getRotation(void) const;
    void                     setScale      (gmtl::Vec3f const &         scale);
    gmtl::Vec3f const &      getScale      (void) const;
    
    virtual void navigate(gmtl::Matrix44f const &matrix,
                          gmtl::Matrix44f       &newMatrix);
    
  private:
    gmtl::Point3f        mPos;
    gmtl::EulerAngleXYZf mRot;
    gmtl::Vec3f          mScale;
};


inline void
    PassiveNavigator::setTranslation(gmtl::Point3f const &pos)
{
    mPos = pos;
}

inline gmtl::Point3f const &
    PassiveNavigator::getTranslation(void) const
{
    return mPos;
}

inline void
    PassiveNavigator::setRotation(gmtl::EulerAngleXYZf const &rot)
{
    mRot = rot;
}

inline gmtl::EulerAngleXYZf const &
    PassiveNavigator::getRotation(void) const
{
    return mRot;
}

inline void
    PassiveNavigator::setScale(gmtl::Vec3f const &scale)
{
    mScale = scale;
}

inline gmtl::Vec3f const &
    PassiveNavigator::getScale(void) const
{
    return mScale;
}

#endif // _PASSIVENAVIGATOR_H_

