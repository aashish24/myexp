
#include <ShaderManager.h>

#include <PathHandler.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

#include <ostream>

    ShaderManager::ShaderManager(PathHandler const *pPathHandler)
    
    : _vertexProgMap    (),
      _vertexProgCache  (),
      _fragmentProgMap  (),
      _fragmentProgCache(),
      _pPathHandler     (pPathHandler)
{
}

ShaderProgramDesc const *
    ShaderManager::getVertexProgDesc(std::string const &name) const
{
    ProgramMap::const_iterator pIt = _vertexProgMap.find(name);
    
    if(pIt != _vertexProgMap.end())
    {
        return &(pIt->second);
    }
    else
    {
        return NULL;
    }
}

std::string const *
    ShaderManager::getVertexProg(std::string const &name) const
{
    std::string const *             pVP  = NULL;
    ProgramCacheMap::const_iterator pIt  = _vertexProgCache.find(name);
    
    if(pIt != _vertexProgCache.end())
    {
        pVP = &(pIt->second);
    }
    else
    {
        ShaderProgramDesc const *pDesc = getVertexProgDesc(name);
        std::string              vertProg;
        
        if(pDesc != NULL && constructProg(pDesc, vertProg))
        {
            _vertexProgCache[pDesc->_name] = vertProg;
            
            pIt = _vertexProgCache.find(name);
            pVP = &(pIt->second);
        }
    }
    
    return pVP;
}

ShaderProgramDesc const *
    ShaderManager::getFragmentProgDesc(std::string const &name) const
{
    ProgramMap::const_iterator pIt = _fragmentProgMap.find(name);
    
    if(pIt != _fragmentProgMap.end())
    {
        return &(pIt->second);
    }
    else
    {
        return NULL;
    }
}

std::string const *
    ShaderManager::getFragmentProg(std::string const &name) const
{
    std::string const *             pFP = NULL;
    ProgramCacheMap::const_iterator pIt = _fragmentProgCache.find(name);
    
    if(pIt != _fragmentProgCache.end())
    {
        pFP = &(pIt->second);
    }
    else
    {
        ShaderProgramDesc const *pDesc = getFragmentProgDesc(name);
        std::string              fragProg;
        
        if(pDesc != NULL && constructProg(pDesc, fragProg))
        {
            _fragmentProgCache[pDesc->_name] = fragProg;
            
            pIt = _fragmentProgCache.find(name);
            pFP = &(pIt->second);
        }
    }
       
    return pFP;
}

void
    ShaderManager::addDesc(ShaderProgramDesc const *pDesc, bool replace)
{
    if(pDesc->_type == "vp")
    {
        ProgramMap::iterator pmIt = _vertexProgMap.find(pDesc->_name);
        
        if(pmIt != _vertexProgMap.end())
        {
            if(replace)
            {
                pmIt->second = *pDesc;
            }
        }
        else
        {
            _vertexProgMap.insert(
                ProgramMap::value_type(pDesc->_name, *pDesc));
        }
    }
    
    if(pDesc->_type == "fp")
    {
        ProgramMap::iterator pmIt = _fragmentProgMap.find(pDesc->_name);
        
        if(pmIt != _fragmentProgMap.end())
        {
            if(replace)
            {
                pmIt->second = *pDesc;
            }
        }
        else
        {
            _fragmentProgMap.insert(
                ProgramMap::value_type(pDesc->_name, *pDesc));
        }
    }
}

bool
    ShaderManager::subDesc(ShaderProgramDesc const *pDesc)
{
    bool retVal = false;

    if(pDesc->_type == "vp")
    {
        ProgramMap     ::iterator pmIt   = _vertexProgMap  .find(pDesc->_name);
        ProgramCacheMap::iterator pcIt   = _vertexProgCache.find(pDesc->_name);
        
        if(pcIt != _vertexProgCache.end())
        {
            retVal = true;
            _vertexProgCache.erase(pcIt);
        }
        
        if(pmIt != _vertexProgMap.end())
        {
            retVal = true;
            _vertexProgMap.erase(pmIt);
        }
    }
    
    if(pDesc->_type == "fp")
    {
        ProgramMap     ::iterator pmIt   = _fragmentProgMap  .find(pDesc->_name);
        ProgramCacheMap::iterator pcIt   = _fragmentProgCache.find(pDesc->_name);
        
        if(pcIt != _fragmentProgCache.end())
        {
            retVal = true;
            _fragmentProgCache.erase(pcIt);
        }
        
        if(pmIt != _fragmentProgMap.end())
        {
            retVal = true;
            _fragmentProgMap.erase(pmIt);
        }
    }
    
    return retVal;
}

void
    ShaderManager::dump(std::ostream &os)
{
    ProgramMap::const_iterator pIt  = _vertexProgMap.begin();
    ProgramMap::const_iterator pEnd = _vertexProgMap.end  ();
    
    for(; pIt != pEnd; ++pIt)
    {
        os << "VertexProgram '" << pIt->first << "' ";
        pIt->second.dump(os);
        os << "\n";
    }
    
    pIt  = _fragmentProgMap.begin();
    pEnd = _fragmentProgMap.end  ();
    
    for(; pIt != pEnd; ++pIt)
    {
        os << "FragmentProgram '" << pIt->first << "' ";
        pIt->second.dump(os);
        os << "\n";
    }
}

bool
    ShaderManager::constructProg(
        ShaderProgramDesc const *pDesc, std::string &progString) const
{
    std::string fullProgPath;
    
    if(_pPathHandler->findFile(pDesc->_fileName, fullProgPath))
    {
        std::ifstream stream(fullProgPath.c_str());
        
        if(stream.good())
        {
            int const   bufferSize = 500;
            OSG::Char8 *pBuffer    = new OSG::Char8[bufferSize];
            
            do
            {
                stream.getline(pBuffer, bufferSize);
                progString.append(pBuffer);
                progString.append("\n");
            }
            while(!stream.eof());
            
            delete [] pBuffer;
            
            return true;
        }
    }
    
    vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
        << "ShaderManager::constructProg: "
        << "Could not read file [" << fullProgPath << "] for "
        << "shader [" << pDesc->_name << "].\n"
        << vprDEBUG_FLUSH;
        
    return false;
}

