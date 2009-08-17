#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

#include "Skeleton.hpp"
#include "AsfParser.hpp"

AsfParser *AsfParser::_instance = 0;

AsfParser *AsfParser::GetInstance(void) {
   if(_instance == 0)
      _instance = new AsfParser();

   return _instance;
}

AsfParser::AsfParser(){}

Skeleton *AsfParser::Parse(std::string fileName) {
   std::ifstream inf;
   inf.open(fileName.c_str());
   if(inf.is_open()) {
      std::cout << "File opened: ready to read now." << std::endl;
      Skeleton *skel = ReadSkeleton(inf);
      inf.close();
      skel->ComputeMatrices();
      return skel;
   }
   else
      return 0;
}

Skeleton *AsfParser::ReadSkeleton(std::ifstream& in) {
   Skeleton *skel = new Skeleton();
   std::string line;
   while(!in.eof()) {
      getline(in, line);
      //ignoring the comments
//      std::cout << "LINE: " << line << std::endl;
      if(line[0] != '#'){
         if(line[0] == ':') {
            line = line.erase(0, 1);
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;
            if(keyword == "version") {
               std::string version;
               iss >> version;
               skel->SetVersion(version);
            }
            else if(keyword == "name") {
               std::string name;
               iss >> name;
               skel->SetName(name);
            }
            else if(keyword == "units") {
               skel = HandleUnits(in, skel);
            }
            else if(keyword == "documentation") {
               skel = HandleDocumentation(in, skel);
            }
            else if(keyword == "root") {
               skel = HandleRoot(in, skel);
            }
            else if(keyword == "bonedata") {
               skel = HandleBoneData(in, skel);
            }
            else if(keyword == "hierarchy") {
               skel = HandleHierarchy(in, skel);
            }
            else {
               std::cout << "Unknown keyword: " << keyword << std::endl;
            }
         }
      }
   }
   return skel;
}

Skeleton *AsfParser::HandleUnits(std::ifstream& in, Skeleton *skel) {
   std::string line;
   std::string keyword;

   while(!in.eof() && in.peek() != ':') {
      getline(in, line);
      std::istringstream iss(line);
      iss >> keyword;
      if(keyword == "mass") {
         float mass;
         iss >> mass;
         skel->SetMass(mass);
      }
      else if(keyword == "length") {
         float length;
         iss >> length;
         skel->SetLength(length);
      }
      else if(keyword == "angle") {
         std::string angle;
         iss >> angle;
         skel->SetAngle(angle);
      }
      else {
         std::cout << "Unknown value for units" << std::endl;
      }
   }
   return skel;
}

Skeleton *AsfParser::HandleDocumentation(std::ifstream& in, Skeleton *skel) {
   std::string line;
   std::string doc;
   while(!in.eof() && in.peek() != ':') {
      getline(in, line);
      doc += line;
   }
   skel->SetDocumentation(doc);
   return skel;
}

Skeleton *AsfParser::HandleRoot(std::ifstream& in, Skeleton *skel) {
   std::string line;
   BoneInfo *bi = new BoneInfo();
   bi->SetName("root");
   while(!in.eof() && in.peek() != ':') {
      getline(in, line);
      std::istringstream iss(line);
      std::string keyword;
      iss >> keyword;
      if(keyword == "order") {
         std::string order[6];
         iss >> order[0] >> order[1] >> order[2] >> order[3] >> order[4] >> order[5];
         skel->SetRootOrder(order[0], order[1], order[2], order[3], order[4], order[5]);
      }
      else if(keyword == "axis") {
         std::string axis;
         iss >> axis;
         bi->SetAxis(0.0, 0.0, 0.0, axis);
         skel->SetRootAxis(axis);
      }
      else if(keyword == "position") {
         float pos[3];
         iss >> pos[0] >> pos[1] >> pos[2];
         skel->SetRootPosition(pos[0], pos[1], pos[2]);
      }
      else if(keyword == "orientation") {
         float orientation[3];
         iss >> orientation[0] >> orientation[1] >> orientation[2];
         skel->SetRootOrientation(orientation[0], orientation[1], orientation[2]);
      }
      else {
         std::cout << "Unknown keyword in root: " << keyword << std::endl;
      }
   }
   bi->SetLength(0.0);
   bi->SetDirection(0, 0, 0);
   skel->AddBone(bi);
   return skel;
}

Skeleton *AsfParser::HandleBoneData(std::ifstream& in, Skeleton *skel) {
   std::string line;
   BoneInfo *bi;
   while(!in.eof() && in.peek() != ':') {
      getline(in, line);
      std::istringstream iss(line);
      std::string keyword;
      iss >> keyword;
//      std::cout << "Keyword: " << keyword << std::endl;
      if(keyword == "begin") {
         bi = new BoneInfo();
      }
      else if(keyword == "id") {
         int id;
         iss >> id;
         bi->SetId(id);
      }
      else if(keyword == "name") {
         std::string name;
         iss >> name;
         bi->SetName(name);
      }
      else if(keyword == "direction") {
         float x, y, z;
         iss >> x >> y >> z;
         bi->SetDirection(x, y, z);
      }
      else if(keyword == "length") {
         float length;
         iss >> length;
         bi->SetLength(length);
      }
      else if(keyword == "axis") {
         float x, y, z;
         std::string rotString;
         iss >> x >> y >> z >> rotString;
         bi->SetAxis(x, y, z, rotString);
      }
      else if(keyword == "dof") {
         std::vector<std::string> dof;
         dof.resize(0);
         while(!iss.eof()) {
            std::string axis;
            iss >> axis;
//            std::cout << "axis: " << axis << std::endl;
            if(axis.size() != 0)
               dof.push_back(axis);
//            bi->AddDof(axis);
         }
         bi->SetDof(dof);
      }
      else if(keyword == "limits") {
         int nLimits = bi->GetDof();
//         std::cout << "nLimits: " << nLimits << std::endl;
         iss.ignore(256, '(');
         std::pair<float, float> limit;
         iss >> limit.first >> limit.second;
//         std::cout << "Limit: " << limit.first << " " << limit.second  << std::endl;
         bi->AddLimit(limit);
         for(int i = 1; i < nLimits; ++i) {
            std::string limitLine;
            getline(in, limitLine);
            std::istringstream limitiss(limitLine);
            limitiss.ignore(256, '(');
            limitiss>>limit.first >> limit.second;
//            std::cout << "Limit: " << limit.first << " " << limit.second  << std::endl;
            bi->AddLimit(limit);
         }
      }
      else if(keyword == "end") {
//         std::cout << "Name: " << bi->GetName() << " Id: " << bi->GetId() << std::endl;
         skel->AddBone(bi);
      }
      else {
         std::cout << "Unknown keyword: " << keyword << std::endl;
      }
   }
   return skel;
}

Skeleton *AsfParser::HandleHierarchy(std::ifstream& in, Skeleton *skel) {
   std::string line;
   while(!in.eof() && in.peek() != ':') {
      getline(in, line);
      std::istringstream iss(line);
      std::string keyword;
      iss >> keyword;
      if(keyword == "begin") {
         ;
      }
      else if(keyword == "end"){
         ;
      }
      else {
         int id = skel->GetId(keyword);
         std::vector<int> adjList;
         std::cout << keyword << " (" << id << ") ";
         while(!iss.eof()) {
            std::string child;
            iss >> child;
            if(child.size() > 0) {
               int childId = skel->GetId(child);
               adjList.push_back(childId);
               std::cout << child << " (" << childId << ") ";
            }
         }
         std::cout << std::endl;
         skel->AddChildren(id, adjList);
      }
   }
   return skel;
}
