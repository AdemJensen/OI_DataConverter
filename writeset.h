void writesettings()
{
	int selection=keyboard("是否将当前设置写入\"settings.ini\"? (Esc=否,Enter=是)",false,2,27,13);
	cline();
	if(selection==2)
	{
		fstream settings;
		if(!openstream(settings,"settings.ini","out"))
		{
			_err("[错误]无法打开\"settings.ini\"!写入失败!\n");
			cout<<"[等待响应]按任意键继续。"<<endl;
			pause();
		}
		else
		{
			settings<<"ExeName = "<<exename<<"      //已编译的exe文件名"<<endl;//程序名
			settings<<"NumberFrom = "<<from<<"      //文件开始序号"<<endl;//文件开始编号 
			settings<<"NumberTo = "<<to<<"      //文件结束序号"<<endl;//文件结束编号
			settings<<"InFileName = "<<inname<<"      //用于确定输入文件的命名方式"<<endl;//输入文件名 
			settings<<"OutFileName = "<<outname<<"      //用于确定输出文件的命名方式"<<endl;//输出文件名
			settings<<"//'%d'表示文件编号。百分号后添加一个数字代表输出后面的编号所占的长度，并用'0'填充空隙。"<<endl;
			settings.close();
			_ok("[信息]写入成功!\n");
			cout<<"[等待响应]按任意键继续。"<<endl;
			pause();
		}
	}
}
