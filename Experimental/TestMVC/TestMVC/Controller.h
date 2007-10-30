
// Type of event
// Source is mother of all the objects that are capable of generating an event. 
class Event
{
  public:
    Event( Source* src )
    {
    }

    Source* getSource()
    {
      returm mSrc;
    }

  private: 
      Source* mSrc;
};

// Still need to think about this class. Why we need this and if we do how we should design this. 
class DigitalInputChangeEvent : public Event
{
  public: 
    DigitalInputChangeEvent( Source* src ) : Event( src )
    {
    }
};


// How we couple the event with the delegator??

// Delegate the event and the source of the event to the handlers. 
class Delegator
{
  public: 
    Delegator()
    {
    }
    void addEventHandler( EventHandler* )
    {
    }
};


// Event handler has to know the source of the event. As what we are going to do is 
// attach a  funtion with the generator of the event so that we can get handle to that function. s 

// I may have to visit the functor tutorials again. May be what we will do is each item would have atleast one delegator and 
// one event handler that would be in the list. And that event handler would execute the function. 

// Knowing the source of the event start the process of handling the event. 
class EventHandler
{
  public: 
    EventHandler( Delegator* dtr )
    {
      dtr->addEventHandler( this );
    }
};



