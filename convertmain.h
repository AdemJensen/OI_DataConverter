bool mainconversion(bool show)
{
	if(show) clearall();
	string outfilename;
	string infilename;
	announcedata();
	for(int i=from;i<=to;i++)
	{
		infilename=getfilename(inname,i);
		outfilename=getfilename(outname,i);
		if(show) cout<<"[��Ϣ]����ת��: "<<infilename<<" --> "<<outfilename<<"\r";
		CopyFile(infilename.c_str(),"std.in",false);
		int result=system((exename + " < \"" + infilename + "\" > \"" + outfilename + "\"").c_str());
		if(result!=0)
		{
			if(show) cline();
			if(show) cout<<endl;
			if(show) _err("[����]����"),_err(infilename),_err(" --> "),_err(outfilename),_err("����������:\n");
			if(show) _err("[����]���ṩ�ĳ���������ʱ����!����ֵ:"),_err(result),_err('\n');
			if(show) _err("[����]������ȡ��!�������������\n");
			return false;
		}
		if(show) cline();
	}
	if(show) cline();
	return true;
}
