#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
class profile
 {
  public:
  char name[50];
  char username[50];
  char pass[50];
  int un;
  char me[500];
  int age;
  int nm;
  profile()
	{
	 nm=0;
	}
  void edit()
	{
	 nm++;
	}
 };
struct message
 {
  char u[50];
  char su[50];
  char me[500];
 };
void read(profile &p)
 {
  char c;
  int i=0;
  cout<<"Name : ";
  gets(p.name);
  cout<<"Age : ";
  cin>>p.age;
  cout<<"Username : ";
  gets(p.username);
  cout<<"Password : ";
  while(c!='\r')
	{
	 c=getch();
	 if(c!=8)
	  {
		p.pass[i]=c;
		i++;
		cout<<'*';
	  }
	};
  p.pass[i-1]='\0';

 }
void display(profile p)
 {
  cout<<"Name : "<<p.name<<endl;
  cout<<"Age : "<<p.age<<endl;
  cout<<"Username : "<<p.username<<endl;
  cout<<"Messages : "<<p.nm<<endl;
  cout<<"User Number : "<<p.un<<endl;
 }
int create(int nu)
 {
  ofstream fout;
  fout.open("Pro.dat",ios::binary);
  profile p;
  read(p);
  p.un=nu;
  fout.write((char*)&p,sizeof(p));
  fout.close();
  cout<<endl<<"Account Successfully Created."<<endl;
  return 1;
 }
void morec(int nu)
 {
  ofstream fout;
  fout.open("Pro.dat",ios::binary|ios::app);
  profile p;
  read(p);
  p.un=nu;
  fout.write((char*)&p,sizeof(p));
  fout.close();
  cout<<endl<<"Account Successfully Created."<<endl;
 }

int cu(char u[50])
 {
  profile p;
  int x=1;
  char nu[50];
  fstream file;
  file.open("Pro.dat",ios::in|ios::out|ios::binary);
  cout<<"Enter new Username : ";
  gets(nu);
  file.read((char*)&p,sizeof(p));
  int N=sizeof(p);
  while(file)
	{
	 if(strcmp(p.username,u)==0)
	  {
		strcpy(p.username,nu);
		cout<<endl<<"New Username : "<<p.username<<endl;
		file.seekp(-N,ios::cur);
		file.write((char*)&p,sizeof(p));
		x=0;
	  }
	 file.read((char*)&p,sizeof(p));
	}
  file.close();
  cout<<endl<<"YOU WILL HAVE TO LOGIN AGAIN WITH YOUR NEW USERNAME."<<endl;
  return x;
 }
int cp(char u[50])
 {
  profile p;
  int x=1,N=sizeof(p);
  char np[50],pass[50];
  fstream fin;
  fin.open("Pro.dat",ios::binary|ios::in|ios::out);
  fin.read((char*)&p,sizeof(p));
  while(fin)
	{
	 if(strcmp(p.username,u)==0)
	  {
		do
		{
		 cout<<endl<<"Enter Old Password : ";
		 gets(pass);
		 if(strcmp(p.pass,pass)==0)
		  {
			cout<<"Enter new Password : ";
			gets(np);
			strcpy(p.pass,np);
			fin.seekp(-N,ios::cur);
			fin.write((char*)&p,sizeof(p));
			cout<<endl<<"New Password : "<<np<<endl;
			x=0;
			cout<<endl<<"You will have to login again with your new password."<<endl;
			break;
		  }
		 else
		  {
			char ch;
			cout<<"Enter Old Password again ? (y/n) :";
			cin>>ch;
			if(ch=='y')
			 continue;
			else
			 break;
		  }
		}
	  while(x==1);
	  }
	 fin.read((char*)&p,sizeof(p));
	}
  return x;
  fin.close();
 }
int da(char u[50])
 {
  char ch;
  cout<<endl<<"Are you sure you want to delete your account? You cannot retrieve it later."<<endl;
  cin>>ch;
  if(ch=='y'||ch=='Y')
	{
	 profile p;
	 ifstream fin("Pro.dat",ios::binary);
	 ofstream fout("NPro.dat",ios::binary);
	 fin.read((char*)&p,sizeof(p));
	 while(fin)
		{
		 if(strcmp(p.username,u)!=0)
		  {
			fout.write((char*)&p,sizeof(p));
		  }
		 fin.read((char*)&p,sizeof(p));
		}
	 cout<<endl<<"Ok"<<endl;
	 remove("Pro.dat");
	 rename("NPro.dat","Pro.dat");
	 fin.close();
	 fout.close();
	 cout<<endl<<"Account Deleted."<<endl;
	 return 0;
  }
  else
	cout<<endl<<"We'll try to better your experience."<<endl;
  return 1;
 }
