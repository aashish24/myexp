/*
   .obj Loader
   Game Graphics Programming
   Created by Allen Sherrod

   Purpose:
      For reading a OBJ model and preparing it for rendering.
*/


#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_


class ObjModel
{
   public:
      ObjModel()
      {
         m_vertices = NULL;
         m_normals = NULL;
         m_texCoords = NULL;
         m_totalVerts = 0;
      }
      
      ~ObjModel()
      {
         Release();
      }


      void Release();
      bool LoadOBJ(char *fileName);


      float *GetVertices()   { return m_vertices; }
      float *GetNormals()    { return m_normals; }
      float *GetTexCoords()  { return m_texCoords; }
      int    GetTotalVerts() { return m_totalVerts; }

   private:
      float *m_vertices;
      float *m_normals;
      float *m_texCoords;
      int m_totalVerts;
};

#endif