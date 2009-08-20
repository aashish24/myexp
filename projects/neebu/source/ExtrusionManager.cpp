
#include <ExtrusionManager.h>

#include <ExtrusionParser.h>
#include <NamedObjectCache.h>

// OpenSG includes
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

// boost includes
#include <boost/lexical_cast.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// std library includes
#include <ostream>

    ExtrusionManager::ExtrusionManager(void)
    
    : _pObjCache   (NULL),
      _extMap      (),
      _infoMap     ()
{
    // nothing to do
}

void
    ExtrusionManager::readFile(std::string const &fileName)
{
    typedef char                          char_t;
    typedef bs::file_iterator<char_t>     FileItType;
    
    typedef ExtrusionBuilder<FileItType>  ExtBuilder;
    typedef ExtrusionGrammar<ExtBuilder>  ExtGrammar;
    
    ExtBuilder extBuilder;
    ExtGrammar extGrammar(&extBuilder);
    
    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "ExtrusionManager::readFile: Could not open extrusion file "
            << "'" << fileName << "'."
            << std::endl << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
    
    bs::parse_info<FileItType> info = 
        parse(fileIt, fileEnd, extGrammar >> bs::eps_p, bs::space_p);
        
    if(!info.hit)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL)
            << "ExtrusionManager::readFile: Parsing of extrusion file "
            << "'" << fileName << "' failed.\n"
            << vprDEBUG_FLUSH;
            
            return;
    }
    
    ExtBuilder::ExtrusionStoreConstIt esIt  = extBuilder._extStore.begin();
    ExtBuilder::ExtrusionStoreConstIt esEnd = extBuilder._extStore.end  ();
    
    for(; esIt != esEnd; ++esIt)
    {
        _extMap[esIt->_name] = *esIt;
    }
}

void
    ExtrusionManager::apply(void)
{    
    ExtrusionMap::const_iterator emIt  = _extMap.begin();
    ExtrusionMap::const_iterator emEnd = _extMap.end  ();
    
    for(; emIt != emEnd; ++emIt)
    {
        // find the placeholder object in the scene
//         OSG::FieldContainerRefPtr pAPFC(_pObjCache->getObject(emIt->first));
        OSG::FieldContainerRefPtr pAPFC(_pObjCache->getObject("_internal_mModelN"));
        OSG::NodeRefPtr           pAP  ( OSG::dynamic_pointer_cast< OSG::Node >( pAPFC ) );
        
        if(!pAP)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "ExtrusionManager::apply: Could not find object ["
                << emIt->first << "] to attach extrusion.\n"
                << vprDEBUG_FLUSH;
        }
        
        // check if the placeholder is a geometry
//        OSG::GeometryRefPtr pAPGeo(dynamic_cast<OSG::Geometry *>(pAP->getCore()));
//        
//        if(!pAPGeo)
//        {
//            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
//                << "ExtrusionManager::apply: Attach point is not a"
//                << " geometry, skipping.\n"
//                << vprDEBUG_FLUSH;
//            continue;
//        }
        
        // get/create info object
        ExtrusionInfo &info = _infoMap[emIt->first];
        
        // construct extrusion geometry
        constructGeo(emIt->second, info);
        
        ExtrusionDesc::SpineCPNameStore::const_iterator cpIt  =
            emIt->second._spineCPNames.begin();
        ExtrusionDesc::SpineCPNameStore::const_iterator cpEnd =
            emIt->second._spineCPNames.end  ();
        
        // add spine control points
        for(; cpIt != cpEnd; ++cpIt)
        {
            // get control point placeholder object
            OSG::FieldContainerRefPtr pCPFC(_pObjCache->getObject(*cpIt)                 );
            OSG::NodeRefPtr           pCP  (OSG::dynamic_pointer_cast< OSG::Node >(pCPFC));
            
            if(!pCP)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << "ExtrusionManager::apply: Could not find control point"
                    << " [" << *cpIt << "].\n"
                    << vprDEBUG_FLUSH;
                continue;
            }
            
            // check if the control point placeholder is a geometry
            OSG::GeometryRefPtr pCPGeo( dynamic_cast<OSG::Geometry *>(pCP->getCore()));
            
            if(!pCPGeo)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << "ExtrusionManager::apply: Control point is not a"
                    << " geometry, skipping.\n"
                    << vprDEBUG_FLUSH;
                continue;
            }
            
            // obtain the mesh transform parent of the control point
            OSG::NodeRefPtr      pCPMTrafoN(pCP->getParent());
            OSG::TransformRefPtr pCPMTrafo (dynamic_cast<OSG::Transform *>(pCPMTrafoN->getCore()));
            
            if(!pCPMTrafo)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << "ExtrusionManager::apply: Control point does not have "
                    << "a mesh transform.\n"
                    << vprDEBUG_FLUSH;
                continue;
            }

            // obtain the node transform parent of the control point
            OSG::NodeRefPtr       pCPNTrafoN(pCPMTrafoN->getParent());
            OSG::TransformRefPtr  pCPNTrafo (dynamic_cast<OSG::Transform *>(pCPNTrafoN->getCore()));
            
            if(!pCPNTrafo)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                    << "ExtrusionManager::apply: Control point does not have "
                    << "a node transform.\n"
                    << vprDEBUG_FLUSH;
                continue;
            }

            // add translation to center of control point geometry
            OSG::NodeRefPtr      pBBoxTrafoN(OSG::Node     ::create());
            OSG::TransformRefPtr pBBoxTrafo (OSG::Transform::create());
            
            OSG::Pnt3f bbCenter;
            pCP->updateVolume();
            pCP->getVolume().getCenter(bbCenter);
