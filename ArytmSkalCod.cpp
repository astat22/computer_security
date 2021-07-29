//Jacek Mucha
//17 maja 2013
//zadanie 2 lista 6 Kodowanie i Bezpieczeñstwo Informacji
//algorytm kodowania arytmetycznego ze skalowaniem
//kodowanie algorytmiczne ze skalowaniem, entropia, srednia dlugosc kodu Huffmana
//srednia dlugosc kodowania arytmetycznego
//Program czyta dane z linii komend
//wersja 1.0, czytaj¹ca tekst do kodowania z linii komend

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <list>
# include <bitset>
 
using namespace std;

int LengthOfCodeCounter[256];
double MedHuffLength;
list<bool> Code;
int AritmLength;

typedef struct Tree* HT;

struct Tree
{
    Tree* pater;       //poprzednik
    double probability;//prawdopodobienstwo
    Tree* left;        //lewy nastepnik
    Tree* right;       //prawy nastepnik
    int symbol[256];   //kod
    int length;        //dlugosc kodu=poziom drzewa+1
    int byte;          //bajt, ktory kodujemy
    double LeftBorder;// lewy i prawy koniec na tablicy prawdopodobienstw
    double RightBorder;
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

//zwraca prawdp[pdpbenstwo wystapienia danego bajtu
double Probability(int numerator, int denumerator)
{
    return (double)numerator/(double)denumerator;
}

//zwraca minimalne prawdopodobienstwo korzenia na liscie drzew
//ProbTable niepotrzebna
double MinProbability(list<HT> ProbList, double ProbTable[])
{
       double MinProb=1;
       for(list<HT>::iterator itx=ProbList.begin();itx!=ProbList.end(); itx++)
       {
           HT TempTree= *itx;
           if(TempTree->probability<=MinProb)
               MinProb=TempTree->probability;
       }
       return MinProb;
}

double MedLength(list<HT> ProbList, int TextLength)
{
    double PX=1.0;
    double SX=0.0;
    for(list<HT>::iterator itx=ProbList.begin();itx!=ProbList.end(); itx++)
       {
           HT TempTree= *itx;
           if(TempTree->probability>0.0)
               PX=PX*(TempTree->probability);
           SX=SX+(TempTree->probability);
           //cout<<TempTree->probability<<" ";
       }
     //cout<<"srednio: "<<SX*TextLength<<endl;
    //cout<<log(1/PX)+1<<endl<<" "<<PX;
    return log(1/PX)/log(2.0)+1;
}

double MaxProbability(list<HT> ProbList, double ProbTable[])
{
       double MaxProb=0.0;
       for(list<HT>::iterator itx=ProbList.begin();itx!=ProbList.end(); itx++)
       {
           HT TempTree= *itx;
           if(TempTree->probability>=MaxProb)
               MaxProb=TempTree->probability;
       }
       return MaxProb;
}

void WriteTab(int A[], int N)
{
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
}
 
void ArCo(double BorderProbability[], int ByteBuffor[], int BufforLength /*,list<bool> Code*/)
{
    int Counter=0;
    int ActualByte;
    double LeftProb, RightProb;

    for (int i=0;i<BufforLength;i++)
    {
        ActualByte=ByteBuffor[i];
        LeftProb=BorderProbability[ActualByte];
        RightProb=BorderProbability[ActualByte+1];
        if(LeftProb<0.5 && RightProb<0.5)
        {
            while(RightProb<=0.5)
            {
                LeftProb=LeftProb*2;
                RightProb=RightProb*2;
   
            }
        Code.push_back(false);
            while(Counter>0)
            {
                Code.push_back(true);
                Counter--;
            }
        }
        if(LeftProb>=0.5 && RightProb>=0.5)
        {
            LeftProb=LeftProb*2-1;
            RightProb=RightProb*2-1;
            Code.push_back(true);
            while(Counter>0)
            {
                Code.push_back(false);
                Counter--;
            }
        }
        if(LeftProb<0.5 && RightProb>0.5 && LeftProb>=0.25 && RightProb<0.75)
        {
            LeftProb=LeftProb*2-0.5;
            RightProb=RightProb*2-0.5;
            Counter++;
        }
    }
}

void WriteCode(list<bool> Code)
{
    cout<<endl<<endl<<"Code: ";
    for(list<bool>::iterator itx=Code.begin();itx!=Code.end(); itx++)
    {
        if(*itx==true)
            cout<<"1";
        else
            cout<<"0";
        AritmLength++;
    }
    cout<<endl<<endl;
} 

int main()
{
    int ByteCounter[256];//ile razy dany bajt wystepuje w tekscie
    double ByteProbability[256];//prawdopodobienstwo wystapienia danego bajta w tekscie
    list<HT> TreeConstructionList;//lista korzeni drzew do utworzenia drzewa Huffmana
    for(int i=0; i<256; i++) //wyzeruj
        ByteCounter[i]=0;
    //string TextToCode;
    AritmLength=0;
    char TextToCode[1000];
    for(int i=0;i<1000;i++)
        TextToCode[i]='\n';
    cout<<"Wpisz tekst do zakodowania: ";
    //cin>>TextToCode;
    cin.getline(TextToCode,1000);
    //cout<<endl<<TextToCode;
    MedHuffLength=0.0;
    int i2=0;
    while(TextToCode[i2]!='\n')
        i2++;
    int TextLength = i2-1;
    int A[TextLength];
    double BorderProbability[257];//[TextLength+1];
    BorderProbability[0]=0.0;
    for(int i=0;i<TextLength;i++)//ile razy dany bit wystepuje w tekscie
    { 
        A[i]=(int)TextToCode[i]+128; 
        //cout<<" "<<A[i];
        ByteCounter[A[i]]++;

    }
    bool ByteControl[256];
    //WriteTab(ByteCounter,256);
    for(int i=0;i<256;i++)
    {
         BorderProbability[i+1]=0.0; 
         ByteProbability[i]=Probability(ByteCounter[i],TextLength);
         BorderProbability[i+1]=BorderProbability[i]+ByteProbability[i];
         if(ByteProbability[i]>0)
         {
             cout<<"byte "<<i<<" prob="<<ByteProbability[i]<<" l="<<BorderProbability[i]<<" p="
             <<BorderProbability[i+1]<<endl;
             ByteControl[i]=true;
         }
         else
             ByteControl[i]=false;
    }
    cout<<"Entropia="<<Entropia(ByteProbability);
    HT T[256]; //utworz tablice korzeni drzewa. wezly, z ktorych utworzymy drzewo
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
    cout<<"bitow jednoznacznie (zaokraglic w gore): "<<MedLength(TreeConstructionList,TextLength)<<endl<<endl;
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
 //kodowanie arytmetyczne ze skalowaniem   

    ArCo(BorderProbability,A,TextLength/*,Code*/);
    WriteCode(Code);
    cout<<endl<<"srednia dlugosc kodowania arytmetycznego: "<<AritmLength<<":"<<TextLength<<endl<<endl;//wielkosci pliku wyjsiowego/wielkosc pliku wejsciowego

    system("Pause");
    return 0;
}
