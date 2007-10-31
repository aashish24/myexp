
#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

class View;

class Model 
{
  public: 

    Model();

    ~Model();
    
    void addView( const View& view );

    int getData();

    void update();

  private: 
    
    int                 mData;

    std::vector< const View* > mViews;
};

#endif // __MODEL_H__