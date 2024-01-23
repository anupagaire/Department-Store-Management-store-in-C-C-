#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
#include<fstream.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<time.h>
#define RETURNTIME 15
char catagories[][15]={"BISCUIT\t","BAKERY\t","SNACKS\t","CHOCOLATE","DRINKS\t","TOILETRIES", "FROZEN FOODS", "DAIRY PRODUCT"};
void returnfunc(void);
void mainmenu(void);
void additems(void);
void deleteitems(void);
void edititems(void);
void searchitems(void);
void issueitems(void);
void viewitems(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void issuerecord();
void deleterecord();
//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;
//list of global variable
int s;
char finditems;
 struct meroDate
 {
	int mm,dd,yy;
	int total, sum, initial, final;
 };
struct items
{
	int id;
	char cuname[20];
	char category[20];
	char name[20];
	int quantity;
	float Price;
	int count;
	int rackno;
	char *cat;
	struct meroDate issued;
	struct meroDate duedate;

};
struct items a;
union REGS in, o;
int x, y, z, i, j, k, m, n, cl;
char check[9]={"password"};
void admin();
void exit();
void welcome();
void mainmenu()
{
	system("clr");
	clrscr();
	cleardevice();
	setbkcolor(0);
	int i;
	printf("\n.................... DEPARTMENT STORE MANAGEMENT SYSTEM .................\n");
	printf("\n1=> Add items   ");
	printf("\n2=> Delete items");
	printf("\n3=> Search items");
	printf("\n4=> Issue items");
	printf("\n5=> View items List");
	printf("\n6=> Edit item's Record");
	printf("\n7=> Close Application");
	printf("\nEnter your choice:\t\n");
	switch(getch())
	{
		case '1':
			additems();
			break;
		case '2':
			deleteitems();
			break;
		case '3':
			searchitems();
			printf("\nTry another search?(Y/N)\n");
			if(getch()=='y')
			{       system("clr");
				clrscr();
				cleardevice();
				setbkcolor(0);
				searchitems();
			}
			else
				mainmenu();
			break;
		case '4':
			issueitems();
			break;
		case '5':
			viewitems();
			printf("\nPress ENTER to return to main menu\n");
			a:
			if(getch()==13) //allow only use of enter
				mainmenu();
			else
				goto a;
			break;
		case '6':
			edititems();
			break;
		case '7':
			welcome();
		default:
		{
		     printf("\nWrong Entry!!\n");
		     printf("\nPlease re-entered correct option from 1 to 7\n");
		     if(getch())
			mainmenu();
		}
	}
}

void additems(void)    //funtion to add items
{
	system("clr");
	clrscr();
	cleardevice();
	int i;
	printf("\n....................SELECT CATEGORIES....................\n");
	printf("\n1=> BISCUIT ");
	printf("\n2=> BAKERY");
	printf("\n3=> SNACKS");
	printf("\n4=> CHOCOLATE");
	printf("\n5=> DRINKS");
	printf("\n6=> TOILETRIES");
	printf("\n7=> FROZEN FOODS");
	printf("\n8=> DAIRY PRODUCT");
	printf("\n9=> Back to main menu\n");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\nEnter your choice:\n");
	scanf("%d",&s);
	if(s==9)
		mainmenu() ;
	system("cls");
	fp=fopen("lib.txt","ab+");
	if(getdata()==1)
	{
		a.cat=catagories[s-1];
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		printf("\nThe Record Is Sucessfully Saved");
		printf("\nDo you want to save more?(Y / N):");
		if(getch()=='n')
			mainmenu();
		else
			additems();
	}
}
void deleteitems()    //function that delete items from file fp
{
	system("clr");
	clrscr();
	cleardevice();
	int d;
	char another='y';
	while(another=='y')  //infinite loop
	{
		printf("Enter the item ID to  delete:\n");
		scanf("%d",&d);
		fp=fopen("lib.txt","rb+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(a.id==d)
			{
				printf("\nThe Item Record Is Available");
				printf("\nItem name is %s",a.name);
				printf("\nRack No. is %d",a.rackno);
				finditems='t';
			}
		}
		if(finditems!='t')
		{
			printf("\nNo record is found modify the search\n");
			if(getch())
				mainmenu();
		}
		if(finditems=='t' )
		{
			printf("\nDo you want to delete it?(Y/N):\n");
			if(getch()=='y')
			{
			   ft=fopen("test.txt","wb+");  //temporary file for delete
			   rewind(fp);
			   while(fread(&a,sizeof(a),1,fp)==1)
			   {
				if(a.id!=d)
				{
				   fseek(ft,0,SEEK_CUR);
				   fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
				}                              //we want to delete
			   }
			   fclose(ft);
			   fclose(fp);
			   remove("lib.txt");
			   rename("test.txt","lib.txt"); //copy all item from temporary file to fp except that
			   fp=fopen("lib.txt","rb+");    //we want to delete
			   if(finditems=='t')
			   {
				printf("\nThe Record Is Sucessfully Deleted\n");
				printf("Delete another record?(Y/N)\n");
			   }
			}
			else
				mainmenu();
			another=getch();
		}
	}
	mainmenu();
}
void searchitems()
{
	int d;
	printf(":::::::::::::::::::::Search Items:::::::::::::::::");
	printf("\n1=> Search By ID");
	printf("\n2=> Search By Name");
	printf("\nEnter Your Choice:\n");
	fp=fopen("lib.txt","rb+"); //open file for reading propose
	rewind(fp);   //move pointer at the begining of file
	switch(getch())
	{
		case '1':
		{
			printf("::::Search Items By Id::::");
			printf("\nEnter the item id:\t");
			scanf("%d",&d);
			printf("\nSearching.....\n");
			while(fread(&a,sizeof(a),1,fp)==1)
			{
			   if(a.id==d)
			   {
				printf("The Item Is Available\n");
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				printf("\xB2 ID:%d\n",a.id);
				printf("\xB2");
				//printf("\xB2 Category:%s\n",a.category);
				//printf("\xB2");
				printf("\xB2 Name:%s\n",a.name);
				printf("\xB2");
				printf("\xB2 Qantity:%d\n",a.quantity);
				printf("\xB2");
				printf("\xB2 Price:Rs.%.2f\n",a.Price);
				printf("\xB2");
				printf("\xB2 Rack No:%d\n",a.rackno);
				printf("\xB2");
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				finditems='t';
			   }
			}
			if(finditems!='t')  //checks whether conditiion enters inside loop or not
			{
			   printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			   printf("\xB2");
			   printf("\xB2");
			   printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			   printf("\nNo Record Found\n");
			}
			printf("\nTry another search?(Y/N)\n");
			if(getch()=='y')
			{
				system("clr");
				clrscr();
				cleardevice();
				setbkcolor(0);
				searchitems();
			}
			break;
		}
		case '2':
		{
			char s[15];
			printf("::::Search Items By Name::::\n");
			printf("\nEnter Item Name:\t");
			scanf("%s",s);
			printf("\nSearching.....\n");
			int d=0;
			while(fread(&a,sizeof(a),1,fp)==1)
			{
			   if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
			   {
				printf("The Item Is Available\n");
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				printf("\xB2 ID:%d\n",a.id);
				printf("\xB2");
				//printf("\xB2 Category:%s\n",a.category);
				//printf("\xB2");
				printf("\xB2 Name:%s\n",a.name);
				printf("\xB2");
				printf("\xB2 Qantity:%d\n",a.quantity);
				printf("\xB2");
				printf("\xB2 Price:Rs.%.2f\n",a.Price);
				printf("\xB2");
				printf("\xB2 Rack No:%d\n",a.rackno);
				printf("\xB2");
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				d++;
			   }
			}
			if(d==0)
			{
			   printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			   printf("\xB2");
			   printf("\xB2");
			   printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			   printf("\nNo Record Found\n");
			}
			printf("\nTry another search?(Y/N)\n");
			if(getch()=='y')
			{
				system("clr");
				clrscr();
				cleardevice();
				setbkcolor(0);
				searchitems();
			}
			break;
		}
		default:
		{
		     printf("\nWrong Entry!!\n");
		     printf("\nPlease re-entered correct option from 1 or 2\n");
		     if(getch())
			searchitems();
		}
	}
	fclose(fp);
}
void issueitems(void)  //function that issue items from store
{
	int t;
	time_t s;
	struct tm* current_time;
	s = time(NULL);
 //	current_time = localtime(&s);
	printf(":::::::::::::ISSUE SECTION::::::::::::::\n");
	printf("\n1=> Issue a item");
	printf("\n2=> View Issued item");
	printf("\n3=> Search Issued item");
	printf("\n4=> Remove Issued item");
	printf("\n5=> Return to Menu");
	printf("\nEnter a Choice:\n");
	switch(getch())
	{
		case '1':  //issue item
		{
			FILE *fg;
			int c=0;
			char another='y';
			while(another=='y')
			{
			   printf(":::Issue Item section:::\n");
			   printf("Enter the Item Id:\n");
			   scanf("%d",&t);
			   fp=fopen("lib.txt","rb");
			   fs=fopen("Issue.txt","ab+");
			   if(checkid(t)==0) //issues those which are present in store
			   {
				fg=fopen("temp.txt","wb+");
				printf("The Item Record Is Available!\n");
				printf("There are %d unissued items in store\n",a.quantity);
				printf("The name of item is %s\n",a.name);
				printf("Enter customer name:\n");
				scanf("%s",a.cuname);
				cout<<"Issued date:"<<endl;
				cout<<"Year:";
				cin>>a.issued.yy;
				cout<<"Month:";
				cin>>a.issued.mm;
				cout<<"day:";
				cin>>a.issued.dd;
				if(a.issued.dd>30)
				{
				   a.issued.mm+=a.issued.dd/30;
				   a.issued.dd-=30;
				}
				if(a.issued.mm>12)
				{
				   a.issued.yy+=a.issued.mm/12;
				   a.issued.mm-=12;
				}
				printf("Issued date=%d-%d-%d\n",a.issued.dd,a.issued.mm,a.issued.yy);
				printf("The Item of ID %d is issued\n",a.id);
				a.quantity--;
				int quan = a.quantity;
				printf("Now the unissued book is %d",a.quantity);
				//printf("\nThe Item of ID %d is issued\n",a.id);
				fseek(fs,sizeof(a),SEEK_END);
				fwrite(&a,sizeof(a),1,fs);
				fclose(fs);
				fclose(fp);
				fp=fopen("lib.txt","rb");
				while(fread(&a,sizeof(a),1,fp)==1)
				{
				 if(a.id==t)
				 {
				   a.quantity = quan;
				   fwrite(&a,sizeof(a),1,fg);
				 }
				 else
				 {
				  fwrite(&a,sizeof(a),1,fg);
				 }
				}
				rewind(fp);
				fclose(fp);
				fclose(fg);
				fg=fopen("temp.txt","rb");
				fp=fopen("lib.txt","wb+");
				while(fread(&a,sizeof(a),1,fg)==1)
				{
				  fwrite(&a,sizeof(a),1,fp);
				}
				fclose(fg);
				fclose(fp);
				c=1;
			   }
			   if(c==0)
			   {
				printf("No record found\n");
			   }
			   printf("Issue any more(Y/N):\n");
			   fflush(stdin);
			   another=getch();
			   fclose(fp);
			}
			break;
		}

			 case '2':  //show issued item list
		{
			system("cls");
			int j=4,day_pass,mon_pass;
			printf(":::::::::::::Issued Item List:::::::::::::\n");
			printf("CUSTOMER NAME\tCATEGORY\tID\tITEM NAME\tISSUED DATE\n");
			fs=fopen("Issue.txt","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
			   printf("    %s\t",a.cuname);
			   printf("%s\t",a.cat);
			   printf("    %d\t",a.id);
			   printf("    %s\t\t",a.name);
			   printf(" %d-%d-%d\t",a.issued.yy,a.issued.mm,a.issued.dd);

			    day_pass= current_time->tm_mday;
			    mon_pass= (current_time->tm_mon + 1);

			   day_pass = (day_pass + (mon_pass*30));
			   if(day_pass<0)
			   {
			   day_pass = 0;
			   }
			  // printf("=>Charge: %d",day_pass);
			   printf("\n");
			   j++;
			}
			fclose(fs);

			returnfunc();
		}
		break;


	  case '3':   //search issued items by id
		{
		   printf("Enter Item ID:\n");
		   int p,c=0;
		   char another='y';
		   while(another=='y')
		   {
			scanf("%d",&p);
			fs=fopen("Issue.txt","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
			   if(a.id==p)
			   {
				issuerecord();
				printf("Press any key.......\n");
				getch();
		     //		issuerecord();
				c=1;
			   }
			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
			   printf("No Record Found\n");
			}
			printf("Try Another Search?(Y/N)\n");
			another=getch();
		   }
		}
		break;
		  case '4':  //remove issued items from list
		{
			int b;
			FILE *fg;  //declaration of temporary file for delete
			char another='y';
			while(another=='y')
			{
				printf("Enter item id to remove:\n");
				scanf("%d",&b);
				fs=fopen("Issue.txt","rb+");
				while(fread(&a,sizeof(a),1,fs)==1)
				{
					if(a.id==b)
					{
						issuerecord();
						finditems='t';
					}
					if(finditems=='t')
					{
					   printf("Do You Want to Remove it?(Y/N)\n");
					   if(getch()=='y')
					   {
					      fg=fopen("record.txt","wb+");
					      rewind(fs);
					      while(fread(&a,sizeof(a),1,fs)==1)
					      {
						if(a.id!=b)
						{
						   fseek(fs,0,SEEK_CUR);
						   fwrite(&a,sizeof(a),1,fg);
						}
					      }
					      fclose(fs);
					      fclose(fg);
					      remove("Issue.txt");
					      rename("record.txt","Issue.txt");
					      printf("The issued item is removed from list\n");

					   }
					}
					if(finditems!='t')
					{
					   printf("No Record Found\n");
					}
				}
				printf("Delete any more?(Y/N)\n");
				another=getch();
			}
		}
		default:
		printf("\Wrong Entry!!");
		getch();
		issueitems();

		case '5':
			mainmenu();
		break;
	}
	returnfunc();
}
void viewitems(void)  //show the list of item persists in store
{
	int i=0,j;
	printf(":::::::::::Items list::::::::::\n");
	printf(".....CATEGORY.....\t\tID\t NAME\tQTY\tPRICE\tRackNo\n");
	j=4;
	fp=fopen("lib.txt","rb");
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		printf("%s\t",a.cat);
		printf("\t\t%d\t",a.id);
		//printf("%s\t",a.category);
		printf("%s\t",a.name);
		printf("%d\t",a.quantity);
		printf("%.2f\t",a.Price);
		printf("%d\t",a.rackno);
		printf("\n");
		j++;
		i=i+a.quantity;
	}
	printf("Total Items =%d\n",i);
	fclose(fp);
 //	returnfunc();
}
void edititems(void)  //edit information about item
{
	int c=0;
	int d,e;
	printf("\n****Edit Items Section****\n");
	char another='y';
	while(another=='y')
	{
		printf("Enter Item Id to be edited:\n");
		scanf("%d",&d);
		fp=fopen("lib.txt","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("The Item Is Available\n");
				printf("The Item ID:\t\t%d",a.id);
				//cout<<"\nThe Item Category:\t"<<a.category;
				cout<<"\nThe Item Name:\t\t"<<a.name;
				cout<<"\nThe Item Quantity:\t"<<a.quantity;
				cout<<"\nThe Item Price:\t\t"<<a.Price;
				cout<<"\nThe Item Rack No.:\t"<<a.rackno;
				//printf("\nEnter New Category:\t\t");
				//scanf("%s",a.category);
				printf("Enter New Name:\t");
				scanf("%s",a.name);
				printf("Add New Quantity:\t");
				scanf("%d",&a.quantity);
				printf("Enter New Price:\t");
				scanf("%f",&a.Price);
				printf("Enter New Rack No.:\t");
				scanf("%d",&a.rackno);
				printf("The record is modified\n");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("No record found\n");
			}
		}
		printf("Modify another Record?(Y/N)\n");
		fflush(stdin);
		another=getch() ;
	}
	returnfunc();
}
void returnfunc(void)
{
	printf("Press ENTER to return to main menu\n");
	a:
	if(getch()==13) //allow only use of enter
		mainmenu();
	else
	goto a;
}
int getdata()
{
	int t;
	printf("Enter the Information Below\n");
	printf("\nCategory:");
	printf("%s",catagories[s-1]);
	printf("\nItem ID:\t");
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		printf("\nThe item id already exists\n");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	//printf("Item Category:\t");
	//scanf("%s",a.category);
	printf("Name:\t\t");
	scanf("%s",a.name);
	printf("Quantity:\t");
	scanf("%d",&a.quantity);
	printf("Price:\t\t");
	scanf("%f",&a.Price);
	printf("Rack No:\t");
	scanf("%d",&a.rackno);
	return 1;
}
int checkid(int t)  //check whether the item is exist in store or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if item exits
	return 1; //return 1 if it not
}
void issuerecord()  //display issued item's information
{
	printf("\nThe item has taken by Mr. %s",a.cuname);
	printf("\nIssued Date:%d-%d-%d",a.issued.yy,a.issued.mm,a.issued.dd);

	printf("\n");
}
void deleterecord()  //display delete item's information
{
	printf("\nThe item has taken by Mr. %s",a.cuname);
	printf("\nIssued Date:%d-%d-%d",a.issued.yy,a.issued.mm,a.issued.dd);

			//cout<<"Year:";
			//cout<<"Month:";
			//cout<<"day:";

}
void click(int *, int *, int *)
{
	in.x.ax=3;
	int86(0x33, &in, &o);
	cl=o.x.bx;
	m=o.x.cx;
	n=o.x.dx;
}
void admin()
{

       char pass[9];
	top1:
       cleardevice();
       setbkcolor(1);
       int gd=DETECT, gm;
       initgraph(&gd, &gm, "..\\bgi");
       in.x.ax=1;
       int86(0x33, &in, &o);
       setbkcolor(1);
       settextstyle(DEFAULT_FONT, 0, 1);
       setlinestyle(SOLID_LINE,7, THICK_WIDTH);
       setfillstyle(SOLID_LINE, 3);
       outtextxy(x/3, y/2-50,"USER NAME:");
       rectangle(x/3+100, y/2-60, x/3+200, y/2-35);
       outtextxy(x/3+120, y/2-50,"ADMIN");
       outtextxy(x/3+3, y/2+5,"PASSWORD:");
       rectangle(x/3+100, y/2-5, x/3+200,y/2+20);
       outtextxy(x/3+140,y/2+55,"OK");
       rectangle(x/3+122,y/2+50,x/3+173,y/2+65);
       int i=0;
       while(i<8)
       {
	  gotoxy(x/3+85+i,y/2+33);
	  pass[i]=getch();
	  if(pass[i]==8)
	  {
	    cout<<"\b \b";
	    i--;
	    if(i<0)
	    {
	      cout<<"";
	      i++;
	    }
	  }
	  else if(pass[i]==13)
	    break;
	  else
	  {
	    cout<<"*";
	    i++;
	  }
	}
	  pass[i]='\0';
	  char hit;
	  while(!kbhit())
	  {
	     click(&m, &n, &cl);
	     if(m>(x/3+122) && m<(x/3+173) && n>(y/2+50) && n<(y/2+65) && cl==1)
	     {
     //	     entry:
	    if(strcmp(check,pass)==0)
	    {
	      setcolor(WHITE);
	      outtextxy(x/3+100,y/2+80,"Correct Password!!!");
	      delay(1000);
	      cleardevice();

	     mainmenu();
	    }
	    else
	    {
	      setcolor(RED);
	      outtextxy(x/3+100,y/2+80,"Wrong Password!!!");
	      delay(1000);
	      cleardevice();
     //	      goto top1;
	    }
	 }
     }
}
void welcome()
{
	cleardevice();
	int gd=DETECT, gm;
	initgraph(&gd, &gm, "..\\bgi");
	in.x.ax=1;
	int86(0x33, &in, &o);
	for(i=0;i<=310;i+=8)
	{
		setcolor(i-5);
		outtextxy((x/2-155)+i,(y/2-200),"*");
		outtextxy((x/2-155)+i,(y/2-50),"*");
	}
	for(i=0;i<=145;i+=5)
	{
		outtextxy((x/2-155),(y/2-200)+i,"*");
		outtextxy((x/2+149),(y/2-195)+i,"*");
	}
	setcolor(GREEN);
	settextstyle(8,0,3);
	outtextxy(x/2-70,y/2-180,"WELCOME TO");
	outtextxy(x/2-143,y/2-140,"STORE MANAGEMENT");
	outtextxy(x/2-40,y/2-100,"SYSTEM");
	delay(1000);
	setlinestyle(SOLID_LINE,7, THICK_WIDTH);
	rectangle(x/2-190,y/2,x/2-40,y/2+30);
	outtextxy(x/2-180,y/2,"ADMIN");
	rectangle(x/2+90,y/2,x/2+210,y/2+30);
	outtextxy(x/2+100,y/2,"EXIT");

	while(!kbhit())
	{
		click(&m, &n, &cl);
	   if(m>(x/2-190) && m<(x/2-40) && n>(y/2) && n<(y/2+30) && cl==1)
	   {
		cleardevice();
		setbkcolor(1);
		cout<<"\n\n\n\n\n\n\t\t   *****************************************";
		cout<<"\n\t\t\t*******************************";
		cout<<"\n\t\t   *****************************************";
		cout<<"\n\t\t\t    Welcome to Admin Pannel";
		cout<<"\n\t\t   *****************************************";
		cout<<"\n\t\t\t*******************************";
		cout<<"\n\t\t   *****************************************";
		delay(2000);
		cleardevice();

	     admin();

	  }
	  else if(m>(x/2+90) && m<(x/2+210) && n>(y/2) && n<(y/2+30) && cl==1)

	  {
		exit(0);
	  }

	}
}
void main()
{
	clrscr();
	int gd=DETECT, gm;
	initgraph(&gd, &gm,"..\\bgi");
	in.x.ax=1;
	int86(0x33, &in, &o);
	x=getmaxx();
	y=getmaxy();
	welcome();
	getch();
}