//             pCP->editVolume(true).getCenter(bbCenter);
            
            //OSG::beginEditCP(pBBoxTrafo, OSG::Transform::MatrixFieldMask);
                pBBoxTrafo->editMatrix().setTranslate(bbCenter.subZero());
            //OSG::endEditCP  (pBBoxTrafo, OSG::Transform::MatrixFieldMask);
            OSG::commitChanges();
  
            //OSG::beginEditCP(pBBoxTrafoN, OSG::Node::ChildrenFieldMask);
                pBBoxTrafoN->setCore(pBBoxTrafo);
            //OSG::endEditCP  (pBBoxTrafoN, OSG::Node::ChildrenFieldMask);
            OSG::commitChanges();            
            //OSG::beginEditCP(pCPMTrafoN, OSG::Node::ChildrenFieldMask);
                pCPMTrafoN->addChild(pBBoxTrafoN);
            //OSG::endEditCP  (pCPMTrafoN, OSG::Node::ChildrenFieldMask);
            OSG::commitChanges();

            // store the transforms on top of the cp
            info._cpBBoxTrans.push_back(pBBoxTrafo);
            info._cpMeshTrans.push_back(pCPMTrafo );
            info._cpNodeTrans.push_back(pCPNTrafo );
            
            // remove the control point geometry
            //OSG::beginEditCP(pCPMTrafoN, OSG::Node::ChildrenFieldMask);
                pCPMTrafoN->subChild(pCP);
            //OSG::endEditCP  (pCPMTrafoN, OSG::Node::ChildrenFieldMask);

            OSG::commitChanges();
        }
        
        // replace attach point geometry
//        //OSG::beginEditCP(pAP, OSG::Node::CoreFieldMask);
//            pAP->setCore(info._pGeo);
//        //OSG::endEditCP  (pAP, OSG::Node::CoreFieldMask);

        OSG::NodeRefPtr pGeoN(OSG::Node::create());
        //OSG::beginEditCP(pGeoN);
            pGeoN->setCore(info._pGeo);
        //OSG::endEditCP  (pGeoN);
        OSG::commitChanges();

        // @todo: Find Alternate function. 
        OSG::setName(pGeoN, emIt->first);

        //OSG::beginEditCP(pAP);
            pAP->addChild(pGeoN);
        //OSG::endEditCP  (pAP);
        OSG::commitChanges();

        // remove placeholder geometry
        OSG::FieldContainerRefPtr pPHFC    (_pObjCache->getObject(emIt->first));
        OSG::NodeRefPtr           pPH      (OSG::dynamic_pointer_cast<OSG::Node>(pPHFC));
        OSG::NodeRefPtr           pPHParent(pPH->getParent());

        //OSG::beginEditCP(pPHParent);
            pPHParent->subChild(pPH);
        //OSG::endEditCP  (pPHParent);

        OSG::commitChanges();
    }
}

