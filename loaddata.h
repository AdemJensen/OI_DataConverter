bool loadexename(string &temp)
{
	cout<<"程序名:";
	getline(cin,temp);
	temp=nfaspace(temp);
	if(checkexename(temp,true))
	{
		exenameset=true;
		exename=temp;
		return true;
	}
	return false;
}
bool loadfrom(string &temp)
{
	fromset=false;
	from=9999;
	cout<<"文件开始编号:";
	getline(cin,temp);
	temp=nfaspace(temp);
	if(checknum(temp,true))
	{
		fromset=true;
		from=s2i(temp);
		return true;
	}
	return false;
}
bool loadto(string &temp)
{
	toset=false;
	to=0;
	cout<<"文件结束编号:";
	getline(cin,temp);
	temp=nfaspace(temp);
	if(checknum(temp,true))
	{
		toset=true;
		to=s2i(temp);
		return true;
	}
	return false;
}
bool loadinname(string &temp)
{
	innameset=false;
	inname="";
	cout<<"输入文件名:";
	getline(cin,temp);
	temp=nfaspace(temp);
	if(checkrule(temp,true))
	{
		innameset=true;
		inname=temp;
		return true;
	}
	return false;
}
bool loadoutname(string &temp)
{
	outnameset=false;
	outname="";
	cout<<"输出文件名:";
	getline(cin,temp);
	temp=nfaspace(temp);
	if(checkrule(temp,true))
	{
		outnameset=true;
		outname=temp;
		return true;
	}
	return false;
}
