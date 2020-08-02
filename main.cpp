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
				cline();cout<<"[信息]已完成!"<<endl;
				return 0;
			}
			return -1;
		}
		if(option=="-auto-mode")
		{
			if(Auto_load(false))
			{
				mainconversion(false);
				cline();cout<<"[信息]已完成!"<<endl;
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
	
	string mainbef="[等待响应]请选择您想使用的主模式:\n________________________________________\n";
	int mainmode=arrowselect(mainbef,"________________________________________\n",3,1,"快速自动模式",2,"快速文件模式",3,"详细设置模式");
	if(mainmode==1)
	{
		if(!Auto_load(false))
		{
			mainmode=3;
			_err("[错误]设置失败，已退出自动模式。\n");
			cout<<"[等待响应]按任意键继续。";
			pause();
		}
		clearall();
	}
	if(mainmode==2)
	{
		if(!File_load(false,false))
		{
			mainmode=3;
			_err("[错误]设置失败，已退出快速模式。\n");
			cout<<"[等待响应]按任意键继续。";
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
			string selbef="[信息]转换器需要设置。\n[等待响应]请选择您想使用的数据加载模式:\n________________________________________\n";
			int selmode=arrowselect(selbef,"________________________________________\n",3,1,"自动分析模式",2,"文件读取模式",3,"手动设置模式");
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
			string nexbef="[等待响应]转换器数据设置已完成。当前数据:\n________________settings________________\n\n";
			string sel1="程序名:"+exename;
			string sel2="文件开始编号:"+itos(from);
			string sel3="文件结束编号:"+itos(to);
			string sel4="输入文件:"+inname;
			string sel5="输出文件:"+outname;
			nexbef+=sel1;nexbef+='\n';
			nexbef+=sel2;nexbef+='\n';
			nexbef+=sel3;nexbef+='\n';
			nexbef+=sel4;nexbef+='\n';
			nexbef+=sel5;nexbef+='\n';
			nexbef+="[等待响应]接下来您想:\n________________________________________\n";
			int nextmove=arrowselect(nexbef,"________________________________________\n",3,1,"立即开始",2,"修改数据",3,"保存数据");
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
		_ok("[信息]已完成!按任意键退出。\n");
	}
	pause();
	return 0;
}

