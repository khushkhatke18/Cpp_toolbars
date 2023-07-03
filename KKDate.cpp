#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
class TMdate
{
private:
int dayofMonth;
int month;
int year;
int dayNumber;
int isleapyear(int);
void toDayNumber();
void fromDayNumber();
void isValidDate(const char *dateString , int *isValid , int *d , int *m , int *y);
public:
TMdate();
TMdate( const TMdate &other);
TMdate & operator=( const TMdate &other);
TMdate(const char *dateString);
virtual ~TMdate();
int getdayofMonth();
int getmonth();
int getyear();
int getdayofWeek();
int isleapyear();
void getMonthString(char *monthstring);
void getMonthShortString( char *monthshortstring);
void getdayofweekString( char *dayofweekstring);
void getdayofweekShortString( char *dayofweekshortstring);

// operators

TMdate & operator=( const char *dateString);
void operator+=(int);
void operator-=(int);
int operator<(const TMdate &other);
int operator>(const TMdate &other);
int operator <=(const TMdate &other);
int operator >=(const TMdate &other);
int operator==(const TMdate &other);
int operator !=(const TMdate &other);
TMdate operator +( int days);
TMdate operator -( int days);
};

TMdate :: ~TMdate()
{
// do nothing
}

TMdate :: TMdate()
{
time_t x;
time(&x);
struct tm *now;
now = localtime(&x);
dayofMonth = now->tm_mday;
month = now->tm_mon+1;
year = now-> tm_year +1900;
this->toDayNumber();
}

TMdate ::TMdate  (const char *dateString)
{
int d , m,y , isValid;
isValidDate(dateString, &isValid, &d, &m, &y);
{
if(isValid)
{
this->dayofMonth = d;
this->month = m;
this->year = y;
this->toDayNumber();
}
else
{
this->dayNumber =0;
this->dayofMonth = 0;
this->month = 0;
this->year = 0;
}
}
}

TMdate :: TMdate( const TMdate &other)
{
this->dayNumber = other.dayNumber;
this->dayofMonth = other.dayofMonth;
this->month = other.month;
this->year = other.year;
}

TMdate & TMdate :: operator=( const TMdate &other)
{
this->dayNumber = other.dayNumber;
this->dayofMonth = other.dayofMonth;
this->month = other. month;
this->year = other. year;
return *this;
}

void  TMdate ::isValidDate(const char *dateString , int *isValid , int *d , int *m , int *y)
{
int dd , mm ,yy ;
int sepindex1 , sepindex2 , i ,r;
char mth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
char sep;
*isValid = 0;
if(dateString == NULL) return;
int  x= strlen(dateString);
if(x<8 || x>10) return;
if(!(dateString[1]=='/' || dateString[2]=='/' || dateString[1]=='-' || dateString[2] == '-')) return;
 if(dateString[1]=='/' || dateString[1]== '-') sepindex1 = 1;
else sepindex1 = 2;
sep = dateString[sepindex1];
if(dateString[0]<48 || dateString[0]>57) return;
if(sepindex1==2 && (dateString[1]<48 || dateString[1]>57)) return;
if(sepindex1==1)
{
dd =dateString[0]-48;
if(dd==0) return;
}
else
{
dd = ((dateString[0]-48)*10) +(dateString[1]-48);
if(dd == 0) return;
}
i = sepindex1 +1;
if(!(dateString[i+1]== sep || dateString[i+2]== sep)) return;
if(dateString[i+1] == sep) sepindex2 = i+1;
else sepindex2 = i+2;
if(dateString[i]<48 || dateString[i]>57) return;
if(sepindex2==2 && (dateString[i+1]<48 || dateString[i+1]>57)) return;
if(sepindex2==1)
{
mm = dateString[i] -48;
}
else
{
mm = ((dateString[i] - 48)*10) +(dateString[i+1]-48);
}
if( mm<1 || mm>12) return;
i = sepindex2 +1;
yy= 0;
r=0;
while(r<=3)
{
if(dateString[i+r]<48 || dateString[i+r]>57 ) return;
yy = (yy*10) + (dateString[i+r]-48);
r++;
}
if(yy<1901) return;
if(yy%400 == 0) mth[1]=29;
else if(yy%100 == 0) mth[1]= 28;
else if(yy%4==0) mth[1] = 29;
else mth[1] = 28;

if(dd<1 || dd > mth[mm-1]) return;
*d =dd;
*m =mm;
*y = yy;
*isValid = 1;
}
int  TMdate:: isleapyear(int  y)
{
if(y%400==0) return 1;
else if(y%100==0) return 0;
else if(y%4==0) return 1;
else return 0;
}
void TMdate :: fromDayNumber()
{
if(this->dayNumber<=0)
{
this->dayofMonth =  0;
this-> month =0;
this->year = 0;
return;
}
int d,m,y;
int x= this->dayNumber;
int dayinyear;
int dayinmonth;
y=1901;
while(1)
{
if(isleapyear(y)) dayinyear =366;
else dayinyear = 365;
if(x<=dayinyear) break;
x = x- dayinyear;
y =y+1;
}
int mth[12] ={ 31,28,31,30,31,30,31,31,30,31,30,31};
if(isleapyear(y)) mth[1] =29;
m=0;
while(1)
{
dayinmonth = mth[m];
if(x<dayinmonth) break;
x =x-dayinmonth;
m++;
}
m++;
d=x;
this->dayofMonth = d;
this->month = m;
this->year = y;
}

