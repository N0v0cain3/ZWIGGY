#include<iostream.h>
#include<dos.h>
#include<conio.h>
#include<string.h>
#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<iomanip.h>
#include<fstream.h>
int check=0;
int flag=0;
void menu();
void admin_menu();
void user();
class product
{
	int pno;
	char name[50];
	float price,qty,tax,dis;
	public:
	void create_product()
	{
		cout<<"\nPlease Enter The Product No. ";
		cin>>pno;
		cout<<"\n\nPlease Enter The Name of The Product ";
		gets(name);
		cout<<"\nPlease Enter The Price of The Product ";
		cin>>price;
		cout<<"\nPlease Enter The Discount (%) ";
		cin>>dis;
	}

	void modify()
{

		clrscr();
		textcolor(2);
		textbackground(0);
		int x=pno,pri=price,d=dis;
		char tmp[20],t[20];
		int i;
		strcpy(t,name);
		cout<<"\n\n\n\t\t--------MODIFY--------\n";


		cprintf("New Product no. (Enter '-1' to retain old one)"); cout<<endl;
		cin>>i;
		if(i!=-1)
			{pno=i;}
		else
	       {	pno=x;
		 }

		cprintf("New Name (Enter dot to retain old one) ");
		gets(tmp);

		if(strcmp(tmp,".")!=0)
		     strcpy(name,tmp);

		else
		 {strcpy(t,name);
		   }
		cout<<"\nNew price (-1 to retain old one) ";
		cin>>i;
		if(i!=-1)
		     {price=i; }
		 else
		 price=pri;

		cout<<"\n Enter The Discount (%) (-1 to retain old one) ";
		cin>>i;
		if(i!=-1)
		     {dis=i; }
		else
		dis=d;
}

