package dt;

/**
 *	Generated from IDL interface "DtSubject"
 *	@author JacORB IDL compiler V 2.1, 16-Feb-2004
 */

public final class DtSubjectHolder	implements org.omg.CORBA.portable.Streamable{
	 public DtSubject value;
	public DtSubjectHolder()
	{
	}
	public DtSubjectHolder (final DtSubject initial)
	{
		value = initial;
	}
	public org.omg.CORBA.TypeCode _type()
	{
		return DtSubjectHelper.type();
	}
	public void _read (final org.omg.CORBA.portable.InputStream in)
	{
		value = DtSubjectHelper.read (in);
	}
	public void _write (final org.omg.CORBA.portable.OutputStream _out)
	{
		DtSubjectHelper.write (_out,value);
	}
}
