#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
class OutPutFileStream
{
private:
FILE *f;
int mode;
int lastOperationFailed;
public:
const static int append=1;
const static int overwrite=2;
OutPutFileStream()
{
this->lastOperationFailed=0;
this->f=NULL;
this->mode=-1;
}
OutPutFileStream(const char *fileName,int mode)
{
this->lastOperationFailed=0;
this->f=NULL;
this->mode=-1;
this->open(fileName,mode);
}
void open(const char *fileName,int mode)
{
if(f!=NULL)
{
fclose(f);
this->f=NULL;
this->mode=-1;
}
this->lastOperationFailed=1;
if(fileName==NULL)return;
if(mode!=append && mode!=overwrite)return;
if(mode==append)
{
f=fopen(fileName,"a");
}
else if(mode==overwrite)
{
f=fopen(fileName,"w");
}
if(f==NULL)return;
this->lastOperationFailed=0;
}
void close()
{
this->lastOperationFailed=0;
if(this->f==NULL)return;
fclose(this->f);
}
int fail()
{
return this->lastOperationFailed; 
}
OutPutFileStream & operator<<(char c)
{
this->lastOperationFailed=1;
if(this->f==NULL)return *this;
fputc(c,this->f);
this->lastOperationFailed=0;
return *this;
}
};
class InputFileStream
{
private:
FILE *f;
int lastOperationFailed;
public:
InputFileStream()
{
this->f=NULL;
this->lastOperationFailed=0;
}
InputFileStream(const char *fileName)
{
this->f=NULL;
this->lastOperationFailed=0;
open(fileName);
}
void open(const char *fileName)
{
if(this->f!=NULL)
{
fclose(this->f);
this->lastOperationFailed=0;
}
this->lastOperationFailed=1;
if(fileName==NULL)return;
this->f=fopen(fileName,"r");
if(this->f==NULL)return;
this->lastOperationFailed=0;
}
int fail()
{
return this->lastOperationFailed;
}
InputFileStream & operator>>(char &c)
{
this->lastOperationFailed=1;
if(this->f==NULL)return *this;
if(feof(this->f))return *this;
c=fgetc(this->f);
if(feof(this->f))return *this;
this->lastOperationFailed=0;
return *this;
}
void close()
{
this->lastOperationFailed=0;
if(this->f!=NULL)fclose(this->f);
}
};
void addFriends()
{
char name[22],contactNumber[82];
cout<<"Enter name:";
fgets(name,22,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
int i;
for(int i=0;name[i]!='\0';i++)
{
if(name[i]=='!')
{
cout<<"Name cannot contain ! symbol"<<endl;
return;
}
}
cout<<"Enter contact number:";
fgets(contactNumber,82,stdin);
fflush(stdin);
contactNumber[strlen(contactNumber)-1]='\0';
for(int i=0;contactNumber[i]!='\0' ; i++)
{
if(contactNumber[i]=='!')
{
cout<<"Contact Number cannot contain ! symbol"<<endl;
return;
}
}
OutPutFileStream f("friends.ddd",OutPutFileStream::append);
i=0;
while(name[i]!='\0')
{
f<<name[i];
i++;
}
f<<'!';
i=0;
while(contactNumber[i]!='\0')
{
f<<contactNumber[i];
i++;
}
f<<'!';
f.close();
cout<<"Friends added"<<endl;
}
void displayListOfFriends()
{
InputFileStream k("friends.ddd");
if(k.fail()) // return true if lastOperationFailed
{
cout<<"No friends added"<<endl;
return;
}
char nm[21];
char cn[82];
int x;
char m;
while(1)
{
k>>m;
if(k.fail())break;
nm[0]=m;
x=1;
while(1)
{
k>>m;
if(m=='!')break;
nm[x]=m;
x++;
}
nm[x]='\0';
x=0;
while(1)
{
k>>m;
if(m=='!')break;
cn[x]=m;
x++;
}
cn[x]='\0';
cout<<"Name:"<<nm<<","<<"ContactNumber:"<<cn<<endl;
}
k.close();
}
int main()
{
int ch;
while(1)
{
cout<<"1.Addfriends:"<<endl;
cout<<"2.DisplayListOfFriends:"<<endl;
cout<<"3.EXIT"<<endl;
cout<<"Enter your choice:";
scanf("%d",&ch);
fflush(stdin);
if(ch==1)addFriends();
if(ch==2)displayListOfFriends();
if(ch==3)break;
}
return 0;
}