
#include <Lib3dsBridge.h>

// OpenSG includes
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypedGeoIntegralProperty.h>
#include <OpenSG/OSGTypedGeoVectorProperty.h>

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


OSG::NodeRefPtr
    Lib3dsBridge::construct(void)
{
    vprDEBUG_OutputGuard(vprDBG_ALL, vprDBG_DETAILED_LVL,
                         "Lib3dsBridge::constructOpenSGScene() called.\n",
                         "Lib3dsBridge::constructOpenSGScene() exiting.\n");

    OSG::NodeRefPtr  pRootN(OSG::Node ::create());
    OSG::GroupRefPtr pRoot (OSG::Group::create());
    
    //OSG::beginEditCP(pRootN, OSG::Node::CoreFieldMask);
        pRootN->setCore(pRoot);
    //OSG::endEditCP(pRootN, OSG::Node::CoreFieldMask);
    
    OSG::commitChanges();

    for(Lib3dsNode *pLNode = _pLFile->nodes; pLNode != NULL; pLNode = pLNode->next)
    {
        constructScene(pLNode, pRootN);
    }
    
    _pRoot = pRootN;

    return pRootN;
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
        OSG::NodeRefPtr   pNTransN =  nmIt    ->_pNode;
        OSG::TransformRefPtr pNTrans  = dynamic_cast<OSG::Transform *>(pNTransN->getCore());
        
        OSG::Matrix nodeMatrix;
        OSG::Matrix pivotMatrix;
        
        nodeMatrix .setValue(&pLNode->matrix[0][0]);
        pivotMatrix.setTranslate(OSG::Vec3f(- pData->pivot[0],
                                            - pData->pivot[1],
                                            - pData->pivot[2] ));
        
        nodeMatrix.mult(pivotMatrix);
        
        //OSG::beginEditCP(pNTrans, OSG::Transform::MatrixFieldMask);
            pNTrans->setMatrix(nodeMatrix);
        //OSG::endEditCP  (pNTrans, OSG::Transform::MatrixFieldMask);
        OSG::commitChanges();
    }
}

