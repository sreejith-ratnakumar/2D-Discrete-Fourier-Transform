#include<math.h>
#include <stdio.h>
#include<stdlib.h>
#define pi 3.14159265359
void generate_A_matrix(float*,float*,int);
void generate_A_matrix_transpose(float*,float*,float*,float*,int);
void get_input_matrix(float*,int);
void display_imaginary(float*,float*,int);
void multiply_complex(float*,float*,float*,float*,float*,float*);
void multiply_complex_array(float*,float*,float*,float*,float*,float*,int);
void display_complex(float*,float*,int);
void U_imaginary_fill(float*,int);
int main()
{
    int n;
    printf("Enter the order of matrix\n");
    scanf("%d",&n);
    float *W_real=(float*)malloc(4*n*n);
    float *W_imaginary=(float*)malloc(4*n*n);
    float *W_real_transpose=(float*)malloc(4*n*n);
    float *W_imaginary_transpose=(float*)malloc(4*n*n);
    float *u_real=(float*)malloc(4*n*n);
    float *u_imaginary=(float*)malloc(4*n*n);
    float *temp_real=(float*)malloc(4*n*n);
    float *temp_imaginary=(float*)malloc(4*n*n);
    float *result_real=(float*)malloc(4*n*n);
    float *result_imaginary=(float*)malloc(4*n*n);
    printf("Enter the input matrix\n");
    get_input_matrix(u_real,n);
    U_imaginary_fill(u_imaginary,n);
    generate_A_matrix(W_real,W_imaginary,n);
    generate_A_matrix_transpose(W_real,W_imaginary,W_real_transpose,W_imaginary_transpose,n);
    multiply_complex_array(W_real,W_imaginary,u_real,u_imaginary,temp_real,temp_imaginary,n);
    multiply_complex_array(temp_real,temp_imaginary,W_real_transpose,W_imaginary_transpose,result_real,result_imaginary,n);
    display_complex(result_real,result_imaginary,n);
    
    //test code for complex matrix multiplication
    /*float* a_r=(float*)malloc(4*16);
    float* a_i=(float*)malloc(4*16);
    float* b_r=(float*)malloc(4*16);
    float* b_i=(float*)malloc(4*16);
    float* r_r=(float*)malloc(4*16);
    float* r_i=(float*)malloc(4*16);
    printf("Real A\n");
    get_input_matrix(a_r,4);
    printf(" A\n");
    get_input_matrix(a_i,4);
    printf("Real B\n");
    get_input_matrix(b_r,4);
    printf("B\n");
    get_input_matrix(b_i,4);
    multiply_complex_array(a_r,a_i,b_r,b_i,r_r,r_i,4);
    display_complex(r_r,r_i,4);*/
    
    /*complex multiplication test code
    float a=2,b=5,c=2,d=10,e,f;
    float *aa=&a,*bb=&b,*cc=&c,*dd=&d,*ee=&e,*ff=&f;
    multiply_complex(aa,bb,cc,dd,ee,ff);
    printf("%f+j%f",*ee,*ff);*/
    
    return 0;
}
void generate_A_matrix(float* W_real,float* W_imaginary,int n)
{
    float rad=2*pi/n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            *(W_real+(i*n)+j)=cos(rad*i*j);
            *(W_imaginary+(i*n)+j)=-sin(rad*i*j);
        }
    }
}
void generate_A_matrix_transpose(float* W_real,float* W_imaginary,float* W_real_transpose,float* W_imaginary_transpose,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            *(W_real_transpose+(i*n)+j)=*(W_real+(j*n)+i);
            *(W_imaginary_transpose+(i*n)+j)=*(W_imaginary+(j*n)+i);
        }
    }
}
void get_input_matrix(float* u,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%f",u+(i*n)+j);
        }
    }
}
void display_complex(float* real,float* imaginary,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%f+j%f ",*(real+(i*n)+j),*(imaginary+(i*n)+j));
        }
        printf("\n");
    }
}
void multiply_complex_array(float* multiplier_real,float* multiplier_imaginary,float* multiplicant_real,float* multiplicant_imaginary,float* result_real,float* result_imaginary,int n)
{
    float sum_real=0,sum_imaginary=0,temp_real,temp_imag;
    float* p=&temp_real;float* q=&temp_imag;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            sum_real=0,sum_imaginary=0;
            for(int k=0;k<n;k++)
            {
                multiply_complex((multiplier_real+(i*n)+k),(multiplier_imaginary+(i*n)+k),(multiplicant_real+(k*n)+j),(multiplicant_imaginary+(k*n)+j),p,q);
                sum_real+= *p;
                sum_imaginary+= *q;
            }
            *(result_real+(i*n)+j)=sum_real;
            *(result_imaginary+(i*n)+j)=sum_imaginary;
        }
    }
}
void multiply_complex(float* a,float* b,float* c,float* d,float* p,float* q)
{
    float aa=*a,bb=*b,cc=*c,dd=*d;
    *p=(aa*cc)-(bb*dd);
    *q=(bb*cc)+(aa*dd);
}
void U_imaginary_fill(float* start,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        *(start+(i*n)+j)=0;
    }
}
