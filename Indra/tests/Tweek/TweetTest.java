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

package dt;

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

public class DtTweek extends JPanel implements CommunicationListener, ActionListener
{
    /**
     * Sample GUI for tweek observer.
     * Check boxes for selecting which texture to be on.
     * Button to apply texture on the scene.
     * Button to hide the scene.
     */
    private BorderLayout borderLayout1 = new BorderLayout(1, 4);
    private DtObserverImpl mDtObserver = null;
    //private FrameListener mFrameListener = null;
    private JFrame mFrame = null;

    private JPanel mPanel1 = null;
    private JPanel mPanel2 = null;

    private JButton mTextureButton = null;
    private JButton mHideButton = null;

    private int mHide = 0;
    private int mTextureOn = 1;
    JButton jButton1 = new JButton();
    JComboBox jComboBox1 = new JComboBox();
    JSlider jSlider1 = new JSlider();
    public DtTweek() {
        try {
            jbInit();
        } catch (Exception exception) {
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
        if (mDtObserver != null) {
            mDtObserver.detach();
            mDtObserver = null;
        }
    }

    public void connectionOpened(CommunicationEvent e)
    {
        CorbaService corba_service = e.getCorbaService();
        SubjectManager mgr = corba_service.getSubjectManager();

        Subject subject = mgr.getSubject("DtSubject");
        DtSubject dt_subject = null;

        try
        {
            dt_subject = DtSubjectHelper.narrow(subject);

            if(dt_subject != null)
            {
                mDtObserver = new DtObserverImpl(dt_subject);
                corba_service.registerObject(mDtObserver, "DtObserver");
                dt_subject.attach(mDtObserver._this());
            }
        }
        catch(BAD_PARAM narrow_ex)
        {
           System.out.println(" [DtTweek] Error narrowing down the subject: ");
        }
    }

    public void connectionClosed(CommunicationEvent e)
    {
        if(mDtObserver != null)
        {
            mDtObserver.detach();
            mDtObserver = null;
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
                if (mDtObserver != null)
                    mDtObserver.getSubject().setCommand("Command1", "SceneRoot", "", "OFF", true, 0);
                mHideButton.setText("UnHide Scene");
            }
            else
            {
                mHide = 0;
                if (mDtObserver != null)
                    mDtObserver.getSubject().setCommand("Command1", "SceneRoot", "", "ON", true, 0);
                mHideButton.setText("Hide Scene");
            }
            System.out.println(mHide);

        }
        if(e.getSource() == mTextureButton)
        {
           if(mTextureOn == 1)
           {
                mTextureOn = 0;
                if (mDtObserver != null)
                    mDtObserver.getSubject().setCommand("Command2", "Cow", "TextureUnit0", "OFF", true, 0);
                mTextureButton.setText("Texture ON");
            }
            else
            {
                mTextureOn = 1;
                if (mDtObserver != null)
                    mDtObserver.getSubject().setCommand("Command2", "Cow", "TextureUnit0", "ON", true, 0);
                mTextureButton.setText("Texture OFF");
            }
                System.out.println(mTextureOn);
        }
    }
}


class FrameListener extends TweekFrameAdapter
{
    public FrameListener (DtTweek bean)
    {
        this.mBean = bean;
    }

    public boolean frameClosing(TweekFrameEvent e)
    {
        return true;
    }

    private DtTweek mBean = null;
}

