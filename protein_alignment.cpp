////////////////////////////////////////////////////////////////////////
// Smith-Waterman    Dynamic programming                              //
// Ognjen Perisic  2002-2013                                          //
//                                                                    //
////////////////////////////////////////////////////////////////////////




#define test1
#include "stdafx.h"
#include <stdio.h>
#include <direct.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

float mat[2000][2000];
int dir_mat[2000][2000];
int a[2000] = {0};
int b[2000] = {0};
float score = 0;

static double mdm[26][26] = {
/*        A    B    C    D    E     F    G    H    I    J    K     L    M    N    O    P    Q     R    S    T    U    V    W    X   Y    Z */
/*A*/   { 2,   0,  -2,   0,   0,   -4,   1,  -1,  -1,   0,  -1,   -2,  -1,   0,   0,   1,   0,   -2,   1,   1,   0,   0,  -6,   0,   -3,   0},
/*B*/   { 0,   2,  -4,   3,   2,   -5,   0,   1,  -2,   0,   1,   -3,  -2,   2,   0,  -1,   1,   -1,   0,   0,   0,  -2,  -5,   0,   -3,   2},
/*C*/   {-2,  -4,  12,  -5,  -5,   -4,  -3,  -3,  -2,   0,  -5,   -6,  -5,  -4,   0,  -3,  -5,   -4,   0,  -2,   0,  -2,  -8,   0,    0,  -5}, 
/*D*/   { 0,   3,  -5,   4,   3,   -6,   1,   1,  -2,   0,   0,   -4,  -3,   2,   0,  -1,   2,   -1,   0,   0,   0,  -2,  -7,   0,   -4,   3}, 
/*E*/   { 0,   2,  -5,   3,   4,   -5,   0,   1,  -2,   0,   0,   -3,  -2,   1,   0,  -1,   2,   -1,   0,   0,   0,  -2,  -7,   0,   -4,   3}, 
/*F*/   {-4,  -5,  -4,  -6,  -5,    9,  -5,  -2,   1,   0,  -5,    2,   0,  -4,   0,  -5,  -5,   -4,  -3,  -3,   0,  -1,   0,   0,    7,  -5}, 
/*G*/   { 1,   0,  -3,   1,   0,   -5,   5,  -2,  -3,   0,  -2,   -4,  -3,   0,   0,  -1,  -1,   -3,   1,   0,   0,  -1,  -7,   0,   -5,  -1}, 
/*H*/   {-1,   1,  -3,   1,   1,   -2,  -2,   6,  -2,   0,   0,   -2,  -2,   2,   0,   0,   3,    2,  -1,  -1,   0,  -2,  -3,   0,    0,   2}, 
/*I*/   {-1,  -2,  -2,  -2,  -2,    1,  -3,  -2,   5,   0,  -2,    2,   2,  -2,   0,  -2,  -2,   -2,  -1,   0,   0,   4,  -5,   0,   -1,  -2},
/*J*/   { 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0},
/*K*/   {-1,   1,  -5,   0,   0,   -5,  -2,   0,  -2,   0,   5,   -3,   0,   1,   0,  -1,   1,    3,   0,   0,   0,  -2,  -3,   0,   -4,   0}, 
/*L*/   {-2,  -3,  -6,  -4,  -3,    2,  -4,  -2,   2,   0,  -3,    6,   4,  -3,   0,  -3,  -2,   -3,  -3,  -2,   0,   2,  -2,   0,   -1,  -3}, 
/*M*/   {-1,  -2,  -5,  -3,  -2,    0,  -3,  -2,   2,   0,   0,    4,   6,  -2,   0,  -2,  -1,    0,  -2,  -1,   0,   2,  -4,   0,   -2,  -2}, 
/*N*/   { 0,   2,  -4,   2,   1,   -4,   0,   2,  -2,   0,   1,   -3,  -2,   2,   0,  -1,   1,    0,   1,   0,   0,  -2,  -4,   0,   -2,   1}, 
/*O*/   { 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0},
/*P*/   { 1,  -1,  -3,  -1,  -1,   -5,  -1,   0,  -2,   0,  -1,   -3,  -2,  -1,   0,   6,   0,    0,   1,   0,   0,  -1,  -6,   0,   -5,   0}, 
/*Q*/   { 0,   1,  -5,   2,   2,   -5,  -1,   3,  -2,   0,   1,   -2,  -1,   1,   0,   0,   4,    1,  -1,  -1,   0,  -2,  -5,   0,   -4,   3}, 
/*R*/   {-2,  -1,  -4,  -1,  -1,   -4,  -3,   2,  -2,   0,   3,   -3,   0,   0,   0,   0,   1,    6,   0,  -1,   0,  -2,   2,   0,   -4,   0}, 
/*S*/   { 1,   0,   0,   0,   0,   -3,   1,  -1,  -1,   0,   0,   -3,  -2,   1,   0,   1,  -1,    0,   2,   1,   0,  -1,  -2,   0,   -3,   0}, 
/*T*/   { 1,   0,  -2,   0,   0,   -3,   0,  -1,   0,   0,   0,   -2,  -1,   0,   0,   0,  -1,   -1,   1,   3,   0,   0,  -5,   0,   -3,  -1}, 
/*U*/   { 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0},
/*V*/   { 0,  -2,  -2,  -2,  -2,   -1,  -1,  -2,   4,   0,  -2,    2,   2,  -2,   0,  -1,  -2,   -2,  -1,   0,   0,   4,  -6,   0,   -2,  -2}, 
/*W*/   {-6,  -5,  -8,  -7,  -7,    0,  -7,  -3,  -5,   0,  -3,   -2,  -4,  -4,   0,  -6,  -5,    2,  -2,  -5,   0,  -6,  17,   0,    0,  -6}, 
/*X*/   { 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0},
/*Y*/   {-3,  -3,   0,  -4,  -4,    7,  -5,   0,  -1,   0,  -4,   -1,  -2,  -2,   0,  -5,  -4,   -4,  -3,  -3,   0,  -2,   0,   0,   10,  -4}, 
/*Z*/   { 0,   2,  -5,   3,   3,   -5,  -1,   2,  -2,   0,   0,   -3,  -2,   1,   0,   0,   3,    0,   0,  -1,   0,  -2,  -6,   0,   -4,   3}}; 