void TMdate :: toDayNumber()
{
int x=0;
int y=1901;
int m;
while(y <this->year)
{
if(isleapyear(y))  x= x+366;
else x= x+365;
y++;
}
int mth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
if(isleapyear(this->year)) mth[1] =29;
int ep = this->month -2;
m=0;
while(m<=ep)
{
x = x+ mth[m];
m++;
}
x =x+this->dayofMonth;
this-> dayNumber = x;
}

int TMdate:: getdayofMonth()
{
return this-> dayofMonth;
}

int TMdate:: getmonth()
{
return this->month;
}

int TMdate:: getyear()
{
return this->year;
}

void TMdate :: getMonthString(char *monthstring)
{
if(this->dayNumber == 0)
{
*monthstring = '\0';
return;
}
if(this->month == 1) strcpy(monthstring , "January");
if(this->month == 2) strcpy(monthstring , "febuary");
if(this->month == 3) strcpy(monthstring , "march");
if(this->month == 4) strcpy(monthstring , "April ;");
if(this->month == 5) strcpy(monthstring , "may ");
if(this->month == 6) strcpy(monthstring , "June");
if(this->month == 7) strcpy(monthstring , "July");
if(this->month == 8) strcpy(monthstring , "Auguest");
if(this->month == 9) strcpy(monthstring , "september");
if(this->month == 10) strcpy(monthstring , "octomber");
if(this->month == 11) strcpy(monthstring , "November");
if(this->month == 12) strcpy(monthstring , "december");
}

void TMdate :: getMonthShortString( char *monthshortstring)
{
if(this->dayNumber == 0)
{
*monthshortstring = '\0';
}
if(this->month == 1) strcpy(monthshortstring , "Jan");
if(this->month == 2) strcpy(monthshortstring , "feb");
if(this->month == 3) strcpy(monthshortstring , "mar");
if(this->month == 4) strcpy(monthshortstring , "Apr");
if(this->month == 5) strcpy(monthshortstring , "may");
if(this->month == 6) strcpy(monthshortstring , "Jun");
if(this->month == 7) strcpy(monthshortstring , "Jul");
if(this->month == 8) strcpy(monthshortstring , "Aug");
if(this->month == 9) strcpy(monthshortstring , "sep");
if(this->month == 10) strcpy(monthshortstring ,"oct");
if(this->month == 11) strcpy(monthshortstring ,"Nov");
if(this->month == 12) strcpy(monthshortstring ,"dec");
}
int  TMdate ::getdayofWeek()
{
int leftdays = this->dayNumber% 7;
int dow = 2+ leftdays;
if(dow > 7) dow = dow%7;
return dow;
}

void TMdate :: getdayofweekString( char *dayofweekstring)
{
if(this->dayNumber == 0)
{
*dayofweekstring = '\0';
return;
}
 int dow = getdayofWeek();
if(dow==1) strcpy(dayofweekstring , "Sunday");
else if(dow==2) strcpy(dayofweekstring , "Monday");
else if(dow==3) strcpy(dayofweekstring , "Tuesday");
else if(dow==4) strcpy(dayofweekstring , "Wednesday");
else if(dow==5) strcpy(dayofweekstring , "Thursday");
else if(dow==6) strcpy(dayofweekstring , "Friday");
else  strcpy(dayofweekstring , "Saturday");
}