void
    Lib3dsBridge::constructScene(Lib3dsNode *pLNode, OSG::NodeRefPtr pNode)
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
            
            //OSG::beginEditCP(pNode, OSG::Node::ChildrenFieldMask);
                pNode->addChild(pNTransN);
            //OSG::endEditCP  (pNode, OSG::Node::ChildrenFieldMask);
            OSG::commitChanges(); 

            //OSG::beginEditCP(pNTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
                pNTransN->setCore (pNTrans );
                pNTransN->addChild(pMTransN);
            //OSG::endEditCP  (pNTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
            OSG::commitChanges(); 

            //OSG::beginEditCP(pMTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
                pMTransN->setCore (pMTrans);
                pMTransN->addChild(pGeoN  );
            //OSG::endEditCP  (pMTransN, OSG::Node::ChildrenFieldMask | OSG::Node::CoreFieldMask);
            OSG::commitChanges(); 

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
            
            //OSG::beginEditCP(pNTrans, OSG::Transform::MatrixFieldMask);
                pNTrans->setMatrix(nodeMat);
            //OSG::endEditCP  (pNTrans, OSG::Transform::MatrixFieldMask);
            OSG::commitChanges(); 

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
                
            //OSG::beginEditCP(pMTrans, OSG::Transform::MatrixFieldMask);
                pMTrans->setMatrix(meshMat);
            //OSG::endEditCP  (pMTrans, OSG::Transform::MatrixFieldMask);
            OSG::commitChanges(); 

            // geometry
            OSG::GeometryRefPtr pGeo(constructGeometry(pLMesh));
            
            if(!meshName.empty())
            {
                lookupName(meshName, meshName);
            
                OSG::setName(pGeoN, meshName);
            }
            
            //OSG::beginEditCP(pGeoN, OSG::Node::CoreFieldMask);
                pGeoN->setCore(pGeo);
            //OSG::endEditCP  (pGeoN, OSG::Node::CoreFieldMask);
            OSG::commitChanges(); 

            // store node mapping
            _nodeMap.push_back(NodeMapEntry(pLNode, pNTransN));
        }

        OSG::commitChanges(); 
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
    
    if((pLMesh->texels > 0) && (pLMesh->texels == pLMesh->points))
        hasTexCoords = true;
    
    OSG::GeometryRefPtr         pGeo(OSG::Geometry::create());
    
    OSG::GeoUInt8PropertyRefPtr  pTypes     = OSG::GeoPTypesUI8   ::create();
    OSG::GeoUInt32PropertyRefPtr pLengths   = OSG::GeoPLengthsUI32::create();

    // Indices for the vertex.
    OSG::GeoUInt32PropertyRefPtr pIndices   = OSG::GeoIndicesUI32 ::create();
    //OSG::GeoUInt32PropertyRefPtr tIndices   = OSG::GeoIndicesUI32 ::create();
    OSG::GeoUInt32PropertyRefPtr nIndices   = OSG::GeoIndicesUI32 ::create();

    OSG::GeoPnt3fPropertyRefPtr  pPos       = OSG::GeoPositions3f ::create();
    OSG::GeoVec3fPropertyRefPtr  pNorms     = OSG::GeoNormals3f   ::create();
    OSG::GeoVec2fPropertyRefPtr  pTexCoords = OSG::GeoTexCoords2f ::create();
    
    //OSG::beginEditCP(pTypes    );
    //OSG::beginEditCP(pLengths  );
    //OSG::beginEditCP(pIndices  );
    //OSG::beginEditCP(pPos      );
    //OSG::beginEditCP(pNorms    );
    //OSG::beginEditCP(pTexCoords);
    {
        OSG::GeoUInt8Property ::StoredFieldType *pT = pTypes    ->editFieldPtr();
        OSG::GeoUInt32Property::StoredFieldType *pL = pLengths  ->editFieldPtr();      
         
        OSG::GeoUInt32Property::StoredFieldType *pI = pIndices  ->editFieldPtr();
        //OSG::GeoUInt32Property::StoredFieldType *tI = tIndices  ->editFieldPtr();
        OSG::GeoUInt32Property::StoredFieldType *nI = nIndices  ->editFieldPtr();  
            
        OSG::GeoPnt3fProperty ::StoredFieldType *pP = pPos      ->editFieldPtr();
        OSG::GeoVec3fProperty ::StoredFieldType *pN = pNorms    ->editFieldPtr();
        OSG::GeoVec2fProperty ::StoredFieldType *pX = pTexCoords->editFieldPtr();
               
        pT->push_back(GL_TRIANGLES     );
        pL->push_back(3 * pLMesh->faces);
        
        //pI->reserve(2 * 3 * pLMesh->faces );
        pI->reserve(3 * pLMesh->faces );
        nI->reserve(3 * pLMesh->faces );

        pP->reserve(        pLMesh->points);
        pN->reserve(    3 * pLMesh->faces );
        pX->reserve(        pLMesh->points);
        
        for(unsigned int f = 0; f < pLMesh->faces; ++f)
        {
            Lib3dsFace const *pLFace = &pLMesh->faceL[f];
            
            for(unsigned int v = 0; v < 3; ++v)
            {
                pI->push_back(pLFace->points[v]); // vertex index
                //pI->push_back(3 * f + v        ); // normal index

                nI->push_back( 3* f + v            ); // normal index
                
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

        OSG::commitChanges();
    }
    //OSG::endEditCP  (pTypes    );
    //OSG::endEditCP  (pLengths  );
    //OSG::endEditCP  (pIndices  );
    //OSG::endEditCP  (pPos      );
    //OSG::endEditCP  (pNorms    );
    //OSG::endEditCP  (pTexCoords);
    
    // free lib3ds data
    vprDEBUG(vprDBG_ALL, vprDBG_STATE_LVL)
        << "Lib3dsBridge::constructGeomerty: Freeing lib3ds data.\n"
        << vprDEBUG_FLUSH;
    
    lib3ds_mesh_free_point_list(pLMesh);
    lib3ds_mesh_free_face_list (pLMesh);
    
    if(hasTexCoords)
        lib3ds_mesh_free_texel_list(pLMesh);
    
    delete [] pLNormals;
    
    //OSG::beginEditCP(pGeo);
        pGeo->setTypes    (pTypes    );
        pGeo->setLengths  (pLengths  );
        //pGeo->setIndices  (pIndices  );
        pGeo->setPositions(pPos      );
        pGeo->setNormals  (pNorms    );
        
        if(hasTexCoords)
        {
            pGeo->setTexCoords(pTexCoords);

            pGeo->setIndex( pIndices, OSG::Geometry::TexCoordsIndex );
            pGeo->setIndex( pIndices, OSG::Geometry::PositionsIndex );
            pGeo->setIndex( nIndices, OSG::Geometry::NormalsIndex );
        }
        else
        {
            pGeo->setIndex( pIndices, OSG::Geometry::PositionsIndex );            
            pGeo->setIndex( nIndices, OSG::Geometry::NormalsIndex );
        }
    //OSG::endEditCP  (pGeo);
    
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

