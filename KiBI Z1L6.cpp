//Jacek Mucha
//15 maja 2013
//zadanie 1 lista 6 Kodowanie i Bezpieczeñstwo Informacji
//program licz¹cy entropiê, œredni¹ d³ugoœæ kodu Huffmana,
//wspó³czynnik kompresji i wspó³czynnik œredniej d³ugoœci kH do entropii

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
# include <bitset>
//#include <cryptopp/sha.h>
//#include <cryptopp/modes.h>
//#include <cryptopp/hex.h>
//#include <cryptopp/aes.h>
//#include <cryptopp/filters.h>
//#include <cryptopp/base64.h>

using namespace std;

typedef unsigned char byte;

struct File
{
 int number1;
 float number2;
};

double Entropia(int FileLength, double BytesProbability[])//entropia w natach
{
    double Entropia=0;
    for(int i=0;i<FileLength;i++)
        Entropia=Entropia+BytesProbability[i]*log(1/BytesProbability[i]);
    return Entropia;
}

double HuffmanLength()
{
} 

double KCompr()
{
}

int CharCardinality(list<char> ListOfChar)
{
    int card=0;
    return card;
}

double Probability(int numerator, int denumerator)
{
    return (double)numerator/(double)denumerator;
}

void WriteTab(int A[], int N)
{
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}

int main()
{

    //fstream File1;    //plik do wczytywania danych
	//byte * input = new byte[1000000];
    char* FileName;   //nazwa pliku
    string FileNameS; //do kontroli petli
    //list<int> ListOfBytes;         //tu zapisujemy bajty z pliku
    //list<byte> ByteListOfBytes;
    char FileCharPointer;   //do tego odczytujemy bajt
    int FileBytePointer;
    int ListOfCharLength;   //dlugosc pliku w bajtach
    while(FileNameS!="0") //jesli string==0, to zamknij program
    {
        cout<<"Podaj nazwe pliku: ";
        cin>>FileName;
        FileNameS=FileName;
        /*if(FileNameS=="0")
            return 0;*/
            
            
            
 ifstream ifs("skrypt.txt", ios::binary); // otwieramy plik do odczytu binarnego
 

 char* temp = new char[1000]; // tymczasowy bufor na dane
 ifs.read(temp, 1000); // wczytujemy dane do bufora
 unsigned int A[1000];
 for(int i=0;i<1000;i++)
     cout<<temp[i];
 cout<<endl<<endl;
 for(int i=0;i<1000;i++)
     { A[i]=(int)temp[i]; cout<<" "<<A[i]; }            
            
            
            
            
        //ifstream File2(FileName, ios::binary);
/*	    ifstream file (FileName, ios::in);

       	int FileLength = 2000;//file.tellg();
       	cout<<"plik"<<FileName<<" "<<FileLength<<" - dlugosc pliku"<<endl<<endl;
        //byte * input = new byte[FileLength];
	    char * buffer = new char [FileLength];
        file.read (buffer,FileLength);
	    for(int i=0;i<FileLength;i++) 
        {
		    input[i]=(const byte) buffer[i];
        }
        for(int i=0;i<FileLength;i++)
            cout<<buffer[i];
        cout<<endl<<endl;
        for(int i=0;i<FileLength;i++)
            cout<<input[i];*/
                
        /*char* temp = new char[sizeof(long long int)]; // tymczasowy bufor na dane
        File2.read(temp, sizeof(long long int)); // wczytujemy dane do bufora
        long long int* number1 = (long long int*)(temp); */ // rzutujemy zawartoœæ bufora na typ int
        //cout<<number1<<endl;
 
        /*File1.open(FileName,ios::in);        //otwieranie pliku
        if( File1.is_open() == false )
        {
           cout << "Problem z plikiem";
           system("Pause");
           return 1;
        }
        ListOfCharLength=0;*/
        /*while(!File1.eof() )
        {
            File1>>FileCharPointer;
            //File1>>FileBytePointer;
            FileBytePointer=(int)FileCharPointer;
            ListOfBytes.push_front(FileBytePointer);
            ListOfCharLength++;
            cout/*<<FileBytePointer<FileCharPointer;
        } 
        //ListOfBytes.sort();
        int CountingTable[128];
        for(int i=0;i<128;i++)
            CountingTable[i]=0;
        for(list<int>::iterator itx=ListOfBytes.begin();itx!=ListOfBytes.end(); itx++)
        {
            cout<<",";
            CountingTable[*itx]++;
        }
        WriteTab(CountingTable,ListOfCharLength);*/
        //File1.close();
        //file.close();
//        File2.close();
        
    }
    system("Pause");
    return 0;
}
