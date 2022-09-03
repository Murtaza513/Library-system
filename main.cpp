
#include<vector>
#include<list>
#include<string.h>
#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
class node
{

public:
    string name;
    int price;
    node *next;
    node *temp;

    node()
    {
    }

    node(string name,int price)
    {
        this->name=name;
        this->price=price;
        next=NULL;
    }

    void insert(node **head_ref,int price,string name)
    {

        if((*head_ref)==NULL)
        {
            (*head_ref)=new node(name,price);
            temp=(*head_ref);
        }
        else
        {
            temp->next=new node(name,price);
            temp=temp->next;
        }

    }

    void printReciept(node *head)
    {
        node *temp= head;
        int total=0;
        for(int i=0; i<5; i++)
    {
        cout<<"*\t\t\t\t\t*"<<endl;

    }
    cout<<"-\tItems purchased\t-"<<endl;


        cout<<" "<<endl;
        while(temp!=NULL)
        {
            cout<<"Name: "<<head->name<<"\n"<<". "<<"Price: "<<head->price<<"\n"<<endl;
            total=total+temp->price;
            temp=temp->next;
        }
        cout<<"Total Bill : "<<total<<endl;
         for(int i=0; i<5; i++)
    {
        cout<<"*\t\t\t\t\t\t*"<<endl;

    }
    }


};
class Edge
{

public:
    int DestinationBookID;
    string name;

    Edge()
    {
    }
    Edge(int destVID,string bname)
    {

        DestinationBookID=destVID;
        name=bname;
    }
    void setEdgeValues(int destVID)
    {
        DestinationBookID=destVID;

    }

    int getDestinationBookByID()
    {
        return DestinationBookID;
    }
    string getDestinationBookByName()
    {
        return name;
    }
};



class Book
{
public:
    int book_id;
    string book_name;
    int price;
    string authorName;

    list<Edge> edgeList;
    list<Edge> priceEdgeList;

    Book()
    {
        book_id=0;
        book_name="";
        price=0;
        authorName="";
    }
    Book(int id,string name,int Price,string Aname)
    {
        book_id=id;
        book_name=name;
        price=Price;
        authorName=Aname;
    }


    int getbookID()
    {
        return book_id;
    }
    string getBookName()
    {
        return book_name;
    }


    int getPrice()
    {
        return price;
    }
    string getAuthorName()
    {
        return authorName;
    }
    void setAuthorName(string aname)
    {
        authorName=aname;
    }
    void setID(int id)
    {
        book_id=id;
    }
    void setbookName(string sname)
    {
        book_name=sname;
    }
    void setPrice(int Price)
    {
        price=Price;
    }
    list<Edge> getEdgeList()
    {
        return edgeList;
    }
    list<Edge> getPriceEdgeList()
    {
        return priceEdgeList;
    }
    void printEdgeList()
    {
        cout<<"More books by same author"<<endl;

        for(auto it=edgeList.begin(); it !=edgeList.end(); it++)
        {
            cout<<"ID: "<<it->getDestinationBookByID()<<" "<<"Name: "<<it->getDestinationBookByName()<<endl;

        }

    }

    void printPriceEdgeList()
    {
        cout<<"[";
        for(auto it=priceEdgeList.begin(); it !=priceEdgeList.end(); it++)
        {
            cout<<it->getDestinationBookByID()<<" "<<it->getDestinationBookByName()<<"-->";
            cout<<endl;
        }
        cout<<"]";
        cout<<endl;
    }
};

class Graph
{
public:
    vector<Book> bookCollection;

    Book getBookByID(int vid)
    {
        Book temp;
        for(int i=0; i<bookCollection.size(); i++)
        {
            temp=bookCollection.at(i);
            if(temp.getbookID()==vid)
            {
                return temp;
            }
        }
    }

