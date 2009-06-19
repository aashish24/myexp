
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  A material class.
//
///////////////////////////////////////////////////////////////////////////////

#include "GSG/Core/Precompiled.h"
#include "GSG/Core/Material.h"

using namespace GSG;

GSG_IMPLEMENT_REFERENCED ( Material );


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Material::Material() : Attribute(),
  _ambient(),
  _diffuse(),
  _specular(),
  _emissive(),
  _shininess ( 0 ),
  _side ( FRONT )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Copy constructor.
//
///////////////////////////////////////////////////////////////////////////////

Material::Material ( const Material &m ) : Attribute ( m ),
  _ambient   ( m._ambient ),
  _diffuse   ( m._diffuse ),
  _specular  ( m._specular ),
  _emissive  ( m._emissive ),
  _shininess ( m._shininess ),
  _side      ( m._side )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor.
//
///////////////////////////////////////////////////////////////////////////////

Material::Material (
  const Color &a, 
  const Color &d, 
  const Color &sp, 
  const Color &e, 
  value_type sh,
  Side side ) :
  Attribute(),
  _ambient   ( a ),
  _diffuse   ( d ),
  _specular  ( sp ),
  _emissive  ( e ),
  _shininess ( sh ),
  _side      ( side )
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Destructor.
//
///////////////////////////////////////////////////////////////////////////////

Material::~Material()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the material.
//
///////////////////////////////////////////////////////////////////////////////

void Material::setFrom ( const Material &m )
{
  Lock lock ( this );
  _ambient   = m._ambient;
  _diffuse   = m._diffuse;
  _specular  = m._specular;
  _emissive  = m._emissive;
  _shininess = m._shininess;
  _side      = m._side;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the material.
//
///////////////////////////////////////////////////////////////////////////////

void Material::set ( const Color &a, const Color &d, const Color &sp, const Color &e, value_type sh, Side side )
{
  Lock lock ( this );
  _ambient   = a;
  _diffuse   = d;
  _specular  = sp;
  _emissive  = e;
  _shininess = sh;
  _side      = side;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Are they equal?
//
///////////////////////////////////////////////////////////////////////////////

bool Material::equal ( const Material &m ) const
{
  return
    _ambient   == m._ambient &&
    _diffuse   == m._diffuse &&
    _specular  == m._specular &&
    _emissive  == m._emissive &&
    _shininess == m._shininess &&
    _side      == m._side;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Assignment.
//
///////////////////////////////////////////////////////////////////////////////

Material &Material::operator = ( const Material &rhs )
{
  this->setFrom ( rhs );
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the color.
//
///////////////////////////////////////////////////////////////////////////////

void Material::ambient ( const Color &c )
{
  Lock lock ( this );
  _ambient = c;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the color.
//
///////////////////////////////////////////////////////////////////////////////

void Material::diffuse ( const Color &c )
{
  Lock lock ( this );
  _diffuse = c;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the color.
//
///////////////////////////////////////////////////////////////////////////////

void Material::specular ( const Color &c )
{
  Lock lock ( this );
  _specular = c;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the color.
//
///////////////////////////////////////////////////////////////////////////////

void Material::emissive ( const Color &c )
{
  Lock lock ( this );
  _emissive = c;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the value.
//
///////////////////////////////////////////////////////////////////////////////

void Material::shininess ( Material::value_type s )
{
  Lock lock ( this );
  _shininess = s;
}


///////////////////////////////////////////////////////////////////////////////
//
//  Set the value.
//
///////////////////////////////////////////////////////////////////////////////

void Material::side ( Side s )
{
  Lock lock ( this );
  _side = s;
}
