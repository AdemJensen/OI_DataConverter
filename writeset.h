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
