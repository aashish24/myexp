#ifndef MOCAP_BONE_HPP
#define MOCAP_BONE_HPP

#include <gmtl/Vec.h>
#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>
#include <vector>
#include <string>

class BoneInfo {
   int id;
   std::string name;
   gmtl::Vec3f direction;
   float length;
   gmtl::Vec3f axis;
   std::string axisString;
   std::vector<std::string> dof;
   std::vector<std::pair<float, float> > limits;
   //matrices for transforming bones to their actual position
   //and orientation
   gmtl::Matrix44f C, Cinv, B;
public:
   BoneInfo();
   ~BoneInfo(){}
   void SetId(int _id);
   int GetId(void);
   void SetName(std::string _name);
   std::string GetName(void);
   void SetDirection(float x, float y, float z);
   gmtl::Vec3f GetDirection(void);
   void SetLength(float _length);
   float GetLength(void);
   void SetAxis(float x, float y, float z, std::string _axisString);
   void SetMatrix(gmtl::Matrix44f _C);
   gmtl::Matrix44f GetMatrix(void);
   void SetDof(std::vector<std::string> _dof);
   void AddLimit(std::pair<float, float> _limit);

   int GetDof(void);
};

#endif