void
    ExtrusionManager::update(void)
{
    ExtrusionMapConstIt emIt  = _extMap .begin();
    ExtrusionMapConstIt emEnd = _extMap .end  ();
    
    for(; emIt != emEnd; ++emIt)
    {
        InfoMapIt imIt = _infoMap.find(emIt->first);
        
        if(imIt == _infoMap.end())
            continue;
        
        ExtrusionDesc const &desc = emIt->second;
        ExtrusionInfo       &info = imIt->second;
        
        updateVertices(desc, info);
    }
}

void
    ExtrusionManager::dump(std::ostream &os) const
{
    os << "ExtrusionManager: ";

    ExtrusionMapConstIt emIt   = _extMap.begin();
    ExtrusionMapConstIt emEnd  = _extMap.end  ();
    
    InfoMapConstIt eiIt  = _infoMap.begin();
    InfoMapConstIt eiEnd = _infoMap.end  ();
    
    for(; emIt != emEnd; ++emIt)
    {
        emIt->second.dump(os);
        
        if(eiIt == eiEnd)
            continue;
        
        OSG::GeoUInt8PropertyRefPtr  pTypes = dynamic_cast<OSG::GeoUInt8Property *>(eiIt->second._pGeo->getTypes    ());
        OSG::GeoUInt32PropertyRefPtr pLen   = dynamic_cast<OSG::GeoUInt32Property *>(eiIt->second._pGeo->getLengths  ());
        OSG::GeoUInt32PropertyRefPtr pInd   = dynamic_cast<OSG::GeoUInt32Property *>(eiIt->second._pGeo->getIndices  ());
        OSG::GeoPnt3fPropertyRefPtr  pPos   = dynamic_cast<OSG::GeoPnt3fProperty  *>(eiIt->second._pGeo->getPositions());
        OSG::GeoVec3fPropertyRefPtr  pNorms = dynamic_cast<OSG::GeoVec3fProperty  *>(eiIt->second._pGeo->getNormals  ());
        //OSG::GeoVec3fPropertyRefPtr pNorms = dynamic_cast<OSG::GeoVec3fProperty *>(
        
        OSG::GeoUInt8Property ::StoredFieldType *pT = pTypes->editFieldPtr();
        OSG::GeoUInt32Property::StoredFieldType *pL = pLen  ->editFieldPtr();
        OSG::GeoUInt32Property::StoredFieldType *pI = pInd  ->editFieldPtr();
        OSG::GeoPnt3fProperty ::StoredFieldType *pP = pPos  ->editFieldPtr();
        OSG::GeoVec3fProperty ::StoredFieldType *pN = pNorms->editFieldPtr();
        
        os << "\n Types [";
        
        for(OSG::UInt32 i = 0; i < pT->size(); ++i)
        {
            os << static_cast<OSG::UInt32>((*pT)[i]) << ", ";
        }
        
        os << "]\n Lengths [";
        
        for(OSG::UInt32 i = 0; i < pL->size(); ++i)
        {
            os << (*pL)[i] << ", ";
        }
        
        os << "]\n Indices [";
        
        for(OSG::UInt32 i = 0; i < pI->size(); ++i)
        {
            os << (*pI)[i] << ", ";
        }
        
        os << "]\n Positions [";
        
        for(OSG::UInt32 i = 0; i < pP->size(); ++i)
        {
            os << "<" << (*pP)[i] << ">, ";
        }
        
        os << "]\n Normals [";
        
        for(OSG::UInt32 i = 0; i < pN->size(); ++i)
        {
            os << "<" << (*pN)[i] << ">, ";
        }
    
        ++eiIt;
    
        os << "\n";
    }
}

