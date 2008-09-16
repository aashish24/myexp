
#include <Lib3dsBridge.h>

// OpenSG includes
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGTransform.h>

// VRJuggler includes
#include <vpr/Util/Debug.h>

// boost includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>

// lib3ds includes
#include <lib3ds/file.h>
#include <lib3ds/matrix.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>

namespace bs = boost::spirit;


    Lib3dsBridge::Lib3dsBridge(void)
    
    : _nodeMap(),
      _nameMap(),
      _pLFile (NULL),
      _pRoot  ()
{
    // nothing to do
}

void
    Lib3dsBridge::readNameMapFile(std::string const &fileName)
{
    typedef char                               char_t;
    typedef bs::file_iterator<char_t>          FileItType;
   
    typedef boost::tokenizer<
        boost::escaped_list_separator<char>,
        FileItType                           > TokenizerType;

    FileItType fileIt(fileName);
        
    if(!fileIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
            << "Lib3dsBridge::readNameMapFile: Could not open name mapping file"
            << " [" << fileName << "].\n"
            << vprDEBUG_FLUSH;
            
        return;
    }
    
    FileItType fileEnd = fileIt.make_end();
                                                          
    TokenizerType tok(fileIt, fileEnd);
    TokenizerType::iterator tokIt  = tok.begin();
    TokenizerType::iterator tokEnd = tok.end  ();
    
    while(tokIt != tokEnd)
    {
        std::string objName = *tokIt;
                
        if(++tokIt == tokEnd)
            break;
        
        std::string objId   = *tokIt;
                
        boost::trim(objName);
        boost::trim(objId  );
        
        std::pair<NameMap::iterator, bool> res = 
            _nameMap.insert(NameMap::value_type(objId, objName));
            
        if(res.second == false)
        {
            vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL)
                << "Lib3dsBridge::readFile: Could not insert mapping ["
                << objId << "] -> [" << objName << "]\n"
                << vprDEBUG_FLUSH;
        }
        
        ++tokIt;
    }
}

void
    Lib3dsBridge::dumpNameMap(void) const
{
    NameMap::const_iterator nmIt  = _nameMap.begin();
    NameMap::const_iterator nmEnd = _nameMap.end  ();
    
    for(; nmIt != nmEnd; ++nmIt)
    {
        vprDEBUG(vprDBG_ALL, vprDBG_DETAILED_LVL)
            << " [" << nmIt->first << "]  ->  [" << nmIt->second << "]\n"
            << vprDEBUG_FLUSH;
    }
}


OSG::NodePtr
    Lib3dsBridge::construct(void)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "Lib3dsBridge::constructOpenSGScene() called.\n",
                         "Lib3dsBridge::constructOpenSGScene() exiting.\n");

    OSG::NodeRefPtr  pRootN(OSG::Node ::create());
    OSG::GroupRefPtr pRoot (OSG::Group::create());
    
    OSG::beginEditCP(pRootN, OSG::Node::CoreFieldMask);
        pRootN->setCore(pRoot);
    OSG::endEditCP(pRootN, OSG::Node::CoreFieldMask);
    
    for(Lib3dsNode *pLNode = _pLFile->nodes; pLNode != NULL; pLNode = pLNode->next)
    {
        constructScene(pLNode, pRootN);
    }
    
    _pRoot = pRootN;
    
    return pRootN.get();
}

void
    Lib3dsBridge::update(void)
{   
    NodeMap::iterator nmIt  = _nodeMap.begin();
    NodeMap::iterator nmEnd = _nodeMap.end  ();
    
    for(; nmIt != nmEnd; ++nmIt)
    {
        Lib3dsNode       *pLNode   =  nmIt    ->_pLNode;
        Lib3dsObjectData *pData    = &pLNode  ->data.object;
        OSG::NodePtr      pNTransN =  nmIt    ->_pNode;
        OSG::TransformPtr pNTrans  =
            OSG::TransformPtr::dcast(pNTransN->getCore());
        
        OSG::Matrix nodeMatrix;
        OSG::Matrix pivotMatrix;
        
        nodeMatrix .setValue(&pLNode->matrix[0][0]);
        pivotMatrix.setTranslate(OSG::Vec3f(- pData->pivot[0],
                                            - pData->pivot[1],
                                            - pData->pivot[2] ));
        
        nodeMatrix.mult(pivotMatrix);
        
        OSG::beginEditCP(pNTrans, OSG::Transform::MatrixFieldMask);
            pNTrans->setMatrix(nodeMatrix);
        OSG::endEditCP  (pNTrans, OSG::Transform::MatrixFieldMask);
    }
}

