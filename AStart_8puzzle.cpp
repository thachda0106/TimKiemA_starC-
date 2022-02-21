#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int KT[3][3] = {1, 2, 3,
                8, 0, 4,
                7, 6, 5 };

void swap(int & x, int &y){
   int temp = x;
   x = y;
   y = temp;

}
enum action {
   LEFT,RIGHT,UP,DOWN,STAY
};
class node{
   public:
   int a[3][3], x, y, g = 0, h= 0, f = 0, truoc = -1;   // truoc la node cha 
   action move = STAY;  // trang thai di chuyen tu not cha den hien tai
   bool canMoveLeft(){
   	if( move != RIGHT && y>0) return true;
      else return false;
   }
   bool canMoveRight(){
   	if( move != LEFT && y<2) return true;
      else return false;
   }
   bool canMoveUp(){
   	if( move != DOWN && x>0) return true;
      else return false;
   }
   bool canMoveDown(){
   	if(  move != UP && x<2) return true;
      else return false;
   }   
   
   void moveLeft(){
   	swap(a[x][y] ,a[x][y-1]);
      y--;
   }

   void moveRight(){
   	swap(a[x][y] ,a[x][y+1]);
      y++;
   }
   void moveUp(){
   	swap(a[x][y] ,a[x-1][y]);
      x--;

   }
   void moveDown(){
   	swap(a[x][y] , a[x+1][y]);
      x++;
   }
};

vector <node> Open, Close, NODE;
void init(node &puzzle){
   cout<<" Nhap trang thai cho puzzle: ";
   for(int i =0; i<3; i++){
	for(int j=0; j<3; j++){
	    cin>>puzzle.a[i][j];
	}
   }
}

void xuatNodePuzzle(node p){
   cout<<"puzzle[3][3]\n"; 
   for(int i=0; i< 3; i++){
     for(int j = 0; j<3; j++){
        cout<< p.a[i][j]<< " ";
     }
     cout<<endl;
  } 
  cout<< "g= "<<p.g<<", h= "<<p.h<<", f= "<<p.f<<endl;
}


void getXYnode(int a[3][3],int n, int& x, int &y ){
  for(int i=0; i< 3; i++){
     for(int j = 0; j<3; j++){
        if(a[i][j] == n) {
           x = i;
           y = j ;
           return;
        }
     }
  }   
}

int calc_h(node puzzle){
   int h = 0;
   int x, y, x1,y1;
   for(int n= 0; n<9; n++){
      getXYnode(puzzle.a,n,x,y);
      getXYnode(KT,n,x1,y1);
      h += (abs(x - x1) + abs (y - y1));
   }  
   return h;
}

void get_XY(node puzzle, int &x, int &y){
  for(int i=0; i< 3; i++){
     for(int j = 0; j<3; j++){
        if(puzzle.a[i][j] == 0) {
           x = i;
           y = j;
        }
     }
  } 

}

int findMinf(vector<node> Open){
  int index = 0;
  for(int i = 1; i< Open.size(); i++){
    if(Open[i].f < Open[index].f) index = i;
  }
  return index;
}

bool checkTT(int arr[3][3], int buzz_a[3][3]){
  for(int i=0; i< 3; i++){
     for(int j = 0; j<3; j++){
        if(arr[i][j] != buzz_a[i][j] ) {
            return false;
        }
     }
  }    
  return true;
}

int findNodeOpen(vector<node> Open, int buzz_a[3][3]){
  for(int i =0; i< Open.size(); i++){
    if( checkTT(Open[i].a, buzz_a) ) return i;
  }
  return -1;
}


int findNodeClose(vector<node> Close, int buzz_a[3][3]){
  for(int i =0; i< Close.size(); i++){
    if( checkTT(Close[i].a, buzz_a) ) return i;
  }
  return -1;
}