int setting(char u[50])
 {
  int c,x;
  char ch;
  do
	{
	 cout<<"1. Change Username."<<endl;
	 cout<<"2. Change Password."<<endl;
	 cout<<"3. Delete Account."<<endl;
	 cin>>c;
	 switch(c)
	  {
		case 1:x=cu(u); break;
		case 2:x=cp(u); break;
		case 3:x=da(u); break;
		default:cout<<"Enter correct choice."<<endl;
				  continue;
	  }
	 if(x!=0)
	  {
		cout<<"Enter again? (y/n) : ";
		cin>>ch;
	  }
	}
  while((ch=='y'||ch=='Y')&&(x));
  return x;
 }
int logout()
 {
  return 0;
 }
void status(char u[50])
 {
  char s[500];
  ofstream fout("statuses.dat",ios::binary|ios::app);
  gets(s);
  fout<<u<<endl;
  fout<<s<<endl;
  fout.close();
 }
void noti(char u[50])
 {
  char line[500];
  ifstream fin("statuses.dat");
  fin.getline(line,500);
  while(fin)
	{
	 cout<<line<<endl;
	 fin.getline(line,500);
	}
  fin.close();
 }
void messages(char u[50])
 {
  ifstream fin;
  profile p;
  fin.open("Pro.dat",ios::binary);
  fin.read((char*)&p,sizeof(p));
  while(fin)
	{
	if(strcmp(p.username,u)==0)
	 {
	  char line[500];
	  message m;
	  ifstream fin1;
	  fin1.open("Messages.dat",ios::binary);
	  fin1.read((char*)&m,sizeof(m));
	  while(fin1)
		{
		 if(strcmp(m.u,u)==0)
		  {
			cout<<m.su<<" says : "<<endl;
			cout<<m.me<<endl;
			break;
		  }
		 fin1.read((char*)&m,sizeof(m));
		}
	  fin1.close();
	 }
	fin.read((char*)&p,sizeof(p));
	}
  fin.close();
 }
void smessage(char u[50])
 {
  char m[500],mu[50];
  int flag=0;
  cout<<"Enter the name of the user whom you want to text.";
  gets(mu);
  ifstream fin;
  profile p;
  fin.open("Pro.dat",ios::binary);
  fin.read((char*)&p,sizeof(p));
  while(fin)
	{
	if(strcmp(p.username,mu)==0)
	 {
	  flag=1;
	  break;
	 }
	fin.read((char*)&p,sizeof(p));
	}
  if(flag==0)
	cout<<endl<<"No such user found."<<endl;
  else
	{
	 char c,m1[500];
	 cout<<"Enter message : ";
	 gets(m1);
	 message m;
	 strcpy(m.u,mu);
	 strcpy(m.su,u);
	 strcpy(m.me,m1);
	 ofstream fout2("Messages.dat",ios::binary);
	 fout2.write((char*)&m,sizeof(m));
	 fout2.close();
	 profile p1;
	 p.edit();
	 ifstream fin1("Pro.dat",ios::binary);
	 ofstream fout1("NPro.dat",ios::binary);
	 fin.read((char*)&p1,sizeof(p1));
	 while(fin1)
		{
		 if(strcmp(p1.username,mu)!=0)
		  {
			fout1.write((char*)&p1,sizeof(p1));
		  }
		 else
			fout1.write((char*)&p,sizeof(p));
		 fin1.read((char*)&p1,sizeof(p1));
		}
	 remove("Pro.dat");
	 rename("NPro.dat","Pro.dat");
	 fin1.close();
	 fout1.close();
	}
  fin.close();
 }
