#include "Build_CRISPR.h"


Build_CRISPR::Build_CRISPR(void)
{
	Read::Run();
	segment_num=0;
	Sample_Rate=1;
}


Build_CRISPR::~Build_CRISPR(void)
{
}
bool Build_CRISPR::Go_Through_Train_Data()
{
	for(int i=0;i<train_data_num;i++)
	{
		cout<<"Processing Data No:"<<i<<endl;
		int sample_num=Sample_Rate*Train_Data_Head[i]._content.length();
		for(int j=0;j<sample_num;j++)
		{
			Segment temp_sg=Sample(Train_Data_Head[i]);
			if(Is_Confilct(temp_sg))
				continue;
			/*else 
				if(Is_OnArray(temp_sg))
				{
					Updata(temp_sg);
				}
				else
				{
					Register(temp_sg);
				}
*/
				
		}
	}
	return true;
}
Segment Build_CRISPR::Sample(Standard_Data_Format data)
{
	Segment sg;
	sg.start=rand()%data._content.length();
	sg.length=rand()%(data._content.length()-sg.start);
	if(sg.length==0&&sg.start<sg.content.length()-1)
		sg.length=1;
	sg.content=data._content.substr(sg.start,sg.length);
	return sg;
}
bool Build_CRISPR::Is_Confilct(Segment sg)
{
	int num=Conflict_Index_Head[sg.start].num;
	Segment *temp=Conflict_Index_Head[sg.start].next;
	if(num==0)
	{
		Conflict_Index_Head[sg.start].next=&sg;
		Conflict_Index_Head[sg.start].end=&sg;
		Conflict_Index_Head[sg.start].num++;
		return false;
	}
	int i=0;
	for(;i<num;i++)
	{
		if(sg.start>=temp->start&&sg.start+sg.length<=temp->start+temp->length)
			return true;
		if(sg.start<=temp->start&&sg.start+temp->length>=temp->start+temp->length)
			return true;
		temp=temp->conflict_next;
	}
	if(i==num)
	{
		Conflict_Index_Head[sg.start].end->conflict_next=&sg;
		Conflict_Index_Head[sg.start].end=&sg;
		sg.conflict_next=NULL;
		Conflict_Index_Head[sg.start].num++;
	}
	return false;
}
bool Build_CRISPR::Run()
{
	Go_Through_Train_Data();
	return true;
}