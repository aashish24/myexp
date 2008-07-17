
#ifndef __MSG_CORE_NODE_H__
#define __MSG_CORE_NODE_H__

#include "MsgCore/Object.h"
#include "MsgCore/StateSet.h"

#include <vector>

namespace Msg
{
	namespace MsgCore
	{		
		class Group;
    class Geode;
		class NodeVisitor;

		class MSG_EXPORT Node : public Object
		{
			public:
				
        // Typedefs. 
				typedef std::vector< Group* > Parents;

				///////////////////////////////////////////////////////////////
				//
				// Constructor. 
				//
				///////////////////////////////////////////////////////////////				
				
        Node() :
					Object(),
					_stateSet( new StateSet() )
				{

				}

			
				///////////////////////////////////////////////////////////////
				//
				// Copy constructor ( only implementing DEEP_COPY_ALL ). 
				//
				///////////////////////////////////////////////////////////////				
				
        Node( const Node& node ) :
					Object( node ), 
					_parents(), 
					_stateSet( node._stateSet )
				{}				


        ///////////////////////////////////////////////////////////////
				//
				// 
				//
				///////////////////////////////////////////////////////////////				
        
        virtual Group* asGroup(); 


        ///////////////////////////////////////////////////////////////
				//
				// 
				//
				///////////////////////////////////////////////////////////////				
        
        virtual Geode* asGeode();


				///////////////////////////////////////////////////////////////
				//
				// Get parent with given index. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual Group* parent( unsigned int index )
				{
					if( index < _parents.size() )
					{
						return _parents[index];
					}
					else
					{
						return 0x00;
					}
				}


				///////////////////////////////////////////////////////////////
				//
				// Get array of parents. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual Parents parents()
				{
					return _parents;
				}


				///////////////////////////////////////////////////////////////
				//
				// Add a parent in the list of parents.  
				//
				///////////////////////////////////////////////////////////////				
				
        virtual void addParent( Group* parent )
				{
					_parents.push_back( parent );
				}

				///////////////////////////////////////////////////////////////
				//
				// Get the StateSet object if not create one and return the 
        // newly created StateSet object. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual StateSet* getOrCreateStateSet() 
				{
					if( _stateSet.valid() )
					{
						return _stateSet.get();
					}
					else
					{
            _stateSet = new StateSet();
            return _stateSet.get();
					}
				}


				///////////////////////////////////////////////////////////////
				//
				// Set StateSet for the node. 
        // @Note: It unrefs the last StateSet. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual void stateSet( StateSet* stateset )
				{
					if( _stateSet.valid() )
					{
						_stateSet->unref();
						_stateSet = stateset;
					}
					else
					{
						_stateSet = stateset;
					}
				}


         
				///////////////////////////////////////////////////////////////
				//
				// Activate the StateSet on the Node. 
        // @Note:
        // We are missing the case of over-riding the parent state sets. 
				//
				///////////////////////////////////////////////////////////////				 

        virtual void activateStateSet()
        {
          if( _stateSet.valid() )
					{
						_stateSet->activateStateSet( this );
					}
        }

        
        ///////////////////////////////////////////////////////////////
				//
				// Deactivate the StateSet on the Node.         
				//
				///////////////////////////////////////////////////////////////				         

        virtual void deActivateStateSet()
        {
          if( _stateSet.valid() )
					{
						_stateSet->deActivateStateSet( this );
					}
        }
        
        
				///////////////////////////////////////////////////////////////
				//
				// Start update and draw traversal. 
				//
				///////////////////////////////////////////////////////////////
				
        virtual void accept( NodeVisitor& nv );

			
				///////////////////////////////////////////////////////////////
				//
				// Traverse the scene with given NodeVisitor. 
        // @Note: 
        // Only Group nodes can call activeStateSet. 
				//
				///////////////////////////////////////////////////////////////
				
        virtual void traverse( NodeVisitor& nv ) 
				{	
				}


			protected:
				
        ///////////////////////////////////////////////////////////////
				//
				// Destructor. 
				//
				///////////////////////////////////////////////////////////////	

				virtual ~Node()
				{ 
        }


			protected:

				///////////////////////////////////////////////////////////////
				//
				// 
				//
				///////////////////////////////////////////////////////////////		

				Parents					      _parents;

		
				///////////////////////////////////////////////////////////////
				//
				// 
				//
				///////////////////////////////////////////////////////////////	

				SmartPtr< StateSet >	_stateSet;
		};
	}
}

#endif // __MSG_CORE_NODE_H__
