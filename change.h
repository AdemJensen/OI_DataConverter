void changesettings()
{
	while(true)
	{
		clearall();
		string cbef="[等待响应]请选择您想修改的项:\n________________________________________\n";
		string sel1="程序名:"+exename;
		string sel2="文件开始编号:"+itos(from);
		string sel3="文件结束编号:"+itos(to);
		string sel4="输入文件:"+inname;
		string sel5="输出文件:"+outname;
		int select=arrowselect(cbef,"________________________________________",6,1,sel1.c_str(),2,sel2.c_str(),2,sel3.c_str(),2,sel4.c_str(),3,sel5.c_str(),4,"[退出修改]");
		announcedata();
		if(select==1)
		{
			bool curok=false;
			string temp;
			while(!curok) curok=loadexename(temp);
		}
		if(select==2)
		{
			bool curok=false;
			string temp;
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
						_err("[错误]开始编号大于结束编号!\n");
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
		}
		if(select==3)
		{
			bool curok=false;
			string temp;
			while(!curok||!checkallset(true)) curok=loadoutname(temp);
		}
		if(select==4) return;
	}
}
