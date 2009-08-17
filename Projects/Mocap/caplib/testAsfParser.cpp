#include <iostream>
#include "AsfParser.hpp"
#include "Skeleton.hpp"

int main(int argc, char **argv) {
   AsfParser *parser = AsfParser::GetInstance();
   std::cout << "Parser created" << std::endl;
   Skeleton *skel = parser->Parse("02.asf");
   delete skel;
}
