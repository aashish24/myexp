/**
 * <p>Title: </p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: </p>
 *
 * @author Aashish Chaudhary
 * @version 1.0
 */

package Veda.ITweek;

import java.awt.BorderLayout;

import javax.swing.JPanel;

import javax.swing.*;

import java.awt.*;

import java.awt.event.*;

import javax.swing.event.*;

import org.omg.CORBA.BAD_PARAM;


import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;

import org.omg.CORBA.BAD_PARAM;
import org.vrjuggler.tweek.event.*;
import org.vrjuggler.tweek.net.*;
import org.vrjuggler.tweek.net.corba.*;
import tweek.*;

import Veda.*;

public class TweekTest extends JPanel implements CommunicationListener, ActionListener
{
    /**
     * Sample GUI for tweek observer.
     * Check boxes for selecting which texture to be on.
     * Button to apply texture on the scene.
     * Button to hide the scene.
     */
    private BorderLayout 	borderLayout1 = new BorderLayout(1, 4);
    private TweekObserverImpl 	mTweekObserver = null;
    
    //private FrameListener mFrameListener 	= null;
    
    private JFrame 		mFrame = null;

    private JPanel 		mPanel1	= null;
    private JPanel 		mPanel2	= null;

    private JButton 		mTextureButton = null;
    private JButton 		mHideButton = null;

    private int 		mHide = 0;
    private int 		mTextureOn = 1;

    JButton 			jButton1 = new JButton();
    JComboBox 			jComboBox1 = new JComboBox();
    JSlider 			jSlider1 = new JSlider();
    
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
        //: Numeric variables.
        mHide = 0;

        //this. setLayout(borderLayout1);
        //mPanel = new JPanel();
        //mPanel.setEnabled(true);
        mFrame = new JFrame("TweekDemo");
        Container cn = mFrame.getContentPane();
        cn.setLayout(new BorderLayout(1, 4));

        mPanel1 = new JPanel(new BorderLayout(1, 4));
        mPanel1.setEnabled(true);

        mPanel2 = new JPanel(new BorderLayout(1, 4));
        mPanel2.setEnabled(true);

        mTextureButton = new JButton("Texture OFF");
        mTextureButton.setSize(100, 100);
        mTextureButton.addActionListener(this);

        mHideButton = new JButton("Hide Scene");
        mHideButton.setSize(100, 100);
        mHideButton.addActionListener(this); //mPanel.add(mCheckBox1, BorderLayout.NORTH);
        jButton1.setText("jButton1"); //mPanel.add(mCheckBox2, BorderLayout.NORTH);
        //mPanel.add(mChkBoxButton, BorderLayout.SOUTH);
        //mPanel.add(mButton, BorderLayout.SOUTH);

        //: Panel 1
        mPanel1.add(mTextureButton, BorderLayout.SOUTH);

        //: Panel 2.
        mPanel2.add(mHideButton);

        cn.add(mPanel1, BorderLayout.NORTH);
        cn.add(mPanel2, BorderLayout.SOUTH);
        this.add(jButton1);
        this.add(jComboBox1);
        this.add(jSlider1);
        mFrame.pack();
        mFrame.setVisible(true);

        //mFrameListener = new FrameListener(this);
        //EventListenerRegistry.instance().registerListener(mFrameListener, TweekFrameListener.class);
    }

    public boolean frameClosing()
    {
        System.out.println("frameClosing()");
        disconnect();
        return true;
    }

    private void disconnect() {
        if (mTweekObserver != null) {
            mTweekObserver.detach();
            mTweekObserver = null;
        }
    }

    public void connectionOpened(CommunicationEvent e)
    {
        CorbaService corba_service = e.getCorbaService();
        SubjectManager mgr = corba_service.getSubjectManager();

        Subject subject = mgr.getSubject( "TweekSubject" );
        TweekSubject tSubject = null;

        try
        {
            tSubject = TweekSubjectHelper.narrow( subject );

            if( tSubject != null)
            {
                mTweekObserver = new TweekObserverImpl( tSubject );
                corba_service.registerObject( mTweekObserver, "TweekObserver" );
                tSubject.attach( mTweekObserver._this() );
            }
        }
        catch(BAD_PARAM narrow_ex)
        {
           System.out.println(" [TweekTest] Error narrowing down the subject: ");
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

    
	/*
		public void frameStateChanged (TweekFrameEvent e)
    
		{
      if ( e.getType() == TweekFrameEvent.FRAME_CLOSE )
      {
         disconnect();
      }
    
		}

	*/
    public void actionPerformed(ActionEvent e)
    {
        if(e.getSource() == mHideButton)
        {
            if (mHide == 0)
            {
                mHide = 1;
                if (mTweekObserver != null)
                    mTweekObserver.getSubject().setCommand("Command1", "HIDE" );
                mHideButton.setText("Show");
            }
            else
            {
                mHide = 0;
                if (mTweekObserver != null)
                    mTweekObserver.getSubject().setCommand("Command1", "SHOW");
                mHideButton.setText("Hide");
            }
            System.out.println(mHide);

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

