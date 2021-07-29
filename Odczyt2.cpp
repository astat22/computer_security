#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
# include <bitset>
 
using namespace std;


int main()
{
    std::ifstream ifs("Chinese.pdf", ios::in | ios::binary); // input file
    std::ostringstream oss; // output to string

    int len;
    char buf[1024];
    while((len = ifs.readsome(buf, 1024)) > 0)
    {
        oss.write(buf, len);
    }

    std::string data = oss.str(); // get string data out of stream
    //cout<<data;

    //long int dl=strlen(data);
    int A[1000];
        //char * temp;
        //temp=data;
 for(int i=0;i<1000;i++)
     { A[i]=(int)data[i]+128; cout<<" "<<A[i]; }
     system("Pause");
    return 0;
}
