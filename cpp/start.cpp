#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

struct Books
{
    char title[5];
    int book_id;
};

int main()
{
    Books book;
    strcpy(book.title,"haha");
    clog << "name is :"<< book.title  << endl;

    char data[100];

    ofstream of;
    of.open("xx.log",ios::app|ios::in);
    of << "xot\n";
    of.close();

    ifstream infile;
    infile.open("xx.log"); 
    infile.seekg(3);
    infile >> data;
    cout << data << endl;
    infile.close();
    return 0;

}
