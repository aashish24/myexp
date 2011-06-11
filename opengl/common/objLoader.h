
#ifndef __OBJ_MODEL_H__
#define __OBJ_MODEL_H__


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

    int    m_totalVerts;
};

#endif
