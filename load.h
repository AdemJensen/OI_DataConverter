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
	if(show) cout<<"[��Ϣ]���ڽ����ֶ�����:"<<endl;
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
				if(show) _err("[����]��ʼ��Ŵ��ڽ������!\n");
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
	if(show) _ok("[��Ϣ]������ȫ���������!\n");
	if(show) cout<<"[�ȴ���Ӧ]�������������"<<endl;
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
		if(show) _err("[����]�޷���\"settings.ini\"�������Ի���ʹ���ֶ�ģʽ��\n");
		if(show) cout<<"[�ȴ���Ӧ]�������������"<<endl;
		if(show) pause();
		return false;
	}
	clearall();
	if(show) _ok("[��Ϣ]�Ѿ���ȡ�������ļ���Ϣ������ִ�����ݼ��...\n");
	
	string curline;
	bool ok=true;
	while(getline(settings,curline))
	{
		curline=nocomment(curline);
		curline=nfaspace(curline);
		int eqa_position=curline.find('=');
		if(eqa_position==-1)
		{
			//if(show) cout<<"[����]��Ч��������:\""<<curline<<"\"!"<<endl;
			continue;
		}
		string beingset=exract(curline,0,eqa_position-1);
		beingset=nospace(beingset);
		string setto=exract(curline,eqa_position+1,curline.size()-1);
		setto=nfaspace(setto);
		if(setto.size()==0)
		{
			if(show) _warn("[����]��Ч��������:\""),_warn(curline),_warn("\"!\n");
			continue;
		}
		if(beingset=="ExeName")
		{
			if(checkexename(setto,show))
			{
				if(show) if(exenameset) _warn("[����]�������Ʊ���������Ϊ\""),_warn(setto),_warn("\"!\n");
				exename=setto;
				exenameset=true;
			}
			else ok=false;
		}
		else if(beingset=="NumberFrom")
		{
			if(checknum(setto,show))
			{
				if(show) if(fromset) _warn("[����]�ļ���ʼ��ű���������Ϊ\""),_warn(setto),_warn("\"!\n");
				from=stoi(setto);
				fromset=true;
			}
			else ok=false;
		}
		else if(beingset=="NumberTo")
		{
			if(checknum(setto,show))
			{
				if(show) if(toset) _warn("[����]�ļ�������ű���������Ϊ\""),_warn(setto),_warn("\"!\n");
				to=stoi(setto);
				toset=true;
			}
			else ok=false;
		}
		else if(beingset=="InFileName")
		{
			if(checkrule(setto,show))
			{
				if(show) if(innameset) _warn("[����]�����ļ�������������Ϊ\""),_warn(setto),_warn("\"!\n");
				inname=setto;
				innameset=true;
			}
			else ok=false;
		}
		else if(beingset=="OutFileName")
		{
			if(checkrule(setto,show))
			{
				if(show) if(outnameset) _warn("[����]����ļ�������������Ϊ\""),_warn(setto),_warn("\"!\n");
				outname=setto;
				outnameset=true;
			}
			else ok=false;
		}
		else
		{
			if(show) _warn("[����]��Ч��������:\""),_warn(curline),_warn("\"!\n");
		}
	}
	settings.close();
	if(from>to)
	{
		if(show) _err("[����]��ʼ��Ŵ��ڽ������!\n");
		ok=false;
	}
	if(!infilecheck(inname,from,to,show)) ok=false;
	if(checkallset(show)&&ok)
	{
		if(show) _ok("[��Ϣ]������ȫ����ȡ��������!\n");
		if(show) cout<<"[�ȴ���Ӧ]�������������"<<endl;
		if(show) if(pau) pause();
		return true;
	}
	else
	{
		if(show) _err("[����]����ʧ��!���ֲ���ȱʧ����Ч!�����Ի����ֶ�ģʽ!\n");
		if(show) cout<<"[�ȴ���Ӧ]�������������"<<endl;
		if(show) pause();
		cleardata();
		return false;
	}
}

bool Auto_load(bool show)
{
	if(show) cout<<"[��Ϣ]���ڽ����ļ��б����..."<<endl;
	system("dir *.exe *.in /B > __filelist.txt");
	fstream list;
	if(!openstream(list,"__filelist.txt","in"))
	{
		if(show) _err("[����]�޷������ļ���!\n");
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
		if(show) _warn("[����]�����ļ�������"),_warn(exenum),_warn("��exe�ļ�������ϵͳ����Χ��\n");
		if(show) _warn("[����]���ڰ�ȫ���ǣ������Զ����������ѱ��ܾ���\n");
		if(show) _err("[����]�Զ�����ʧ��!�볢������ģʽ!\n");
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
				if(show) _ok("[��Ϣ]�ҵ�exe�ļ�:"),_ok(exename),_ok('\n');
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
			_ok("[��Ϣ]�Զ������ɹ�!�����ѱ�����!\n");
			pause();
		}
		return true;
	}
	if(show)
	{
		_err("[����]�Զ�����ʧ��!�볢������ģʽ!\n");
		pause();
	}
	return false;
}
