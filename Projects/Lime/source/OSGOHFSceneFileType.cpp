/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/


#include <string>
#include <map>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGeoProperty.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include "OSGOHFSceneFileType.h"

OSG_USING_NAMESPACE

const Char8 *OHFSceneFileType::_suffixA[] = { "ohf" };

OHFSceneFileType  OHFSceneFileType::_the(_suffixA,
                                           sizeof(_suffixA),
                                           false,
                                           10,
                                           SceneFileType::OSG_READ_SUPPORTED);

/*!
 * \brief
 * \param
 * \return
 */
NodePtr OHFSceneFileType::read(std::istream &is, const Char8 *) const
{
    if(!is)
        return NullFC;

    _materials.clear();

    OHF::LOHF scene;
    if(!scene.Load(is))
    {
        SWARNING << "Couldn't read from stream!" << std::endl;
        return NullFC;
    }

    NodePtr root = Node::create();
    GroupPtr group = Group::create();
    beginEditCP(root);
        root->setCore(group);
    endEditCP(root);
    
    
    short int prev_level;    
    NodePtr m_parent, prim_node, prev_node;    
      
    
    std::map<short int, NodePtr> parent_map;
    parent_map[OHF::MAINOHF_ROOT] = root;
    prev_level = OHF::MAINOHF_ROOT;     
    prev_node = root;
    m_parent = root;
    
    
    
    //SLOG << " ------------------------------------------------- " << std::endl;
            
        
    OHF::LHierarchyInfo hinfo;
    for ( unsigned int i=0;i<scene.GetPrimitiveCount();i++)
    {
        hinfo = scene.GetHierarchyInfo(i);    
        short int obj_hierarchy = hinfo.m_hierarchy;
        SINFO << "Primitive " << i << ", type " << hinfo.ptype << ", index " << hinfo.index << ", hierarchy " << obj_hierarchy << std::endl;
            
        OHF::LDummy m_dummy;
        OHF::LMesh  m_mesh;
        switch (hinfo.ptype){
            case OHF::PRIM_GEOMETRY:
                m_mesh = scene.GetMesh(hinfo.index);                
                prim_node = createMesh(scene, m_mesh);
                break;
            case OHF::PRIM_HELPER:
                m_dummy = scene.GetDummy(hinfo.index);                
                prim_node = Node::create();
                OSG::setName(prim_node, m_dummy.GetName().c_str());
                GroupPtr dummy_group = Group::create();
                beginEditCP(prim_node);
                    prim_node->setCore(dummy_group);
                endEditCP(prim_node);                
                break;              
        }
        
        if(prim_node != NullFC)
        {
            if (obj_hierarchy < prev_level)
            {
                m_parent = parent_map[obj_hierarchy];
            }
            else if (obj_hierarchy > prev_level)
            {
                parent_map[obj_hierarchy] = prev_node;
                m_parent = prev_node;
                
            }            
            
            beginEditCP(m_parent);
                    m_parent->addChild(prim_node);
            endEditCP(m_parent);
            
            
            prev_level = obj_hierarchy;
            prev_node = prim_node;
        }
    }
    //SLOG << " ------------------------------------------------- " << std::endl;


    return root;
}

/*!
 * \brief
 * \param
 * \return
 */
OHFSceneFileType::OHFSceneFileType(const Char8  *suffixArray[],
                                         UInt16  suffixByteCount,
                                         bool    override,
                                         UInt32  overridePriority,
                                         UInt32  flags) :
    SceneFileType(suffixArray,
                  suffixByteCount,
                  override,
                  overridePriority,
                  flags)
{
}


/*!
 * \brief
 * \param
 * \return
 */
OHFSceneFileType &OHFSceneFileType::the(void)
{
    return _the;
}


/*!
 * \brief
 * \param
 * \return
 */
const Char8 *OHFSceneFileType::getName(void) const
{
    return "OHF Geometry";
}


/*!
 * \brief
 * \param
 * \return
 */
