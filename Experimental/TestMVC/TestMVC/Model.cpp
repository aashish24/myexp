
#include "Model.h"
#include "View.h"

Model::Model() : 
  mData( 0 )
{
}

Model::~Model()
{
  mViews.clear();
}

void Model::addView( const View& view )
{
  mViews.push_back( &view );
}

int Model::getData()
{
  return mData;
}

void Model::update()
{
  std::vector< const View* >::const_iterator itr = mViews.begin();
  for( ; itr != mViews.end(); ++itr )
  {
    (*itr)->update();
  }
}