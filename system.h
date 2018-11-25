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

enum Color{red,blue,green,white,black,yellow};
void pause()
{
	_getch();
}
void clearall()
{
	system("cls");
	
	cout<<"数据转换器 S2"<<endl;
	cout<<"________________________________________________________________________________\n";
}
void cline()
{
	cout<<"\r                                                                              \r";
}
 //一共有16种文字颜色，16种背景颜色，组合有256种。传入的值应当小于256  
bool SetConsoleColor(WORD wAttributes)  
{  
    if(GetStdHandle(STD_OUTPUT_HANDLE)==INVALID_HANDLE_VALUE) return false;  
    return SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wAttributes);
}
void changecolor(Color back,Color txt)
{
	int final=0;
	switch(back)
	{
		case black:
			final=0;
			break;
		case red:
			final=BACKGROUND_RED;
			break;
		case blue:
			final=BACKGROUND_BLUE;
			break;
		case green:
			final=BACKGROUND_GREEN;
			break;
		case white:
			final=(BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE);
			break;
		case yellow:
			final=(BACKGROUND_RED|BACKGROUND_GREEN);
			break;
	}
	switch(txt)
	{
		case black:
			final=(final|(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE));
		case red:
			final=(final|FOREGROUND_RED|FOREGROUND_INTENSITY);
			break;
		case blue:
			final=(final|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			break;
		case green:
			final=(final|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			break;
		case white:
			final=(final|(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE));
			break;
		case yellow:
			final=(final|(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY));
			break;
	}
	SetConsoleColor(final);
}
template<typename T>
void _warn(T s)
{
	changecolor(black,yellow);
	cout<<s;
	changecolor(black,white);
}
template<typename T>
void _ok(T s)
{
	changecolor(black,green);
	cout<<s;
	changecolor(black,white);
}
template<typename T>
void _err(T s)
{
	changecolor(black,red);
	cout<<s;
	changecolor(black,white);
}
int keyboard(string show,bool standalone,int num,...)
{
	va_list arg_ptr;
	va_start(arg_ptr,num);
	cline();
	cout<<"[等待响应]"<<show;
	if(standalone) cout<<endl;
	int keylist[55];
	for(int i=1;i<=num;i++)
	{
		keylist[i]=va_arg(arg_ptr,int);
	}
	va_end(arg_ptr);
	while(true)
	{
		int recieve=_getch();
		for(int i=1;i<=num;i++)
		{
			if(keylist[i]==recieve) return i;
		}
	}
}
int arrowselect(string before,string after,int num,...)
{
	va_list arg_ptr;
	va_start(arg_ptr,num);
	char temp[605];
	string showlist[55];
	int numlist[55];
	int now=1,maxium=-9999;
	for(int i=1;i<=num;i++)
	{
		numlist[i]=va_arg(arg_ptr,int);
		strcpy(temp,va_arg(arg_ptr,char*));
		showlist[i]=temp;
		maxium=max(maxium,numlist[i]);
	}
	while(true)
	{
		cout<<before<<endl;
		for(int i=1;i<=num;i++)
		{
			if(numlist[i]==now) changecolor(green,white);
			cout<<showlist[i]<<endl;
			if(numlist[i]==now) changecolor(black,white);
		}
		cout<<after<<endl;
		int press=keyboard(" UP=向上,DW=向下,Enter=选中",true,3,72,80,13);
		if(press==1)
		{
			now--;
			if(now==0) now=maxium;
		}
		if(press==2)
		{
			now++;
			if(now>maxium) now=1;
		}
		if(press==3)
		{
			clearall();
			return now;
		}
		if(press==4)
		{
			clearall();
			return 0;
		}
		clearall();
	}
	
}
bool openstream(fstream &targetstream,string filename,string way)
{
	if(way=="in") targetstream.open(filename.c_str(),ios::in);
	else targetstream.open(filename.c_str(),ios::out);
	return targetstream.is_open();
}
bool exist(string filename)
{
	ifstream checktemp;
	checktemp.open(filename.c_str(),ios::in);
	bool result=checktemp.is_open();
	checktemp.close();
	return result;
}
string itos(int a)
{
	string ans="";
	if(a==0)
	{
		ans="0";
		return ans;
	}
	while(a!=0)
	{
		char add=a%10+'0';
		ans=add+ans;
		a=a/10;
	}
	return ans;
}
string exract(string s,int l,int r)
{
	if(l>r) return "";
	string ans;
	for(int i=l;i<=r;i++)
	{
		ans+=s[i];
	}
	return ans;
}
int stoi(string s)
{
	if(s.size()==0) return 0;
	char str[1005];
	strcpy(str,s.c_str());
	return atoi(str);
}
void cleardata()
{
	exename="";//程序名 
	inname="";//输入文件名 
	outname="";//输出文件名 
	from=9999;//文件开始编号 
	to=0;//文件结束编号
	exenameset=false;//程序名已设置 
	innameset=false;//输入文件名已设置 
	outnameset=false;//输出文件名已设置 
	fromset=false;//文件开始编号已设置
	toset=false;//文件结束编号已设置
}
void announcedata()
{
	cout<<"________________settings________________"<<endl<<endl;
	cout<<"程序名:"<<exename<<endl;//程序名
	cout<<"文件开始编号:"<<from<<endl;//文件开始编号 
	cout<<"文件结束编号:"<<to<<endl;//文件结束编号
	cout<<"输入文件:"<<inname<<endl;//输入文件名 
	cout<<"输出文件:"<<outname<<endl;//输出文件名 
	cout<<"________________________________________"<<endl;
}
string nospace(string s)
{
	int len=s.size();
	string ans;
	for(int i=0;i<len;i++)
	{
		if(s[i]!=' ') ans+=s[i];
	}
	return ans;
}
string nfaspace(string temp)
{
	while(temp[0]==' ') temp=exract(temp,1,temp.size()-1);
	while(temp[temp.size()-1]==' ') temp=exract(temp,0,temp.size()-2);
	return temp;
}
string nocomment(string temp)
{
	int len=temp.size();
	for(int i=0;i<len-1;i++)
	{
		if(temp[i]=='/'&&temp[i+1]=='/') return exract(temp,0,i-1);
	}
	return temp;
}
