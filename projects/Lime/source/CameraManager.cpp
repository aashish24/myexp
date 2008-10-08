// std library includes
#include <ostream>
#include <limits>


// boost includes
#include <boost/spirit/iterator/file_iterator.hpp>

// VRJuggler includes
#include <vpr/Util/Debug.h>

//OpenSG includes
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGTransform.h>
//#include <OpenSG/OSGNodePtr.h>
//#include <OpenSG/OSGSimpleAttachments.h>


#include <CameraManager.h>
#include <CameraParser.h>
#include <AnimationTools.h>
#include <CameraNavigator.h>
#include <NavigatorAdapterBase.h>


#include <PathHandler.h>



namespace bs = boost::spirit;

	CameraManager::CameraManager(void)    
    : _camMap       (),
      _mCamNavigator(NULL),
      _camLoaded    (false)
{
    // nothing to do
}

	CameraManager::~CameraManager()
{
	if (_mCamNavigator)
		delete _mCamNavigator;
}
	
	
void
    CameraManager::readFile(std::string const &fileName)
{
    typedef char                           char_t;
    typedef bs::file_iterator<char_t>      FileItType;
    
    typedef CameraBuilder<FileItType>  CamBuilder;
    typedef CameraGrammar<CamBuilder>  CamGrammar;
    
    CamBuilder camBuilder;
    CamGrammar camGrammar(&camBuilder);
    
    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "CameraManager::readFile: Could not open camera file "
            << "'" << fileName << "'."
            << std::endl << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
    
    bs::parse_info<FileItType> info = 
        parse(fileIt, fileEnd, camGrammar >> bs::eps_p, bs::space_p);
        
    if(!info.hit)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "CameraManager::readFile: Parsing of animation file "
            << "'" << fileName << "' failed.\n"
            << vprDEBUG_FLUSH;
            
            return;
    }
    
    CamBuilder::CameraStoreConstIt animIt  = camBuilder.getCamStore().begin();
    CamBuilder::CameraStoreConstIt animEnd = camBuilder.getCamStore().end  ();
    
    for(; animIt != animEnd; ++animIt)
    {
        _camMap[animIt->_name] = *animIt;
    }
    
}

void
    CameraManager::dump(std::ostream &os) const
{
    CameraMap::const_iterator amIt  = _camMap.begin();
    CameraMap::const_iterator amEnd = _camMap.end  ();
    
    for(; amIt != amEnd; ++amIt)
    {
        amIt->second.dump(os);
    }
}


void CameraManager::rewind()
{
    if (_camLoaded)
    {
        _mCamNavigator->rewind();
    }
}

 
void CameraManager::fastForward()
{
	
}



void CameraManager::update(vpr::Interval const currTime)
{		
		_mCamNavigator->updateTime(currTime);	
}


void CameraManager::init(NavigatorAdapterBase *NavAdapter){
	_mNavAdapter    = NavAdapter;
	_mFreeNavigator = NavAdapter->getNavigator();
	_mCamNavigator  = new CameraNavigator(_mFreeNavigator->getApp());	
	_mCamNavigator->initialize();
}

void CameraManager::load(unsigned int cameraIndex){
	if (cameraIndex < _camMap.size()){
		_mNavAdapter->setNavigationMode(NavigatorAdapterBase::NAV_FULL);
		_mNavAdapter->setNavigator(_mCamNavigator);
		CameraMapIt camIt = _camMap.begin();
		for (unsigned int i=0; i<cameraIndex; i++)
			camIt++;
		
		_mCamNavigator->setEnabled(true);
		_mCamNavigator->load(camIt->second);
		_camLoaded = true;
		_camName  = camIt->first;
	}
	else
		vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
					<< "CameraManager::load: Out of range camera index:  " << cameraIndex 		            
				    << vprDEBUG_FLUSH;  
	
}


void CameraManager::play_pause (vpr::Interval currTime, bool loop){
	_mCamNavigator->play_pause(currTime, loop);
}

void CameraManager::eject(){
	if (_camLoaded){
		_mNavAdapter->setNavigationMode(NavigatorAdapterBase::NAV_INCREMENTAL);
		_mNavAdapter->setNavigator(_mFreeNavigator);		
		_mCamNavigator->setEnabled(false);		
		_camLoaded = false;
	}
}

