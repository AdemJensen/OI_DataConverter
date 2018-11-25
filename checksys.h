// Copyright (C) 2018 AdemJensen
// This library is free software; you can redistribute it and/or 
// modify it under the terms of the GNU General Public License as 
// published by the Free Software Foundation; either version 3, 
// or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

bool checkexename(string s,bool show)
{
	if(show) cout<<"[��Ϣ]���ڼ��exe�Ϸ���...";
	int len=s.size();
	if(s[len-4]!='.'||s[len-3]!='e'||s[len-2]!='x'||s[len-1]!='e')
	{
		cline();
		if(show) _err("[����]ָ�����ļ�����exe�ļ�!\n");
		return false;
	}
	if(!exist(s))
	{
		cline();
		if(show) _err("[����]�޷��ҵ�ָ��exe�ļ�!\n");
		return false;
	}
	if(s==currentexe)
	{
		cline();
		if(show) _err("[����]����ָ��ת����ΪĿ��exe����!\n");
		return false;
	} 
	string opera=s+" -anti-reopen-mode";
	cline();_warn("[ע��]���exe��Ҫ��������exe�����б�����������������\n");
	
	WinExec(opera.c_str(),SW_SHOW);
	
	Sleep(500);
	opera="taskkill /IM "+s;
	opera+=" /f";
	system(opera.c_str());
	clearall();
	
	if(!exist("std.out"))
	{
		cline();
		if(show) _err("[����]ָ����exe����δ��ȷ�����ļ�����!\n");
		return false;
	}
	remove("std.out");
	//remove("std.in");
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
			if(show) _err("[����]�޷�ʶ��ı�ʶ��\""),_err(exract(s,pos,i)),_err("\"!\n");
			ok=false;
		}
	}
	if(!havenes)
	{
		if(show) _err("[����]ȱ�ٱ�ʶ��\"%d\"!\n");
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
				int snum=stoi(exract(s,pos+1,i-1));
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
			if(show) _err("[����]�޷��ҵ�\""),_err(getfilename(s,i)),_err("\"!\n");
			ok=false;
		}
	}
	return ok;
}

bool checknum(string s,bool show)
{
	if(!numcheck(s))
	{
		if(show) _err("[����]�����а����Ƿ��ַ�!\n");
		return false;
	}
	if(stoi(s)<0)
	{
		if(show) _err("[����]������Ч!\n");
		return false;
	}
	return true;
}

bool checkallset(bool show)
{
	bool result=true;
	if(!exenameset)
	{
		if(show) _err("[����]δ���ó�����!\n");
		result=false;
	}
	if(!innameset)
	{
		if(show) _err("[����]δ���������ļ���!\n");
		result=false;
	}
	if(!outnameset)
	{
		if(show) _err("[����]δ��������ļ���!\n");
		result=false;
	}
	if(!fromset)
	{
		if(show) _err("[����]δ�����ļ���ʼ���!\n");
		result=false;
	}
	if(!toset)
	{
		if(show) _err("[����]δ�����ļ��������!\n");
		result=false;
	}
	if(getfilename(inname,from)==getfilename(outname,from)||getfilename(inname,to)==getfilename(outname,to))
	{
		if(show) _err("[����]�����ļ�������ļ����ظ�!\n");
		result=false;
	}
	return result;
}
