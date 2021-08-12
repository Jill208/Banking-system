#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
using namespace std;
#define MIN_BALANCE 500
struct node
{
    float balance;
    string fname;
    string lname;
    int acc_no;
    node *next;
}*first=NULL;

class bank{

    public:
    bank(){}

    void openAcc(string f,string l,float b,int a);
    void display_acc();
    void Deposit(int amount,int a);
    void Withdraw(int amount, int a);
    void BalanceEnquiry(int a);
    void CloseAccount(int a);
    void transfer(int key1,int key2, int a);
    void receipt(int acc);

};

void bank::openAcc(string f,string l,float b,int a)
{
    ofstream outfile;
     outfile.open("Bank_data.txt",ios::app);

            outfile<<"Account number: "<<a<<endl;
            outfile<<"First name: "<<f<<endl;
            outfile<<"Last name: "<<l<<endl;
            outfile<<"Balance: "<<b<<endl;
            outfile.close();

    node *t=new node;
    node *p=first;
    if(first==NULL)
    {
        t->next=NULL;
        t->fname=f;
        t->lname=l;
        t->balance=b;
        t->acc_no=a;
        first=t;
    }
    else
    {
        while(p->next!=NULL)
        {
            p=p->next;
        }
        t->fname=f;
        t->lname=l;
        t->balance=b;
        t->acc_no=a;
        t->next=NULL;
         p->next=t;


    }


}
void bank::receipt(int acc)
{
    node *p=first;
    while(p!=NULL)
    {
        if(p->acc_no==acc)
        {
            cout<<"\t\t\t\t-----------------------------------------------------------------------------"<<endl<<"\t\t\t\t\t\t\tBANK RECEIPT "<<endl<<"\t\t\t\t First name: "<<p->fname<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t            "<<endl<<"\t\t\t\t Last name: "<<p->lname<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t            "<<endl<<"\t\t\t\t Account number: "<<acc<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t            "<<endl<<"\t\t\t\t Balance: "<<p->balance<<"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t                 "<<endl<<endl<<endl<<"\t\t\t\t\t\tHave a Good day :)"<<endl<<"\t\t\t\t-----------------------------------------------------------------------------"<<endl;
        }
        p=p->next;
    }
}
int read_file()
{
    int i;
    string filename = "mob.txt";
    ifstream fin;
    fin.open(filename);
    if(fin.is_open()) {
        fin.seekg(-1,ios_base::end);

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            fin.get(ch);

            if((int)fin.tellg() <= 1) {
                fin.seekg(0);
                keepLooping = false;
            }
            else if(ch == '\n') {
                keepLooping = false;
            }
            else {
                fin.seekg(-2,ios_base::cur);
            }
        }

        string lastLine;
        getline(fin,lastLine);                      // Read the current line

         i=stoi(lastLine,nullptr,10);
         i++;

        fin.close();
    }
    return i;
}

void bank::transfer(int key1,int key2, int money)
{
    node *p,*q;
    p=first;
    q=first;
    while(p->acc_no!=key1 && p!=NULL)
    {
        p=p->next;
    }
    if(p==NULL)
    {
        cout<<"Invalid account number"<<endl;
        return;
    }
    while(q->acc_no!=key2 && q!=NULL)
    {
        q=q->next;
    }
    if(q==NULL)
    {
        cout<<"Entered account number is not valid"<<endl;
        return;
    }
    if(MIN_BALANCE<(p->balance - money))
    {
    q->balance+=money;
    p->balance-=money;
    cout<<"Money transfer successfull"<<endl;
    }

}

void bank::Deposit(int amount,int key)
{
    node *p=first;
    int b;
    while(p!=NULL)
    {
        if(p->acc_no==key)
        {
            p->balance=p->balance+amount;
            b=p->balance;
             ofstream outfile("Bank_data.txt",ios::app);
             outfile<<"Balance after deposit: "<<b<<endl;
        }
        p=p->next;
    }
    cout<<"Amount deposit sucessfully"<<endl;

}
void bank::Withdraw(int amount,int key)
{
    node *p=first;

    while(p!=NULL)
    {
        if(p->acc_no==key)
        {
            if(p->balance - amount<MIN_BALANCE)
            {
                cout<<"Insufficient balance";
                return;
            }
            p->balance=p->balance-amount;
              cout<<"Amount withdraw sucessfully"<<endl;
        }
        p=p->next;

    }

}
void bank::BalanceEnquiry(int key)
{
    node *p=first;

    while(p!=NULL)
    {
        if(p->acc_no==key)
        {
          cout<<"First name: "<<p->fname<<endl;
         cout<<"Last name: "<<p->lname<<endl;
          cout<<"Balance: "<<p->balance<<endl;

        }
        p=p->next;
    }

}
void bank::CloseAccount(int key)
{
   node *p=first;
   node *q=NULL;
   string f,l;
   int b,a;

   if(key==p->acc_no)
   {
      f=p->fname;
      l=p->lname;
      b=p->balance;
      a=p->acc_no;
      p=first;
      first=first->next;
      delete p;
   }
   else
   {
       for(int i=p->acc_no;i<=key-1;i++)
       {
           q=p;
           p=p->next;
       }
       q->next=p->next;
       f=p->fname;
      l=p->lname;
      b=p->balance;
      a=p->acc_no;
      delete p;

   }
   cout<<"Account close sucessfully"<<endl;;


}
void bank::display_acc()
{
    node *p=first;

    while(p!=NULL)
    {

        cout<<"Account number: "<<p->acc_no<<endl;
        cout<<"First name: "<<p->fname<<endl;
        cout<<"Last name: "<<p->lname<<endl;
        cout<<"Balance: "<<p->balance<<endl;
        p=p->next;
        cout<<endl;

    }
    cout<<endl;


}