void
    Lib3dsBridge::constructScene(Lib3dsNode *pLNode, OSG::NodePtr pNode)
{
    if(pLNode->type                          == LIB3DS_OBJECT_NODE && 
       std::strcmp(pLNode->name, "$$$DUMMY") != 0                    )
    {
        Lib3dsMesh  *pLMesh = NULL;
        std::string  meshName;
        
        std::string  instanceName(pLNode->data.object.instance);
        std::string  nodeName    (pLNode->name                );
        
        if(!instanceName.empty())
        {
            pLMesh   = lib3ds_file_mesh_by_name(_pLFile, nodeName.c_str());
            meshName = instanceName;
        }
        else if(!nodeName.empty())
        {
            pLMesh   = lib3ds_file_mesh_by_name(_pLFile, nodeName.c_str());
            meshName = nodeName;
        }
        
        if(pLMesh != NULL)
        {
            OSG::NodeRefPtr      pNTransN(OSG::Node     ::create());
            OSG::TransformRefPtr pNTrans (OSG::Transform::create());
            
            OSG::NodeRefPtr      pMTransN(OSG::Node     ::create());
            OSG::TransformRefPtr pMTrans (OSG::Transform::create());
            
            OSG::NodeRefPtr      pGeoN   (OSG::Node     ::create());
            
            OSG::beginEditCP(pNode, OSG::Node::ChildrenFieldMask);
                pNode->addChild(pNTransN);
            OSG::endEditCP  (pNode, OSG::Node::ChildrenFieldMask);
            
            OSG::beginEditCP(pNTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
                pNTransN->setCore (pNTrans );
                pNTransN->addChild(pMTransN);
            OSG::endEditCP  (pNTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
            
            OSG::beginEditCP(pMTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
                pMTransN->setCore (pMTrans);
                pMTransN->addChild(pGeoN  );
            OSG::endEditCP  (pMTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
            
            // set names
    //         std::string nodeTransName(pLNode->name != NULL ? pLNode->name : "");
    //         std::string meshTransName(pLNode->name != NULL ? pLNode->name : "");
    //         
    //         lookupName(nodeTransName, nodeTransName);
    //         lookupName(meshTransName, meshTransName);
    //         
    //         nodeTransName.append("_node_transform");
    //         meshTransName.append("_mesh_transform");
    //         
    //         OSG::setName(pNTransN, nodeTransName);
    //         OSG::setName(pMTransN, meshTransName);
            
            // node matrix
            OSG::Matrix nodeMat;
            nodeMat.setValue(&pLNode->matrix[0][0]);
            
            OSG::beginEditCP(pNTrans, OSG::Transform::MatrixFieldMask);
                pNTrans->setMatrix(nodeMat);
            OSG::endEditCP  (pNTrans, OSG::Transform::MatrixFieldMask);
            
            // mesh matrix
            OSG::Matrix meshMat;
            meshMat.setValue(&pLMesh->matrix[0][0]);
            
            if(meshMat.invert() == false)
            {
                vprDEBUG(vprDBG_ALL, vprDBG_WARNING_LVL) 
                    << "Lib3dsBridge::constructScene: Mesh ["
                    << (pLMesh->name != NULL ? pLMesh->name : "unnamed")
                    << "] matrix is singular.\n"
                    << vprDEBUG_FLUSH;
            }        
                
            OSG::beginEditCP(pMTrans, OSG::Transform::MatrixFieldMask);
                pMTrans->setMatrix(meshMat);
            OSG::endEditCP  (pMTrans, OSG::Transform::MatrixFieldMask);
            
            // geometry
            OSG::GeometryRefPtr pGeo(constructGeometry(pLMesh));
            
            if(!meshName.empty())
            {
                lookupName(meshName, meshName);
            
                OSG::setName(pGeoN, meshName);
            }
            
            OSG::beginEditCP(pGeoN, OSG::Node::CoreFieldMask);
                pGeoN->setCore(pGeo);
            OSG::endEditCP  (pGeoN, OSG::Node::CoreFieldMask);
            
            // store node mapping
            _nodeMap.push_back(NodeMapEntry(pLNode, pNTransN));
        }
    }
    
    // recursively add children
    for(Lib3dsNode *pLChild = pLNode->childs;
        pLChild != NULL;
        pLChild = pLChild->next)
    {
        constructScene(pLChild, pNode);
    }
}

OSG::GeometryRefPtr
    Lib3dsBridge::constructGeometry(Lib3dsMesh *pLMesh)
{
    bool hasTexCoords = false;

    // calculate normals
    Lib3dsVector *pLNormals = new Lib3dsVector[3 * pLMesh->faces];
    lib3ds_mesh_calculate_normals(pLMesh, pLNormals);
    
    if((pLMesh->texels > 0) && (pLMesh->texels == pLMesh->points));
        hasTexCoords = true;
    
    OSG::GeometryRefPtr         pGeo(OSG::Geometry::create());
    
    OSG::GeoPTypesUI8Ptr    pTypes     = OSG::GeoPTypesUI8   ::create();
    OSG::GeoPLengthsUI32Ptr pLengths   = OSG::GeoPLengthsUI32::create();
    OSG::GeoIndicesUI32Ptr  pIndices   = OSG::GeoIndicesUI32 ::create();
    OSG::GeoPositions3fPtr  pPos       = OSG::GeoPositions3f ::create();
    OSG::GeoNormals3fPtr    pNorms     = OSG::GeoNormals3f   ::create();
    OSG::GeoTexCoords2fPtr  pTexCoords = OSG::GeoTexCoords2f ::create();
    
    OSG::beginEditCP(pTypes    );
    OSG::beginEditCP(pLengths  );
    OSG::beginEditCP(pIndices  );
    OSG::beginEditCP(pPos      );
    OSG::beginEditCP(pNorms    );
    OSG::beginEditCP(pTexCoords);
    {
        OSG::GeoPTypesUI8   ::StoredFieldType *pT = pTypes    ->getFieldPtr();
        OSG::GeoPLengthsUI32::StoredFieldType *pL = pLengths  ->getFieldPtr();
        OSG::GeoIndicesUI32 ::StoredFieldType *pI = pIndices  ->getFieldPtr();
        OSG::GeoPositions3f ::StoredFieldType *pP = pPos      ->getFieldPtr();
        OSG::GeoNormals3f   ::StoredFieldType *pN = pNorms    ->getFieldPtr();
        OSG::GeoTexCoords2f ::StoredFieldType *pX = pTexCoords->getFieldPtr();
               
        pT->push_back(GL_TRIANGLES     );
        pL->push_back(3 * pLMesh->faces);
        
        pI->reserve(2 * 3 * pLMesh->faces );
        pP->reserve(        pLMesh->points);
        pN->reserve(    3 * pLMesh->faces );
        pX->reserve(        pLMesh->points);
        
        for(unsigned int f = 0; f < pLMesh->faces; ++f)
        {
            Lib3dsFace const *pLFace = &pLMesh->faceL[f];
            
            for(unsigned int v = 0; v < 3; ++v)
            {
                pI->push_back(pLFace->points[v]); // vertex index
                pI->push_back(3 * f + v        ); // normal index
                
                // copy normal
                OSG::Vec3f norm(pLNormals[3 * f + v][0],
                                pLNormals[3 * f + v][1],
                                pLNormals[3 * f + v][2] );
                
                pN->push_back(norm);
            }
        }
        
        // copy vertices
        for(unsigned int v = 0; v < pLMesh->points; ++v)
        {
            pP->push_back(OSG::Pnt3f(pLMesh->pointL[v].pos[0],
                                     pLMesh->pointL[v].pos[1],
                                     pLMesh->pointL[v].pos[2] ));
            
        }
        
        // copy tex coords
        if(hasTexCoords)
        {
//            vprDEBUG(vprDBG_ALL, vprDBG_CRITICAL_LVL) 
//                << "Lib3dsBridge::constructScene: Mesh ["
//                << (pLMesh->name != NULL ? pLMesh->name : "")
//                << "] has tex coords:\n"
//                << vprDEBUG_FLUSH;
        
            for(unsigned int v = 0; v < pLMesh->texels; ++v)
            {
                pX->push_back(OSG::Vec2f(pLMesh->texelL[v][0],
                                         pLMesh->texelL[v][1] ));
                                         
//                std::cout << "<" << pLMesh->texelL[v][0] << ", "
//                                 << pLMesh->texelL[v][1] << ">  ";
            }
            
//            std::cout << std::endl;
        }
    }
    OSG::endEditCP  (pTypes    );
    OSG::endEditCP  (pLengths  );
    OSG::endEditCP  (pIndices  );
    OSG::endEditCP  (pPos      );
    OSG::endEditCP  (pNorms    );
    OSG::endEditCP  (pTexCoords);
    
    // free lib3ds data
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "Lib3dsBridge::constructGeomerty: Freeing lib3ds data.\n"
        << vprDEBUG_FLUSH;
    
    lib3ds_mesh_free_point_list(pLMesh);
    lib3ds_mesh_free_face_list (pLMesh);
    
    if(hasTexCoords)
        lib3ds_mesh_free_texel_list(pLMesh);
    
    delete [] pLNormals;
    
    OSG::beginEditCP(pGeo);
        pGeo->setTypes    (pTypes    );
        pGeo->setLengths  (pLengths  );
        pGeo->setIndices  (pIndices  );
        pGeo->setPositions(pPos      );
        pGeo->setNormals  (pNorms    );
        
        if(hasTexCoords)
        {
            pGeo->setTexCoords(pTexCoords);
        
            pGeo->getIndexMapping().push_back(OSG::Geometry::MapPosition  |
                                              OSG::Geometry::MapTexCoords  );
            pGeo->getIndexMapping().push_back(OSG::Geometry::MapNormal     );
        }
        else
        {
            pGeo->getIndexMapping().push_back(OSG::Geometry::MapPosition   );
            pGeo->getIndexMapping().push_back(OSG::Geometry::MapNormal     );
        }
    OSG::endEditCP  (pGeo);
    
    return pGeo;
}

void
    Lib3dsBridge::lookupName(std::string const &oldName, std::string &newName)
{
    NameMap::const_iterator nmIt = _nameMap.find(oldName);
    
    if(nmIt != _nameMap.end())
    {
        newName = nmIt->second;
    }
    else
    {
        newName = oldName;
    }
}

