#include  <iostream>
#include   <cstdlib>
#include   <fstream>
#include     <cmath>
using namespace std;




/***********************************************************/
/*                       Parameters                        */
/***********************************************************/
const int D =   100;   // row ond col of lattice
const int N =   D*D;   // number of nodes

int   L      [N][5];   // incidence list
int   G   [N][5][5];   // groups
int   strategy  [N];   // strategy of each node
float g     =     5;   // number of groups members
float K     =   0.1;   // noise
double r    =     2;   // enhancement factor
double r_max=     6;
float C_g[] = {0,1};   // cost of cooperation
float alpha =   2.;

int  mcs_max  =  10*N;   // montecarlo steps
int  ens_max  =    10;
int  idx_twin = 80000;
int  l_twin   = mcs_max - idx_twin;




/***********************************************/
/*            initialize functions             */
/***********************************************/
void time_evolution();
void phase_transition();
void phase_transition_2();

float NC(int);
float I(int, int);
float payoff(int, int);
float set_payoff(int);
bool  W(float, float);
void  PGG();
void  init();
float c_count();

void neighbor(int i, int j);
void set_neighbors();
void set_groups();
void make_network();

/***********************************************/
/*                    Main                     */
/***********************************************/
int main(){
    srand(time(NULL));
    make_network();
    //time_evolution();
    //phase_transition();
    phase_transition_2();
    return 0;
}


void time_evolution(){
    init();
    string filename = "time-evol-r" + to_string(r) + ".txt";
    ofstream output(filename);

    float p_c = c_count() / (float)N;

    for(int mcs=0; mcs<mcs_max; mcs++){
        PGG();
        p_c = c_count() / (float)N;
        output << mcs << "," << p_c << endl; 
    }
    output.close();
}


void phase_transition(){
    r = 1;
    float r_max = 10;
    float p_c = 0;

    ofstream output("hetro-sq-a0.txt");
    
    while(r<=r_max){
        std::cout << r << endl;
        p_c = 0;
        for(int ensmbl=0; ensmbl<10; ensmbl++){
            init();
            for(int mcs=0; mcs<mcs_max; mcs++){
                PGG();
            }
            p_c += c_count() / (float)N;
        }
        output << r << "," << p_c/10. << endl;
        r += 0.1;
    }
    output.close();
}


// both ensembel and time-window averaging 
void phase_transition_2(){
    r = 2;
    string file_name = "alpha-" + to_string(alpha) + ".txt";
    ofstream output(file_name);

    while (r <= r_max)
    {   
        std::cout << r << endl;
        float p_c = 0;

        for(int ens=0; ens<ens_max; ens++){
            std::cout << "   " << ens+1 << endl;
            init();
            float p_c_ens = 0;
            float pl_c[mcs_max];

            for(int mcs=0; mcs<mcs_max; mcs++){
                PGG();
                pl_c[mcs] = c_count() / (float)N;
            }

            for(int mcs=idx_twin; mcs < mcs_max; mcs++){
                p_c_ens += pl_c[mcs];
            }
            p_c += p_c_ens / (float)l_twin;
        }
        output << r << "," << p_c / (float)ens_max << endl;
        r += 0.1;
    }
    

    output.close();
}
/***********************************************/





/***********************************************************/
/*                       PGG DYNAMIC                       */
/***********************************************************/

float NC(int x){
    float nc = 0;
    for(int i=0; i<5; i++){
        if(strategy[L[x][i]] == 1){ nc+=1; }
    }
    return nc;
}


float I(int j, int i){
    if(strategy[i]==0){ return 0; }

    float DEN = 0;
    for(int n=0; n<5; n++){
        int l = L[i][n];
        DEN += pow(NC(l), alpha);
    }

    return pow(NC(j), alpha) / DEN;
}


float payoff(int i, int j){
    float I_SUM = 0;

    for(int n=0; n<5; n++){
        int l = L[j][n];
        I_SUM += I(j, l);
    }

    return ((r*I_SUM)/5) - I(j, i);
}


float set_payoff(int i){
    float Pi = 0;
    
    for(int n=0; n<5; n++){
        int j = L[i][n];
        Pi += payoff(i, j);
    }
    return Pi;
}



bool W(float P_x, float P_y){
    if((float)rand()/RAND_MAX < (1.0 / ( 1.0 + exp( (P_x-P_y) / K) ))){
          return  true; }
    else{ return false; }
}


void PGG(){
    for(int i=0; i<N; i++){
        int X = rand()%N;
        int Y = L[X][(rand()%(5-1))+1];

        if(strategy[X]==strategy[Y]){continue;}

        float P_x = set_payoff(X);
        float P_y = set_payoff(Y);

        if(W(P_x, P_y)==true){ strategy[X] = strategy[Y]; }
    }
}


void init(){
    // initial nodes strategy randomly
    for(int i=0; i<D; i++){
        for(int j=0; j<D; j++){
            strategy[i*D+j] = rand()%2;
        }
    }
}


float c_count(){
    float counter = 0;
    for(int i=0; i<N; i++){
        if(strategy[i]==1){ counter += 1;}
    }
    return counter;
}


/***********************************************************/
/*                         Network                         */
/***********************************************************/
void neighbor(int i, int j){
    int i_prev = i-1;
    int i_next = i+1;

    int j_prev = j-1;
    int j_next = j+1;

    if(i==0){i_prev = (D-1) - i;}
    if(i==(D-1)){i_next = (D-1) - i;}

    if(j==0){j_prev = (D-1) - j;}
    if(j==(D-1)){j_next = (D-1) - j;}

    L[i*D+j][0] = i*D + j;
    L[i*D+j][1] = i_prev*D + j;
    L[i*D+j][2] = i*D + j_prev;
    L[i*D+j][3] = i_next*D + j;
    L[i*D+j][4] = i*D + j_next;
}

void set_neighbors(){
    for(int i=0; i<D; i++){
        for(int j=0; j<D; j++){
            neighbor(i, j);
        }
    }
}

void set_groups(){
    for(int i=0; i<N; i++){
        for(int n=0; n<5; n++){
            for(int m=0; m<5; m++){
                G[i][n][m] = L[L[i][n]][m];
            }
        }
    }
}

void make_network(){
    set_neighbors();
    set_groups();
}