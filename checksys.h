bool checkexename(string s,bool show)
{
	if(show) cout<<"[信息]正在检查exe合法性...";
	int len=s.size();
	if(s[len-4]!='.'||s[len-3]!='e'||s[len-2]!='x'||s[len-1]!='e')
	{
		cline();
		if(show) _err("[错误]指定的文件不是exe文件!\n");
		return false;
	}
	if(!exist(s))
	{
		cline();
		if(show) _err("[错误]无法找到指定exe文件!\n");
		return false;
	}
	if(s==currentexe)
	{
		cline();
		if(show) _err("[错误]不能指定转换器为目标exe程序!\n");
		return false;
	} 
	
	cline();
	return true;
}

bool checkrule(string s,bool show)
{
	int len=s.size();
	int pos;
	bool ok=true;
	bool havenes=false;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='%')
		{
			pos=i;
			i++;
			if(s[i]=='%') continue;
			while(isdigit(s[i])&&i<len-1) i++;
			if(s[i]=='d')
			{
				havenes=true;
				continue;
			}
			if(show) _err("[错误]无法识别的标识符\""),_err(exract(s,pos,i)),_err("\"!\n");
			ok=false;
		}
	}
	if(!havenes)
	{
		if(show) _err("[错误]缺少标识符\"%d\"!\n");
		ok=false;
	}
	return ok;
}

bool numcheck(string s)
{
	int len=s.size();
	for(int i=0;i<len;i++)
	{
		if(!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

string getfilename(string s,int now)
{
	int len=s.size();
	int pos;
	string ans;
	for(int i=0;i<len;i++)
	{
		if(s[i]=='%')
		{
			pos=i;i++;
			if(s[i]=='%')
			{
				ans+=s[i];
				continue;
			}
			while(isdigit(s[i])&&i<len-1) i++;
			if(s[i]=='d')
			{
				int snum=s2i(exract(s,pos+1,i-1));
				string targetnum=itos(now);
				int divis=snum-targetnum.size();
				for(int i=1;i<=divis;i++) ans+='0';
				ans+=targetnum;
			}
		}
		else
		{
			ans+=s[i];
		}
	}
	return ans;
}

bool infilecheck(string s,int from,int to,bool show)
{
	bool ok=true;
	for(int i=from;i<=to;i++)
	{
		if(!exist(getfilename(s,i)))
		{
			if(show) _err("[错误]无法找到\""),_err(getfilename(s,i)),_err("\"!\n");
			ok=false;
		}
	}
	return ok;
}

bool checknum(string s,bool show)
{
	if(!numcheck(s))
	{
		if(show) _err("[错误]数字中包含非法字符!\n");
		return false;
	}
	if(s2i(s)<0)
	{
		if(show) _err("[错误]数字无效!\n");
		return false;
	}
	return true;
}

bool checkallset(bool show)
{
	bool result=true;
	if(!exenameset)
	{
		if(show) _err("[错误]未设置程序名!\n");
		result=false;
	}
	if(!innameset)
	{
		if(show) _err("[错误]未设置输入文件名!\n");
		result=false;
	}
	if(!outnameset)
	{
		if(show) _err("[错误]未设置输出文件名!\n");
		result=false;
	}
	if(!fromset)
	{
		if(show) _err("[错误]未设置文件开始编号!\n");
		result=false;
	}
	if(!toset)
	{
		if(show) _err("[错误]未设置文件结束编号!\n");
		result=false;
	}
	if(getfilename(inname,from)==getfilename(outname,from)||getfilename(inname,to)==getfilename(outname,to))
	{
		if(show) _err("[错误]输入文件与输出文件有重复!\n");
		result=false;
	}
	return result;
}