int home(char u[50])
 {
  clrscr();
  int x=0,c;
  char ch;
  cout<<endl<<"Welcome "<<u<<endl;
  cout<<endl<<"HOME."<<endl;
  do
	{
	 cout<<"1. What's on your mind ?"<<endl;
	 cout<<"2. Notifications."<<endl;
	 cout<<"3. Messages."<<endl;
	 cout<<"4. Send A Message."<<endl;
	 cout<<"5. Go Back To Main Menu."<<endl;
	 c=getch();
	 switch(c)
	  {
		case '1':status(u);break;
		case '2':noti(u);break;
		case '3':messages(u);break;
		case '4':smessage(u);break;
		case '5':x=2;
					break;
	  }
	}
  while(ch=='y'||ch=='Y');
  return x;
 }
void pro(char u[50])
 {
  ifstream fin;
  profile p;
  fin.open("Pro.dat",ios::binary);
  fin.read((char*)&p,sizeof(p));
  while(fin)
	{
	if(strcmp(p.username,u)==0)
	 {
	  cout<<"Profile."<<endl;
	  display(p);
	  break;
	 }
	fin.read((char*)&p,sizeof(p));
	}
  fin.close();
 }
void loggedin(char u[50])
 {
  int c,x=1;
  char ch='n';
  do
	{
	 a:
    clrscr();
	 cout<<endl<<"Welcome "<<u<<endl;
	 cout<<"1. Home."<<endl;
	 cout<<"2. Profile."<<endl;
	 cout<<"3. Settings."<<endl;
	 cout<<"4. Log Out."<<endl;
	 c=getch();
	 switch(c)
	  {
		case '1':x=home(u); break;
		case '2':pro(u); break;
		case '3':x=setting(u);break;
		case '4':x=logout(); break;
		default:cout<<"Enter correct choice."<<endl;
				  continue;
	  }
	 if(x==2)
	  goto a;
	 else if(x!=0)
	 {
	  cout<<"Enter again? (y/n) : ";
	  cin>>ch;
	 }
	}
  while((ch=='y'||ch=='Y')&&(x));
 }
void login()
 {
  int flag=0;
  char ch,u[50],pa[50];
  ifstream fin;
  fin.open("Pro.dat",ios::binary);
  cout<<"Username : ";
  gets(u);
  profile p;
  fin.read((char*)&p,sizeof(p));
  while(fin)
	{
	 if(strcmp(p.username,u)==0)
	  {
		flag=1;
		break;
	  }
	 fin.read((char*)&p,sizeof(p));
	}
  if(flag==0)
	cout<<endl<<"No such user found."<<endl;
  else
	{
	 a:
	 cout<<"Password : ";
	 gets(pa);
	 if(strcmp(p.pass,pa)==0)
	  {
		cout<<"Successfully logged in."<<endl;
		loggedin(u);
	  }
	 else
	  {
		char ch;
		cout<<"Wrong Password."<<endl;
		cout<<"Enter again? (y/n) :";
		cin>>ch;
		if(ch=='y'||ch=='Y')
		 goto a;
	  }
	}
 }
void main()
 {
  int x=0,c,nu=0;
  char ch;
  cout<<"\t\t\t\tWelcome."<<endl<<endl<<endl;
  cout<<"\t  ******      *      *     *  *       *      *       ******  "<<endl;
  cout<<"\t *          *   *    **    *  *       *    *   *    *        "<<endl;
  cout<<"\t*          *     *   * *   *  *       *   *     *  *         "<<endl;
  cout<<"\t *******   *_____*   *  *  *   *     *    *_____*   *******  "<<endl;
  cout<<"\t       *   *     *   *   * *    *   *     *     *         *  "<<endl;
  cout<<"\t      *    *     *   *    **     * *      *     *        *   "<<endl;
  cout<<"\t *****     *     *   *     *      *       *     *   *****    "<<endl;
  cout<<endl;
  getch();
  do
	{
	 clrscr();
	 cout<<endl<<"\t\t\t\tMAIN MENU."<<endl;
	 cout<<"\t\t\t\t1. Create Account."<<endl;
	 cout<<"\t\t\t\t2. Log In."<<endl;
	 c=getch();
	 switch(c)
	  {
		case '1': clrscr();
					 if(x==0)
					{
					 nu++;
					 x=create(nu);
					}
				  else
					{
					 nu++;
					 morec(nu);
					}
				  break;
		case '2': clrscr();login(); break;
		default: cout<<"Enter correct choice."<<endl;
					continue;
	  }
	 cout<<"Continue? (y/n) : ";
	 cin>>ch;
	}
  while(ch=='y'||ch=='Y');
 }
