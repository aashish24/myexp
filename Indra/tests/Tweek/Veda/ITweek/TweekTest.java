
package Veda.ITweek;

import java.awt.BorderLayout;
import java.awt.*;
import java.awt.event.*;

import javax.swing.JPanel;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;

import org.omg.CORBA.BAD_PARAM;

import org.vrjuggler.tweek.event.*;
import org.vrjuggler.tweek.net.*;
import org.vrjuggler.tweek.net.corba.*;
import tweek.*;

import Veda.*;

///////////////////////////////////////////////////////////////////////////////
//
// Implements a simple GUI for demo purpose. 
// 
///////////////////////////////////////////////////////////////////////////////

public class TweekTest extends JPanel implements CommunicationListener, ActionListener
{
    
  private BorderLayout 	      borderLayout1 = new BorderLayout(1, 4);
  private TweekObserverImpl 	mTweekObserver = null;   


  private JFrame 		          mFrame = null;

  private JPanel 		          mPanel1	= null;
  private JPanel 		          mPanel2	= null;

  private JButton 		        mToggleTextureBtn = null;
  private JButton 		        mToggleSceneBtn = null;

  private int 		            mHide = 0;
  private int 		            mTextureOn = 1;

  ///////////////////////////////////////////////////////////////////////////
  //
  // Constructor. 
  //
  ///////////////////////////////////////////////////////////////////////////

  public TweekTest() 
  {
    try 
    {
      jbInit();
    } 
    catch ( Exception exception ) 
    {
      exception.printStackTrace();
    }
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Initialize. 
  //
  ///////////////////////////////////////////////////////////////////////////

  private void jbInit() throws Exception
  {
    mHide = 0;        
    mFrame = new JFrame( "TweekDemo" );

    Container cn = mFrame.getContentPane();
    cn.setLayout(new BorderLayout(1, 4));

    mPanel1 = new JPanel( new BorderLayout( 1, 4 ) );
    mPanel1.setEnabled( true );

    mPanel2 = new JPanel( new BorderLayout( 1, 4 ) );
    mPanel2.setEnabled( true );

    mToggleTextureBtn = new JButton( "Toggle Texture" );
    mToggleTextureBtn.setSize( 100, 100 );
    mToggleTextureBtn.addActionListener( this );

    mToggleSceneBtn = new JButton( "Toggle Scene" );
    mToggleSceneBtn.setSize( 100, 100 );
    mToggleSceneBtn.addActionListener( this ); 
    
    mPanel1.add( mToggleTextureBtn, BorderLayout.SOUTH );        
    mPanel2.add( mToggleSceneBtn );

    cn.add( mPanel1, BorderLayout.NORTH );
    cn.add( mPanel2, BorderLayout.SOUTH );
    
    mFrame.pack();
    mFrame.setVisible(true);        
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Perform any operations here before exit. 
  //
  ///////////////////////////////////////////////////////////////////////////
  
  public boolean frameClosing()
  {
    System.out.println( "Exiting......" );
    disconnect();
    
    return true;
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Disconnect and detach from our subject. 
  //
  ///////////////////////////////////////////////////////////////////////////

  private void disconnect() 
  {
    if ( mTweekObserver != null ) 
    {
      mTweekObserver.detach();
      mTweekObserver = null;
    }
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Open a new connection. 
  //
  ///////////////////////////////////////////////////////////////////////////

  public void connectionOpened( CommunicationEvent e )
  {
    TweekSubject tSubject = null;

    CorbaService corba_service = e.getCorbaService();
    SubjectManager mgr = corba_service.getSubjectManager();
    Subject subject = mgr.getSubject( "TweekSubject" );

    try
    {
      tSubject = TweekSubjectHelper.narrow( subject );

      if( tSubject != null )
      {
        mTweekObserver = new TweekObserverImpl( tSubject );
        corba_service.registerObject( mTweekObserver, "TweekObserver" );
        tSubject.attach( mTweekObserver._this() );
      }
    }
    catch( BAD_PARAM narrow_ex )
    {
      System.out.println( "Error no: Error narrowing down the subject: ") ;
    }
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Close existing connection. 
  //
  ///////////////////////////////////////////////////////////////////////////

  public void connectionClosed( CommunicationEvent e )
  {
    if( mTweekObserver != null )
    {
      mTweekObserver.detach();
      mTweekObserver = null;
    }
  }


  ///////////////////////////////////////////////////////////////////////////
  //
  // Take action based on the source of the event. 
  //
  ///////////////////////////////////////////////////////////////////////////

  public void actionPerformed( ActionEvent e )
  {
    if( e.getSource() == mToggleSceneBtn )
    {
      if( mHide == 0 )
      {
        mHide = 1;

        if (mTweekObserver != null)
        {
          mTweekObserver.getSubject().setCommand( "Command1", "HIDE" );
        }
        
        mToggleSceneBtn.setText( "Show" );
      }
      else
      {
        mHide = 0;
        if (mTweekObserver != null)
        {
          mTweekObserver.getSubject().setCommand( "Command1", "SHOW" );
        }
        mToggleSceneBtn.setText( "Hide" );
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////
//
// 
//
///////////////////////////////////////////////////////////////////////////

class FrameListener extends TweekFrameAdapter
{
  public FrameListener ( TweekTest bean )
  {
      this.mBean = bean;
  }

  public boolean frameClosing( TweekFrameEvent e )
  {
      return true;
  }

  private TweekTest mBean = null;
}

