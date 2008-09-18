
#include <MaterialBinder.h>

#include <Descriptors.h>
#include <MaterialBindingParser.h>
#include <MaterialManager.h>
#include <NamedObjectCache.h>
#include <PathHandler.h>

// OpenSG includes
#include <OpenSG/OSGGeometry.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// boost includes
#include <boost/token_iterator.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

// std library includes
#include <ostream>

namespace bs = boost::spirit;


    MaterialBinder::MaterialBinder(void)
    
    : _pMatMgr     (NULL),
      _pObjCache   (NULL),
      _bindMap     ()
{
    // nothing to do
}

    
    MaterialBinder::~MaterialBinder(void)
{
    // nothing to do
}
       
void
    MaterialBinder::apply(void)
{
    NamedObjectCache::ObjectMap::const_iterator omIt  =
        _pObjCache->getObjectMap().begin();
    NamedObjectCache::ObjectMap::const_iterator omEnd =
        _pObjCache->getObjectMap().end  ();
        
    for(; omIt != omEnd; ++omIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MaterialBinder::apply: Searching binding for object ["
            << omIt->first << "].\n"
            << vprDEBUG_FLUSH;
    
        OSG::FieldContainerRefPtr pObj  = omIt->second;
        OSG::NodeRefPtr           pNode = OSG::dynamic_pointer_cast<OSG::Node>(pObj);
        OSG::NodeCoreRefPtr       pCore = OSG::dynamic_pointer_cast<OSG::Node>(pObj);
        
        if(pNode && OSG::getName(pNode->getCore()) == NULL)
            pCore = pNode->getCore();
        
        if(pCore)
        {
            OSG::MaterialDrawableRefPtr pMatDraw  =
                OSG::dynamic_pointer_cast<OSG::MaterialDrawable>(pCore);
            OSG::MaterialGroupRefPtr    pMatGroup =
              OSG::dynamic_pointer_cast<OSG::MaterialGroup>(pCore);
                
            if(pMatDraw)
            {
                bindMaterialDrawable(omIt->first, pMatDraw);
                
                continue;
            }   
            else if(pMatGroup)
            {
                bindMaterialGroup(omIt->first, pMatGroup);
                
                continue;
            }
        }
        
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MaterialBinder::apply: Object does not use materials.\n"
            << vprDEBUG_FLUSH;
    }
}

void
    MaterialBinder::apply(
        std::string const &objName,
        std::string const &matName,
        bool               storeBinding)
{       
    boost::regex objNameRE(objName);
    
    NamedObjectCache::ObjectMap::const_iterator omIt  =
        _pObjCache->getObjectMap().begin();
    NamedObjectCache::ObjectMap::const_iterator omEnd =
        _pObjCache->getObjectMap().end  ();
    
    for(; omIt != omEnd; ++omIt)
    {
        if(!boost::regex_match(omIt->first, objNameRE))
            continue;
            
        OSG::MaterialRefPtr pMat = _pMatMgr->getMaterial(matName);
        
        if(pMat)
        {
            OSG::FieldContainerRefPtr pObj  = omIt->second;
            OSG::NodeRefPtr           pNode = OSG::dynamic_pointer_cast<OSG::Node>(pObj);
            OSG::NodeCoreRefPtr       pCore = OSG::dynamic_pointer_cast<OSG::NodeCore>(pObj);
            
            if(pNode && OSG::getName(pNode->getCore()) == NULL)
                pCore = pNode->getCore();
            
            if(pCore)
            {
                OSG::MaterialDrawableRefPtr pMatDraw  =
                    OSG::dynamic_pointer_cast<OSG::MaterialDrawable>(pObj);
                OSG::MaterialGroupRefPtr    pMatGroup =
                    OSG::dynamic_pointer_cast<OSG::MaterialGroup>(pObj);
                    
                if(pMatDraw)
                {
                    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                        << "MaterialBinder::apply: "
                        << "Binding object [" << omIt->first << "] to material ["
                        << matName << "].\n"
                        << vprDEBUG_FLUSH;
                
                    //beginEditCP(pMatDraw);
                        pMatDraw->setMaterial(pMat);
                    //endEditCP  (pMatDraw);
                }
                
                if(pMatGroup)
                {
                    vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                        << "MaterialBinder::apply: "
                        << "Binding object [" << omIt->first << "] to material ["
                        << matName << "].\n"
                        << vprDEBUG_FLUSH;
                
                    //beginEditCP(pMatGroup);
                        pMatGroup->setMaterial(pMat);
                    //endEditCP  (pMatGroup);
                }
            }
        }
    }
    
    if(storeBinding)
        addBindingBack(objName, matName);
}

void
    MaterialBinder::addBindingFront(
        std::string const &objName, std::string const &matName)
{
    _bindMap.push_front(BindingMapEntry(boost::regex(objName), matName));
}

void
    MaterialBinder::addBindingBack(
        std::string const &objName, std::string const &matName)
{
    _bindMap.push_back(BindingMapEntry(boost::regex(objName), matName));
}

void
    MaterialBinder::setBinding(
        std::string const &objName, std::string const &matName)
{
    BindingMap::iterator bmIt  = _bindMap.begin();
    BindingMap::iterator bmEnd = _bindMap.end  ();
    
    boost::regex objNameRE(objName);
    
    for(; bmIt != bmEnd; ++bmIt)
    {
        if(bmIt->first == objNameRE)
        {
            bmIt->second = matName;
            return;
        }
    }
    
    addBindingBack(objName, matName);
}

bool
    MaterialBinder::findBinding(
        std::string const &objName, std::string &matName, bool matchObjLiteral)
{
    BindingMap::const_iterator bmIt  = _bindMap.begin();
    BindingMap::const_iterator bmEnd = _bindMap.end  ();
    
    if(matchObjLiteral)
    {
        boost::regex objNameRE(objName);
        
        for(; bmIt != bmEnd; ++bmIt)
        {
            if(bmIt->first == objNameRE)
            {
                matName = bmIt->second;
                return true;
            }
        }
    }
    else
    {
        for(; bmIt != bmEnd; ++bmIt)
        {
            if(boost::regex_match(objName, bmIt->first))
            {
                matName = bmIt->second;
                return true;
            }
        }
    }
    
    return false;
}

bool
    MaterialBinder::findBinding(
        std::string const &objName, OSG::MaterialRefPtr &pMat,
        bool matchObjLiteral)
{
    bool        retVal = false;
    std::string matName;
    
    if(findBinding(objName, matName, matchObjLiteral))
    {
        pMat   = _pMatMgr->getMaterial(matName);
        
        retVal = (pMat);
    }
    
    return retVal;
}

void
    MaterialBinder::readFile(std::string const &fileName)
{
    typedef char                         char_t;
    typedef bs::file_iterator<char_t>    FileItType;
    
    typedef BindingBuilder<FileItType >  BindBuilder;
    typedef BindingGrammar<BindBuilder>  BindGrammar;
    
    BindBuilder bindBuilder;
    BindGrammar bindGrammar(&bindBuilder);
    
    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "MaterialBinder::readFile: Could not open binding file "
            << "'" << fileName << "'."
            << std::endl << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
    
    bs::parse_info<FileItType> info = 
        parse(fileIt, fileEnd, bindGrammar, bs::space_p);
        
    if(!info.hit)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "MaterialBinder::readFile: Parsing of binding file "
            << "'" << fileName << "' failed.\n"
            << vprDEBUG_FLUSH;
            
            return;
    }
    
    BindBuilder::BindStringMap::const_iterator bmIt  =
        bindBuilder.getBindMap().begin();
    BindBuilder::BindStringMap::const_iterator bmEnd =
        bindBuilder.getBindMap().end  ();
        
    for(; bmIt != bmEnd; ++bmIt)
    {   
        addBindingBack(bmIt->first, bmIt->second);
    }
}

