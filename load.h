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

bool Manual_load(bool show)
{
	if(show) clearall();
	if(show) cout<<"[信息]正在进行手动设置:"<<endl;
	bool curok=false;
	string temp;
	while(!curok) curok=loadexename(temp);
	while(true)
	{
		while(true)
		{
			curok=false;
			while(!curok) curok=loadfrom(temp);
			curok=false;
			while(!curok) curok=loadto(temp);
			if(from>to)
			{
				if(show) _err("[错误]开始编号大于结束编号!\n");
				toset=false;
				fromset=false;
				continue;
			}
			break;
		}
		curok=false;
		while(!curok) curok=loadinname(temp);
		if(!infilecheck(inname,from,to,true)) continue;
		break;
	}
	curok=false;
	while(!curok||!checkallset(true)) curok=loadoutname(temp);
	if(show) _ok("[信息]设置已全部设置完成!\n");
	if(show) cout<<"[等待响应]按任意键继续。"<<endl;
	if(show) pause();
	return true;
}

bool File_load(bool pau,bool show)
{
	if(show) clearall();
	fstream settings;
	if(!openstream(settings,"settings.ini","in"))
	{
		if(show) cline();
		if(show) _err("[错误]无法打开\"settings.ini\"，请重试或者使用手动模式。\n");
		if(show) cout<<"[等待响应]按任意键继续。"<<endl;
		if(show) pause();
		return false;
	}
	clearall();
	if(show) _ok("[信息]已经读取到配置文件信息，正在执行数据检查...\n");
	
	string curline;
	bool ok=true;
	while(getline(settings,curline))
	{
		curline=nocomment(curline);
		curline=nfaspace(curline);
		int eqa_position=curline.find('=');
		if(eqa_position==-1)
		{
			//if(show) cout<<"[警告]无效的设置项:\""<<curline<<"\"!"<<endl;
			continue;
		}
		string beingset=exract(curline,0,eqa_position-1);
		beingset=nospace(beingset);
		string setto=exract(curline,eqa_position+1,curline.size()-1);
		setto=nfaspace(setto);
		if(setto.size()==0)
		{
			if(show) _warn("[警告]无效的设置项:\""),_warn(curline),_warn("\"!\n");
			continue;
		}
		if(beingset=="ExeName")
		{
			if(checkexename(setto,show))
			{
				if(show) if(exenameset) _warn("[警告]程序名称被覆盖设置为\""),_warn(setto),_warn("\"!\n");
				exename=setto;
				exenameset=true;
			}
			else ok=false;
		}
		else if(beingset=="NumberFrom")
		{
			if(checknum(setto,show))
			{
				if(show) if(fromset) _warn("[警告]文件开始编号被覆盖设置为\""),_warn(setto),_warn("\"!\n");
				from=stoi(setto);
				fromset=true;
			}
			else ok=false;
		}
		else if(beingset=="NumberTo")
		{
			if(checknum(setto,show))
			{
				if(show) if(toset) _warn("[警告]文件结束编号被覆盖设置为\""),_warn(setto),_warn("\"!\n");
				to=stoi(setto);
				toset=true;
			}
			else ok=false;
		}
		else if(beingset=="InFileName")
		{
			if(checkrule(setto,show))
			{
				if(show) if(innameset) _warn("[警告]输入文件名被覆盖设置为\""),_warn(setto),_warn("\"!\n");
				inname=setto;
				innameset=true;
			}
			else ok=false;
		}
		else if(beingset=="OutFileName")
		{
			if(checkrule(setto,show))
			{
				if(show) if(outnameset) _warn("[警告]输出文件名被覆盖设置为\""),_warn(setto),_warn("\"!\n");
				outname=setto;
				outnameset=true;
			}
			else ok=false;
		}
		else
		{
			if(show) _warn("[警告]无效的设置项:\""),_warn(curline),_warn("\"!\n");
		}
	}
	settings.close();
	if(from>to)
	{
		if(show) _err("[错误]开始编号大于结束编号!\n");
		ok=false;
	}
	if(!infilecheck(inname,from,to,show)) ok=false;
	if(checkallset(show)&&ok)
	{
		if(show) _ok("[信息]设置已全部读取并检查完成!\n");
		if(show) cout<<"[等待响应]按任意键继续。"<<endl;
		if(show) if(pau) pause();
		return true;
	}
	else
	{
		if(show) _err("[错误]设置失败!部分参数缺失或无效!请重试或尝试手动模式!\n");
		if(show) cout<<"[等待响应]按任意键继续。"<<endl;
		if(show) pause();
		cleardata();
		return false;
	}
}

bool Auto_load(bool show)
{
	if(show) cout<<"[信息]正在进行文件列表分析..."<<endl;
	system("dir *.exe *.in /B > __filelist.txt");
	fstream list;
	if(!openstream(list,"__filelist.txt","in"))
	{
		if(show) _err("[错误]无法访问文件夹!\n");
		system("del __filelist.txt");
		if(show) pause();
		return false;
	}
	int exenum=0;
	string curline;
	while(getline(list,curline))
	{
		if((int)curline.find(".exe")!=-1)
		{
			exenum++;
		}
	}
	list.close();
	if(exenum>=4)
	{
		if(show) _warn("[警告]您的文件夹中有"),_warn(exenum),_warn("个exe文件，超出系统允许范围。\n");
		if(show) _warn("[警告]出于安全考虑，您的自动分析请求已被拒绝。\n");
		if(show) _err("[错误]自动分析失败!请尝试其他模式!\n");
		system("del __filelist.txt");
		if(show) pause();
		return false;
	}
	int leastinserial=9999;
	openstream(list,"__filelist.txt","in");
	while(getline(list,curline))
	{
		if((int)curline.find(".exe")!=-1)
		{
			if(checkexename(curline,false)&&!exenameset)
			{
				exename=curline;
				exenameset=true;
				if(show) _ok("[信息]找到exe文件:"),_ok(exename),_ok('\n');
			}
		}
		else
		{
			int len=curline.size();
			int dpos=0;
			string anawhy;
			for(int i=0;i<len;i++)
			{
				if(isdigit(curline[i]))
				{
					dpos=i;
					while(isdigit(curline[i])) i++;
					string dig=exract(curline,dpos,i-1);
					int extracted=stoi(dig);
					leastinserial=min((int)dig.size(),leastinserial);
					from=min(from,extracted);
					to=max(to,extracted);
					anawhy+='%';
					anawhy+=itos(leastinserial);
					anawhy+='d';
				}
				if(curline[i]=='.') break;
				anawhy+=curline[i];
			}
			inname=anawhy+".in";
			outname=anawhy+".ans";
		}
	}
	list.close();
	system("del __filelist.txt");
	if(inname!="")
	{
		if(infilecheck(inname,from,to,false))
		{
			innameset=outnameset=true;
			fromset=toset=true;
		}
	}
	if(checkallset(false))
	{
		if(show)
		{
			_ok("[信息]自动分析成功!数据已被加载!\n");
			pause();
		}
		return true;
	}
	if(show)
	{
		_err("[错误]自动分析失败!请尝试其他模式!\n");
		pause();
	}
	return false;
}
