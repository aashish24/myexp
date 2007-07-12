
package Veda.ITweek;

import javax.swing.JSlider;
import tweek.*;

///////////////////////////////////////////////////////////////////////////////
//
// Implement Observer in the Subject-Observer pattern for Tweek. 
// 
///////////////////////////////////////////////////////////////////////////////

public class TweekObserverImpl  extends ObserverPOA
{
    private TweekSubject mTweekSubject = null;

    ///////////////////////////////////////////////////////////////////////////
    //
    // Constructor. 
    //
    ///////////////////////////////////////////////////////////////////////////

    public TweekObserverImpl() 
    {
        try 
        {            
            jbInit();
        } 
        catch (Exception ex) 
        {
            ex.printStackTrace();
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    // Set subject for this observer. 
    //
    ///////////////////////////////////////////////////////////////////////////

    public TweekObserverImpl( TweekSubject subject )
    {
        mTweekSubject = subject;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    // Get subject. 
    //
    ///////////////////////////////////////////////////////////////////////////

    public TweekSubject getSubject()
    {
        return mTweekSubject;
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    // Update obsever. 
    //
    // @Note: This will be called by the subject to notify attached observers
    //        for any state changes.   
    //
    ///////////////////////////////////////////////////////////////////////////

    public void update()
    {
        System.out.println( "Updated by SUBJECT" );
    }


    ///////////////////////////////////////////////////////////////////////////
    //
    // Detach from the subject. 
    //
    ///////////////////////////////////////////////////////////////////////////

    public void detach()
    {
        mTweekSubject.detach( this._this() );
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    // Initialize any data here. 
    //
    ///////////////////////////////////////////////////////////////////////////

    private void jbInit() throws Exception     
    {
    }
}
