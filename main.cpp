#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include<iomanip>
using namespace std;
char name[6][8]; //各个单位的名称
float zhl[6]; //各个单位的转换率存储在此数组中
float result[10] ; //10个结果
void read(); //从文件读入并计算
void write(); //写入到文件
int isOperator(string str); //判断是否是运算符，加为7，减为8
int isUnit(string str); //判断单位
float str2float(string str);//string转floatint 
main()
{  
  read(); //读取数据	
  write(); //写入数据	
  return 0;
}
void read()
{	
  int num; //读取不需要的数字
  char str[10]; //读取不需要的字符串 	
  ifstream infile("input.txt");   	
  if(!infile) 	
  {		
     cerr << "open error!" << endl;		
     exit(1);	
  }  	//将文件前6行读入到数组中	
  for(int i = 0;i < 6;i++)	
  {	
    infile >> num; //读取第一个数字		
    infile >> name[i]; //读取单位名字		
    infile >> str; //读取不需要的字符，“=”		
    infile >> zhl[i]; //单位转换率		
    infile >> str; //读取不需要的字符，“m”	
  }	//读取需要计算的部分，并加以计算	
  float tmp; //计算存储数字	
  string cal; //要计算的字符串（部分）	
  string line; //要计算的字符串（行）	
  int statius1 = 0,statius2 = 0; //是否换行的标志（运算符，单位）	
  int l=0; //第几行	
  int zf=1; //判断加减	
  while(!(infile.eof()))	
  {
    infile >> cal;		
    if(!isUnit(cal) && !isOperator(cal)) //判断是否为数字		
    {			
      statius1 = statius2;			
      statius2 = 1;			
      tmp = str2float(cal);			
      if(statius1==2 && statius2==1) //换行标志（单位2，数字1）			
      {				
        l++;				
        zf=1; //换行后符号要重置			
      }			
      continue;	
    }		
    if(isUnit(cal))		
    {		
      statius1 = statius2;			
      statius2 = 2;			
      cout<<zf<<endl;		
      result[l] += tmp * zhl[isUnit(cal)-1] *zf;			
      continue;		
    }		
    if(isOperator(cal))		
    {			
    statius1 = statius2;			
    statius2 = 3;			
    if(isOperator(cal)-7)				
    zf=-1;			
    else	zf=1;			
    continue;	
    }
  }	
  infile.close();}
  void write()
  {
     ofstream outfile("output.txt");	
     if(!outfile)	
     {		
       cerr << "open output.txt error!" << endl;		
       exit(1);
      }	
     //输出结果
     outfile << "447407567@qq.com" << endl; //第1行是您在渣打编程马拉松官网上报名时的注册邮箱	
     //第2行是空行	
     //输出计算结果	
     for(int i = 0 ; i < 10 ; i++)		
     outfile << endl <<setiosflags(ios::fixed)<<setprecision(2)<< result[i] << " m"; 
     //从上一行处输出，本次输出不换行	//最后一行不需要换行	
     outfile.close();
  }
  int isOperator(string str)
  {
    if(str=="+")		
    return 7;	
    if(str=="-")		
    return 8;
    return 0;
  }
  int isUnit(string str)
  {
    if((str=="mile") || (str=="miles"))		return 1;
      if((str=="yard") || (str=="yards"))		return 2;	
        if((str=="inch") || (str=="inches"))		return 3;	
          if((str=="foot") || (str=="feet"))		return 4;	
            if((str=="fath") || (str=="faths"))		return 5;	
              if((str=="furlong") || (str=="furlongs"))		return 6;	else return 0;
  }
  float str2float(string str)
  { 
    stringstream sstr(str);    
    float num;    
    if((sstr >> num).fail())    
    { 
      //ERROR     
    } 
    return num;
  }
