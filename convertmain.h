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
		if(show) cout<<"[信息]正在转换: "<<infilename<<" --> "<<outfilename<<"\r";
		CopyFile(infilename.c_str(),"std.in",false);
		int result=system((exename + " < \"" + infilename + "\" > \"" + outfilename + "\"").c_str());
		if(result!=0)
		{
			if(show) cline();
			if(show) cout<<endl;
			if(show) _err("[错误]进行"),_err(infilename),_err(" --> "),_err(outfilename),_err("操作过程中:\n");
			if(show) _err("[错误]您提供的程序在运行时错误!返回值:"),_err(result),_err('\n');
			if(show) _err("[错误]进程已取消!按任意键继续。\n");
			return false;
		}
		if(show) cline();
	}
	if(show) cline();
	return true;
}