void  TMdate :: getdayofweekShortString( char *dayofweekshortstring)
{
if(this->dayNumber == 0)
{
*dayofweekshortstring = '\0';
return;
}
int dow = getdayofWeek();
if(dow==1)strcpy(dayofweekshortstring, "Sun");
else if(dow==2)strcpy(dayofweekshortstring, "Mon");
else if(dow==3)strcpy(dayofweekshortstring, "Tue");
else if(dow==4)strcpy(dayofweekshortstring, "Wed");
else if(dow==5)strcpy(dayofweekshortstring, "Thu");
else if(dow==6)strcpy(dayofweekshortstring, "Fri");
else  strcpy(dayofweekshortstring , "Sat");
}

int TMdate :: isleapyear()
{
if(this->dayNumber== 0 ) return 0;
if(this->dayNumber%400 == 0) return 1;
if(this->dayNumber%100 == 0) return 0;
if(this->dayNumber%4 == 0) return 1;
return 0;
}
ostream & operator<<(ostream &oo , TMdate &tmdate)
{
oo<<tmdate.getdayofMonth()<<"/"<<tmdate.getmonth()<<"/"<<tmdate.getyear();
return oo;
}

void TMdate :: operator+=(int days)
{
if(this->dayNumber == 0) return;
this->dayNumber  += days;
this->fromDayNumber();
}

void TMdate :: operator-=(int days)
{
if(this->dayNumber == 0) return;
this->dayNumber  -= days;
this->fromDayNumber();
}

int TMdate :: operator<(const TMdate &other)
{
return this->dayNumber < other.dayNumber;
}

int  TMdate :: operator>(const TMdate &other)
{
return this->dayNumber > other.dayNumber;
}
int  TMdate :: operator <=(const TMdate &other)
{
return this->dayNumber <= other.dayNumber;
}
int  TMdate :: operator >=(const TMdate &other)
{
return this->dayNumber >= other.dayNumber;
}
int TMdate :: operator==(const TMdate &other)
{
return this->dayNumber== other.dayNumber;
}
int TMdate :: operator !=(const TMdate &other)
{
return this->dayNumber !=  other.dayNumber;
}
TMdate TMdate ::  operator+( int days)
{
if(this->dayNumber == 0) return TMdate("00/00/0000");
TMdate date;
date.dayNumber = this->dayNumber +days;
date.fromDayNumber();
return date;
}
TMdate TMdate :: operator-( int days)
{
if(this->dayNumber == 0) return TMdate("00/00/0000");
TMdate date;
date.dayNumber = this->dayNumber - days;
date.fromDayNumber();
return date;
}

TMdate & TMdate ::  operator=( const char *dateString)
{
int d,m,y,isValid;
isValidDate(dateString, &isValid, &d, &m, &y);
{
if(isValid)
{
this->dayofMonth = d;
this->month = m;
this->year = y;
this->toDayNumber();
}
else
{
this->dayNumber =0;
this->dayofMonth = 0;
this->month = 0;
this->year = 0;
}
}
return *this;
}

int main()
{
TMdate date1  = "2/07/2023";
TMdate date2 = "10/10/2020";
TMdate date3 = "12/10/2020";
cout<<(date1== date2)<<endl;
cout<<(date1== date3)<<endl;
cout<<(date1 < date2)<<endl;
cout<<(date1 > date2)<<endl;
cout<<(date1 <= date2)<<endl;
cout<<(date1 >= date2)<<endl;
cout<<(date1!= date3)<<endl;

TMdate date4 = date2;
cout<<date4<<endl;
TMdate date5 = date1;
cout<<date5<<endl;

TMdate date6 = "29/05/2021";
cout<<date6.getdayofWeek()<<endl;
char a[21];
date6.getdayofweekString(a);
cout<<a<<endl;
date6. getdayofweekShortString(a);
cout<<a<<endl;

TMdate date7;
date7 = date6 +10;
cout<<date7<<endl;
TMdate date8 ;
date8 = date6 - 20;
cout<<date8<<endl;
TMdate date9 = "1/1/1885";
cout<<date9<<endl;
return 0;
}


