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
		from=stoi(temp);
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
		to=stoi(temp);
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
