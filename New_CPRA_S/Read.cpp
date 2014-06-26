#include "Read.h"


Read::Read(void)
{
	temp_data_num=0;
	train_data_num=0;
	test_data_num=0;
}

Read::~Read(void)
{
	data_ifs.close();
}
bool Read::DNA_Read()
{
	if(!data_ifs)
		cout<<"Could not read in DNA_Read"<<endl;
	data_ifs.open("..\\data.txt");
	while(!data_ifs.eof())
	{
		Temp_Data_Head[temp_data_num].number=temp_data_num;
		data_ifs>>Temp_Data_Head[temp_data_num]._class>>Temp_Data_Head[temp_data_num]._content;
		temp_data_num++;
	}
	return true;
}
bool Read::shuffle(int n)
{
	for(int i=0;i<temp_data_num;i++)
	{
		if(i%n==0)
		{
			Test_Data_Head[test_data_num]=Temp_Data_Head[i];
			test_data_num++;
		}
		else
		{
			Train_Data_Head[train_data_num]=Temp_Data_Head[i];
			train_data_num++;
		}
	}
	return true;
}
bool Read::Count_Class_Num()
{
	//here we know DNA has 12 kinds of class so we do not count but set the number to 12
	class_num=12;
	return true;
}
bool Read::Run()
{
	DNA_Read();
	shuffle(10);
	Count_Class_Num();
	return true;
}