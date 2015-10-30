#include<fstream>    //for reading and writing files
#include<conio.h>      //for clrscr()
#include<string.h>     //for string characters
#include<stdio.h>      //for gets and puts function
#include<process.h>    //for exit function
#include<iomanip>    //for setw function
#include<iostream>
#include<windows.h>
using namespace std;
void gotoxy(short x, short y)
{
   COORD pos = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int choosecategory();
//global variable
int cust_code=1001;
int serv_code=1001;
int bill_code=1;
static int cat3;
int quant,bill_no,serno;
float tamt;

class shopcart
{public: virtual void startup()=0;
};

class start:public shopcart
{
public:
void startup();
};

class shopinvoice
{
int serviceno,billno,quantity;
float amount;
public:
   void invoice();
   void showinvoice();
   int get_bill_no();
   void showall();
   shopinvoice()
   {serviceno=serv_code;
    billno=bill_code;}
}shop;

class product:public shopinvoice
{
	private:
	      int pcode;
		  char pname[25];
		  float itemcost,qty,tax,dis;
    public:
	      int get_prod_id();
	      void add_item(void);
		  void create_items(void);
		  void delete_item(void);
		  void modify_item(void);
		  void category(void);	
		  void search(char pname[25]);
		  void search(int pcode);
		  void showdata();
		  void place_order(); 
		  void displayproduct();
}prod;

class customer:public product
		{
		private:
			int cno;
			char cname[20];
			char address[20];
			long smartcard,mob;
		public:
			void write();
			void entry();
			int get_cust_no();
			void showdetails();
			customer(){cno=cust_code;}
		}cust;
		
class admin:public product
{
  private:
         char pass[7];
		 int k;
  public:
        void pass_verification();
		void admin_menu();    
};	

//invoice detail
void shopinvoice::invoice()
{      fflush(stdin);
 	    fstream infile;
 	    serviceno=serno;
		amount=tamt;
		billno=bill_no;
		quantity=quant;		
		infile.open("invoice.dat",ios::out|ios::app);
		infile.write((char*)&shop,sizeof(shop));
		infile.close();
}
void shopinvoice::showinvoice()
{
system("cls");
fstream infile; 
cout<<"\n\n********************************INVOICE***********************************************\n";
cout<<"\nServNO\tbillNo\tQuantity\tAmount";
infile.open("invoice.dat",ios::in);//open file for reading
infile.read((char*)&shop,sizeof(shop));//read the first record
while(!infile.eof())
		{  
		cout<<"\n"<<serviceno<<"\t"<<billno<<"\t"<<quantity<<"\t"<<amount;
		infile.read((char*)&shop,sizeof(shop));
		}	
		infile.close();getch();
}

void admin::pass_verification()
{
   admin adm;
  system("cls");
  pass:
	cout<<"\n\n\t\t\tEnter your Password\t";
	pass[0]=getch();
	cout<<"*";
	pass[1]=getch();
	cout<<"*";
	pass[2]=getch();
	cout<<"*";
	pass[3]=getch();
	cout<<"*";
	pass[4]=getch();
	cout<<"*";
	pass[5]=getch();
	cout<<"*";
	pass[6]=getch();
	cout<<"*";
	pass[7]='\0';
	cout<<"*";
	
	if(strcmp(pass,"Nitt100")==0)
	adm.admin_menu();
		
	else
	{
	cout<<"\n\n\t\t\t$$$$$$ Ooop's wrong password $$$$$$\n";
	cout<<"\n\n\t\t\t%%%%%% Please re-enter the password%%%%%%\n";
	getch();
	k++;
	//getch();
	if(k==3)
	{
	cout<<"\nExiting from the project!!!!! Bye\n";
	getch();
	exit(0);
	}goto pass;
	}
	
}	

void admin::admin_menu()
{
  menu:
  system("cls");
  int code;
  char chr,ch,iname[25];
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\t1.ADD ITEMS";
  cout<<"\n\t2.DELETE ITEMS";
  cout<<"\n\t3.MODIFY ITEMS ";
  cout<<"\n\t4.VIEW ALL product";
  cout<<"\n\t5.SEARCH ITEMS";
  cout<<"\n\t6.VIEW PRODUCT MENU";
  cout<<"\n\t7.VIEW ALL CUSTOMER DETAIL";
  cout<<"\n\t8.VIEW INVOICE";
  cout<<"\n\t9.LOGOUT";
  cout<<"\n\n\tPlease Enter Your Choice (1-8) ";
  chr=getche();
  switch(chr)
  {
    case '1': system("cls");
	          prod.add_item();
			  goto menu;
    case '2': system("cls");
	          prod.delete_item();
			  goto menu;
    case '3': system("cls");
			  prod.modify_item();
			  goto menu;
    case '4': system("cls");
				prod.category();
				goto menu;
    case '5': system("cls");
				choice:
				cout<<"\n\n\t\t\tChoose category:\n\n";
				cout<<"\n\t\t1.Search By Name";
				cout<<"\n\t\t2.Search By Item code";
				cout<<"\n\t\t3.Exit\n";
				ch=getche();
				switch(ch)
				{
				   case '1':cout<<"\n\n\tPlease Enter The Product Name. ";
                           gets(iname);
                           prod.search(iname);
				            break;
				   case '2':cout<<"\n\n\tPlease Enter The Product code: ";
                            cin>>code;
                            prod.search(code);
							break;
				   case '3':break;
				}
			   goto menu;
    case '6': prod.category();
	           goto menu;
		        
    case '7':cust.showdetails();
	          goto menu;
		        
	case '8':shop.showinvoice();
	         goto menu;
	case '9':break;
   }
}
void product::displayproduct()
{
     system("cls");
      cout<<"P.NO.\tPNAME\t\t\tPRICE\t\tQuantity\tDiscount\n";
      cout<<"===========================================================================\n";
      cout<<pcode<<"\t"<<pname<<"\t"<<itemcost<<"\t"<<qty<<"\t"<<dis;
	  getch();
}
void product::showdata()
{  char file[25];  
fstream fp;
if(cat3==1)
     strcpy(file,"electronics.dat");
    else if(cat3==2)
     strcpy(file,"books.dat");
     else if(cat3==3)
     strcpy(file,"clothes.dat");
   else if(cat3==4)
     strcpy(file,"sports.dat");
    else
     strcpy(file,"travel_lugguage.dat");	 
      system("cls");
      cout<<"P.NO.\tPNAME\t\t\tPRICE\t\tQuantity\tDiscount\n";
      cout<<"===========================================================================\n";
	         fp.open(file,ios::in|ios::binary);
			 fp.read((char*)&prod,sizeof(prod));
	   while(!fp.eof())
			{   
			cout<<pcode<<"\t"<<pname<<"\t\t"<<itemcost<<"\t"<<qty<<"\t"<<dis<<endl;
				fp.read((char*)&prod,sizeof(prod));//read the next record
			}
					fp.close();
	  getch();
}
//this function displays data
void product::search(char name[25])
{
int counter=0,flag=0;
char fname[25];
system("cls");
  fstream infile;
 int ch=choosecategory();
 if(ch==1)
  {
    infile.open("electronics.dat",ios::in|ios::binary);//open file for reading
    infile.read((char*)&prod,sizeof(prod));//read first record
	while(!infile.eof())
	{
	 if(strcmpi(prod.pname,name)==0)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();    
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
  }
else if(ch==2)	
	{
	 infile.open("books.dat",ios::in);
	 infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	 if(strcmpi(prod.pname,name)==0)
	 { 
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 } 
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
  }
else if(ch==3)	
	{infile.open("clothes.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	 if(strcmpi(prod.pname,name)==0)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	else if(ch==4)
	{infile.open("sports.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	 if(strcmpi(prod.pname,name)==0)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	else
	{infile.open("travel_lugguage.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	 if(strcmpi(prod.pname,name)==0)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct(); 
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	cout<<"\n\nRECORDS FOUND="<<counter;//display counter
	if(flag!=1)
	cout<<"\n\n\t\t\tNO RECORD FOUND!!!";
	getch(); 
}
//search by item code
void product::search(int icode)
{
int counter=0,flag=0;
char fname[25];
system("cls");
 fflush(stdin);

 fstream infile;
 int ch=choosecategory();
 if(ch==1)
  {
    infile.open("electronics.dat",ios::in|ios::binary);//open file for reading
    infile.read((char*)&prod,sizeof(prod));//read first record
	while(!infile.eof())
	{
	 if(prod.pcode==icode)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();    
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
  }
else if(ch==2)	
	{
	 infile.open("books.dat",ios::in);
	 infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	if(prod.pcode==icode)
	 { 
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 } 
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
  }
else if(ch==3)	
	{infile.open("clothes.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	 if(prod.pcode==icode)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	else if(ch==4)
	{infile.open("sports.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	if(prod.pcode==icode)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct();
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	else
	{infile.open("travel_lugguage.dat",ios::in);
	infile.seekg(0,ios::beg);
	infile.read((char*)&prod,sizeof(prod));
	while(!infile.eof())
	{
	if(prod.pcode==icode)
	 {  //record found
	  counter++;//increment counter
	  flag=1;
	  prod.displayproduct(); 
	 }
	 infile.read((char*)&prod,sizeof(prod));//read next record
	}
	infile.close();//if end of file , close file infile
	}
	cout<<"\n\nRECORDS FOUND="<<counter;//display counter
	if(flag!=1)
	cout<<"\n\n\t\t\tNO RECORD FOUND!!!";
	getch(); 
}
//create items
void product::create_items()
{
     cout<<"\nEnter The Product No. of The Product: ";
	 cin>>pcode;
	 fflush(stdin);
	 cout<<"\n\nEnter The Name of The Product: ";
	 gets(pname);
	 cout<<"\nEnter The Price of The Product: ";
	 cin>>itemcost;
	 cout<<"\nEnter The Quantity of The Product: ";
	 cin>>qty;
	 cout<<"\nEnter The Discount (%) ";
	 cin>>dis;
}
//Add items
void product::add_item()
{
fstream file1;
int choosecat;
system("cls");
op:
 choosecat=choosecategory();
 switch(choosecat)
 {
  case 1:   system("cls");
            file1.open("electronics.dat",ios::out|ios::app);
            prod.create_items();
            file1.write((char*)&prod,sizeof(prod));
            file1.close();
            cout<<"\n\nAn Item Has Been Created ";
			break;
  
  case 2:   system("cls");
            file1.open("books.dat",ios::out|ios::app);
            prod.create_items();
            file1.write((char*)&prod,sizeof(prod));
            file1.close();
            cout<<"\n\nAn Item Has Been Created ";
			break;
			
  case 3:    system("cls");
            file1.open("clothes.dat",ios::out|ios::app);
            prod.create_items();
            file1.write((char*)&prod,sizeof(prod));
            file1.close();
            cout<<"\n\nAn Item Has Been Created ";
			break;
			
   case 4:   system("cls");
            file1.open("sports.dat",ios::out|ios::app);
            prod.create_items();
            file1.write((char*)&prod,sizeof(prod));
            file1.close();
            cout<<"\n\nAn Item Has Been Created ";
			break;
			
   case 5:  system("cls");
            file1.open("travel_luggage.dat",ios::out|ios::app);
            prod.create_items();
            file1.write((char*)&prod,sizeof(prod));
            file1.close();
            cout<<"\n\nAn Item Has Been Created ";
			break;
 default:  goto op;
}
getch();
}
//modify items
void product::modify_item()
{
 fstream file;
 int mod_choice;
 int code;
 int choosecat=choosecategory();
 	  
 do
 {//display modify menu
  system("cls");
  
  cout<<"\n     MODIFY MENU  ";
  cout<<"\n---------------------------------";
  cout<<"\n CHANGED NAME               ....1";
  cout<<"\n CHANGE COST                ....2";
  cout<<"\n CHANGE QUANTITY            ....3";
  cout<<"\n CHANGE DISCOUNT            ....4";
  cout<<"\n EXIT MODIFY MENU           ....5";
  cout<<"\n\n ENTER YOUR CHOICE NO.---------->";
  cin>>mod_choice;
  if(mod_choice!=5)
  {
   cout<<"\n ENTER THE PRODUCT CODE--------->";
   cin>>code;
   
   if(choosecat==1)
         file.open("electronics.dat",ios::in|ios::out); 
   else if(choosecat==2)
          file.open("books.dat",ios::in|ios::out); 
   else if(choosecat==3)
		  file.open("clothes.dat",ios::in|ios::out); 
   else if(choosecat==4)
		  file.open("sports.dat",ios::in|ios::out);	
   else 
		  file.open("travel_luggage.dat",ios::in|ios::out);	
		  
   file.seekg(0,ios::beg);//set file pointer to the begining of the file
   file.read((char*)&prod,sizeof(prod));//read first record
   int  n=file.tellg();//tell where we are
   
   while(!file.eof())
   {
    if(code==prod.pcode)//record found
    {
     switch(mod_choice)
     {
      case 1 : system("cls");
	   //get new information
	   cout<<"\n ENTER THE NAME-------------->";
	   gets(pname);
	   file.seekg(n-sizeof(prod));//set file pointer to the record
				     //to be modified
	   file.write((char*)&prod,sizeof(prod));//update record
	   file.flush();
	   break;

      case 2 : system("cls");
	   //get new information
	   cout<<"\n ENTER THE COST------------>";
	   cin>>itemcost;
	   file.seekg(n-sizeof(prod));//set file pointer to the record
				     //to be changed
	   file.write((char*)&prod,sizeof(prod));//update record
	   file.flush();
	   break;

      case 3 : system("cls");
	   //get new information
	   cout<<"\n ENTER NEW QUANTITY-------------->";
	   cin>>qty;
	   file.seekg(n-sizeof(prod));//set file pointer to the record
				     //to be modified
	   file.write((char*)&prod,sizeof(prod));
	   file.flush();
	   break;
	   
	   case 4 : system("cls");
	   //get new information
	   cout<<"\n ENTER NEW DISCOUNT-------------->";
	   cin>>dis;
	   file.seekg(n-sizeof(prod));//set file pointer to the record
				     //to be modified
	   file.write((char*)&prod,sizeof(prod));
	   file.flush();
	   break;

     }//end of switch
    }//end if
    file.read((char*)&prod,sizeof(prod));//raed next record
    n=file.tellg();//tell where we are
   }//end while
   file.close();
  }//end if
 }//end do while loop
 while(mod_choice!=5);
 system("cls");
 cout<<"\n YOU ENDED THE MODIFY SESSION ";
 cout<<"\n THANK YOU!";
 //delay(700);
}


void product::delete_item()
{
 int code,cat2;
 fstream infile,file1;
 char fname[20];
 int choosecat=choosecategory();
 cout<<"\n ENTER THE ITEM CODE TO BE DELETED--------->";
 cin>>code;
 //update emp file
 file1.open("tempfile.dat",ios::app|ios::binary);//open temporary file
 if(choosecat==1){infile.open("electronics.dat",ios::in|ios::binary);strcpy(fname,"electronics.dat");}
 else if(choosecat==2)
 {infile.open("books.dat",ios::in|ios::binary);strcpy(fname,"books.dat");}
  else if(choosecat==3)
 {infile.open("clothes.dat",ios::in|ios::binary);strcpy(fname,"clothes.dat");}
 else if(choosecat==4)
 {infile.open("sports.dat",ios::in|ios::binary);strcpy(fname,"sports.dat");}
 else
 {infile.open("travel_lugguage.dat",ios::in|ios::binary);strcpy(fname,"travel_lugguage.dat");}
 
 infile.seekg(0,ios::beg);//set file pointer to the begining of the file
 infile.read((char*)&prod,sizeof(prod));//read the first record
 while(!infile.eof())
 {
  if(prod.pcode!=code)//if this record is not to be deleted
      //write in temporary file
  file1.write((char*)&prod,sizeof(prod));
  infile.read((char*)&prod,sizeof(prod));//read the next record
 }
 infile.close();
 file1.close();//close temporary file

 remove(fname);//delete old employee file
 rename("tempfile.dat",fname);
 //cout<< "Item Deleted.";
getch();				 
}
int customer::get_cust_no()
  {
      fstream infile;
      int flag=0;
      infile.open("customer.dat",ios::in|ios::binary);//open file for reading
	  infile.read((char*)&cust,sizeof(cust));//read first record
	  while(!infile.eof())
	 {
		if(cust.cno==cust_code)
			{ //record found
				flag=1;break;
			}
	 infile.read((char*)&cust,sizeof(cust));//read next record
	 }
	 infile.close();//if end of file , close file
	 return flag;
    }
	
	//customer details
void customer::showdetails()
{
system("cls");
int cnt=0;
fstream infile;
    infile.open("customer.dat",ios::in|ios::binary);//open file for reading
	infile.read((char*)&cust,sizeof(cust));//read first record
	 cout<<"CUST NO\tCNAME\tADDRESS\tSMARTCARD_NO.\tMOBILE\n";
     cout<<"=========================================================\n";
	  while(!infile.eof())
	 { cnt++;
      cout<<cno<<"\t"<<cname<<"\t"<<address<<"\t"<<smartcard<<"\t\t"<<mob<<"\n";
	 infile.read((char*)&cust,sizeof(cust));//read next record
	}
	infile.close();
	cout<<"\n\nPRESS ANY KEY TO CONTINUE";
	if(cnt==0)
	cout<<"\n\n\t\tNO RECORDS FOUND!!!!";
	getch();
}	

	int shopinvoice::get_bill_no()
	{
	  fstream infile;
	  int flag2=0;
      infile.open("invoice.dat",ios::in);//open file for reading
	  infile.seekg(0,ios::beg);//set file pointer to the begining
				     // of the file
	  infile.read((char*)&shop,sizeof(shop));//read first record
	  while(!infile.eof())
	 {
		if(shop.billno==bill_code)
			{ //record found
				flag2=1;break;
			}
	 infile.read((char*)&cust,sizeof(cust));//read next record
	 }
	 infile.close();//if end of file , close file
	 return flag2;
	}

	   
	void customer::entry()
		{
		int cn;
		cn=get_cust_no();
		while(cn==1)
		{
		  cust_code++;
		  cn=get_cust_no();
		}
		serv_code=cno=cust_code;
		system("cls");
		gotoxy(32,4);
		puts("SHOPPING CART");
		gotoxy(5,8);
		puts("Customer ID :");

		gotoxy(5,10);
		puts("ENTER THE NAME:");
		gotoxy(5,12);
        puts("ENTER THE ADDRESS:");
		gotoxy(5,14);
		puts("Costumer Smart card number :");
		gotoxy(5,16);
		puts("Costumer Mobile number :");
		gotoxy(45,8);
		cout<<cno;
		gotoxy(45,10);
		fflush(stdin);
		gets(cname);
		gotoxy(45,12);
		gets(address);
		gotoxy(45,14);
		cin>>smartcard;
		gotoxy(45,16);
		cin>>mob;
		}
				
	
//FUNCTION TO WRITE THE VALUES
 
    void customer:: write()
		{
		char ch;
		fstream infile;
		cust.entry();
		infile.open("customer.dat",ios::app|ios::out|ios::binary);
		cout<<"\n\n\tDO you want to save the customer record(y/n)\t";
		cin>>ch;
		if(ch=='y'||ch=='Y')
		{
		infile.write((char*)&cust,sizeof(cust));
		}
		infile.close();	
		}
		
void product::place_order()
{
fstream fp;
int  order[10],quan[10],c=0;
char file[25];
int bill,tquant=0;
bill=shop.get_bill_no();

while(bill==1)
	{
	   bill_code++;
	  bill=shop.get_bill_no();
    }
    float amt,damt,total=0;
    char ch='Y';
    prod.category(); 
	if(cat3==1)
     strcpy(file,"electronics.dat");
    else if(cat3==2)
     strcpy(file,"books.dat");
     else if(cat3==3)
     strcpy(file,"clothes.dat");
   else if(cat3==4)
     strcpy(file,"sports.dat");
    else
     strcpy(file,"travel_lugguage.dat");	 
system("cls");
	cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    do{
	 cout<<"\n\nEnter The Product No. Of The Product : ";
	 cin>>order[c];
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 c++;
	 cout<<"\nDo You Want To Order Another Product ? (y/n)";
	 cin>>ch;
    }while(ch=='y' ||ch=='Y');
	
    cout<<"\n\nThank You For Placing The Order";
	getch();
	system("cls");
	  
      cout<<"\n\n********************************INVOICE***********************************************\n";
      cout<<"\nServ.NO\tBill NO\tPR.NO\tPr Name\tQuantity\tPrice\tAmount\tAmount after discount\n";
	     for(int x=0;x<=c;x++)
	       {  fp.open(file,ios::in);
			 fp.read((char*)&prod,sizeof(prod));
		     while(!fp.eof())
			 { 
			   if(prod.pcode==order[x])
				{  try{
				  if(prod.qty>=quan[x])
				  {
				   amt=prod.itemcost*quan[x];
				   damt=amt-(amt*prod.dis/100);			   	 
				   cout<<"\n"<<serv_code<<"\t"<<bill_code<<"\t"<<order[x]<<"\t"<<prod.pname<<"\t"<<quan[x]<<"\t"<<prod.itemcost<<"\t"<<amt<<"\t"<<damt;
				   total+=damt;
				   tquant=tquant+quan[x];
				  }
				  
				 else throw(prod.qty>=quan[x]);
               }
                 catch(int f){cout<<"\n"<<"Quntity of item "<<prod.pname<<" is more than available stock.";
				       break;}
				}
				 fp.read((char*)&prod,sizeof(prod));
			}
	      fp.close();	
	  }
     cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;	
     fflush(stdin);
	 tamt=total;
	 serno=serv_code;
	 bill_no=bill_code;
	 quant=tquant;
	 shop.invoice();
    getch();
    }

		
int main()
{
start show;
shopcart *sptr;
sptr=&show;
  admin ad;
  char ch,pu;
  cout.setf(ios::fixed,ios::floatfield);
  cout.setf(ios::showpoint);
  sptr->startup();                        //FUNTION TO DISPLAY INTRODUCTION SCREEN
  do
    {
	  system("cls");
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. VIEW ALL ITEMS";
	  cout<<"\n\n\t02. CUSTOMER PORTAL";
	  cout<<"\n\n\t03. ADMINISTRATOR PORTAL";
	  cout<<"\n\n\t04. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3) ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': system("cls");
			      prod.category();
			      break;
		 case '2':char purch;
              		cust.write();
					cout<<"\n\n\nDO YOU WANT TO PURCHASE(Y/N): ";
					cin>>pu;
					try{
					  if(pu=='Y'||pu=='y')
					   prod.place_order();
                       else throw(pu); 
					   }
                       catch(char purch){cout<<"Thanks for visiting.";}
			         break;
		  case '3':ad.pass_verification();
		         break;
          case '4': exit(0);				 
	}
    }while(ch!='4');
    getch();
    return 0;
}

void start::startup()
{
 int a;
 for(a=50;a>30;a--)
  {
  system("cls");;
  gotoxy(25,10);cout<<"Welcome to the Shopping Cart";
  gotoxy(a,12);cout<<"DEVELOPED BY : VIJAY LAKRA";
  }
 for(a=42;a<52;a++)
  {
  gotoxy(27,18);cout<<"Please Wait";
  gotoxy(a,18);cout<<".";
  }
system("cls");;
for(int j=0;j<10;j++)
{
system("cls");;
gotoxy(j,6); puts("          ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n\r");
gotoxy(j,7); puts("            ÜÜÜÜÜÜÜ   Ü    Ü    ÜÜ     ÛÜÜÛÛÛ");
gotoxy(j,8); puts("            ÛÛ        Û    Û  Û    Û   Û   ÛÛ");
gotoxy(j,9); puts("              ÛÛÛÛÛÛ  ÛÜÜÜÛÛ Û      Û  ÛÜÛÜÜÜ  ");
gotoxy(j,10);puts("                  ÛÛ  Û    Û  Û    Û   ÛÛ");
gotoxy(j,11);puts("           ÛÛÛÛÛÛÛ    Û    Û    ÛÛ     ÛÛ");

gotoxy(63-j,6); puts("ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n\r");
gotoxy(63-j,7); puts(" ÜÛÛÛÛÛÛ Û     Û  ÜÜÜÜÜÜ    \n\r");
gotoxy(63-j,8); puts("    Û    ÛÛ    Û  Û \n\r");
gotoxy(63-j,9); puts("    Û    Û  Û  Û  Ü ÛÛÛÛÛ \n\r");
gotoxy(63-j,10);puts("    Û    Û   Û Û  Û   Û Û\n\r");
gotoxy(63-j,11);puts(" ÛÛÛÛÛÛÛ Û    ÛÛ  ÛÛÛÛÛ Û\n\r\n\n\n");

gotoxy(j,13);puts("                          ÜÜÜÜÜÜ ÛÛÛÛÜÛ ÛÜÛÛÛÛ ÛÛÛÛÛÛ \n\r");
gotoxy(j,14);puts("                          Û      Û    Û Û    Û    Û \n\r");
gotoxy(j,15);puts("                          Û      ÛÛÛÛÛÛ Û ÛÛÛ     Û \n\r");
gotoxy(j,16);puts("                          Û      Û    Û Û  ÛÛ     Û \n\r");
gotoxy(j,17);puts("                          ÜÜÜÛÜÜ Û    Û Û    Û    Û \n\r");
gotoxy(j,18);puts("                       ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n\r");

//sleep(80);
}
gotoxy(25,25);
cout<<"press any key to continue...";
getch();
}
int choosecategory()
{
       system("cls");
       int cat1;
	   ct:
       for(int j=0;j<20;j++)
       {
       system("cls");;
       gotoxy(j+3,5);cout<<"Choose Category";
       gotoxy(j,10);cout<<"ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» "<<endl;
       gotoxy(j,11);cout<<"º      1.Electronics            º "<<endl;
       gotoxy(j,12);cout<<"º      2.Books                  º "<<endl;
       gotoxy(j,13);cout<<"º      3.Clothes                º "<<endl;
       gotoxy(j,14);cout<<"º      4.Sports                 º "<<endl;
       gotoxy(j,15);cout<<"º      5.Travel and Luggage     º "<<endl;
       gotoxy(j,16);cout<<"º  ??ENTER CHOICE(1..5)>>.....? º "<<endl;
       gotoxy(j,17);cout<<"ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÐ "<<endl;
       //sleep(50);
       }
       gotoxy(45,17);
	   cin>>cat1;
	   if(cat1!=1 && cat1!=2 && cat1!=3 && cat1!=4 && cat1!=5)
	  goto ct;	 
	   return cat1;
}
/**********************************************
FUNTION USED TO DISPLAY CHOICE OF CATEGORY.
**********************************************/
void product::category()
{
char cat;
fstream infile;
       for(int j=0;j<20;j++)
       {
       system("cls");;
      gotoxy(j+3,5); cout<<"Choose Category";
       gotoxy(j,10);cout<<"ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» "<<endl;
       gotoxy(j,11);cout<<"º      1.Electronics            º "<<endl;
       gotoxy(j,12);cout<<"º      2.Books                  º "<<endl;
       gotoxy(j,13);cout<<"º      3.Cloths                 º "<<endl;
       gotoxy(j,14);cout<<"º      4.Sports                 º "<<endl;
       gotoxy(j,15);cout<<"º      5.Travel and Luggage     º "<<endl;
       gotoxy(j,16);cout<<"º      6.EXIT                   º "<<endl;
       gotoxy(j,17);cout<<"º  ??ENTER CHOICE>>.....?       º "<<endl;
       gotoxy(j,18);cout<<"ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÐ "<<endl;
       }
       gotoxy(45,17); cat=getche();
if (cat!=6)
{
 switch(cat)
 {
  case '1': 			    cat3=1;
							prod.showdata();//display record
							 						
							break;

  case '2':					cat3=2;  
							prod.showdata();
							 
							break;

case '3': 					cat3=3;
							prod.showdata();
							break;

case '4': 				cat3=4;
						 prod.showdata();	 
						break;

case '5':				cat3=5; 
							prod.showdata();		    
	              break;
case '6':exit(0);

	}
  }
 }
