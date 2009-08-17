#ifndef MOCAP_SKELETON_HPP
#define MOCAP_SKELETON_HPP

#include <vector>
#include <string>
#include <map>

#include "BoneInfo.hpp"

class Skeleton {
   std::vector<BoneInfo *> skeleton;
   std::map<std::string, int> boneMap;
   std::map<int, std::vector<int> > boneFrame;
   std::string name;
   std::string version;
   std::string doc;
   float length;
   float mass;
   std::string angle;
   std::string order[6];
   std::string axis;
   float p[3];
   float o[3];
public:
   Skeleton();
   ~Skeleton();

   void AddBone(BoneInfo *bi);
   void SetName(std::string s_name);
   void SetVersion(std::string s_version);
   void SetDocumentation(std::string s_documentation);
   void SetMass(float _mass);
   void SetLength(float _length);
   void SetAngle(std::string _angle);
   void SetRootOrder(std::string o1, std::string o2, std::string o3, std::string o4, std::string o5, std::string o6);
   void SetRootAxis(std::string _axis);
   void SetRootPosition(float x, float y, float z);
   void SetRootOrientation(float o1, float o2, float o3);
   int GetId(std::string _name);
   void AddChildren(int _id, std::vector<int> _children);
   std::vector<int> GetChildren(int _id);
   BoneInfo* GetBoneInfo(int _id);
   void ComputeMatrices(void);
};

#endif