void
    MaterialBinder::dump(std::ostream &os)
{
    BindingMap::const_iterator bmIt   = _bindMap.begin();
    BindingMap::const_iterator bmEnd  = _bindMap.end  ();
    
    for(; bmIt != bmEnd; ++bmIt)
    {
        os << "Name RE [" << bmIt->first 
           << "] -- > [" << bmIt->second << "] Material.\n";
    }
    
    os << "objCache:\n";
    _pObjCache->dump(os);
}

void
    MaterialBinder::bindMaterialDrawable(
        std::string const &objNameStr, OSG::MaterialDrawableRefPtr pMatDraw)
{
    OSG::MaterialRefPtr  pMat;
    MaterialDesc const  *pMatDesc;
    std::string          matName;
     
    if(findMaterial(objNameStr, pMat, pMatDesc, matName) && pMat)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MaterialBinder::bindMaterialDrawable: "
            << "Binding object [" << objNameStr << "] to material ["
            << matName << "].\n"
            << vprDEBUG_FLUSH;
    
#if 0
        // adjust texture coordinates
        OSG::GeometryPtr pGeo = OSG::GeometryPtr::dcast(pMatDraw);
        
        // only need to consider geo and materials with textures
        if((pGeo != OSG::NullFC) && (pMatDesc->_texNames.size() > 0))
        {
            // TODO XXX this only handles on set of tex coords
            int   sizeX   = pMatDesc->_texSizesX[0];
            int   sizeY   = pMatDesc->_texSizesY[0];
            
            // divide tex coord by tex size
            float factorX = (sizeX != -1) ? 1.0f / sizeX : 1.0f;
            float factorY = (sizeY != -1) ? 1.0f / sizeY : 1.0f;
            
            vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                << "MaterialBinder::bindMaterialDrawable: "
                << "adjusting texture coordinates x [" << factorX
                << "] y [" << factorY << "].\n"
                << vprDEBUG_FLUSH;
            
            OSG::GeoTexCoords2fPtr                pTexCoords =
                OSG::GeoTexCoords2fPtr::dcast(pGeo->getTexCoords());
            OSG::GeoTexCoords2f::StoredFieldType *pTC        =
                pTexCoords->getFieldPtr();
                
            OSG::GeoTexCoords2f::StoredFieldType::iterator tcIt  = pTC->begin();
            OSG::GeoTexCoords2f::StoredFieldType::iterator tcEnd = pTC->end  ();
            
            OSG:://beginEditCP(pTexCoords);
            for(; tcIt != tcEnd; ++tcIt)
            {
                (*tcIt)[0] = factorX * (*tcIt)[0];
                (*tcIt)[1] = factorY * (*tcIt)[1];
            }
            OSG:://endEditCP(pTexCoords);
        }
#endif
        
        // set the material
        //beginEditCP(pMatDraw);
            pMatDraw->setMaterial(pMat);
        //endEditCP  (pMatDraw);
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "MaterialBinder::bindMaterialDrawable: "
            << "Could not find material for object [" << objNameStr << "].\n"
            << vprDEBUG_FLUSH;
    }
}

