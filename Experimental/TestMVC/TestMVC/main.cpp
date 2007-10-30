

#include "Model.h"
#include "View.h"

int main()
{
  Model* model = new Model();

  View* view = new View( model );

  view->render();
}