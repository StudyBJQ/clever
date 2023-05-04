// unicode转gb312.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"g.h"
#include"u.h"
//#define u_code 1
//#define g_code 2

int readfile();//读取文件，处理文件,判断大小
int isright(unsigned short origin_code, int method);//判断编码正确与否
int search_gb2132(unsigned short origin_code, int method);//搜索


void main()
{
    int u_code = 1;
    int some;
    int int_code;
    char str_begin[3] = { 0 };
    int flag;
    int str_begin_num;
    long long_code;
    char str[4] = { 0 };
    char* end;
    int code_right;
    int str_num;
    /* printf("1.unicode转gb2132\n2.gb2132转unicode\n输入你的选择：");
     scanf("%d",&some);
     if (some==1)
     {
         u_code = 1;
     }*/
    FILE* fp;
    fp = fopen("D:\\vs\\target.txt", "rb");
    //printf("%d", flag);
    flag = readfile();
    while (flag > 0)
    {
        flag--;
        //printf("%d", flag);

        str_begin_num = fread(str_begin, sizeof(char), 2, fp);
        str_num = fread(str, sizeof(char), 4, fp);
        long_code = strtol(str, &end, 16);
        int_code = (int*)long_code;
        code_right = isright(int_code, u_code);
        if (code_right == 1)
        {
            search_gb2132(int_code, u_code);
        }
    }
    fclose(fp);//关闭文件并保存
    FILE* fpp;
    fpp = fopen("c:\\123.txt", "a+");
    fprintf(fpp, "\n\n\n");
    fclose(fpp);
    fclose(fp);
    return 0;
}

//搜索，处理
//method,1  u-->gb
int search_gb2132(unsigned short origin_code, int method)
{
    char code_c[2];
    unsigned short end_code;
    int code = -1;
    int left = 0;
    int right = 7444;
    int num;
    int num2 = 0;
    FILE* fp;
    if (method == 1)//通过unicode，查gb2132
    {
        while (left <= right)
        {//在while循环中直到有一个条件结束搜索 
            num = (left + right) / 2;
            if (uni_map[num].value > origin_code)
            {
                left = num + 1;

                //printf("%d\n",left);
            }
            else if (uni_map[num].value < origin_code)
            {
                right = num - 1;
                //printf("%d\n", right);
            }
            else
            {
                code = uni_map[num].key;
                break;//一定要break跳出循环 
            }
        }
    }
    //else
    //{
    //    while (left <= right)
    //    {//在while循环中直到有一个条件结束搜索 
    //        num = (left + right) / 2;
    //        if (gb2312_map[num].key < origin_code)
    //        {
    //            left = num + 1;

    //            //printf("%d\n",left);
    //        }
    //        else if (gb2312_map[num].key > origin_code)
    //        {
    //            right = num - 1;
    //            //printf("%d\n", right);
    //        }
    //        else
    //        {
    //            code = gb2312_map[num].value;
    //            break;//一定要break跳出循环 
    //        }
    //    }
    //}
    if (code == -1)
    {
        printf("[\\u%X编码有误]", origin_code);
        fp = fopen("c:\\123.txt", "a+");
        fprintf(fp, "[\\u%X编码有误]", origin_code);
    }
    else
    {
        end_code = code;
        //printf("%x\n", a);
        code_c[0] = end_code & 0x0ff;
        //printf("%x\n",c[0]);
        code_c[1] = end_code >> 8 & 0x0ff;
        //printf("%x\n", c[1]);
        printf("%c%c", code_c[1], code_c[0]);

        fp = fopen("c:\\123.txt", "a+");
        fprintf(fp, "%c%c", code_c[1], code_c[0]);

    }
    fclose(fp);
    return code;
}

//判断编码正确与否
int isright(unsigned short origin_code, int method)
{
    FILE* fp;
    if (method == 1)
    {
        if (origin_code < 0x00a4 || origin_code>0xffe5)
        {
            printf("[\\u%X编码有误]", origin_code);
            FILE* fp;
            fp = fopen("c:\\123.txt", "a+");
            fprintf(fp, "[\\u%X编码有误]", origin_code);
            fclose(fp);
            return 0;
        }
    }
    /*else
    {
        if (origin_code < 0xa1a1 || origin_code > 0xf7fe)
        {
            printf("[%X编码有误]", origin_code);
            FILE* fp;
            fp = fopen("c:\\123.txt", "a+");
            fprintf(fp, "[\\u%X编码有误]", origin_code);
            fclose(fp);
            return 0;
        }
    }*/

    return 1;
}

//读取文件，处理文件,判断大小
int readfile()
{
    int address[50];
    int len = 0;
    int flag;
    //printf("输入编码文件地址,注意地址最长50字节且\\需输入两次");
    //gets(address);
    FILE* fp;
    fp = fopen("D:\\vs\\target.txt", "rb");
    if (fp == NULL) //当文件不存在，或者无法创建时会报错；
    {
        printf("读取文件失败！！！\n");
    }
    while (!feof(fp))
    {
        fgetc(fp);
        len++;
    }
    rewind(fp);//文件指针回到开头
    flag = (len - 1) / 6;
    fclose(fp);//关闭文件并保存
    return flag;
}



// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
