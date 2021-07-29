//Jacek Mucha
//15 maja 2013
//zadanie 1 lista 6 Kodowanie i Bezpieczeñstwo Informacji
//program licz¹cy entropiê, œredni¹ d³ugoœæ kodu Huffmana,
//wspó³czynnik kompresji i wspó³czynnik œredniej d³ugoœci kH do entropii
//wersja 2.0

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
# include <bitset>
 
using namespace std;

int LengthOfCodeCounter[256];
double MedHuffLength;

typedef struct Tree* HT;

struct File//struktura do przepisania pliku, nieistotna dla zadania
{
 long long int number1;
 float number2;
};

struct Tree
{
    Tree* pater;       //poprzednik
    double probability;//prawdopodobienstwo
    Tree* left;        //lewy nastepnik
    Tree* right;       //prawy nastepnik
    int symbol[256];   //kod
    int length;        //dlugosc kodu=poziom drzewa+1
    int byte;          //bajt, ktory kodujemy
};

double Entropia( double BytesProbability[])//entropia w natach
{
    double Entropia=0.0;
    for(int i=0;i<256;i++)
        if(BytesProbability[i]!=0)
            Entropia=Entropia+BytesProbability[i]*log(1/BytesProbability[i])/log(2.0);
    return Entropia;
}

void InOrder(Tree* x, int N)
{
     if(x!=NULL /*&& N>=0*/)
     {
         InOrder(x->left, N+1);
         x->length=N;
         LengthOfCodeCounter[N]++;
         InOrder(x->right, N+1);
     }
};

void MedHuffmanLength(Tree * HuffmanTree)
{
    if(HuffmanTree!=NULL)
    {
        if(HuffmanTree->left==NULL && HuffmanTree->right==NULL)
            MedHuffLength=MedHuffLength+HuffmanTree->probability*(double)HuffmanTree->length;
        MedHuffmanLength( HuffmanTree->left);
        MedHuffmanLength( HuffmanTree->right);
    }
} 

/*double KCompr(double , double NonEncoded)
{
    return Encoded
}*/

//zwraca prawdp[pdpbenstwo wystapienia danego bajtu
double Probability(int numerator, int denumerator)
{
    return (double)numerator/(double)denumerator;
}

//zwraca minimalne prawdopodobienstwo korzenia na liscie drzew
//ProbTable niepotrzebna
double MinProbability(list<HT> ProbList, double ProbTable[])
{
       double MinProb=1;//ProbTable[0];
       /*for(int i=0;i<256;i++)
           if(ProbTable[i]>0 && ProbTable[i]>=MinProb)
               MinProb=ProbTable[i];*/
       for(list<HT>::iterator itx=ProbList.begin();itx!=ProbList.end(); itx++)
       {
           HT TempTree= *itx;
           if(TempTree->probability<=MinProb)
               MinProb=TempTree->probability;
       }
       return MinProb;
}

void WriteTab(int A[], int N)
{
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}
 
