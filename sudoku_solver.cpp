#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

struct pv{
    int v;
    int valid;
    pv():v(0),valid(1){}
    pv(int i):v(i),valid(1){}
};

struct point{
    int x;
    int y;
    vector<pv> *p;
    //possible value with validbit
    point(int i, int j):x(i),y(j){p = new vector<pv>;};
    point(int i, int j, vector<pv> *pt):x(i),y(j),p(pt){};
};

class sudokur{
  public:
    int readBoard(char *);
    void show();
    bool search(int);
    bool isCorrect();
  private:
    void togValid(int, int, int, int, int);
    int board[10][10];
    vector<point> fill;
};

void sudokur::togValid(int x, int y, int g_value, int g_depth, int validnum){
    for(int d=g_depth+1; d<fill.size(); d++){
        if(fill[d].x == x ||
           fill[d].y == y ||
           (fill[d].x-1)/3 == (x-1)/3 && (fill[d].y-1)/3 == (y-1)/3){
            for(int k=0; k<fill[d].p->size(); k++){
                if(fill[d].p->at(k).v == g_value){
                    fill[d].p->at(k).valid += validnum;
                    break;
                }
            }
        }
    }
} 

bool sudokur::search(int g_depth){
    if(g_depth == fill.size())
        return true;
    for(int i=0; i<fill[g_depth].p->size(); i++){
        if(fill[g_depth].p->at(i).valid<1)
            continue;
        int x = fill[g_depth].x;
        int y = fill[g_depth].y;
        int g_value = fill[g_depth].p->at(i).v;
        board[x][y] = g_value;
        togValid(x, y, g_value, g_depth, -1);
        if(!search(g_depth+1)){
            togValid(x, y, g_value, g_depth, 1);
            board[x][y] = 0;
            continue;
        }
        else{
            return true;
        }
    }
    return false;
}

bool sizeCmp(point p1, point p2){ return p1.p->size() < p2.p->size(); }

bool sudokur::isCorrect(){
    int book[10]={0};
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++)
            book[ board[i][j] ] = 1;
        for(int k=1;k<=9;k++)
            if(book[k]==0)
                return false;
            else
                book[k]=0;
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++)
            book[ board[j][i] ] = 1;
        for(int k=1;k<=9;k++)
            if(book[k]==0)
                return false;
            else
                book[k]=0;
    }
    for(int i=0;i<=6;i+=3){
        for(int j=0;j<=6;j+=3){
            for(int k=1;k<=3;k++){
                for(int l=1;l<=3;l++){
                    book[ board[i+k][j+l] ] = 1;
                }
            }
            for(int m=1;m<=9;m++)
                if(book[m]==0)
                    return false;
                else
                    book[m]=0;
        }
    }
    return true;
}

void sudokur::show(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(board[i][j]==0)
                cout << "_ ";
            else
                cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

int sudokur::readBoard(char *filename){
    ifstream in(filename);
    if(!in.is_open())
        return -1;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            in >> board[i][j];
            if(board[i][j]==0)
                fill.push_back( point(i,j) );
        }
    }
    in.close();
    int book[10]={0};
    for(int it=0;it<fill.size();it++){
        int x=fill[it].x;
        int y=fill[it].y;
        for(int i=1;i<=9;i++){
            book[ board[x][i] ]=1;
            book[ board[i][y] ]=1;
        }
        int i=(x+2)/3;
        int j=(y+2)/3;
        for(int k=i*3;k>=i*3-2;k--)
            for(int l=j*3;l>=j*3-2;l--)
                book[ board[k][l] ]=1;
        for(int m=1;m<=9;m++){
            if(book[m]==0)
                fill[it].p->push_back(pv(m));
            else
                book[m]=0;
        }
    }
    sort(fill.begin(), fill.end(), sizeCmp);
    return 0;
}

int main(int argc, char *argv[]){
    if(argc!=2){
        cout << "give one input file" << endl;
        return -1;
    }
    sudokur player;
    if(player.readBoard(argv[1]) == -1){
        cout << "No such input file" << endl;
        return -1;
    }
    player.show();
    time_t start_search;
    time(&start_search);
    player.search(0);
    time_t end_search;
    time(&end_search);
    cout << " take me " << difftime(end_search, start_search) 
         << " secs:" << endl;
    player.show();
    if(player.isCorrect())
        cout << " Correct!" << endl;
    else
        cout << " Not Correct..." << endl;
    return 0;
}
