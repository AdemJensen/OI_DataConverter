#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#include<windows.h>
#include<fstream>
#include<time.h>
#include<conio.h>
using namespace std;

string currentexe;

#include"varibles.h"
#include"logo.h"
#include"system.h"
#include"checksys.h"
#include"loaddata.h"
#include"load.h"
#include"change.h"
#include"writeset.h"
#include"convertmain.h"

int main(int argc,char *argv[])
{
	cleardata();
	string stemp=argv[0];
	int slen=stemp.size()-1;
	for(int i=slen;i>=0&&stemp[i]!='\\';i--) currentexe=stemp[i]+currentexe;
	if(argc>1)
	{
		string option=argv[1];
		if(option=="-anti-reopen-mode")
		{
			/*fstream out;
			openstream(out,"std.out","out");
			out<<"DOUBLE_CHECK_SYS";
			out.close();*/
			return 1;
		}
		if(option=="-quick-mode")
		{
			if(File_load(false,false))
			{
				mainconversion(false);
				cline();cout<<"[��Ϣ]�����!"<<endl;
				return 0;
			}
			return -1;
		}
		if(option=="-auto-mode")
		{
			if(Auto_load(false))
			{
				mainconversion(false);
				cline();cout<<"[��Ϣ]�����!"<<endl;
				return 0;
			}
			return -1;
		}
	}
	
	/*/Process bar test
	HWND hwnd=FindWindow((LPCWSTR)"ConsoleWindowClass",NULL);
	RECT rect;
	GetWindowRect(hwnd,&rect);
	int lleft=(rect.right-rect.left)/4;
	int top=(rect.bottom-rect.top)/4;
	int right=lleft*3;
	HDC hdcc=GetDC(hwnd);
	Rectangle(hdcc,lleft,top,right,top+10);
	
	for(int i=lleft;i<=right;i++)
	{
		Sleep(40);
		SetRect(&rect,lleft,top,i,top+10);
		FillRect(hdcc,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
	}
	pause(); 
	/*/
	changecolor(black,white);	
	
	LOGOout();
	pause();
	clearall();
	
	string mainbef="[�ȴ���Ӧ]��ѡ������ʹ�õ���ģʽ:\n________________________________________\n";
	int mainmode=arrowselect(mainbef,"________________________________________\n",3,1,"�����Զ�ģʽ",2,"�����ļ�ģʽ",3,"��ϸ����ģʽ");
	if(mainmode==1)
	{
		if(!Auto_load(false))
		{
			mainmode=3;
			_err("[����]����ʧ�ܣ����˳��Զ�ģʽ��\n");
			cout<<"[�ȴ���Ӧ]�������������";
			pause();
		}
		clearall();
	}
	if(mainmode==2)
	{
		if(!File_load(false,false))
		{
			mainmode=3;
			_err("[����]����ʧ�ܣ����˳�����ģʽ��\n");
			cout<<"[�ȴ���Ӧ]�������������";
			pause();
		}
		clearall();
	}
	if(mainmode==3)
	{
		bool dataok=false;
		while(!dataok)
		{
			clearall();
			cleardata();
			string selbef="[��Ϣ]ת������Ҫ���á�\n[�ȴ���Ӧ]��ѡ������ʹ�õ����ݼ���ģʽ:\n________________________________________\n";
			int selmode=arrowselect(selbef,"________________________________________\n",3,1,"�Զ�����ģʽ",2,"�ļ���ȡģʽ",3,"�ֶ�����ģʽ");
			if(selmode==1)
			{
				dataok=Auto_load(true);
			}
			if(selmode==2)
			{
				dataok=File_load(true,true);
			}
			if(selmode==3)
			{
				dataok=Manual_load(true);
			}
		}
	}
	
	if(mainmode==3)
	{
		while(true)
		{
			clearall();
			string nexbef="[�ȴ���Ӧ]ת����������������ɡ���ǰ����:\n________________settings________________\n\n";
			string sel1="������:"+exename;
			string sel2="�ļ���ʼ���:"+itos(from);
			string sel3="�ļ��������:"+itos(to);
			string sel4="�����ļ�:"+inname;
			string sel5="����ļ�:"+outname;
			nexbef+=sel1;nexbef+='\n';
			nexbef+=sel2;nexbef+='\n';
			nexbef+=sel3;nexbef+='\n';
			nexbef+=sel4;nexbef+='\n';
			nexbef+=sel5;nexbef+='\n';
			nexbef+="[�ȴ���Ӧ]����������:\n________________________________________\n";
			int nextmove=arrowselect(nexbef,"________________________________________\n",3,1,"������ʼ",2,"�޸�����",3,"��������");
			if(nextmove==1) break;
			if(nextmove==2)
			{
				changesettings();
			}
			if(nextmove==3)
			{
				writesettings();
			}
		}
	}
	clearall();
	
	if(mainconversion(true))
	{
		cline();
		_ok("[��Ϣ]�����!��������˳���\n");
	}
	pause();
	return 0;
}

