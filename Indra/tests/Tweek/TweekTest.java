
package Veda;

import java.awt.BorderLayout;

import javax.swing.JPanel;

import javax.swing.*;

import java.awt.*;

import java.awt.event.*;

import javax.swing.event.*;

import org.omg.CORBA.BAD_PARAM;

import org.vrjuggler.tweek.event.*;
import org.vrjuggler.tweek.net.*;
import org.vrjuggler.tweek.net.corba.*;

import tweek.*;


//////////////////////////////////////////////////////////////////////////
// 
// Class that provides testing for tweek. 
// 
//////////////////////////////////////////////////////////////////////////

public class TweekTest extends JPanel implements CommunicationListener, ActionListener
{ 
  private BorderLayout 	      borderLayout1 = new BorderLayout( 1, 4 );
  private TweekObserverImpl 	mTweekObserver = null; 
    
  private JFrame 		          mFrame = null;

  private JPanel 		          mPanel1	= null;
  private JPanel 		          mPanel2	= null;

  private JButton 		        mToggleTexturButton = null;
  private JButton 		        mSceneMashButton = null;

  private int 		            mHide = 0;
  private int 		            mShowTexture = 1;  

  public TweekTest() 
  {
    try 
    {
      jbInit();
    } 
    catch (Exception exception) 
    {
      exception.printStackTrace();
    }
  }

  private void jbInit() throws Exception
  {
    // Numeric variables.
    mHide = 0;

    // Create new frame. 
    mFrame = new JFrame( "TweekDemo" );
    
    // Container for this newly created frame.    
    Container cn = mFrame.getContentPane();
    cn.setLayout( new BorderLayout( 1, 4 ) );


    mPanel1 = new JPanel( new BorderLayout( 1, 4 ) );
    mPanel1.setEnabled( true );

    mPanel2 = new JPanel( new BorderLayout( 1, 4 ) );
    mPanel2.setEnabled( true );

    // Adding two buttons for texture and scene hide / show. 
    mToggleTexturButton = new JButton( "Texture OFF" );
    mToggleTexturButton.setSize( 100, 100 );
    mToggleTexturButton.addActionListener( this );

    mSceneMashButton = new JButton( "Hide Scene" );
    mSceneMashButton.setSize( 100, 100 );
    mSceneMashButton.addActionListener( this ); 
        
    mPanel1.add( mToggleTexturButton, BorderLayout.SOUTH );    
    mPanel2.add( mSceneMashButton );

    cn.add( mPanel1, BorderLayout.NORTH );
    cn.add( mPanel2, BorderLayout.SOUTH );
        
    mFrame.pack();
    mFrame.setVisible(true);    
  }

  public boolean frameClosing()
  {
    System.out.println( "frameClosing()" );
    disconnect();

    return true;
  }

  private void disconnect() 
  {
    if ( mTweekObserver != null ) 
    {
      mTweekObserver.detach();
      mTweekObserver = null;
    }
  }

  public void connectionOpened( CommunicationEvent e )
  {
      CorbaService corba_service = e.getCorbaService();
      SubjectManager mgr = corba_service.getSubjectManager();

      Subject subject = mgr.getSubject("TweekSubject");
      TweekSubject tSubject = null;

      try
      {
        tSubject = SubjectHelper.narrow(subject);

        if( tSubject != null)
        {
          mTweekObserver = new TweekObserverImpl( tSubject );
          corba_service.registerObject( mTweekObserver, "TweekObserver" );
          tSubject.attach( TweekObserver._this() );
        }
      }
      catch(BAD_PARAM narrow_ex)
      {
        System.out.println( "Error no: Error narrowing down the subject: ");
      }
  }

  public void connectionClosed(CommunicationEvent e)
  {
    if( mTweekObserver != null )
    {
        mTweekObserver.detach();
        mTweekObserver = null;
    }
  }

  public void actionPerformed(ActionEvent e)
  {
    if(e.getSource() == mSceneMashButton)
    {
      if (mHide == 0)
      {
          mHide = 1;
          if (mTweekObserver != null)
          {
            mTweekObserver.getSubject().setCommand("Command1", "SceneRoot", "", "OFF", true, 0);
          }

          mSceneMashButton.setText("UnHide Scene");
      }
      else
      {
          mHide = 0;
          if (mTweekObserver != null)
          {
            mTweekObserver.getSubject().setCommand("Command1", "SceneRoot", "", "ON", true, 0);
          }
          mSceneMashButton.setText("Hide Scene");
      }
      System.out.println(mHide);

    }
    if( e.getSource() == mToggleTexturButton )
    {       
    }
  }
}


class FrameListener extends TweekFrameAdapter
{
    public FrameListener (TweekTest bean)
    {
      this.mBean = bean;
    }

    public boolean frameClosing(TweekFrameEvent e)
    {
      return true;
    }

    private TweekTest mBean = null;
}