    void addBook(Book newBook)
    {
        bool check = checkIfBookExistByID(newBook.getbookID());

        if(check)
        {
            cout<<"Book already exists"<<endl;
            return;
        }
        else
        {
            fstream my_file;
            my_file.open("my_file.txt", ios::app);

            my_file << newBook.getbookID() << ',' << newBook.getBookName() << ','
                    << newBook.getAuthorName() << ',' << newBook.getPrice() <<'\n';
            my_file.close();


            bookCollection.push_back(newBook);
           cout<<"New Book added"<<endl;
        }

        for(int i=0; i<bookCollection.size(); i++)
        {
            Book temp=bookCollection.at(i);
            if(temp.getAuthorName()==newBook.getAuthorName())
            {
                addEdgeByID(temp.getbookID(),newBook.getbookID());
            }

        }
        for(int i=0; i<bookCollection.size(); i++)
        {
            Book temp=bookCollection.at(i);
            if(temp.getPrice()==newBook.getPrice())
            {
                addEdgeByPrice(temp.getbookID(),newBook.getbookID());
            }

        }
    }


    Book search(string name)
    {
        int flag=0;
        char prompt;
        Book temp;
        for(int i=0; i<bookCollection.size(); i++)
        {
            temp=bookCollection.at(i);
            if(temp.getBookName()==name)
            {
                cout<<"ID: "<<temp.getbookID()<<endl;
                cout<<"Name: "<<temp.getBookName()<<endl;
                cout<<"Price: "<<temp.getPrice()<<endl;
                cout<<"Author: "<<temp.getAuthorName()<<endl;
                flag=1;
                break;
            }


        }
        if(flag==0)
        {
            cout<<"Book not found"<<endl;
        }
        else
        {
            cout<<"Other books by the same author"<<endl;
            temp.printEdgeList();
            cout<<"Other books in the same price range"<<endl;
            temp.printPriceEdgeList();
            cout<<"Buy this book? (Y/N)\n";
            cin>>prompt;
            if(prompt=='N')
            {

            }
            else if(prompt=='Y')
            {
                return temp;
            }
        }
    }
    bool checkIfBookExistByID(int vid)
    {

        for(int i=0; i<bookCollection.size(); i++)
        {
            if(bookCollection.at(i).getbookID()==vid)
            {
                return true;
            }
        }
        return false;
    }

    bool checkIfEdgeExistByID(int fromBook,int toBook)
    {
        Book v= getBookByID(fromBook);
        list<Edge> e;
        e=v.getEdgeList();
        bool flag=false;

        for(auto it=e.begin(); it !=e.end(); it++)
        {
            if(it->getDestinationBookByID()==toBook)
            {
                flag=true;
                return flag;
                break;
            }
        }
        return flag;
    }

    bool checkIfEdgeExistByPrice(int fromBook,int toBook)
    {
        Book v= getBookByID(fromBook);
        list<Edge> e;
        e=v.getPriceEdgeList();
        bool flag=false;

        for(auto it=e.begin(); it !=e.end(); it++)
        {
            if(it->getDestinationBookByID()==toBook)
            {
                flag=true;
                return flag;
                break;
            }
        }
        return flag;
    }

    void addEdgeByID(int fromBook,int toBook)
    {
        Book v=getBookByID(fromBook);
        Book v2=getBookByID(toBook);
        string nameFromBook=v.getBookName();
        string nameToBook=v2.getBookName();

        bool check1=checkIfBookExistByID(fromBook);
        bool check2=checkIfBookExistByID(toBook);
        \
        if(check1 && check2 == true)
        {
            bool check3=checkIfEdgeExistByID(fromBook,toBook);
            if(check3==true)
            {
                //cout<<"Edge already exists"<<endl;
            }
            else
            {
                for(int i=0; i<bookCollection.size(); i++)
                {
                    if(bookCollection.at(i).getbookID()==fromBook)
                    {
                        Edge e(toBook,nameToBook);
                        bookCollection.at(i).edgeList.push_back(e);
                    }
                    else if(bookCollection.at(i).getbookID()==toBook)
                    {
                        Edge e(fromBook,nameFromBook);
                        bookCollection.at(i).edgeList.push_back(e);
                    }
                }
                cout<<"Edge added successfully"<<endl;
            }

        }
        else
        {
            cout<<"Source Id or Destination Id is incorrect.\n"<<endl;
        }
    }