OHFSceneFileType::OHFSceneFileType(const OHFSceneFileType &obj) :
    SceneFileType(obj),
    _materials()
{
    return;
}


/*!
 * \brief
 * \param
 * \return
 */
OHFSceneFileType::~OHFSceneFileType (void )
{
    return;
}

/*!
 * \brief
 * \param
 * \return
 */
NodePtr OHFSceneFileType::createMesh(OHF::LOHF &scene, OHF::LMesh &mesh) const
{
    if(mesh.GetTriangleCount() == 0)
        return NullFC;

    NodePtr node = Node::create();
    GeometryPtr geo = Geometry::create();

    beginEditCP(node);
        node->setCore(geo);
    endEditCP(node);

    OSG::setName(node, mesh.GetName().c_str());

    GeoPositions3fPtr points = GeoPositions3f::create();
    GeoNormals3fPtr normals = GeoNormals3f::create();
    GeoTexCoords2fPtr texcoords  = GeoTexCoords2f::create();

    beginEditCP(points);
    beginEditCP(normals);
    beginEditCP(texcoords);

        for(UInt32 i=0;i<mesh.GetTriangleCount();++i)
        {
            const OHF::LTriangle2 &t = mesh.GetTriangle2(i);

            points->getFieldPtr()->push_back(Pnt3f(t.vertices[0].x, t.vertices[0].y, t.vertices[0].z));
            points->getFieldPtr()->push_back(Pnt3f(t.vertices[1].x, t.vertices[1].y, t.vertices[1].z));
            points->getFieldPtr()->push_back(Pnt3f(t.vertices[2].x, t.vertices[2].y, t.vertices[2].z));

            normals->getFieldPtr()->push_back(Vec3f(t.vertexNormals[0].x, t.vertexNormals[0].y, t.vertexNormals[0].z));
            normals->getFieldPtr()->push_back(Vec3f(t.vertexNormals[1].x, t.vertexNormals[1].y, t.vertexNormals[1].z));
            normals->getFieldPtr()->push_back(Vec3f(t.vertexNormals[2].x, t.vertexNormals[2].y, t.vertexNormals[2].z));

            texcoords->getFieldPtr()->push_back(Vec2f(t.textureCoords[0].x, t.textureCoords[0].y));
            texcoords->getFieldPtr()->push_back(Vec2f(t.textureCoords[1].x, t.textureCoords[1].y));
            texcoords->getFieldPtr()->push_back(Vec2f(t.textureCoords[2].x, t.textureCoords[2].y));
        }

    endEditCP(texcoords);
    endEditCP(normals);
    endEditCP(points);

    // create material opensg supports only one material per geometry!
    MaterialPtr mat = osg::getDefaultMaterial();
    if(mesh.GetMaterialCount() > 0)
        mat = createMaterial(scene, mesh.GetMaterial(0));

    int nv = mesh.GetTriangleCount() * 3;

    GeoIndicesUI32Ptr indices = GeoIndicesUI32::create();
    beginEditCP(indices);
        indices->getFieldPtr()->reserve(nv);
        for (int i = 0; i < nv; ++i)
            indices->getFieldPtr()->push_back(i);
    endEditCP(indices);
    
    GeoPLengthsUI32Ptr lengths = GeoPLengthsUI32::create();
    beginEditCP(lengths);
        lengths->push_back(nv);
    endEditCP(lengths);
    
    GeoPTypesUI8Ptr types = GeoPTypesUI8::create();
    beginEditCP(types);
        types->push_back(GL_TRIANGLES);
    endEditCP(types);
    
    beginEditCP(geo);
        geo->setMaterial(mat);
        geo->setPositions(points);
        geo->setNormals(normals);
        geo->setTexCoords(texcoords);
        geo->setIndices(indices);
        geo->setLengths(lengths);
        geo->setTypes(types);
        geo->getIndexMapping().push_back(Geometry::MapPosition | Geometry::MapNormal |
                                         Geometry::MapTexCoords);
    endEditCP(geo);


    //createSharedIndex(geo);
    //osg::calcVertexNormals(geo);

    return node;
}

