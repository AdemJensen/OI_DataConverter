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

void changesettings()
{
	while(true)
	{
		clearall();
		string cbef="[?ȴ??Ӧ]?ѡ?????ĵ??\n________________________________________\n";
		string sel1="????:"+exename;
		string sel2="?????ʼ??:"+itos(from);
		string sel3="????????:"+itos(to);
		string sel4="?????:"+inname;
		string sel5="??????:"+outname;
		int select=arrowselect(cbef,"________________________________________",6,1,sel1.c_str(),2,sel2.c_str(),2,sel3.c_str(),2,sel4.c_str(),3,sel5.c_str(),4,"[??????");
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
						_err("[?????ʼ????ڽ????!\n");
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
