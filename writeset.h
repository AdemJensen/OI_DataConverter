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

void writesettings()
{
	int selection=keyboard("�Ƿ񽫵�ǰ����д��\"settings.ini\"? (Esc=��,Enter=��)",false,2,27,13);
	cline();
	if(selection==2)
	{
		fstream settings;
		if(!openstream(settings,"settings.ini","out"))
		{
			_err("[����]�޷���\"settings.ini\"!д��ʧ��!\n");
			cout<<"[�ȴ���Ӧ]�������������"<<endl;
			pause();
		}
		else
		{
			settings<<"ExeName = "<<exename<<"      //�ѱ����exe�ļ���"<<endl;//������
			settings<<"NumberFrom = "<<from<<"      //�ļ���ʼ���"<<endl;//�ļ���ʼ��� 
			settings<<"NumberTo = "<<to<<"      //�ļ��������"<<endl;//�ļ��������
			settings<<"InFileName = "<<inname<<"      //����ȷ�������ļ���������ʽ"<<endl;//�����ļ��� 
			settings<<"OutFileName = "<<outname<<"      //����ȷ������ļ���������ʽ"<<endl;//����ļ���
			settings<<"//'%d'��ʾ�ļ���š��ٷֺź����һ�����ִ����������ı����ռ�ĳ��ȣ�����'0'����϶��"<<endl;
			settings.close();
			_ok("[��Ϣ]д��ɹ�!\n");
			cout<<"[�ȴ���Ӧ]�������������"<<endl;
			pause();
		}
	}
}