int main()
{
    int amount;
    float balance;
    string fname,lname;
    bank b;
    int choice;
    float d;
     int acc=1000,Acc1,Acc_No,Acc2;
      int j;

      cout<<"\n\n\t      $             $    $ $ $ $ $ $ $ $    $                  $ $ $ $ $ $ $    $ $ $ $ $ $ $      $ $             $ $   $ $ $ $ $ $ $ $     ";
  cout<<"\n\n\t      $      $      $    $                  $                 $                 $            $     $  $           $  $   $                   ";
  cout<<"\n\n\t      $     $ $     $    $                  $                 $                 $            $     $   $         $   $   $      ";
  cout<<"\n\n\t      $    $   $    $    $ $ $ $ $ $ $ $    $                 $                 $            $     $    $       $    $   $ $ $ $ $ $ $ $     ";
  cout<<"\n\n\t      $   $     $   $    $ $ $ $ $ $ $ $    $                 $                 $            $     $     $     $     $   $ $ $ $ $ $ $ $                  ";
  cout<<"\n\n\t      $  $       $  $    $                  $                 $                 $            $     $      $   $      $   $                   ";
  cout<<"\n\n\t      $ $         $ $    $                  $                 $                 $            $     $       $ $       $   $                   ";
  cout<<"\n\n\t      $             $    $ $ $ $ $ $ $ $    $ $ $ $ $ $ $ $    $ $ $ $ $ $ $    $ $ $ $ $ $ $      $        $        $   $ $ $ $ $ $ $ $  \n\n\n   ";


    cout<<"\t\t\t\t-------------------------------------------"<<endl<<endl<<"\t\t\t\t             Banking system      \t\t\t\t"<<endl<<endl<<"\t\t\t\t-------------------------------------------"<<endl;
    do{
        cout<<"\n\t------------------------------------------------------------"<<endl;
        cout<<"\n\t1.Open Account"<<endl;
        cout<<"\n\t2.Deposit"<<endl;
        cout<<"\n\t3.Withdraw"<<endl;
        cout<<"\n\t4.Balance Enquiry"<<endl;
        cout<<"\n\t5.Show recently created Account"<<endl;
        cout<<"\n\t6.Close account"<<endl;
        cout<<"\n\t7.Transfer money to account"<<endl;
        cout<<"\n\t8.Show bank data"<<endl;
        cout<<"\n\t9.Receipt"<<endl;
        cout<<"\n\t10.Exit"<<endl;
        cout<<"\n\t------------------------------------------------------------"<<endl;
        cout<<"\n\tEnter choice: ";
        cin>>choice;
        cout<<endl;
        switch (choice)
        {
        case 1:
           {



               j=read_file();
              Acc_No=j;

              ofstream out("mob.txt",ios::app);

               out<<"\n"<<Acc_No;


                cout<<"Account no: "<<Acc_No<<endl;
            cout<<"First name: ";
            cin>>fname;
            cout<<"Last name: ";
            cin>>lname;
            cout<<"Balance: ";
            cin>>balance;
             b.openAcc(fname,lname,balance,Acc_No);
            cout<<endl<<"Congratulation Account is Created"<<endl;
           }

            break;

            case 2:

            cout<<"Enter Account number: ";
            cin>>Acc_No;
            cout<<"Enter amount to deposit: "<<endl;
            cin>>amount;

              b.Deposit(amount,Acc_No);



            break;
            case 3:

            cout<<"Enter Account number: ";
            cin>>Acc_No;
            cout<<"Enter amount to withdraw: ";
            cin>>amount;
               b.Withdraw(amount,Acc_No);
              break;

            case 4:
            cout<<"Enter account number: ";
            cin>>Acc_No;
            b.BalanceEnquiry(Acc_No);

            break;

            case 5:
            b.display_acc();
            break;
            case 6:
            cout<<"Enter account number: ";
            cin>>Acc_No;
            b.CloseAccount(Acc_No);
            break;
            case 7:
            cout<<"Enter your acccount number: ";
            cin>>Acc1;
            cout<<"Enter account number in which you want to transfer money: ";
            cin>>Acc2;
            cout<<"Enter amount: ";
            cin>>amount;
            b.transfer(Acc1,Acc2,amount);

            break;
            case 8:
            {
            string myText;
               ifstream MyReadFile("Bank_data.txt");
               while (getline (MyReadFile, myText)) {
                 cout<<endl;
                 cout << myText;
                 cout<<endl;
               }


               MyReadFile.close();
            }
            break;
            case 9:
            cout<<"Enter account number to generate receipt: ";
            cin>>Acc_No;
            b.receipt(Acc_No);
            break;
            case 10:
            break;

        default:
        cout<<"Invalid choice!!"<<endl;
            break;
        }


    }while(choice!=10);

    return 0;
}

