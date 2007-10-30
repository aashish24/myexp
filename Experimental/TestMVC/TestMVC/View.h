
#include <iostream> 

class Model;

class View
{
  public: 
    View( Model* model ) : 
        mModel( model )
    {      
      mModel->addView( *this );
    }
  
    void update() const
    {

    }

    void render()
    {
      std::cout << "Render" << std::endl;
    }

  private: 
    Model* mModel;
};