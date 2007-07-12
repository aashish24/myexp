
package Veda.ITweek;

import javax.swing.JSlider;
import tweek.*;

public class TweekObserverImpl  extends ObserverPOA
{
    public TweekObserverImpl() 
    {
        try {
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public TweekObserverImpl(TweekSubject subject)
    {
        mTweekSubject = subject;
    }

    public TweekSubject getSubject()
    {
        return mTweekSubject;
    }

    public void update()
    {
        System.out.println( "Updated by SUBJECT" );
    }

    public void detach()
    {
        mTweekSubject.detach(this._this());
    }

    private TweekSubject mTweekSubject = null;
    private void jbInit() throws Exception {
    }
}
