

#ifndef	__VRJ_I3DEA_EXPORT_H__
#define __VRJ_I3DEA_EXPORT_H__

#if defined ( _MSC_VER )
#	if defined ( VRJ_I3DEA_COMPILE ) 
#		define	VRJ_I3DEA_EXPORT __declspec( dllexport )
#	else
#		define	VRJ_I3DEA_EXPORT __declspec( dllimport )
#	endif // #ifdef( VRJ_I3DEA_COMPILE )
#endif // #ifdef( _MSC_VER )


#endif // __VRJ_I3DEA_EXPORT_H__