	void show_product()
	{
		cout<<"\nThe Product No. of The Product : "<<pno;
		cout<<"\nThe Name of The Product : ";
		puts(name);
		cout<<"\nThe Price of The Product : "<<price;
		cout<<"\nDiscount : "<<dis;
	}
	int retpno()
	{
		return pno;
	}
	float retprice()
	{
		return price;
	}
	char* retname()
	{
		return name;
	}
	int retdis()
	{
		return dis;
	}
};
fstream fp;
product pr;
void write_product()
{
	fp.open("Shop.dat",ios::out|ios::app);
	pr.create_product();
	fp.write((char*)&pr,sizeof(product));
	fp.close();
	cout<<"\n\nThe Product Has Been Created ";
	check=1;
	getch();
	admin_menu();
}
void display_all()
{
	clrscr();
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<"\n\n====================================\n";
		pr.show_product();
		cout<<"\n\n====================================\n";
		getch();
	}
	fp.close();
	getch();
	admin_menu();
}
void display_sp(int n)
{
	int flag=0;
	fp.open("Shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()==n)
		{
			clrscr();
			pr.show_product();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	cout<<"\n\nrecord not exist";
	getch();
	admin_menu();
}


void modify_product()
{
	int no,found=0;
	clrscr();
	cout<<"\n\n\tTo Modify ";
	cout<<"\n\n\tPlease Enter The Product No. of The Product";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	while(fp.read((char*)&pr,sizeof(product)) && found==0)
	{
		if(pr.retpno()==no)
		{
			pr.show_product();
			getch();
			pr.modify();
			int pos=-1*sizeof(pr);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&pr,sizeof(product));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	fp.close();
	if(found==0)
	cout<<"\n\n Record Not Found ";
	getch();
	admin_menu();
}
void delete_product()
{
	int no;
	check=0;
	clrscr();
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
	cin>>no;
	fp.open("Shop.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno()!=no)
		{
			fp2.write((char*)&pr,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("Shop.dat");
	rename("Temp.dat","Shop.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
	admin_menu();
}
void smenu()
{
	clrscr();
	fp.open("Shop.dat",ios::in|ios::out|ios::nocreate);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
		cout<<"\n\n\n Program is closing ....";
		getch();
		menu();
	}
	else
	cout<<"\n\n\t\tProduct MENU\n\n";
	cout<<"====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
	fp.close();
	getch();
	admin_menu();
}
void place_order()
{


	int order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	double count;
	if(check==0)
	{
		clrscr();
		cout<<"\n\n\n\n\n\tSORRY NO ITEMS HAVE BEEN CREATED YET. PLEASE TRY AGAIN LATER";
		getch();
		menu();
	}
	else

{
	  clrscr();
	fp.open("Shop.dat",ios::in|ios::out|ios::nocreate);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
		cout<<"\n\n\n Program is closing ....";
		getch();
		menu();
	}
	else
	cout<<"\n\n\t\tProduct MENU\n\n";
	cout<<"====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(fp.read((char*)&pr,sizeof(product)))
	{
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	}
	fp.close();
	getch();







	      //	smenu();
		cout<<"\n============================";
		cout<<"\n PLACE YOUR ORDER";
		cout<<"\n============================\n";
		do{
			cout<<"\n\nEnter The Product No. Of The Product : ";
			cin>>order_arr[c];
			cout<<"\nQuantity in number : ";
			cin>>quan[c];
			c++;
			cout<<"\nDo You Want To Order Another Product ? (y/n)";
			cin>>ch;
		}while(ch=='y' ||ch=='Y');
		flag=1;
		cout<<"\n\nThank You For Placing The Order";getch();clrscr();
		cout<<"\n";
		cout<<"\n********************************INVOICE************************\n";
		cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
		for(int x=0;x<=c;x++)
		{
			fp.open("Shop.dat",ios::in);
			fp.read((char*)&pr,sizeof(product));
			while(!fp.eof())
			{
				if(pr.retpno()==order_arr[x])
				{
					amt=pr.retprice()*quan[x];
					damt=amt-(amt*pr.retdis()/100);
					cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()
					<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
					total+=damt;
				}
			fp.read((char*)&pr,sizeof(product));
			}
		fp.close();
		}
		cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
		getch();
		menu();
	}
}
void admin_menu()
{
	clrscr();
	char ch2;
	textcolor(YELLOW);
	textbackground(CYAN);

	cout<<"\n\n\n\t\t";cprintf("      ADMIN MENU             ");
	cout<<"\n\n\t\t";  cprintf("???????????????????????????? ");
	cout<<"\n\t\t";    cprintf("?  1.CREATE PRODUCT        ? ");
	cout<<"\n\t\t";    cprintf("?  2.DISPLAY ALL PRODUCTS  ? ");
	cout<<"\n\t\t" ;   cprintf("?  3.QUERY                 ? ");
	cout<<"\n\t\t";    cprintf("?  4.MODIFY PRODUCT        ? ");
	cout<<"\n\t\t";    cprintf("?  5.DELETE PRODUCT        ? ");
	cout<<"\n\t\t";    cprintf("?  6.VIEW PRODUCT MENU     ? ");
	cout<<"\n\t\t";    cprintf("?  7.BACK TO MAIN MENU     ? ");
	cout<<"\n\t\t";	   cprintf("???????????????????????????? ");
	cout<<"\n\n\nPlease Enter Your Choice (1-7) ";
	ch2=getche();
	switch(ch2)
	{
		case '1': clrscr();
			  write_product();
			  break;
		case '2': display_all();
			  break;
		case '3': int num;
			  clrscr();
			  cout<<"\n\n\tPlease Enter The Product No. ";
			  cin>>num;
			  display_sp(num);
			  break;
		case '4': modify_product();
			  break;
		case '5': delete_product();
			  break;
		case '6': smenu();
			  break;
		case '7': menu();
			  break;
		default:cout<<"\a";
			admin_menu();
	}
}
char hav[10][30];
char hon[10][30];
char sub[10][30];
char mc[10][30];
char mark[10][30];
char domi[10][30];
char hald[10][30];
char ccd[10][30];
char spi[10][30];
char sag[10][30];
void bill(int count,int choice[], int quan[], char name[10][30])
{
	flag=1;
	clrscr();
	for(int j=0;j<count;j++)
	choice[j]--;
	textbackground(0);
	textcolor(BLUE);
	cout<<"\t\t\t\tINVOICE";
	cout<<"\n";
	for(int i=0;i<80;i++)
	{
		cout<<"-";
	}
	cout<<"\n";
	int price,flag=1;
	price=150;
	cout<<"Sr no.\t\t"<<"Item\t\t"<<"Quantity\t"<<"Price\t"<<"Total";
	cout<<"\n";
	for (i=0;i<80;i++)
	{
		cout<<"-";
	}
	cout<<"\n\n";
	for(i=0;i<count;i++,flag++)
	{
		cout<<flag<<"\t\t"<<name[choice[i]]<<"\t\t"<<quan[i]<<"\t"<<price<<"\t"<<quan[i]*price<<"\n";
	}
	display_all;
	getch();
	menu();
}
void havmor()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\t\tHavmor - The Eatery ";
	cout<<"\n\n\n";
	cprintf("1. Aloo Tikki WrapChic    .......... Rs.100");cout<<"\n\n";
	cprintf("2. Fries                  ...........Rs.100");cout<<"\n\n";
	cprintf("3. Chole Bhature          ...........Rs.150");cout<<"\n\n";
	cprintf("4. Pav Bhaji              .......... Rs.150");cout<<"\n\n";
	cprintf("5. Jumbo Grilled Sandwhich...........Rs.150");cout<<"\n\n";
	strcpy(hav[0],"Aloo Tikki WrapChicc");
	strcpy(hav[1],"Fries ");
	strcpy(hav[2],"Chole Bhature ");
	strcpy(hav[3],"Pav Bhaji");
	strcpy(hav[4],"Jumbo Grill Sandwhich");
	char ch;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	  bill(j,choice,quan,hav);
}
void cafe()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\t\t\tCafe Coffee Day";
	cout<<"\n\n\n";
	cprintf("1. Pineapple Cake            .........100");cout<<"\n\n";
	cprintf("2. Cafe Mocha                .........100");cout<<"\n\n";
	cprintf("3. Classic Lemonade          .........150");cout<<"\n\n";
	cprintf("4. Cool Blue                 .........150");cout<<"\n\n";
	cprintf("5. Darjeeling Tea            .........150");cout<<"\n\n";
	strcpy(ccd[0],"Pineapple cake");
	strcpy(ccd[1],"Cafe Mocha");
	strcpy(ccd[2],"Classic Lemonade");
	strcpy(ccd[3],"Cool Blue");
	strcpy(ccd[4],"Darjeeling Tea");
	char ch;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	  bill(j,choice,quan,ccd);
}
void honest()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nHonest";
	cout<<"\n\n\n";
	cprintf("1. Punjabi Thali     .........Rs.100");cout<<"\n\n";
	cprintf("2. Chana Puri        .........Rs.100");cout<<"\n\n";
	cprintf("3. Sweet Corn Soup   .........Rs 150");cout<<"\n\n";
	cprintf("4. Veg Spring Roll   .........Rs 150");cout<<"\n\n";
	cprintf("5. Veg Lollipop      .........Rs 150");cout<<"\n\n";
	strcpy(hon[0],"Punjabi Thali");
	strcpy(hon[1],"Chana Puri");
	strcpy(hon[2],"Sweet Corn Soup");
	strcpy(hon[3],"Veg Spring Roll");
	strcpy(hon[4],"Veg Lollipop");
	char ch;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	  bill(j,choice,quan,hon);
}
void subway()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nSubway";
	cout<<"\n\n\n";
	cprintf("1. Veggie Delite     .........Rs 100");cout<<"\n\n";
	cprintf("2. Corn and Peas     .........Rs 100");cout<<"\n\n";
	cprintf("3. Paneer Tikka      .........Rs 150");cout<<"\n\n";
	cprintf("4. Aloo Patty        .........Rs 150");cout<<"\n\n";
	cprintf("5. Chatpata Sub      .........Rs 150");cout<<"\n\n";
	strcpy(sub[0],"Veggie Delite");
	strcpy(sub[1],"Corn And Peas");
	strcpy(sub[2],"Paneer Tikka ");
	strcpy(sub[3],"Aloo Patty");
	strcpy(sub[4],"Chatpata Sub");
	char ch;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,sub);
}
void mcd()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nMc Donalds";
	cout<<"\n\n\n";
	cprintf("1. Aloo Tikki Burger .........Rs 100");cout<<"\n\n";
	cprintf("2. Mc Veggie         .........Rs 100");cout<<"\n\n";
	cprintf("3. French Fries      .........Rs 150");cout<<"\n\n";
	cprintf("4. Chatpata Aloo Naan.........Rs 150");cout<<"\n\n";
	cprintf("5. Rice Bowl         .........Rs 150");cout<<"\n\n";
	strcpy(mc[0],"Aloo Tikki Burger ");
	strcpy(mc[1],"Mc Veggie ");
	strcpy(mc[2],"French Fries");
	strcpy(mc[3],"Chatpata Aloo Naan");
	strcpy(mc[4],"Rice Bowl");
	char ch;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');

	bill(j,choice,quan,mc);
}
void marky()
{
	int quan[10],choice[10];
	clrscr();
	cout<<"\n\n\n\nMarky Momos";
	cout<<"\n\n\n";
	cprintf("1. Veg Steamed Momos ..........Rs 100");cout<<endl;
	cprintf("2. Veg Afghani Momos ..........Rs 100");cout<<endl;
	cprintf("3. Veg Tandoori Momos..........Rs 150");cout<<endl;
	cprintf("4. Honey Chilli Potatoes.......Rs 150");cout<<endl;
	cprintf("5. Veg Fried Momos   ..........Rs 150");cout<<endl;
	strcpy(mark[0],"Veg Steamed Momos");
	strcpy(mark[1],"Veg Afghani Momos");
	strcpy(mark[2],"Veg Tandoori momos");
	strcpy(mark[3],"Honey Chilli Potatoes");
	strcpy(mark[4],"Veg Fried Momos");
	char ch=0;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,mark);
}
void dom()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nDominos";
	cout<<"\n\n\n";
	cprintf("1. Peppy Paneer     ..........Rs 100");cout<<"\n\n";
	cprintf("2. Veggie Paradise  ..........Rs 100");cout<<"\n\n";
	cprintf("3. Margharita       ..........Rs 150");cout<<"\n\n";
	cprintf("4. Choco Lava Cake  ..........Rs 150");cout<<"\n\n";
	cprintf("5. FarmHouse        ..........Rs 150");cout<<"\n\n";
	strcpy(domi[0],"Peppy Paneer");
	strcpy(domi[1],"Veggie Paradise");
	strcpy(domi[2],"Margharita");
	strcpy(domi[3],"Choco Lava Cake");
	strcpy(domi[4],"Farm House");
	char ch=0;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,domi);
}
void spice()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nSpice And Herb";
	cout<<"\n\n\n";
	cprintf("1. S&H Special Paneer Tikka .........Rs 100");cout<<endl;
	cprintf("2. Quesadilas               .........Rs 100");cout<<endl;
	cprintf("3. Enchilladas              .........Rs 150");cout<<endl;
	cprintf("4. Paneer Lababdar          .........Rs 150");cout<<endl;
	cprintf("5. Cheese Kulcha            .........Rs 150");cout<<endl;
	strcpy(spi[0]," S&H Special Paneer Tikka");
	strcpy(spi[1],"Quesadilas");
	strcpy(spi[2],"Enchilladas");
	strcpy(spi[3],"Paneer Lababdar");
	strcpy(spi[4],"Cheese Kulcha");
	char ch=0;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,spi);
}
void haldi()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nHaldirams";
	cout<<"\n\n\n";
	cprintf("1. Raj Kachori              .........Rs 100");cout<<endl;
	cprintf("2. Masala Dosa              .........Rs 100");cout<<endl;
	cprintf("3. Onion Uttapam            .........Rs 150");cout<<endl;
	cprintf("4. Veg Noodles              .........Rs 150");cout<<endl;
	cprintf("5. Gulab Jamun(4 pcs)       .........Rs 150");cout<<endl;
	strcpy(hald[0],"Raj Kachori ");
	strcpy(hald[1],"Masala Dosa ");
	strcpy(hald[2],"Onion Uttapam ");
	strcpy(hald[3],"Veg Noodles");
	strcpy(hald[4],"Gulaab Jamun");
	char ch=0;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,hald);
}
void sagar()
{
	int choice[10],quan[10];
	clrscr();
	cout<<"\n\n\n\nSagar Ratna";
	cout<<"\n\n\n";
	cprintf("1. Masala Dosa              ..........Rs 100");cout<<endl;
	cprintf("2. Idli Sambhar             ..........Rs 100");cout<<endl;
	cprintf("3. Medu Vada                ..........Rs 150");cout<<endl;
	cprintf("4. Rava Masala Dosa         ..........Rs 150");cout<<endl;
	cprintf("5. Veg Biriyani             ..........Rs 150");cout<<endl;
	strcpy(sag[0],"Masala Dosa");
	strcpy(sag[1],"Idli Sambhar ");
	strcpy(sag[2],"Medu Wada");
	strcpy(sag[3],"Rawa Masala Dosa");
	strcpy(sag[4],"Veg Biryani");
	char ch=0;
	int j=0,k=0;
	do{
		cout<<"\n\nEnter Choice : \n";
		cin>>choice[j];
		cout<<"\nEnter Quantity : \n";
		cin>>quan[k];
		cout<<"\n\n\n\n\t\tDo you want to add any items?(Y/N)";
		cin>>ch;
		j++;
		k++;
	  } while(ch=='y'||ch=='Y');
	    bill(j,choice,quan,sag);
}
void func1(int n)
{
	switch(n)
	{
		case 0: place_order();
			break;
		case 1: havmor();
			break;
		case 2: honest();
			break;
		case 3: subway();
			break;
		case 4: mcd();
			break;
		case 5: marky();
			break;
		case 6: dom();
			break;
		case 7: cafe();
			break;
		case 8: spice();
			break;
		case 9: haldi();
			break;
		case 10: sagar();
			break;
	 }
}
void loading()
{
	int gd=DETECT,gm,i;
	initgraph(&gd,&gm,"C:\\TurboC3\\bgi");
	for(i=0;i<360;i++)
	{
		circle(300,200,80);
		pieslice(300,200,0,i,80);
		outtextxy(200,320,"LOADING....PLEASE WAIT !!");
		delay(5);
	}
	closegraph();
	clrscr();
}
void user()
{
	clrscr();
	char c=205;
	int choice;
	cout<<"\n\t\t\tRESTAURANTS AVAILABLE NEARBY\n\n"<<endl;
	cout<<"\n\n\t";
	textcolor(GREEN);
	textbackground(0);
	cout<<"\n";

   cout<<"\t";  cprintf(" ?????????????????????????????????????????????????????? ");cout<<"\n";
   cout<<"\t";	cprintf("? 1.Havmor-Bakery and Eatery           2.Honest        ?");cout<<"\n";
   cout<<"\t";	cprintf("? 3.Subway                             4.Mc Donalds    ?");cout<<"\n";
   cout<<"\t";	cprintf("? 5.Marky Momos                        6.Dominos       ?");cout<<"\n";
   cout<<"\t";	cprintf("? 7.Cafe Coffee Day                    8.Spice & Herbs ?");cout<<"\n";
   cout<<"\t";	cprintf("? 9.Haldirams                          10.Sagar Ratna  ?");cout<<"\n";
   cout<<"\t";	cprintf(" ?????????????????????????????????????????????????????? ");cout<<"\n";


	cout<<"\n\t\t";
	textcolor(RED+128);
	textbackground(0);
	cprintf("Press 0 for Newly Added Items ");
	textcolor(GREEN);
	cout<<"\nEnter your choice : ";
	cin>>choice;
	func1(choice);
}
void front()
{
	int i, gd = DETECT,gm;
	initgraph(&gd,&gm, "C:\\TurboC3\\bgi");
	setcolor(YELLOW);
	settextstyle(4,HORIZ_DIR,30);
	outtextxy(100,100,"ZWIGGY");
	gotoxy(20,20);
	getch();
	closegraph();
}
void admin()
{
	char password[10]={"password"};
	char pass[10], ch,name[20];
	textcolor(YELLOW);
	textbackground(0);
	int i;
	int flag=0,count=0;
	do
	{
		clrscr();
		i=0;
		cout<<"\n\t\t\tEnter admin name : ";
		gets(name);
		cout<<"\n\n\t\t\tEnter password : ";

 while((ch=getch())!=13)
		{
			password[i]=ch;
			i++;
			cout<<"*";
		}
		password[i]='\0';
		gotoxy(1,20);
		loading();
		if((strcmp(password,"password"))==0)
		{
			cout<<"\t\t\t\t\tSUCCESS!!!";
			delay(500);
			flag=1;
		}
		else
		{
			textcolor(CYAN);
			cprintf("WRONG PASSWORD!!");
			delay(200);
			clrscr();
			count++;
		 }
	}while(flag!=1 && count<3);
	if(flag==0)
	{
		menu();
	}
	else
		admin_menu();
}
void quit()
{
int gdriver=DETECT,gmode,i=0,j=0;
initgraph(&gdriver,&gmode,"C:\\TurboC3\\bgi");
for(i;i<420;++i)
{
line(0,245,650,245);
line(0+i,200,210+i,200);
line(50+i,200,70+i,170);
line(70+i,170,140+i,170);
line(140+i,170,160+i,200);
line(85+i,170,85+i,200);
line(125+i,170,125+i,200);
line(0+i,200,0+i,230);
line(210+i,200,210+i,230);
line(0+i,230,50+i,230);
circle(65+i,230,15);
line(80+i,230,130+i,230);
circle(145+i,230,15);
line(210+i,230,160+i,230);
pieslice(65+i,230,359-j,360-j,15);
pieslice(65+i,230,179-j,180-j,15);
pieslice(65+i,230,89-j,90-j,15);
pieslice(65+i,230,269-j,270-j,15);
pieslice(145+i,230,359-j,360-j,15);
pieslice(145+i,230,179-j,180-j,15);
pieslice(145+i,230,89-j,90-j,15);
pieslice(145+i,230,269-j,270-j,15);
if(j==179)
j=0;
++j;
delay(5);
cleardevice();
}
closegraph();
clrscr();
cout<<"\n\n\n\n\t\t\t\t";
cout<<"Your Order will be deliverd shortly !!";
getch();

textbackground(BLACK);
textcolor(RED);
			clrscr();
			gotoxy(20,12);
			cout<<"\tProject by Shivam";
			delay(5000);
			exit(0);
}
void menu()
{
	clrscr();
	int choice;
	char c=31;
	textcolor(CYAN);
	textbackground(6);
	cout<<"\n\n\n";
	for(int i=0;i<80;i++)
	cout<<c;
	cout<<"\n\t\t\t\t";
	cprintf("WELCOME TO ZWIGGY");
	textcolor(CYAN);
	cout<<"\n\t\t\t";
	cprintf("THE FASTEST FOOD DELIVERING APP");
	cout<<"\n\n\n";
	cout<<"\n\t\t\t";
	cprintf("????????????????????????? "); cout<<"\n\t\t\t";
	cprintf("?   1) ADMIN            ? "); cout<<"\n\t\t\t";
	cprintf("?   2) USER             ? ");cout<<"\n\t\t\t";
	cprintf("?   3) EXIT             ? ");cout<<"\n\t\t\t";
	cprintf("????????????????????????? ");
		cout<<"\n\n\t\t\t\t:";
	cin>>choice;
	switch(choice)
	{
		case 1: admin();
			break;
		case 2: user();
			break;
		case 3: if(flag==1)
			quit();
			else
			exit(0);
			break;
		default: cout<<"\nWRONG OPTION!!!!";

	}
}
void main()
{
	clrscr();
	front();
	menu();
	getch();
}
//IGGY.CPP
//Displaying ZWIGGY.CPP.
