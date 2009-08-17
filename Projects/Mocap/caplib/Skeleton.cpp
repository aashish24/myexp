#include <deque>
#include <gmtl/Matrix.h>
#include <gmtl/Output.h>
#include "Skeleton.hpp"

Skeleton::Skeleton() : skeleton(0) {
}

Skeleton::~Skeleton() {
   if(skeleton.size() > 0) {
      for(size_t i = 0; i < skeleton.size(); ++i)
         delete skeleton[i];
      skeleton.clear();
   }
}

void Skeleton::AddBone(BoneInfo *b) {
   boneMap[b->GetName()] = b->GetId();
   skeleton.push_back(b);
}

void Skeleton::SetName(std::string s_name) {
   name = s_name;
}

void Skeleton::SetVersion(std::string s_version) {
   version = s_version;
}

void Skeleton::SetDocumentation(std::string _doc) {
   doc = _doc;
}

void Skeleton::SetMass(float _mass) {
   mass = _mass;
}

void Skeleton::SetLength(float _length) {
   length = _length;
}

void Skeleton::SetAngle(std::string _angle) {
   angle = _angle;
}

void Skeleton::SetRootOrder(std::string o1, std::string o2, std::string o3, std::string o4, std::string o5, std::string o6) {
   order[0] = o1;
   order[1] = o2;
   order[2] = o3;
   order[3] = o4;
   order[4] = o5;
   order[5] = o6;
}

void Skeleton::SetRootAxis(std::string _axis) {
   axis = _axis;
}

void Skeleton::SetRootPosition(float x, float y, float z) {
   p[0] = x;
   p[1] = y;
   p[2] = z;
}

void Skeleton::SetRootOrientation(float o1, float o2, float o3) {
   o[0] = o1;
   o[1] = o2;
   o[2] = o3;
}

int Skeleton::GetId(std::string _name) {
   return boneMap[_name];
}

void Skeleton::AddChildren(int _id, std::vector<int> _children) {
   boneFrame[_id] = _children;
}

std::vector<int> Skeleton::GetChildren(int _id) {
   return boneFrame[_id];
}

BoneInfo *Skeleton::GetBoneInfo(int _id) {
   for(size_t i = 0; i < skeleton.size(); ++i)
      if(skeleton[i]->GetId() == _id)
         return skeleton[i];
   return 0;
}

void Skeleton::ComputeMatrices(void) {
   std::deque<int> q;
   //parse the tree in breadth first manner
   //and update transformation matrices for each bone
   //starting from root
   q.push_back(0);
   while(!q.empty()) {
      int id = q.front();
      q.pop_front();
      std::vector<int> children = GetChildren(id);
      BoneInfo *bi = GetBoneInfo(id);
      gmtl::Vec3f direction = bi->GetDirection();
      float length = bi->GetLength();
      gmtl::Matrix44f t = bi->GetMatrix();
      gmtl::Vec3f trans;
      trans.set(direction[0]*length, direction[1]*length, direction[2]*length);
      gmtl::setTrans(t, trans);
      std::cout << "id: " << id << " length: " << length << " matrix: " << std::endl << t << std::endl;
      std:: cout << "children: ";
      for(size_t i = 0; i < children.size(); ++i) {
         std::cout << children[i] << " ";
         q.push_back(children[i]);
         BoneInfo *b = GetBoneInfo(children[i]);
         b->SetMatrix(t);
      }
      std::cout << std::endl;
   }
}
