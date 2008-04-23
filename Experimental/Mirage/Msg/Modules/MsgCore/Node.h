
#ifndef __NODE_H__
#define __NODE_H__

#include "MsgCore/Object.h"
#include "MsgCore/StateSet.h"

#include <vector>

namespace Msg
{
	namespace MsgCore
	{		
		class Group;
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
					mStateSet( new StateSet() )
				{

				}

			
				///////////////////////////////////////////////////////////////
				//
				// Copy constructor ( only implementing DEEP_COPY_ALL ). 
				//
				///////////////////////////////////////////////////////////////				
				
        Node( const Node& node ) :
					Object( node ), 
					mParents(), 
					mStateSet( node.mStateSet )
				{}				


				///////////////////////////////////////////////////////////////
				//
				// Get parent with given index. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual Group* getParent( unsigned int index )
				{
					if( index < mParents.size() )
					{
						return mParents[index];
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
				
        virtual Parents getParents()
				{
					return mParents;
				}


				///////////////////////////////////////////////////////////////
				//
				// Add a parent in the list of parents.  
				//
				///////////////////////////////////////////////////////////////				
				
        virtual void addParent( Group* parent )
				{
					mParents.push_back( parent );
				}

				///////////////////////////////////////////////////////////////
				//
				// Get the StateSet object if not create one and return the 
        // newly created StateSet object. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual StateSet* getOrCreateStateSet() 
				{
					if( mStateSet.valid() )
					{
						return mStateSet.get();
					}
					else
					{
            mStateSet = new StateSet();
            return mStateSet.get();
					}
				}


				///////////////////////////////////////////////////////////////
				//
				// Set StateSet for the node. 
        // @Note: It unrefs the last StateSet. 
				//
				///////////////////////////////////////////////////////////////				
				
        virtual void setStateSet( StateSet* stateset )
				{
					if( mStateSet.valid() )
					{
						mStateSet->unref();
						mStateSet = stateset;
					}
					else
					{
						mStateSet = stateset;
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
          if( mStateSet.valid() )
					{
						mStateSet->activateStateSet( this );
					}
        }

        
        ///////////////////////////////////////////////////////////////
				//
				// Deactivate the StateSet on the Node.         
				//
				///////////////////////////////////////////////////////////////				         

        virtual void deActivateStateSet()
        {
          if( mStateSet.valid() )
					{
						mStateSet->deActivateStateSet( this );
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

				Parents					mParents;

		
				///////////////////////////////////////////////////////////////
				//
				// 
				//
				///////////////////////////////////////////////////////////////	

				SmartPtr< StateSet >	mStateSet;
		};
	}
}

#endif // __NODE_H__