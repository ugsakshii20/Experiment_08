#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
using namespace std;
class Student
{
public:
char name[30];
int id;
void input_data()
{
cout<<"Enter the Name:";
cin>> name;
cout<<"Enter the ID:";
cin>>id;
}
void put_data()
{
cout<<setw(10)<<name<<setw(10)<<id<<endl;
}
};
int main()
{
Student rec;
int ID;
int pos,choice,offset,i;
fstream fp;

ifstream in;
ofstream out;
char nm[20];
char ans;
do
{
cout<<"\n1.Read file";
cout<<"\n2.Write file";
cout<<"\n3.Determine Name if ID number is specified";
cout<<"\n4.Determine ID if name is specified";
cout<<"\n5.Update ID number";
cout<<"\nEnter the choice:";
cin>>choice;
switch(choice)
{
case 1:
in.open("test.txt",ios::in|ios::binary);
cout<<"\nThe contents of file are:\n";
while(in.read((char*)&rec,sizeof(rec)))
{
rec.put_data();
}
in.close();
break;
case 2:
rec.input_data();
char ch;
cin.get(ch);
out.open("test.txt",ios::out|ios::app|ios::binary);
out.write((char*)&rec,sizeof(rec));
out.close();
break;

case 3:
cout<<"\nEnter the ID:";
cin>>ID;
fp.open("test.txt",ios::ate|ios::in|ios::out|ios::binary);
fp.seekg(0,ios::beg);
pos=-1;
i=0;
while(fp.read((char*)&rec,sizeof(rec)))
{
if(ID == rec.id)
{
pos = i;
break;
}
i++;
}
offset=pos*sizeof(rec);
fp.seekp(offset);
fp.read((char*)&rec,sizeof(rec));
cout<<"\nName:"<<rec.name;
fp.close();
break;
case 4:
cout<<"\nEnter the Name:";
cin>>nm;
fp.open("test.txt",ios::ate|ios::in|ios::out|ios::binary);
fp.seekg(0, ios::beg);
pos = -1;
i = 0;
while(fp.read((char*)&rec,sizeof(rec)))
{
if((strcmp(nm,rec.name))==0)

{
pos = i;
break;
}
i++;
}
offset = pos*sizeof(rec);
fp.seekp(offset);
fp.read((char*)&rec, sizeof(rec));
cout<<"\nID:"<<rec.id;
fp.close();
break;
case 5:
cout<<"\nEnter the Name:";
cin>>nm;
fp.open("test.txt",ios::ate|ios::in|ios::out|ios::binary);
fp.seekg(0,ios::beg);
pos = -1;
i=0;
while(fp.read((char*)&rec,sizeof(rec)))
{
if((strcmp(nm,rec.name)) == 0)
{
pos = i;
break;
}
i++;
}
offset = (pos)*sizeof(rec);
fp.seekp(offset);
cout<<"\nCurrent ID :"<<rec.id;

cout<<"\nEnter new ID:";
cin>>ID;
rec.id=ID;
fp.write((char*)&rec,sizeof(rec))<<flush;
cout<<"\nrecord updated !!\n";
fp.seekg(0);
while(fp.read((char*)&rec,sizeof(rec)))
{
rec.put_data();
}
fp.close();
break;
}
cout<<"\n Do You want to continue?(y/n)";
cin>>ans;
}while(ans=='y');
return 0;
}
