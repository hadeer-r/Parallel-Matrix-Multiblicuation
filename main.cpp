#include <hpx/hpx_init.hpp>
#include <hpx/iostream.hpp>
#include <hpx/algorithm.hpp>
#include <iostream>
#include<vector>
typedef std::vector<std::vector<int>> matrix_type;
using hpx::cout;


void fill_matrix(matrix_type& matrix, int l, int u) {
    hpx::for_each(hpx::execution::par, matrix.begin(), matrix.end(),
                [&matrix, l, u](std::vector<int>& row) {
                    for (size_t i = 0; i < row.size(); ++i) {
                        row[i]=rand()%(u-l)+l;
                    }
                });
}

void print(matrix_type  matrix ){
    for(auto row:matrix){
        for(auto item:row)
        cout<<item<<" ";
        cout<<"\n";
    }
}

void multiblication(matrix_type &m1,matrix_type& m2, matrix_type& result){
    int R1=(int)m1.size();
    int C1=(int)m1[0].size();
    int R2=(int)m2.size();
    int C2=(int)m2[0].size();
    hpx::experimental::for_loop(hpx::execution::par,0,R1,[&](auto i){
        hpx::experimental::for_loop(0,C2,[&](auto j){
            result[i][j]=0;
            hpx::experimental::for_loop(0,R2,[&](auto k){
                result[i][j]+=m1[i][k]*m2[k][i];
            });
        });
    });
}

int hpx_main(int argc, char* argv[])
{
    int R1{},R2{},C1{},C2{}, l{},u{};

    if(argc>=2)
    {
        R1=std::stoi(argv[1]);
        R2=C1=std::stoi(argv[2]);
        C2=std::stoi(argv[3]);
        l=std::stoi(argv[4]);
        u=std::stoi(argv[5]);
    }
    else{
        cout<<"no argument\n";
        R2=C1=2;
        R1=C2=3;
        l=0;
        u=3;

    }

    matrix_type matrix1(R1,std::vector<int>(C1));
    matrix_type matrix2(R2,std::vector<int>(C2));
    matrix_type result(R1,std::vector<int>(C2));

    fill_matrix(matrix1,u,l);
    fill_matrix(matrix2,u,l);
    multiblication(matrix1,matrix2,result);

    print(matrix1);
    cout<<"\n";

    print(matrix2);
    cout<<"done_________________\n";
    print(result);

    return hpx::finalize();
}
int main(int argc, char* argv[])
{
    return hpx::init(argc,argv);
}
