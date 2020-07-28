/*
港口
口停
停靠
靠
问
问
题
题
某港口提供有足够的泊位供船舶停靠，但现在仅有一个 可供装卸的泊位，船舶先到则先进行装卸，
如果船舶得 不到及时装卸而造成的滞期费为每小时100元。
现要弄 清该系统的性能，
重点考察船舶进入该港后等待装卸的 滞留时间以及卸位(即装卸用的泊位)的利用率，从而 进行经济效益分析。
 首先，对进入该港口的100艘船进行实际调查，记录其活动情况， 
 得到这100艘船到达港口的时间间隔和装卸时间的分布情况的频 数和累积频率分布。
设:一年内到达港口的船舶数为N，到港船舶滞留总时间 为T1，
  船舶平均滞留时间为T2，港口支付滞留费为Y，装 卸泊位空闲时间装卸泊位利用率S。
Step1: 模拟船舶到达港口的时间间隔的分布P1， Step2: 模拟船舶装卸所需时间的分布P2， Setp3: 编写程序。
   为了比较准确地反映系统的性能，我们采用稳态模拟 方式，可以考察系统运行360天的情况。假定港口每 天24小时连续工作，因此模拟时间T设置为8640小时。 考虑到船舶到达港口的事件是影 响整个系统状态的 主要因素，可以将模拟事件设置为该事件的发生时刻。
   所用变量说明:
• t:一艘船到达港口的时间;
• tl:前一艘船驶离港口的时间;
• td:两艘船到达港口的时间间隔;
• ts:当前船舶装卸所需时间;
• tw:t时刻所有已到达港口的船舶等待装卸时间总和;
• tf:t时刻装卸位已空闲时间总和;
   经过6次模拟计算，装卸泊位的平均利用率为95.3%， 
   但到达的船舶的却因得不到及时的服务而造成平均每 艘滞留9.295小时，
   每年到港船舶总滞留6843小时， 因此港口每年约需支付68万元的滞留费，
   这显然是一 笔不小的开支。为此，可修改模拟模型，考虑增设一 个装卸泊位，并重新进行模拟运行，
   将这些数据提供 给决策者一确定是否需要再新建一个装卸泊位。
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#define random() (double)(rand()/(RAND_MAX+1.0))
static double array[14][2]={
   {0.,0.01},
   {0.01,0.04},
   {0.04,0.1},
   {0.1,0.17},
   {0.17,0.26},
   {0.26,0.36},
   {0.36,0.47},
   {0.47,0.58},
   {0.58,0.69},
   {0.69,0.78},
   {0.78,0.85},
   {0.85,0.91},
   {0.91,0.96},
   {0.96,1.00}
},array1[8][2]={
{0,0.20},
{0.20,0.42},
{0.42,0.61},
{0.61,0.77},
{0.77,0.87},
{0.87,0.95},
{0.95,0.98},
{0.98,1.00}
};
static int list[14],list1[8],length=14,length1=8;
typedef struct 
{
    int system_time[2];
    int N;
    int cost;
     int T1[2];
} 
Port;
struct structname
{
    int arrival_time;
    int loading_time;
    struct structname * Next;
};
typedef struct structname Ship;
int Random(double array[][2],int *list,int length)
{
    double r=random();
       for(int i=0;i<length;i++)
       {
            if(array[i][0]<r&&r<array[i][1])
            {
                return list[i];
            }
       }
       return rand();
}
void Solve_Problem(Port *port,Ship *ship,int time,int n,char*filename)
{
    int index,t,t1;
    Ship *ptm=ship;
    FILE*file=fopen(filename,"w");
    char str[100];
    fputs("Transpose@{",file);
    for(int i=0;i<n;i++)
    {
       memset(port->system_time,0,2*sizeof(int));
       memset(port->T1,0,2*sizeof(int));
       port->N=0;port->cost=0;t1=0;
       while(port->system_time[index=(port->system_time[0]>=port->system_time[1])]<=time)
       {
          port->N++;
          t1=(ship->arrival_time=Random(array,list,length)+t1);
          ship->loading_time=Random(array1,list1,length1);
          if((t=ship->arrival_time-port->system_time[index])>=0)
          {
                                 port->T1[index]+=t;
                                 port->system_time[index]+=t+ship->loading_time;   
                                 port->cost+=100*ship->loading_time;                                                                                                                                                                                                            
          }else
          {
                     port->system_time[index]+=ship->loading_time;
                     port->cost+=100*(ship->loading_time-t);
          }
                   ptm=ship;
                 ship->Next=(Ship*)malloc(sizeof(Ship));
                 ship=ship->Next;
                 free(ptm);
       }
       sprintf(str,"{%d,%d,%d,%d},",port->system_time[port->system_time[0]>=port->system_time[1]],port->N,port->cost,port->T1[index]);
       fputs(str,file);
    }
    fputs("Nothing}",file);
    fclose(file);
}
int main(int argc,char **argv)
{
            if(argc==4&&strcmp(argv[1],"calc")==0)
            {
               srand(time(NULL));
               int n;
               char filenames[100];
               sscanf(argv[2],"%d",&n);
               sscanf(argv[3],"%s",filenames);
                Port port;
                Ship *ship=(Ship*)malloc(sizeof(Ship));
               for(int i=0;i<length;i++)
               {
                  list[i]=i+5;
               }
               for(int i=0;i<length1;i++)
               {
                  list1[i]=i+9;
               }
               Solve_Problem(&port,ship,8760,n,filenames);
            }
}
