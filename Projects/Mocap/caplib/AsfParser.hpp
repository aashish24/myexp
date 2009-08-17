#ifndef MOCAP_ASF_PARSER_H
#define MOCAP_ASF_PARSER_H

#include <string>
#include <fstream>

#include "Skeleton.hpp"

class AsfParser {
private:
   static AsfParser* _instance;
private:
   AsfParser();
   Skeleton *HandleUnits(std::ifstream& in, Skeleton *skel);
   Skeleton *HandleDocumentation(std::ifstream& in, Skeleton *skel);
   Skeleton *HandleRoot(std::ifstream& in, Skeleton *skel);
   Skeleton *HandleBoneData(std::ifstream& in, Skeleton *skel);
   Skeleton *HandleHierarchy(std::ifstream& in, Skeleton *skel);
   Skeleton *ReadSkeleton(std::ifstream& in);
public:
   static AsfParser* GetInstance(void);
   Skeleton *Parse(std::string fileName);
};

#endif
