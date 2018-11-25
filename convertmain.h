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
		if(show) cout<<"[��Ϣ]����ת��: "<<infilename<<" --> "<<outfilename<<"\r";
		CopyFile(infilename.c_str(),"std.in",false);
		int result=system(exename.c_str());
		if(result!=0)
		{
			if(show) cline();
			if(show) cout<<endl;
			if(show) _err("[����]����"),_err(infilename),_err(" --> "),_err(outfilename),_err("����������:\n");
			if(show) _err("[����]���ṩ�ĳ���������ʱ����!����ֵ:"),_err(result),_err('\n');
			if(show) _err("[����]������ȡ��!�������������\n");
			remove("std.in");remove("std.out");
			return false;
		}
		CopyFile("std.out",outfilename.c_str(),false);
		remove("std.in");remove("std.out");
		if(show) cline();
	}
	if(show) cline();
	return true;
}
