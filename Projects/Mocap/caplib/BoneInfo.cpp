#include <gmtl/Output.h>

#include "BoneInfo.hpp"

BoneInfo::BoneInfo(){
   id=0;
   name="unknown";
   direction.set(0.0, 0.0, 0.0);
   length=0.0;
   axis.set(0.0, 0.0, 0.0);
   dof.clear();
   limits.clear();
}

void BoneInfo::SetId(int _id) {
   id = _id;
}

int BoneInfo::GetId(void) {
   return id;
}

void BoneInfo::SetName(std::string _name) {
   name = _name;
}

std::string BoneInfo::GetName(void) {
   return name;
}

void BoneInfo::SetDirection(float x, float y, float z) {
   direction.set(x, y, z);
}

gmtl::Vec3f BoneInfo::GetDirection(void) {
   return direction;
}

void BoneInfo::SetLength(float _length) {
   length=_length;
}

float BoneInfo::GetLength(void) {
   return length;
}

void BoneInfo::SetAxis(float x, float y, float z, std::string _axisString) {
   axis.set(x, y, z);
   axisString = _axisString;
}

void BoneInfo::SetDof(std::vector<std::string> _dof) {
   dof.resize(0);
   dof = _dof;
}

void BoneInfo::AddLimit(std::pair<float, float> _limit) {
   limits.push_back(_limit);
}

int BoneInfo::GetDof(void) {
   return (int)dof.size();
}

void BoneInfo::SetMatrix(gmtl::Matrix44f _C) {
   C = _C;
   Cinv = gmtl::invert(_C);
   B = _C;
   std::cout << "SetMatrix: id: " << id << " matrix: " << std::endl << C << std::endl;
}

gmtl::Matrix44f BoneInfo::GetMatrix(void) {
   return C;
}
