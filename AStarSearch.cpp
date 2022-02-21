#include <iostream>
#include <fstream>
#include<vector>
using namespace std;
struct node{
 int index, h = 0, g = 0,f = 0, truoc = 0 ;
};
const int maxx = 100;
vector<node> Open;
vector<node> Close;
node NODE[maxx];

int a[maxx][maxx], n;

bool readFile (string fileName, int a[100][100],node NODE[], int &n){

  ifstream fileInput(fileName, ios:: in);

  if(fileInput.fail()) 
      return false;
  fileInput >> n;  
  for(int i = 1 ; i <= n; i++){
    NODE[i].index = i;
	   fileInput >> NODE[i].h;	
  }
  for (int i = 1 ; i <= n; i++)
  {
      for (int j = 1 ; j <= n; j++)
      {
        fileInput >> a[i][j];
      }
        
  }
  fileInput.close();
  return 0;
} 

void xuatdothi(int a[maxx][maxx],node NODE[], int n ){
  cout<<"So dinh do thi: "<<n<<endl;
  for(int i = 1; i<= n; i++){
    cout<<"h["<<i<<"] = "<<NODE[i].h<<", ";
  }
  cout<<endl;
  for(int i = 1; i<= n; i++){
    for(int j = 1; j<= n; j++){
      cout<<a[i][j]<<" ";
    }
    cout<<endl;
  }
}

int findMinf(vector<node> Open){
  int index = 0;
  for(int i = 1; i< Open.size(); i++){
    if(Open[i].f < Open[index].f) index = i;
  }
  return index;
}

int findNodeOpen(vector<node> Open, int index){
  for(int i =0; i< Open.size(); i++){
    if(Open[i].index == index) return i;
  }
  return -1;
}
int findNodeClose(vector<node> Close, int index){
  for(int i =0; i< Close.size(); i++){
    if(Close[i].index == index) return i;
  }
  return -1;
}
void AStart_Search(int a[maxx][maxx], int n, int start, int finish ){
  // khoi tao  Open = {start}, Close = {rong}
  NODE[start].g = 0;
  NODE[start].f = NODE[start].h;
  Open.push_back(NODE[start]);
  // lap
  while(Open.size() > 0){
    int index = findMinf(Open);
    node p = Open[index];  // lay node p co f min
    Open.erase(Open.begin() + index);   // xoa node p ra khoi Open
    //test p
    cout<<"P: "<<p.index<<endl;
    if(p.index == finish) break;
    else{
      Close.push_back(p); // them p vao close
    }
    // q ke tiep p
    
    for(int q = 1; q<= n ; q++){

      if(a[p.index][q] > 0){
        // test q       
        cout<<"Q: "<<q<<endl;
        // end test
        if(findNodeClose(Close,q) != -1 && NODE[q].g > p.g + a[p.index][q]){  // neu q co trong close mhung tim thay duong di ngan hon =) xoa q khoi close va them q lai vao Open
          cout<<"TH1\n";
          NODE[q].g = p.g + a[p.index][q];
          NODE[q].f = NODE[q].g + NODE[q].h;
          NODE[q].truoc = p.index;
          // xoa q khoi close, them q vao Open
          Close.erase(Close.begin() + findNodeClose(Close,q));
          Open.push_back(NODE[q]);
        }
        else if(findNodeClose(Close,q) != -1) continue;  // neu q trong close nhung duong di, chi phi k cai thien thi giu nguyen va nhay den q khac
        else if(findNodeOpen(Open, q) == -1){     // neu q k co trong close va Open =) them vao Open
          cout<<"TH2\n";
          NODE[q].g = p.g + a[p.index][q];
          NODE[q].f = NODE[q].g + NODE[q].h;
          NODE[q].truoc = p.index;
          Open.push_back(NODE[q]);
        }
        else if(findNodeOpen(Open, q) != -1 && NODE[q].g > p.g + a[p.index][q] ){  // neu da da co trong Open thi xem thu chi phi co cai thien khong ? de cap nhat laij q trong open
          cout<<"TH3\n";
          NODE[q].g = p.g + a[p.index][q];
          NODE[q].f = NODE[q].g + NODE[q].h;  
          NODE[q].truoc = p.index;
          Open[findNodeOpen(Open, NODE[q].index)] = NODE[q];
            
        }
      }
   
    }
      // test open, close
      cout<<"cac dinh trong open: ";
      for(int i= 0; i< Open.size();i++){
        cout<<Open[i].index<<"("<<Open[i].g<<","<<Open[i].f<<"), ";
      }
      cout<<endl<<"cac dinh trong Close: ";
      for(int i= 0; i< Close.size();i++){
        cout<<Close[i].index<<"("<<Close[i].g<<","<<Close[i].f<<"), ";
      }      
    cout<<endl;

  }
  // return kq duong di tu start -> finish

  if(NODE[finish].truoc == 0) cout<<"Khong tim thay duong di tu: "<<start<<" -> "<<finish<<endl;
  else{
    cout<<"Duong di: "<< finish << "<- ";
    int index = NODE[finish].truoc;
    
    do{
      if(index == start) break;
      cout<<index<<"<- ";
      index = NODE[index].truoc;
    }while(index != start);
    cout<<index<<endl;
  }

}

int main(){



  //DOTHI1
  readFile("dothi1.txt",a,NODE,n); 
  xuatdothi(a,NODE,n);
  AStart_Search(a,n,8,9);   

  //DOTHI2
  // readFile("dothi2.txt",a,NODE,n);  
  // xuatdothi(a,NODE,n);
  // AStart_Search(a,n,1,2);



  return 0;
}