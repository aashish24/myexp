/*
   .obj Loader
   Game Graphics Programming
   Created by Allen Sherrod

   Purpose:
      For reading a OBJ model and preparing it for rendering.
*/



#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdlib>
#include"objLoader.h"
#include"TokenStream.h"


void ObjModel::Release()
{
   m_totalVerts = 0;

   if(m_vertices != NULL)
      {
         delete[] m_vertices;
         m_vertices = NULL;
      }

   if(m_normals != NULL)
      {
         delete[] m_normals;
         m_normals = NULL;
      }

   if(m_texCoords != NULL)
      {
         delete[] m_texCoords;
         m_texCoords = NULL;
      }
}


bool ObjModel::LoadOBJ(char *fileName)
{
   std::ifstream fileStream;
   int fileSize = 0;

   fileStream.open(fileName, std::ifstream::in);

   if(fileStream.is_open() == false)
      return false;

   fileStream.seekg(0, std::ios::end);
   fileSize = fileStream.tellg();
   fileStream.seekg(0, std::ios::beg);

   if(fileSize <= 0)
      return false;

   char *buffer = new char[fileSize];

   if(buffer == NULL)
      return false;

   TokenStream tokenStream, tempStream;
   std::string tempLine, token;

   fileStream.read(buffer, fileSize);
   tokenStream.SetTokenStream(buffer);

   delete[] buffer;

   tokenStream.ResetStream();

   std::vector<float> verts, norms, texC;
   std::vector<int> faces;

   while(tokenStream.MoveToNextLine(&tempLine))
      {
         tempStream.SetTokenStream((char*)tempLine.c_str());
         tokenStream.GetNextToken(NULL);

         if(!tempStream.GetNextToken(&token))
            continue;

         if(strcmp(token.c_str(), "v") == 0)
            {
               tempStream.GetNextToken(&token);
               verts.push_back((float)atof(token.c_str()));

               tempStream.GetNextToken(&token);
               verts.push_back((float)atof(token.c_str()));

               tempStream.GetNextToken(&token);
               verts.push_back((float)atof(token.c_str()));
            }
         else if(strcmp(token.c_str(), "vn") == 0)
            {
               tempStream.GetNextToken(&token);
               norms.push_back((float)atof(token.c_str()));

               tempStream.GetNextToken(&token);
               norms.push_back((float)atof(token.c_str()));

               tempStream.GetNextToken(&token);
               norms.push_back((float)atof(token.c_str()));
            }
         else if(strcmp(token.c_str(), "vt") == 0)
            {
               tempStream.GetNextToken(&token);
               texC.push_back((float)atof(token.c_str()));

               tempStream.GetNextToken(&token);
               texC.push_back((float)atof(token.c_str()));
            }
         else if(strcmp(token.c_str(), "f") == 0)
            {
               int index = 0;

               for(int i = 0; i < 3; i++)
                  {
                     tempStream.GetNextToken(&token);
                     int len = (int)strlen(token.c_str());

                     for(int s = 0; s < len + 1; s++)
                        {
                           char buff[12];

                           if(token[s] != '/' && s < len)
                              {
                                 buff[index] = token[s];
                                 index++;
                              }
                           else
                              {
                                 buff[index] = '\0';
                                 faces.push_back((int)atoi(buff));
                                 index = 0;
                              }
                        }
                  }
            }

         token[0] = '\0';
      }

   // "Unroll" the loaded obj information into a list of triangles.

   int vIndex = 0, nIndex = 0, tIndex = 0;
   int numFaces = (int)faces.size() / 9;
   m_totalVerts = numFaces * 3;

   m_vertices = new float[m_totalVerts * 3];

   if((int)norms.size() != 0)
      m_normals = new float[m_totalVerts * 3];

   if((int)texC.size() != 0)
      m_texCoords = new float[m_totalVerts * 2];

   for(int f = 0; f < (int)faces.size(); f+=3)
      {
         m_vertices[vIndex + 0] = verts[(faces[f + 0] - 1) * 3 + 0];
         m_vertices[vIndex + 1] = verts[(faces[f + 0] - 1) * 3 + 1];
         m_vertices[vIndex + 2] = verts[(faces[f + 0] - 1) * 3 + 2];
         vIndex += 3;

         if(m_texCoords)
            {
               m_texCoords[tIndex + 0] = texC[(faces[f + 1] - 1) * 2 + 0];
               m_texCoords[tIndex + 1] = texC[(faces[f + 1] - 1) * 2 + 1];
               tIndex += 2;
            }

         if(m_normals)
            {
               m_normals[nIndex + 0] = norms[(faces[f + 2] - 1) * 3 + 0];
               m_normals[nIndex + 1] = norms[(faces[f + 2] - 1) * 3 + 1];
               m_normals[nIndex + 2] = norms[(faces[f + 2] - 1) * 3 + 2];
               nIndex += 3;
            }
      }

   verts.clear();
   norms.clear();
   texC.clear();
   faces.clear();

   return true;
}