void
    ExtrusionManager::constructGeo(
        ExtrusionDesc const &desc, ExtrusionInfo &info)
{
    OSG::GeoUInt8PropertyRefPtr  pTypes = OSG::GeoPTypesUI8   ::create();
    OSG::GeoUInt32PropertyRefPtr pLen   = OSG::GeoPLengthsUI32::create();
    OSG::GeoUInt32PropertyRefPtr pInd   = OSG::GeoIndicesUI32 ::create();
    
    OSG::UInt32 sizeXS    = desc._crossSectionSamples.size();
    OSG::UInt32 sizeSpine = desc._spineSamples       .size();
    
    //OSG::beginEditCP(pTypes);
    //OSG::beginEditCP(pLen  );
    //OSG::beginEditCP(pInd  );
    
    OSG::GeoUInt8Property ::StoredFieldType *pT = pTypes->editFieldPtr();
    OSG::GeoUInt32Property::StoredFieldType *pL = pLen  ->editFieldPtr();
    OSG::GeoUInt32Property::StoredFieldType *pI = pInd  ->editFieldPtr();
    
    pT->reserve( sizeXS - 1                   );
    pL->reserve( sizeXS - 1                   );
    pI->reserve((sizeXS - 1) * (2 * sizeSpine));
    
    for(OSG::UInt32 i = 0; i < sizeXS - 1; ++i)
    {
        // each hose segment is a tri strip
        pT->push_back(GL_TRIANGLE_STRIP);
        pL->push_back(2 * sizeSpine    );
    
        OSG::UInt32 indTop = i+1;
        OSG::UInt32 indBot = i;
        
        for(OSG::UInt32 j = 0; j < sizeSpine; ++j)
        {
            pI->push_back(indTop + j * sizeXS);
            pI->push_back(indBot + j * sizeXS);
        }
    }
    
    OSG::commitChanges();

    //OSG::endEditCP(pTypes);
    //OSG::endEditCP(pLen  );
    //OSG::endEditCP(pInd  );
    
    OSG::GeoPnt3fPropertyRefPtr pPos  = OSG::GeoPnt3fProperty::create();
    OSG::GeoVec3fPropertyRefPtr pNorm = OSG::GeoVec3fProperty::create();
    
    //OSG::beginEditCP(pPos);
     pPos->resize(sizeXS * sizeSpine);
    //OSG::endEditCP(pPos);
    OSG::commitChanges();

    //OSG::beginEditCP(pNorm);
    pNorm->resize(sizeXS * sizeSpine);
    //OSG::endEditCP(pNorm);    
    OSG::commitChanges();

    info._pGeo = OSG::Geometry::create();
    
    //OSG::beginEditCP(info._pGeo);
        info._pGeo->setDlistCache(false);
        info._pGeo->setTypes    (pTypes);
        info._pGeo->setLengths  (pLen  );
        info._pGeo->setPositions(pPos  );
        info._pGeo->setNormals  (pNorm );
        info._pGeo->setIndices  (pInd  );
    //OSG::endEditCP  (info._pGeo);
    OSG::commitChanges();
}