const int penalty      = -2;
const int open_penalty = -3;

float max(float a, float b, float c)
{
    float temp;
    temp = (a>b)?a:b;
    temp = (temp>c)?temp:c;
    return temp;
}

float value(int a, int b)
{ float val;
   if (a==b)
     val = 1;
   else
     val = -1;

   //return val;
   return mdm[a-65][b-65];
    
}

int main(int argc, char* argv[])
{
    int ai, bi, i, j;
    float r1, r2, r3, res, temp;
    int old_dir = 0;
    int kazna;
    char file_name[60] = "";
    int max_length, min_length;

    FILE* input;
    FILE* output;	

    ai = 1;
	
    input = fopen(argv[1], "r");

    while(!feof(input))	{
      if (!feof(input)){
        fscanf(input, "%c", &a[ai]);
        ai++;
      }
    }
    fclose(input);

    bi = 1;
    input = fopen(argv[2], "r");

    while(!feof(input))	{
      if (!feof(input)) {
        fscanf(input, "%c", &b[bi]);
        bi++;
      }
    }
    fclose(input);
    ai--;
    bi--;

    max_length = __max( ai, bi );
    min_length = __min( ai, bi );

    
    //cout << "Aligning sequences with ratio <= 1.2!" << endl << endl;

    /*if (float(max_length) / float(min_length) > 1.2) {
        cout << "High sequence length ratio (>1.2) " << argv[1] << " " << argv[2] << endl;
        cout << "I am not aligning!" << endl << endl;
        return 0;
    }*/
    

    

    for(i=0; i<ai; i++)
       for(j=0; j<bi; j++)
         mat[i][j] = 0;

    mat[0][1] = open_penalty;
    for (i=2; i<bi; i++)
        mat[0][i] = open_penalty + (i-1)*penalty;

    mat[1][0] = open_penalty;
    for (i=1; i<ai; i++)
        mat[i][0] = open_penalty + (i-1)*penalty;
    
    old_dir = 0;
    for(i=1; i<ai-1; i++) {
        for(j=1; j<bi-1; j++) {
            temp = value(a[i],b[j]);

            if (j==1)
                old_dir = 1;
            
            if (old_dir==1)
                kazna = open_penalty;
            else
                kazna = penalty;
            

            r1 = mat[i-1][j-1] + temp;            
            r2 = mat[i-1][j] + kazna;            
            r3 = mat[i][j-1] + kazna;

            res = max(r1, r2, r3);
            
            if (res==r1)
                dir_mat[i][j] = 1;
            
            if (res==r2)
                dir_mat[i][j] = 2;
            
            if (res==r3)
                dir_mat[i][j] = 3;


            old_dir = dir_mat[i][j];
            mat[i][j] = res;            
        }
        
    }
    i--;
    j--;



    i = ai;
    j = bi;
    int k = 1;
    std::vector<char> first_sequence;
    std::vector<char> second_sequence;
   
    do
    {
        switch(dir_mat[i][j]) {
        	
            case 0:    //printf("%4d : %c  %c\n", k, a[i], b[j]);
                first_sequence.push_back(a[i]);
                second_sequence.push_back(b[j]);
                i--;
                j--;
                k++;
                break;
            case 1:    //printf("%4d : %c  %c\n", k, a[i], b[j]);
                first_sequence.push_back(a[i]);
                second_sequence.push_back(b[j]);
                i--;                
                j--;
                k++;
                break;
                
            case 2:    //printf("%4d : %c  %c\n", k, a[i], '-');
                first_sequence.push_back(a[i]);
                second_sequence.push_back('-');
                i--;
                k++;
                break;
            case 3:	   //printf("%4d : %c  %c\n", k, '-', b[j]);
                first_sequence.push_back('-');
                second_sequence.push_back(b[j]);
                j--;
                k++;
                break;
                
            default: 
                if (i==0) {
                    //printf("%4d : %c  %c\n", k, '-', b[j]);
                    first_sequence.push_back('-');
                    second_sequence.push_back(b[j]);
                    j--;
                    break;
                }
                if (j==0) {
                    //printf("%4d : %c  %c\n", k, a[i], '-');
                    first_sequence.push_back(a[i]);
                    second_sequence.push_back('-');
                    i--;
                    break;
                } 
		}

	} while ((i+j)>0);
    


    i = 0;
    file_name[i] = '\0';
    do{
        file_name[i] = argv[1][i];
        i++;
    }while (argv[1][i]!='.');
    file_name[i++] = '_';

    j = 0;
    do{
        file_name[i] = argv[2][j];
        i++;
        j++;
    }while (argv[2][j]!='.');    
    file_name[++i] = '\0';
    strcat(file_name, ".alignment");

   
    chdir("alignments");
    output = fopen(file_name, "w");

    i = ai - 2;
    j = bi - 2;
    k = 1;

    std::vector<char>::iterator it;
    for (it = first_sequence.end()-1; it > first_sequence.begin(); it--){
        //std::cout << *it;
        fprintf(output, "%c", *it);
    }
    fprintf(output, "\n");

    for (it = second_sequence.end()-1; it > second_sequence.begin(); it--){
        //std::cout << *it;
        fprintf(output, "%c", *it);
    }
   
    fprintf(output, "\n");    
    fclose(output);
	
    return 0;
}