int main()
{
    //char* FileName;   //nazwa pliku
    //string FileNameS; //do kontroli petli
    //cout<<"Podaj nazwe pliku: ";
    //cin>>FileName;
    //FileNameS=FileName;    
    
    int ByteCounter[256];//ile razy dany bajt wystepuje w pliku
    double ByteProbability[256];//prawdopodobienstwo wystapienia danego bajta w pliku
    list<HT> TreeConstructionList;//lista korzeni drzew do utworzenia drzewa Huffmana
    for(int i=0; i<256; i++) //wyzeruj
        ByteCounter[i]=0;
    //ifstream InputFile(FileName, ios::binary);
    //ifstream InputFile("Lista2WdP.rar", ios::binary); // plik odczytany binarnie
    //ifstream InputFile("Ania.jpeg", ios::binary); // plik odczytany binarnie
    //ifstream InputFile("skrypt.txt", ios::binary); // plik odczytany binarnie
    ifstream InputFile("Chinese.pdf", ios::binary); // plik odczytany binarnie
    if( InputFile.is_open() == false )
    {
        cout << "Problem z plikiem";
        system("Pause");
        return 1;
    }
    MedHuffLength=0.0;
    InputFile.seekg(0 , ios::end) ; //przesuwam sie na koniec pliku
    int FileLength = InputFile.tellg() ; //wczytujê rozmiar pliku w bajtach 
    char* temp = new char[FileLength]; //tymczasowa tablica bajtow    
    InputFile.seekg(0 , ios::beg) ; //przesun sie na poczatek
    InputFile.read(temp, FileLength); // wczytujemy dane do bufora
    int A[FileLength];
    //for(int i=0;i<FileLength;i++)
    //    cout<<temp[i];
    cout<<endl<<endl;
    for(int i=0;i<FileLength;i++)//ile razy dany bit wystepuje w pliku
    { 
        A[i]=(int)temp[i]+128; 
        //cout<<" "<<A[i];
        ByteCounter[A[i]]++; 
    }
    File* file = (File*)(temp);
    ofstream ofs("testBit.txt", ios::binary); // otwieramy plik do zapisu binarnego
    ofs.write((char*)(file), FileLength); // zapisujemy dane do pliku
    //WriteTab(ByteCounter,256);
    for(int i=0;i<256;i++)
    {
        //cout<<ByteCounter[i]<<" ";
        ByteProbability[i]=Probability(ByteCounter[i],FileLength);
        //cout<<ByteProbability[i];
    }
    cout<<"Entropia="<<Entropia(ByteProbability);
    delete file;
    HT T[256]; //utworz tablice korzeni drzewa. wezly, z ktorych utworzymy drzewo
    //HT T=new Tree;
    for(int i=0;i<256;i++)//zapelanianie TreeConstructionList
    {
        T[i]=new Tree;
        T[i]->pater=NULL;
        T[i]->left=NULL;
        T[i]->right=NULL;
        T[i]->probability=ByteProbability[i];
        LengthOfCodeCounter[i]=0; //wyzeruj tablice licznosci dlugosci kodu
        for(int j=0;j<256;j++)//kod ustaw na -1 -1 -1... -1
           T[i]->symbol[j]=-1;
        T[i]->length=0;//pierwotny poziom-0, bo kazdy wezel jest korzeniem
        T[i]->byte=i; //zidentyfikuj wezel
        if(T[i]->probability>0)
            TreeConstructionList.push_back(T[i]);
    }
    cout<<endl<<"MinProb="<<MinProbability(TreeConstructionList,ByteProbability)<<endl;
    
        /*for(list<HT>::iterator itx=TreeConstructionList.begin();itx!=TreeConstructionList.end() ; itx++)
        {
           HT TempTree= *itx;
           cout<<"p[i]="<<TempTree->probability<<endl;
        } */   
    while(TreeConstructionList.size()>1 )//zostaw jeden wezel- korzen drzewa Huffmana
    {
        double Min1=MinProbability(TreeConstructionList,ByteProbability);
        bool b=true;
        HT SL;
        HT SR;
        for(list<HT>::iterator itx=TreeConstructionList.begin();itx!=TreeConstructionList.end() && b; itx++)
        {
           HT TempTree= *itx;
           if(TempTree->probability==Min1)
           {
               b=false;
               SL=*itx;
               TreeConstructionList.erase(itx);
               itx--;//=TreeConstructionList.begin();
           }
        }
        b=true;
        double Min2=MinProbability(TreeConstructionList,ByteProbability);

        for(list<HT>::iterator itx=TreeConstructionList.begin();itx!=TreeConstructionList.end() && b; itx++)
        {
           HT TempTree= *itx;
           if(TempTree->probability==Min2)
           {
               b=false;
               SR=*itx;
               TreeConstructionList.erase(itx);
               itx--;//=TreeConstructionList.begin();
               //cout<<".";
           }
        }
        b=true;
        //cout<<"M1="<<Min1<<" M2="<<Min2<<" size="<<TreeConstructionList.size()<<endl;
        HT Node=new Tree;
        Node->probability=Min1+Min2;
        SL->pater=Node;
        SR->pater=Node;
        Node->pater=NULL;
        Node->left=SL;
        Node->right=SR;
        TreeConstructionList.push_back(Node);
    }
    HT HuffmanTree=*TreeConstructionList.begin();
    InOrder(HuffmanTree,0);
    //WriteTab(LengthOfCodeCounter,256);
    MedHuffmanLength( HuffmanTree);
    cout<<"Srednia dlugosc kodu Huffmana: "<<MedHuffLength<<endl;
//wspolczynnik kompresji to srednia dlugosc kodu Huffmana podzielone przez 8
    cout<<"Wspolczynnik kompresji: "<<MedHuffLength/8.0<<endl;
    cout<<"HuffLen/H="<<MedHuffLength/Entropia(ByteProbability)<<endl;
    system("Pause");
    return 0;
}
