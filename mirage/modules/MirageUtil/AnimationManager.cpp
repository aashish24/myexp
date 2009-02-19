
#include "AnimationManager.h"
#include "Animation.h"

#include "MirageCore/SceneManager.h"

using namespace util;
using namespace MirageCore;


AnimationManager::AnimationManager( SceneManager *sceneManager )
{
	mSceneManager = sceneManager;
}

AnimationManager::~AnimationManager()
{
	std::map< std::string, Animation* >::iterator itr;
	for( itr = mMapAnimation.begin(); itr != mMapAnimation.end(); ++itr )
	{
		// Why not ??
		//delete itr->second;
	}
	mMapAnimation.clear();
}

void AnimationManager::setAnimation( std::string id, Animation* anime )
{
	mMapAnimation[id] = anime;
	anime->setSceneManager( mSceneManager );
}

void AnimationManager::update( bool update )
{
	std::map< std::string, Animation* >::iterator itr;
	for( itr = mMapAnimation.begin(); itr != mMapAnimation.end(); ++itr )
	{
		if( itr->second->getAutoUpdate() )
		{
			itr->second->update();
		}		
		else if( update )
		{
			itr->second->update();
		}
	}
}

void AnimationManager::reset()
{
	std::map< std::string, Animation* >::iterator itr;
	for( itr = mMapAnimation.begin(); itr != mMapAnimation.end(); ++itr )
	{
		itr->second->reset();		
	}
}