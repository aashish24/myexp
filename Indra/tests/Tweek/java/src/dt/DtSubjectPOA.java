package dt;

/**
 *	Generated from IDL interface "DtSubject"
 *	@author JacORB IDL compiler V 2.1, 16-Feb-2004
 */


public abstract class DtSubjectPOA
	extends org.omg.PortableServer.Servant
	implements org.omg.CORBA.portable.InvokeHandler, dt.DtSubjectOperations
{
	static private final java.util.Hashtable m_opsHash = new java.util.Hashtable();
	static
	{
		m_opsHash.put ( "setCommand", new java.lang.Integer(0));
		m_opsHash.put ( "notify", new java.lang.Integer(1));
		m_opsHash.put ( "detach", new java.lang.Integer(2));
		m_opsHash.put ( "attach", new java.lang.Integer(3));
	}
	private String[] ids = {"IDL:dt/DtSubject:1.0","IDL:tweek/Subject:1.0"};
	public dt.DtSubject _this()
	{
		return dt.DtSubjectHelper.narrow(_this_object());
	}
	public dt.DtSubject _this(org.omg.CORBA.ORB orb)
	{
		return dt.DtSubjectHelper.narrow(_this_object(orb));
	}
	public org.omg.CORBA.portable.OutputStream _invoke(String method, org.omg.CORBA.portable.InputStream _input, org.omg.CORBA.portable.ResponseHandler handler)
		throws org.omg.CORBA.SystemException
	{
		org.omg.CORBA.portable.OutputStream _out = null;
		// do something
		// quick lookup of operation
		java.lang.Integer opsIndex = (java.lang.Integer)m_opsHash.get ( method );
		if ( null == opsIndex )
			throw new org.omg.CORBA.BAD_OPERATION(method + " not found");
		switch ( opsIndex.intValue() )
		{
			case 0: // setCommand
			{
				java.lang.String _arg0=_input.read_string();
				java.lang.String _arg1=_input.read_string();
				java.lang.String _arg2=_input.read_string();
				java.lang.String _arg3=_input.read_string();
				boolean _arg4=_input.read_boolean();
				int _arg5=_input.read_long();
				_out = handler.createReply();
				setCommand(_arg0,_arg1,_arg2,_arg3,_arg4,_arg5);
				break;
			}
			case 1: // notify
			{
				_out = handler.createReply();
				_notify();
				break;
			}
			case 2: // detach
			{
				tweek.Observer _arg0=tweek.ObserverHelper.read(_input);
				_out = handler.createReply();
				detach(_arg0);
				break;
			}
			case 3: // attach
			{
				tweek.Observer _arg0=tweek.ObserverHelper.read(_input);
				_out = handler.createReply();
				attach(_arg0);
				break;
			}
		}
		return _out;
	}

	public String[] _all_interfaces(org.omg.PortableServer.POA poa, byte[] obj_id)
	{
		return ids;
	}
}
