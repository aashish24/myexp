#include <iostream>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

#include "vtkOpenGLExtensionManager.h"
#include "vtkgl.h"

#include <vtkNew.h>

// OpenGL extensions check
//GL_ARB_depth_texture or OpenGL>=1.4
//GL_ARB_shadow or OpenGL>=1.4
//GL_EXT_shadow_funcs or OpenGL>=1.5
//GL_ARB_vertex_shader or OpenGL>=2.0
//GL_ARB_fragment_shader or OpenGL>=2.0
//GL_ARB_shader_objects or OpenGL>=2.0
//GL_ARB_occlusion_query or OpenGL>=1.5
//GL_ARB_multitexture or OpenGL>=1.3
//GL_ARB_texture_rectangle
//GL_SGIS_texture_edge_clamp or GL_EXT_texture_edge_clamp or OpenGL>=1.2

bool CheckIfDepthPeelingIsSupported(vtkRenderWindow* renWin)
  {
  vtkNew<vtkOpenGLExtensionManager> extensions;
  extensions->SetRenderWindow(renWin);

  if (   !extensions->ExtensionSupported("GL_VERSION_1_2")
      || !extensions->ExtensionSupported("GL_ARB_depth_texture")
      || !extensions->ExtensionSupported("GL_ARB_vertex_shader")
      || !extensions->ExtensionSupported("GL_ARB_fragment_shader")
      || !extensions->ExtensionSupported("GL_ARB_fragment_shader")
      || !extensions->ExtensionSupported("GL_ARB_shader_objects")
      || !extensions->ExtensionSupported("GL_ARB_occlusion_query")
      || !extensions->ExtensionSupported("GL_ARB_multitexture")
      || !extensions->ExtensionSupported("GL_ARB_occlusion_query")
      )
    {
    std::cerr << "Required extensions for depth peeling not supported! \n";
    }
  else
    {
    std::cerr << "Required extensions for depth peeling are supported! \n";
    }
  }

int main()
{
  vtkNew<vtkRenderer> ren;
  vtkNew<vtkRenderWindow> renWin;

  renWin->AddRenderer(ren.GetPointer());
  renWin->Render();

  CheckIfDepthPeelingIsSupported(renWin.GetPointer());
}

