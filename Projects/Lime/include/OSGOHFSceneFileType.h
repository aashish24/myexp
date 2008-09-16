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

#ifndef _OSGOHFSCENEFILETYPE_H_
#define _OSGOHFSCENEFILETYPE_H_
#ifdef  __sgi
#pragma  once
#endif

#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGGeoPositionsFields.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGSceneFileType.h>
#include <OpenSG/OSGMaterial.h>

#include "OSGOHFLoader.h"

OSG_BEGIN_NAMESPACE

/*!\ingroup GrpSystemDrawablesGeometrymetryLoaderLib
 * \brief InventorSceneFileType
 */

class OSG_SYSTEMLIB_DLLMAPPING OHFSceneFileType : public SceneFileType
{
public:

    static OHFSceneFileType &the(void);

    virtual ~OHFSceneFileType(void);

    virtual const Char8 *getName(void) const;

    virtual NodePtr read(std::istream &is, const Char8 *fileNameOrExtension) const;

protected:

    static const Char8            *_suffixA[];
    static       OHFSceneFileType  _the;

    OHFSceneFileType(const Char8  *suffixArray[],
                           UInt16  suffixByteCount,
                           bool    override,
                           UInt32  overridePriority,
                           UInt32  flags);

    OHFSceneFileType(const OHFSceneFileType &obj);

private:

    NodePtr     createMesh    (OHF::LOHF &scene, OHF::LMesh &mesh) const;
    MaterialPtr createMaterial(OHF::LOHF &scene, UInt32      id  ) const;

    mutable std::map<UInt32, MaterialPtr> _materials;
    typedef std::map<UInt32, MaterialPtr>::iterator materialIt;
};

typedef OHFSceneFileType* OHFSceneFileTypeP;

OSG_END_NAMESPACE

#endif // _OSGOHFSCENEFILETYPE_H_
