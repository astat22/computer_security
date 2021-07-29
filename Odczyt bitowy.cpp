#include <iostream>
#include <fstream>
 
using namespace std;
 
struct File
{
 long long int number1;
 float number2;
};
 
int main()
{
 ifstream ifs("Chinese.pdf", ios::binary); // otwieramy plik do odczytu binarnego
 
 /*char* temp = new char[sizeof(File)]; // tymczasowy bufor na dane
 ifs.read(temp, sizeof(File)); // wczytujemy dane do bufora
 File* file = (File*)(temp); // rzutujemy zawartoœæ bufora na typ File*/
 char* temp = new char[1000]; // tymczasowy bufor na dane
 ifs.read(temp, 1000); // wczytujemy dane do bufora
 unsigned int A[1000];
 for(int i=0;i<1000;i++)
     cout<<temp[i];
 cout<<endl<<endl;
 for(int i=0;i<1000;i++)
     { A[i]=(int)temp[i]; cout<<" "<<A[i]; }
 File* file = (File*)(temp);
 cout << file->number1 <<  " " << file->number2 << endl;
 ofstream ofs("testBit.txt", ios::binary); // otwieramy plik do zapisu binarnego
 
 //File* file = new File;
 //cin >> file->number1 >> file->number2 ;
 ofs.write((char*)(file), 1000000); // zapisujemy dane do pliku

 
 delete file;
    system("Pause");
    return 0;
}
