void changesettings()
{
	while(true)
	{
		clearall();
		string cbef="[�ȴ���Ӧ]��ѡ�������޸ĵ���:\n________________________________________\n";
		string sel1="������:"+exename;
		string sel2="�ļ���ʼ���:"+itos(from);
		string sel3="�ļ��������:"+itos(to);
		string sel4="�����ļ�:"+inname;
		string sel5="����ļ�:"+outname;
		int select=arrowselect(cbef,"________________________________________",6,1,sel1.c_str(),2,sel2.c_str(),2,sel3.c_str(),2,sel4.c_str(),3,sel5.c_str(),4,"[�˳��޸�]");
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
						_err("[����]��ʼ��Ŵ��ڽ������!\n");
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
