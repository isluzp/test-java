package net.johnc.thrift;

import org.apache.thrift.TException;

public class TestImp implements Test.Iface{

	@Override
	public void ping(int length) throws TException {
		// TODO Auto-generated method stub
		System.out.println(length);
	}

	@Override
	public boolean test1(String stringName) throws TException {
		// TODO Auto-generated method stub
		System.out.println(stringName);
		return false;
	}

}
