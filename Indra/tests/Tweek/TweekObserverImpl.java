package dt;

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

public class TweekObserverImpl.java extends ObserverPOA
{
    public TweekObserverImpl.java() {
        try {
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public TweekObserverImpl.java(TweekSubject subject)
    {
        mTweekSubject = subject;
    }

    public TweekSubject getSubject()
    {
        return mTweekSubject;
    }

    public void update()
    {
        System.out.println(" [TweekObserverImpl.java] Update from our subject: ");
        System.out.println(" [TweekObserverImpl.java] Update processed: ");
    }

    public void detach()
    {
        mTweekSubject.detach(this._this());
    }

    private TweekSubject mTweekSubject = null;
    private void jbInit() throws Exception {
    }
}