    void addEdgeByPrice(int fromBook,int toBook)
    {
        Book v=getBookByID(fromBook);
        Book v2=getBookByID(toBook);
        string nameFromBook=v.getBookName();
        string nameToBook=v2.getBookName();

        bool check1=checkIfBookExistByID(fromBook);
        bool check2=checkIfBookExistByID(toBook);

        if(check1 && check2 == true)
        {
            bool check3=checkIfEdgeExistByPrice(fromBook,toBook);
            if(check3==true)
            {
                cout<<"Edge already exists"<<endl;
            }
            else
            {
                for(int i=0; i<bookCollection.size(); i++)
                {
                    if(bookCollection.at(i).getbookID()==fromBook)
                    {
                        Edge e(toBook,nameToBook);
                        bookCollection.at(i).priceEdgeList.push_back(e);
                    }
                    else if(bookCollection.at(i).getbookID()==toBook)
                    {
                        Edge e(fromBook,nameFromBook);
                        bookCollection.at(i).priceEdgeList.push_back(e);
                    }
                }
                //cout<<"Edge added successfully"<<endl;
            }

        }
        else
        {
            cout<<"Invalid Book"<<endl;
        }
    }



    void printGraph()
    {
        if(bookCollection.size()==0){
            cout<<"Please add Books First.\n";
        }
        for (int i=0; i<bookCollection.size(); i++)
        {
            Book temp;
            temp=bookCollection.at(i);
            cout<<"Name: "<<temp.getBookName()<<" "<<"Id: "<<temp.getbookID()<<" "<<"Author Name: "
                <<temp.getAuthorName()<<" "<<"Price: "<<temp.getPrice()<<endl;

            /*cout<<temp.getBookName()<<"("<<"ID: "<<temp.getbookID()<<")"<<"("<<"Price: "<<temp.getPrice()<<")"<<" Author Name: "
            <<temp.getAuthorName()<<")-->";
             //temp.printEdgeList();*/
        }
    }
};

