package Veda;

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

//import javax.swing.DefaultBoundedRangeModel;
import javax.swing.JSlider;
import tweek.*;

import Veda.ITweek;

public class TweekObserverImpl  extends ObserverPOA
{
    public TweekObserverImpl() {
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