void
    ExtrusionManager::updateVertices(
        ExtrusionDesc const &desc, ExtrusionInfo &info)
{
    // get the position and normal storage
    OSG::GeoPnt3fPropertyRefPtr pPos  =
        dynamic_cast<OSG::GeoPnt3fProperty *>(info._pGeo->getPositions());
    OSG::GeoVec3fPropertyRefPtr   pNorm =
        dynamic_cast<OSG::GeoVec3fProperty *>(info._pGeo->getNormals());

    if(!pPos || !pNorm)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
            << "ExtrusionManager::updateVertices: Positions or normals for "
            << "object [" << desc._name << "] not present.\n"
            << vprDEBUG_FLUSH;
        return;
    }

    OSG::GeoPnt3fProperty::StoredFieldType *pP = pPos ->editFieldPtr();
    OSG::GeoVec3fProperty::StoredFieldType *pN = pNorm->editFieldPtr();

    // evaluate the cross section
    std::vector<OSG::Pnt2f> xsPnts (desc._crossSectionSamples.size());
    std::vector<OSG::Vec2f> xsTangs(desc._crossSectionSamples.size());
    
    evalCrossSection(desc, xsPnts, xsTangs);
    
    // gather the control point locations from the controlling transforms
    std::vector<OSG::Pnt3f> spineCP;
    spineCP.reserve(info._cpMeshTrans.size());
    
    for(std::size_t i = 0, size = info._cpMeshTrans.size(); i < size; ++i)
    {
        OSG::Matrix const &meshMat = info._cpMeshTrans[i]->getMatrix();
        OSG::Matrix const &nodeMat = info._cpNodeTrans[i]->getMatrix();
        OSG::Matrix const &bboxMat = info._cpBBoxTrans[i]->getMatrix();

        OSG::Pnt3f p(0.0, 0.0, 0.0);
        bboxMat.mult(p,p);
        meshMat.mult(p,p);
        nodeMat.mult(p,p);
        
        //std::cout << "ExtrusionManager::updateVertices: spine cp [" << i << "] << [" << p << "]" << std::endl;

        spineCP.push_back(p);
    }
        
    // calculate positions/normals at spine sample points
    //OSG::beginEditCP(pPos );
    //OSG::beginEditCP(pNorm);
    
    for(OSG::UInt32 i = 0, spSize = desc._spineSamples.size(); i < spSize; ++i)
    {
        OSG::Vec3f xAxis;
        OSG::Vec3f yAxis;
        OSG::Vec3f zAxis;
        OSG::Pnt3f pnt;
    
        evalSpine(spineCP, desc._spineSamples[i], pnt, zAxis);
            
        xAxis = zAxis.cross(desc._upVector);
        xAxis.normalize();
        yAxis = xAxis.cross(zAxis );
        yAxis.normalize();
               
        OSG::Matrix posMat;
        OSG::Matrix normMat;
        
        posMat .setValue  (xAxis, yAxis, zAxis);
        normMat.invertFrom(posMat             );
        normMat.transpose();
        
        for(OSG::UInt32 j = 0, xsSize = desc._crossSectionSamples.size(); j < xsSize; ++j)
        {
            OSG::Pnt3f xsPnt3 (xsPnts [j][0],   xsPnts [j][1], 0.0);
            OSG::Vec3f xsNorm3(xsTangs[j][1], - xsTangs[j][0], 0.0);
        
            // transform to local coordinate system
            posMat .mult(xsPnt3, xsPnt3);
            normMat.mult(xsNorm3, xsNorm3);
            
            xsPnt3 += pnt.subZero();
                        
            // store
            (*pP)[i * xsSize + j] = xsPnt3;
            (*pN)[i * xsSize + j] = xsNorm3;
        }
    }
    
    OSG::commitChanges();
    //OSG::endEditCP(pPos );
    //OSG::endEditCP(pNorm);
}


void
    ExtrusionManager::evalCrossSection(
        ExtrusionDesc const     &desc,
        std::vector<OSG::Pnt2f> &pos,
        std::vector<OSG::Vec2f> &tang )
{
    std::vector<OSG::Pnt2f> scratch(desc._crossSectionCP.size());
    
    evalBezier(
        &(pos.front()), &(tang.front()),
        &(desc._crossSectionSamples.front()), desc._crossSectionSamples.size(),
        &(desc._crossSectionCP     .front()), desc._crossSectionCP     .size(),
        &(scratch                  .front())                                   );
}

void
    ExtrusionManager::evalSpine(
        std::vector<OSG::Pnt3f> const &cp, 
        OSG::Real32                    t,
        OSG::Pnt3f                    &pos,
        OSG::Vec3f                    &tang)
{
    std::vector<OSG::Pnt3f> scratch(cp.size());

    evalBezier(
        &pos, &tang,
        &t, 1,
        &(cp     .front()), cp.size(),
        &(scratch.front())            );
}