void gotoxy(int x, int y)
{
    COORD d;
    d.X = x;
    d.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
}
void ColorChange()
{
    char a = 219;

    for(int i=0; i<5; i++)
    {
        cout<<"*\t\t\t\t\t\t*"<<endl;

    }
    cout<<"-\t\tWELCOME TO BOOKSTORE\t\t-"<<endl;
    for(int i=0; i<5; i++)
    {
        cout<<"*\t\t\t\t\t\t*"<<endl;

    }


}
void load()
{
    char a = 219;
    gotoxy(36, 14);
    cout << "Loading..."<< endl;
    gotoxy(30,16);
    for(int r =1; r<=20; r++)
    {
        for(int q=0; q<=10000000; q++);
        cout << a;
    }
}
void Reading(Book v1,Graph g){
int id1;
int price1;
Book v2;
    string id;
    string str;
    string name;
    string author;
    string price;

     fstream my_file;
	my_file.open("my_file.txt", ios::in);
	while(true){
if( my_file.eof() ) break;
		getline(my_file,str,'\n');

		stringstream ss(str);

        getline(ss,id,',');
       stringstream degree(id);

     id1 = 0;
    degree >> id1;
        v2.setID(id1);
        getline(ss,name,',');

        v2.setbookName(name);
        getline(ss,author,',');

        v2.setAuthorName(author);
        getline(ss,price,',');


           stringstream degree1(price);

     price1 = 0;
    degree >> price1;
cout<<price1;
        v2.setPrice(price1);


        g.addBook(v2);

	}

my_file.close();
}
int main()
{
    int option, id1,price,id2,total=0,determinor;
    Graph g;
    char prompt;

    string sname,aname,searchName;
    Book v1,purchase;
    node reciept;
    node *head=NULL;

            v1.setID(5);
            v1.setbookName("Lotr");
            v1.setPrice(5600);
            v1.setAuthorName("Tolkien");
            g.addBook(v1);

   // Reading(v1,g);


    system("color 30");
    ColorChange();
    cout << endl << endl << endl << endl << endl << endl << endl;
determine:
    cout<<"Type (1) if you're user and (0) for admin :"<<endl;
    cin>>determinor;
    if(determinor==0)
    {
Admin:
        system("cls");

        load();
        cout << endl << endl << endl << endl << endl << endl << endl;
        system("cls");
         do
    {

        cout<<"Select option number, Enter 0 to exit, "<<endl;
        cout<<"1.Add Book"<<endl;
        cout<<"2.Display all books"<<endl;
        cout<<"3.Add edge"<<endl;
        cout<<"4.Switch to Login Page."<<endl;
        cout<<"0.Exit"<<endl;
        cout<<endl;


        cin>>option;

        switch(option)
        {
        case 0:

            return 0;

        case 1:
            system("cls");
            load();
             system("cls");
            cout<<"Enter book ID"<<endl;
            cin>>id1;
            cout<<"Enter Book name"<<endl;
            cin>>sname;
            cout<<"Enter author Name"<<endl;
            cin>>aname;
            cout<<"Enter Price"<<endl;
            cin>>price;



            v1.setID(id1);
            v1.setbookName(sname);
            v1.setPrice(price);
            v1.setAuthorName(aname);
            g.addBook(v1);

            break;

        case 2:
           g.printGraph();
            break;
        case 3:

  cout<<"Enter source Id"<<endl;
            cin>>id1;
            cout<<"Enter destination Id"<<endl;
            cin>>id2;
            g.addEdgeByID(id1,id2);
            break;

        case 4:
            cout<<endl;
            system("cls");
            goto determine;



        default:
            int choice = 0;
        cout<<"Invalid Choice\n"<<endl;
        cout<<"Would you like to choose again?\n";
        cout<<"Press (0) for yes and (1) for exit.\n";
        cin>>choice;
        if(choice==0)
        {
            system("cls");
            goto Admin;
        }
        else
        {
            return 0;
        }

        }
        cout<<endl;

    }

    while(option!=0);




    }
    else if(determinor==1)
    {
        User:
        system("cls");
        system("color 30");
        load();
        cout << endl << endl << endl << endl << endl << endl << endl;
        system("cls");

        do
        {

            cout<<"Select option number, Enter 0 to exit, "<<endl<<endl;

            cout<<"1.Search and Purchase "<<endl;
            cout<<"2.Display all books"<<endl;
            cout<<"3.Switch to Login Page."<<endl;
            cout<<"0.Exit"<<endl;
            cout<<endl;


            cin>>option;

            switch(option)
            {
            case 0:
              return 0;


            case 1:
                while(1)
                {
                    cout<<"Press Y to search and purchase press N to quit"<<endl;
                    cin>>prompt;
                    if(prompt=='N')
                        break;

                    cout<<"Enter name of the book "<<endl;
                    cin>>searchName;
                    purchase=g.search(searchName);
                    reciept.insert(&head,purchase.getPrice(),purchase.getBookName());
                }
                reciept.printReciept(head);
                break;

            case 2:
                g.printGraph();
                break;
            case 3:
            cout<<endl;
            system("cls");
            load();
            system("cls");
            goto determine;



            default:
              int choice = 0;
        cout<<"Invalid Choice\n"<<endl;
        cout<<"Would you like to choose again?\n";
        cout<<"Press (0) for yes and (1) for exit.\n";
        cin>>choice;
        if(choice==0)
        {
            system("cls");
            goto User;
        }
        else
        {
            return 0;
        }
            }

            cout<<endl;
        }
        while(option!=0);


    }

    else
    {
        int choice = 0;
        cout<<"Invalid Choice\n"<<endl;
        cout<<"Would you like to choose again?\n";
        cout<<"Press (0) for yes and (1) for exit.\n";
        cin>>choice;
        if(choice==0)
        {
            system("cls");
            goto determine;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

