
#ifndef _PATHHANDLER_H_
#define _PATHHANDLER_H_

// boost includes
#include <boost/filesystem/path.hpp>

// std library includes
#include <string>
#include <vector>

namespace bfs = boost::filesystem;

class PathHandler
{
  public:
    
    void addPath(bfs::path const &path);
    bool subPath(bfs::path const &path);
    
    bool findFile(std::string const &name, std::string &pathFoundString) const;
    bool findFile(std::string const &name, bfs::path   &pathFound      ) const;
        
  private:
    typedef std::vector<bfs::path>    PathStore;
        
    PathStore _searchPaths;   
};


#endif // _PATHHANDLER_H_