MaterialPtr OHFSceneFileType::createMaterial(OHF::LOHF &scene, UInt32 id) const
{
    materialIt mi = _materials.find(id);
    if(mi != _materials.end())
        return (*mi).second;

    OHF::LMaterial m = scene.GetMaterial(id);

    ChunkMaterialPtr cmat = ChunkMaterial::create();

    OSG::setName(cmat, m.GetName());

    MaterialChunkPtr matc = MaterialChunk::create();

    beginEditCP(cmat);
        cmat->addChunk(matc);
    endEditCP(cmat);

    Real32 t = m.GetTransparency();

    beginEditCP(matc);
        matc->setAmbient(Color4f(m.GetAmbientColor().r, m.GetAmbientColor().g,
                         m.GetAmbientColor().b, 1.0f - t));
        matc->setDiffuse(Color4f(m.GetDiffuseColor().r, m.GetDiffuseColor().g,
                         m.GetDiffuseColor().b, 1.0f - t));
        matc->setSpecular(Color4f(m.GetSpecularColor().r, m.GetSpecularColor().g,
                         m.GetSpecularColor().b, 1.0f - t));
        matc->setEmission(Color4f(0.0f, 0.0f, 0.0f, 1.0f - t));
        matc->setShininess(m.GetShininess() * 128.0f);
    endEditCP(matc);

    // create a texture chunk
    OHF::LMap &map = m.GetTextureMap1();
    const char *texname = map.mapName;
    ImagePtr image = NullFC;
    if(texname != NULL && strlen(texname) > 0)
    {
        image = Image::create();
        bool img_ok = image->read(texname);

        if(!img_ok)
        {
            std::string casename(texname);
            for(std::string::reverse_iterator it = casename.rbegin(); 
                it != casename.rend() && *it != '/' && *it != '\\'; 
                ++it)
            {
                if(*it >= 'a' && *it <= 'z')
                {
                    *it = 'A' + *it - 'a';
                }
                else
                if(*it >= 'A' && *it <= 'Z')
                {
                    *it = 'a' + *it - 'A';
                }
                
            }
            
            FWARNING(("Couldn't load image '%s', trying case "
                      "reversed version '%s'! \n", texname,
                      casename.c_str()));
                      
            img_ok = image->read(casename.c_str());
        }
        
        if(img_ok)
        {
            beginEditCP(image, Image::ForceAlphaBinaryFieldMask);
            image->setForceAlphaBinary(image->calcIsAlphaBinary());
            endEditCP(image, Image::ForceAlphaBinaryFieldMask);

            TextureChunkPtr texc = TextureChunk::create();
            beginEditCP(texc);
                texc->setImage(image);
                // 0x0008 means no tiling.
                GLenum wm = (map.tiling & 0x0008) ? GL_CLAMP_TO_EDGE : GL_REPEAT;
                texc->setWrapS(wm);
                texc->setWrapT(wm);
                texc->setEnvMode(GL_MODULATE);
                texc->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
                texc->setMagFilter(GL_LINEAR);
            endEditCP(texc);

            beginEditCP(cmat);
                cmat->addChunk(texc);
            endEditCP(cmat);
        }
    }

    // add a blend chunk for transparency
    if(t > 0.0 || 
       ( image != NullFC && 
         image->hasAlphaChannel()
      ))
    {
        BlendChunkPtr blendc = BlendChunk::create();
        beginEditCP(blendc);
        
        if(image != NullFC && image->isAlphaBinary())
        {
            blendc->setAlphaFunc(GL_NOTEQUAL);
            blendc->setAlphaValue(0);
        }
        else
        {
            blendc->setSrcFactor(GL_SRC_ALPHA);
            blendc->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        }
        
        endEditCP(blendc);
        beginEditCP(cmat);
            cmat->addChunk(blendc);
        endEditCP(cmat);
    }

    _materials.insert(std::pair<UInt32, MaterialPtr>(id, cmat));

    return cmat;
}

