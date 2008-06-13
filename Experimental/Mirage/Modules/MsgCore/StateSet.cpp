
#include "MsgCore/StateSet.h"
#include "MsgCore/Node.h"
#include "MsgCore/Group.h"

#include <list>

namespace Msg
{
	namespace MsgCore
	{		
    StateSet::StateSet() : 
					Object(), 
          _dirty( true )
		{
		}


    StateSet::StateSet( const StateSet& stateset ) :
			Object( stateset ), 
      _dirty( stateset.dirty() )
		{
		}	


    StateSet::~StateSet()
	  {
	  }
      

    bool StateSet::dirty() const 
    {
      return _dirty;
    }


    void StateSet::dirty( bool flag ) 
    {
      _dirty = flag;
    }

    
    void StateSet::attribute( const std::string& id )
    {
    }


    StateSet::Attributes& StateSet::attributes()
    {
      return _attributes;
    }


    void StateSet::attribute( StateAttribute* attr, const bool& state )
    { 
      if( !attr )
      {
        return;
      }

      Attributes::iterator itr = _attributes.begin();
      
      for( itr; itr != _attributes.end(); ++itr )
      {
        if( itr->first->id() == attr->id() )
        {
          _attributes.erase( itr );
          break;
        }
      }

      this->dirty( true );
      _attributes.push_back( std::make_pair< SmartPtr< StateAttribute >, bool >( attr, state ) );
    }


    StateSet::TextureAttributes& StateSet::textureAttributes()
    {
      return _textureAttributes;
    }


    void StateSet::textureAttribute( unsigned int unit, StateAttribute* attr, const bool& state )
    {
      // Need to implement this. 
    }


    void StateSet::activateStateSet( Node* node )
		{	
      if( node->getOrCreateStateSet()->dirty() )
      {
        // Loop thru all the parents attributes here. 
        Msg::MsgCore::Node::Parents parents = node->parents();
        StateSet::Attributes::iterator start, end;
        StateSet::TextureAttributes::iterator tStart, tEnd;

        for( size_t i = 0; i < parents.size(); ++i )
        { 
          Attributes attr = parents[i]->getOrCreateStateSet()->attributes();
          start = attr.begin();       
          end = attr.end();

          for( start; start != end; ++start )
          {
            //start->first->activateStateSet( node );
            this->attribute( start->first.get(), start->second );
          }

          TextureAttributes tAttr = parents[i]->getOrCreateStateSet()->textureAttributes();
          tStart = tAttr.begin();
          tEnd = tAttr.end();

          // @Todo: Need to fix this. 
          /*for( tStart; tStart != tEnd; ++tStart )
          {            
            tStart->second.first->activateStateSet( node );
            this->textureAttribute( _textureAttributes
          }*/          
        }

        node->getOrCreateStateSet()->dirty( false );
      }
      
      StateSet::Attributes::iterator start, end;
      StateSet::TextureAttributes::iterator tStart, tEnd;
        
      // First iterate thru all the attributes but texture attributes. 
      start = _attributes.begin();
      end = _attributes.end();
      for( start; start != end; ++start )
      {
        start->first->activate( node );
      }
      
      // @Todo: Need to fix this. 
      // Now iterate thru all the texture attributes. 
      /*tStart = _textureAttributes.begin();
      tEnd = _textureAttributes.end();
      for( tStart; tStart != tEnd; ++tStart )
      {
        tStart->second.first->activateStateSet( node );
      }*/
    }


    void StateSet::deActivateStateSet( Node* node )
    {
      StateSet::Attributes::iterator start, end;
      start = _attributes.begin();
      end = _attributes.end();
      for( start; start != end; ++start )
      {
        start->first->deActivate( node );
      }
    }

	}
}
