package dt;

import org.omg.PortableServer.POA;

/**
 *	Generated from IDL interface "DtSubject"
 *	@author JacORB IDL compiler V 2.1, 16-Feb-2004
 */

public class DtSubjectPOATie
	extends DtSubjectPOA
{
	private DtSubjectOperations _delegate;

	private POA _poa;
	public DtSubjectPOATie(DtSubjectOperations delegate)
	{
		_delegate = delegate;
	}
	public DtSubjectPOATie(DtSubjectOperations delegate, POA poa)
	{
		_delegate = delegate;
		_poa = poa;
	}
	public dt.DtSubject _this()
	{
		return dt.DtSubjectHelper.narrow(_this_object());
	}
	public dt.DtSubject _this(org.omg.CORBA.ORB orb)
	{
		return dt.DtSubjectHelper.narrow(_this_object(orb));
	}
	public DtSubjectOperations _delegate()
	{
		return _delegate;
	}
	public void _delegate(DtSubjectOperations delegate)
	{
		_delegate = delegate;
	}
	public POA _default_POA()
	{
		if (_poa != null)
		{
			return _poa;
		}
		else
		{
			return super._default_POA();
		}
	}
	public void setCommand(java.lang.String identifier, java.lang.String entity, java.lang.String state_attribute, java.lang.String modifier_string, boolean modifier_boolean, int modifier_long)
	{
_delegate.setCommand(identifier,entity,state_attribute,modifier_string,modifier_boolean,modifier_long);
	}

	public void _notify()
	{
_delegate._notify();
	}

	public void detach(tweek.Observer o)
	{
_delegate.detach(o);
	}

	public void attach(tweek.Observer o)
	{
_delegate.attach(o);
	}

}
