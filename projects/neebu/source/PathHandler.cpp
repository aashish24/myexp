
#include <PathHandler.h>

// boost includes
#include <boost/filesystem/operations.hpp>
   
// VRJuggler includes
#include <vpr/Util/Debug.h>

void
    PathHandler::addPath(bfs::path const &path)
{
    bfs::path completePath = bfs::complete(path);

    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "PathHandler::addPath: path [" << path.string()
        << "] [" << completePath.string()
        << "].\n"
        << vprDEBUG_FLUSH;
    
    _searchPaths.push_back(completePath);
}

bool
    PathHandler::subPath(bfs::path const &path)
{
    bfs::path completePath = bfs::complete(path);

    PathStore::iterator spIt = std::find(
        _searchPaths.begin(), _searchPaths.end(), completePath);
        
    if(spIt != _searchPaths.end())
    {
        _searchPaths.erase(spIt);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool 
    PathHandler::findFile(
        std::string const &name, std::string &pathFoundString) const
{
    bfs::path searchName(name);
    
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << "PathHandler::findFile: name [" << name << "]\n"
        << vprDEBUG_FLUSH;
    
    PathStore::const_iterator spIt  = _searchPaths.begin();
    PathStore::const_iterator spEnd = _searchPaths.end  ();
    
    for(; spIt != spEnd; ++spIt)
    {
        if(bfs::exists(*spIt / searchName))
        {
            pathFoundString = (*spIt / searchName).string();
            
            vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                << " found [" << pathFoundString << "]\n"
                << vprDEBUG_FLUSH;
            
            return true;
        }
    }
    
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << " NO matching file found.\n"
        << vprDEBUG_FLUSH;
    
    return false;
}
    
bool
    PathHandler::findFile(
        std::string const &name, bfs::path &pathFound) const
{
    bfs::path searchName(name);
    
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << "PathHandler::findFile: name [" << name << "]\n"
        << vprDEBUG_FLUSH;
    
    PathStore::const_iterator spIt  = _searchPaths.begin();
    PathStore::const_iterator spEnd = _searchPaths.end  ();
    
    for(; spIt != spEnd; ++spIt)
    {
        if(bfs::exists(*spIt / searchName))
        {
            pathFound = *spIt / searchName;
            
            vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                << " found [" << pathFound.string() << "]\n"
                << vprDEBUG_FLUSH;
            
            return true;
        }
    }
    
    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
        << " NO matching file found.\n"
        << vprDEBUG_FLUSH;
    
    return false;
}