void
    MaterialBinder::bindMaterialGroup(
        std::string const &objNameStr, OSG::MaterialGroupRefPtr pMatGroup)
{
    OSG::MaterialRefPtr  pMat;
    MaterialDesc const  *pMatDesc;
    std::string          matName;
    
    if(findMaterial(objNameStr, pMat, pMatDesc, matName) && pMat != OSG::NullFC)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
            << "MaterialBinder::bindMaterialGroup: "
            << "Binding object [" << objNameStr << "] to material ["
            << matName << "].\n"
            << vprDEBUG_FLUSH;
    
        //beginEditCP(pMatGroup);
            pMatGroup->setMaterial(pMat);
        //endEditCP  (pMatGroup);
    }
    else
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "MaterialBinder::bindMaterialGroup: "
            << "Could not find material for object [" << objNameStr << "].\n"
            << vprDEBUG_FLUSH;
    }
}

bool
    MaterialBinder::findMaterial(
        std::string const    &objNameStr,
        OSG::MaterialRefPtr  &pMat,
        MaterialDesc const  *&pMatDesc,
        std::string          &matName  )
{
    bool                       retVal = false;
    BindingMap::const_iterator bmIt   = _bindMap.begin();
    BindingMap::const_iterator bmEnd  = _bindMap.end  ();
    
    for(; bmIt != bmEnd; ++bmIt)
    {
        if(boost::regex_match(objNameStr, bmIt->first))
        {
            vprDEBUG(vprDBG_ALL, vprDBG_VERB_LVL)
                << "MaterialBinder::findMaterial: Found object ["
                << objNameStr << "] regex [" << bmIt->first << "] material ["
                << bmIt->second << "]\n"
                << vprDEBUG_FLUSH;
        
            pMat     = _pMatMgr->getMaterial    (bmIt->second);
            pMatDesc = _pMatMgr->getMaterialDesc(bmIt->second);
            matName  = bmIt->second;
            
            if(pMat)
            {
                retVal = true;
                break;
            }
        }
    }
    
    return retVal;
}
