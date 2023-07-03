#include<iostream>
#include<string.h>
using namespace std;
class KKString
{
int size;
char *ptr;
public:
KKString();
KKString(const char *ptr);
KKString &operator =(const char *ptr);
KKString &operator=(const KKString &other); 
int operator <(const KKString &other);
int operator >(const KKString &other);
int operator <=(const KKString &other);
int operator >=(const KKString &other);
int operator !=(const KKString &other);
int operator ==(const KKString &other);
void operator +=(const KKString &other);
KKString operator +(const KKString &other);
virtual ~KKString();
friend ostream &operator <<(ostream &out,KKString &tmString);
};
KKString :: KKString()
{
this->ptr=NULL;
this->size=0;
}
KKString :: KKString(const char *ptr)
{
this->ptr=NULL;
if(ptr==NULL) return;
this->size=strlen(ptr);
this->ptr=new char[size+1];
strcpy(this->ptr,ptr);
}
KKString &KKString::operator=(const char *ptr)
{
if(this->ptr) delete[]this->ptr;
this->ptr=NULL;
this->size=0;
if(ptr==NULL) return *this;
this->size=strlen(ptr);
this->ptr=new char[this->size +1];
 strcpy(this->ptr,ptr);
return*this;
}
KKString &KKString :: operator =(const KKString &other)
{
if(this->ptr)delete[]this->ptr;
this->ptr=NULL;
this->size=0;
if(other.ptr==NULL) return *this;
this->size=strlen(other.ptr);
this->ptr=new char[this->size+1];
strcpy(this->ptr,other.ptr);
return *this;
}
KKString ::~KKString()
{
if(this->ptr) delete[]this->ptr;
}
ostream &operator <<(ostream &out,KKString &tmString)
{
if(tmString.ptr==NULL) return out;
out<<tmString.ptr;
return out;
}
int KKString:: operator <(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL ) return 1;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr,other.ptr)<0;
}
int KKString:: operator >(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL ) return 0;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr)>0;
}
int KKString :: operator <=(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 1;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr,other.ptr) <=0;
}
int KKString :: operator >=(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr)>=0;
}
int KKString :: operator !=(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 0;
if(this->ptr==NULL) return 1;
if(other.ptr==NULL) return 1;
return strcmp(this->ptr,other.ptr) !=0;
}
 int KKString :: operator ==(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return 1;
if(this->ptr==NULL) return 0;
if(other.ptr==NULL) return 0;
return strcmp(this->ptr ,other.ptr) ==0;
}
void KKString :: operator +=(const KKString &other)
{
if(this->ptr==NULL && other.ptr==NULL) return ;
if(other.ptr==NULL) return;
if(this->ptr==NULL)
{
(*this)=other;
return;
}
char *tmp=new char[this->size+other.size +1];
strcpy(tmp,this->ptr);
strcat(tmp,other.ptr);
delete[]this->ptr;
this->ptr=tmp;
this->size=this->size+other.size;
}
KKString KKString :: operator +(const KKString &other)
{
KKString k;
if(this->ptr==NULL && other.ptr==NULL) return k;
if(this->ptr==NULL) k=other;
else if(other.ptr==NULL) k=(*this);
else
{
k=(*this);
k+=other;
}
return k;
}
int main()
{
KKString e,a;
a="Cool";
e="Khush";
e+=a;
cout<<e<<endl;
KKString d="Ujjain";
KKString c="Indore";
KKString f;
f=d+c;
KKString k;
k=d+c+a+e+f;
cout<<d <<endl;
cout<<c<<endl;
cout<<f<<endl;
cout<<k<<endl;
return 0;
}
