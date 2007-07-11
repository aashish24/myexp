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

public class DtObserverImpl extends ObserverPOA
{
    public DtObserverImpl() {
        try {
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    public DtObserverImpl(DtSubject subject)
    {
        mDtSubject = subject;
    }

    public DtSubject getSubject()
    {
        return mDtSubject;
    }

    public void update()
    {
        System.out.println(" [DtObserverImpl] Update from our subject: ");
        System.out.println(" [DtObserverImpl] Update processed: ");
    }

    public void detach()
    {
        mDtSubject.detach(this._this());
    }

    private DtSubject mDtSubject = null;
    private void jbInit() throws Exception {
    }
}