int findNodeNODE(vector<node> NODE, int buzz_a[3][3]){
  for(int i =0; i< NODE.size(); i++){
    if( checkTT(NODE[i].a, buzz_a) ) return i;
  }
  return -1;
}
void AStar_Puzzle(node& puzzle){
   //khoi tao
   puzzle.g = 0;     // chi phi ban dau g =0
   puzzle.h = calc_h(puzzle);    // tinh h ban dau cua puzzle
   puzzle.f = puzzle.h;    // f = h + g
   puzzle.truoc = -1;         // truoc trang thai dau la NULL
   get_XY(puzzle, puzzle.x,puzzle.y);    // get x,y toa do 0 ban dau
   Open.push_back(puzzle);                          // khoi tao Open = trang thai dau, CLOSE = rong

   // lap
   while(Open.size() > 0){
      int index = findMinf(Open);    // vi tri node co fmin trong Open
      node p = Open[index];
      Open.erase(Open.begin() + index);        // lay va xoa p trong open
      NODE.push_back(p);        // luu trang thai 
      // xuat p
      cout<<"p: \n";              // thong tin p(fmin) lay ra tu open
      xuatNodePuzzle(p);
      if(checkTT(p.a,KT)) break;      // neu la trang thai kt =) thoat
      else Close.push_back(p);         /// else them vao Close de va xet cac trang thai lien sau cua p

      // q ke tiep p
      vector <node> listq; node n;
      if(p.canMoveLeft()){
         n = p;
         n.moveLeft();
         n.move = LEFT;
         listq.push_back(n);
      }
      if(p.canMoveRight()){
         n = p;
         n.moveRight();
         n.move = RIGHT;
         listq.push_back(n);
      }
      if(p.canMoveUp()){
         n = p;
         n.moveUp();
         n.move = UP;
         listq.push_back(n);        
      }
      if(p.canMoveDown()){
         n = p;
         n.moveDown();
         n.move = DOWN;
         listq.push_back(n);        
      }
      for(int i = 0; i<listq.size(); i++){
         listq[i].truoc = findNodeNODE(NODE, p.a);
         listq[i].h = calc_h(listq[i]);
         listq[i].g = p.g + 1;
         listq[i].f = listq[i].g + listq[i].h;
         get_XY(listq[i],listq[i].x,listq[i].y);
         
      }
      for(int i=0; i< listq.size();i++){
         node q = listq[i];
         // test
         cout<<"q: \n";
         xuatNodePuzzle(q);
         cout<<"Action:(DI CHUYEN: ) "; 
         switch(q.move){
            case UP:{
               cout<<"LEN\n";
               break;
            }
               case DOWN:{
               cout<<"XUONG\n";
               break;
            }
               case LEFT:{
               cout<<"TRAI\n";
               break;
            }
               case RIGHT:{
               cout<<"PHAI\n";
               break;
            }
               case STAY:{
               cout<<"DUNGIM\n";
               break;
            }
         }
         //
         if(findNodeClose(Close, q.a) != -1 ){  // neu q da co trong Close
            cout<<"th1\n";
            int vt = findNodeNODE(NODE, q.a); // vi tri q trong NODE
            // test 
            if(vt == -1 ) cout<< "loi\n";
            //
            if ( NODE[vt].g > q.g )  {    // neu chi phi den q hien tai thap hon q trong NODE 
              Close.erase(Close.begin() + findNodeClose(Close, q.a));
              NODE.erase(NODE.begin() + vt);
              Open.push_back(q);
            }
         }
         else if( findNodeClose(Close, q.a) != -1 ) continue;
         else if(findNodeOpen(Open, q.a) == -1){
            cout<<"th2\n";
            Open.push_back(q);
         }
         else if(findNodeOpen(Open, q.a) != -1){
            cout<<"th3\n";
            int vt = findNodeOpen(Open, q.a);
            if(Open[vt].g > q.g){
               Open[vt] = q;
            }
         }
      }
   }

   cout<< "\n CAC TRANG THAI SE DI LA: \n";
   if(NODE[NODE.size()-1].truoc == -1) cout<<"Khong tim duoc\n";
   else{
      int index = NODE.size()-1;
      
      vector<int> duongDi;
      duongDi.push_back(index);
      while(index != 0){
         index = NODE[index].truoc;
         duongDi.push_back(index);
      }
      for(int i = duongDi.size() - 1; i>= 0 ; i--){
         xuatNodePuzzle(NODE[duongDi[i]]);
         cout<<"Action:(DI CHUYEN: ) "; 
         switch(NODE[duongDi[i]].move){
            case UP:{
               cout<<"LEN\n";
               break;
            }
               case DOWN:{
               cout<<"XUONG\n";
               break;
            }
               case LEFT:{
               cout<<"TRAI\n";
               break;
            }
               case RIGHT:{
               cout<<"PHAI\n";
               break;
            }
               case STAY:{
               cout<<"DUNGIM\n";
               break;
            }
         }
      }
   }
   


}
int main()
{
   node puzzle;
   init(puzzle); 
   // puzzle.a = {2, 8, 3,
   //             1, 0, 4,
   //             7, 6, 5 };  
   // input : 2 8 3 1 0 4 7 6 5
   AStar_Puzzle(puzzle);


   return 0;
}