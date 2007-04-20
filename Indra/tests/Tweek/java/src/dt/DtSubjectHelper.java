package dt;


/**
 *	Generated from IDL interface "DtSubject"
 *	@author JacORB IDL compiler V 2.1, 16-Feb-2004
 */

public final class DtSubjectHelper
{
	public static void insert (final org.omg.CORBA.Any any, final dt.DtSubject s)
	{
			any.insert_Object(s);
	}
	public static dt.DtSubject extract(final org.omg.CORBA.Any any)
	{
		return narrow(any.extract_Object()) ;
	}
	public static org.omg.CORBA.TypeCode type()
	{
		return org.omg.CORBA.ORB.init().create_interface_tc("IDL:dt/DtSubject:1.0", "DtSubject");
	}
	public static String id()
	{
		return "IDL:dt/DtSubject:1.0";
	}
	public static DtSubject read(final org.omg.CORBA.portable.InputStream in)
	{
		return narrow(in.read_Object());
	}
	public static void write(final org.omg.CORBA.portable.OutputStream _out, final dt.DtSubject s)
	{
		_out.write_Object(s);
	}
	public static dt.DtSubject narrow(final java.lang.Object obj)
	{
		if (obj instanceof dt.DtSubject)
		{
			return (dt.DtSubject)obj;
		}
		else if (obj instanceof org.omg.CORBA.Object)
		{
			return narrow((org.omg.CORBA.Object)obj);
		}
		throw new org.omg.CORBA.BAD_PARAM("Failed to narrow in helper");
	}
	public static dt.DtSubject narrow(final org.omg.CORBA.Object obj)
	{
		if (obj == null)
			return null;
		try
		{
			return (dt.DtSubject)obj;
		}
		catch (ClassCastException c)
		{
			if (obj._is_a("IDL:dt/DtSubject:1.0"))
			{
				dt._DtSubjectStub stub;
				stub = new dt._DtSubjectStub();
				stub._set_delegate(((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate());
				return stub;
			}
		}
		throw new org.omg.CORBA.BAD_PARAM("Narrow failed");
	}
	public static dt.DtSubject unchecked_narrow(final org.omg.CORBA.Object obj)
	{
		if (obj == null)
			return null;
		try
		{
			return (dt.DtSubject)obj;
		}
		catch (ClassCastException c)
		{
				dt._DtSubjectStub stub;
				stub = new dt._DtSubjectStub();
				stub._set_delegate(((org.omg.CORBA.portable.ObjectImpl)obj)._get_delegate());
				return stub;
		}
	}
}
