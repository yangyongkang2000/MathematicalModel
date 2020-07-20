/*某港口有一个万吨级泊位，根据长期观察记录， 两艘船只依次到港的间隔时间服从以下规律:
  
船只到港时间间隔/h
1 5 10 15 20 30 40
频率
0.15 0.1 0.12 0.14 0.17 0.26 0.06

港口现有一台装卸机，根据其它港口的经验，若 用两台装卸机可以节约装卸时间。经过统计，两种情 况下的装卸规律如下:
每条船的装卸时 间/h
一台装卸机
14 16 18 20 22
两台装卸机
10 12 14 15 17
频率
0.05 0.5 0.2 0.2 0.05
 
  按照规定，到港船只必须在15~30h内装卸完毕，其中 包括等待和装卸时间。若超过30h时，港口每小时支 付赔偿费200元;若能少于15h时，每提前1h港口得奖 励250元。
  港口在没有船只装卸时，每小时经济损失 为400元;
  而每艘船在港口每停泊1h损失200元。
  已知 一台装卸机购置与安装费用为60万元，折旧期为10年。 每台装卸机每月维修及油料等开支为3000元。
  试分析该港口增添第二台装卸机在经济上是否合算? 注意:增添设备的经济可行性以投资回收期来衡量，
  若 其短于标准投资期，则增添设备是可行的;否则便不可 取。投资回收期为g=△k/△c，其中△k=60万元为增添设 备的投资，△c是一台装卸机和两台装卸机两种情况下 的经营费用之差，即经营费用的节约值。
 
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#define random() ((double)rand()/(RAND_MAX+1.0))
#define Picewise(low,up,var,var1,val)  if((low)<=(var)&&(var)<(up)){(var1)=(val);continue;}
#define Malloc(ship,n) for(int i=0;i<n;ship[i++]=(Ship *)calloc(1,sizeof(Ship)));
#define change(c,a,b,d) b+=(c>0?((a)>=0?400*(a)+6000:(a<=-15?450*(a)+9750:200*(a)+6000)):(d>=15?200*d-400*(c):450*d-400*(c)-3750));
#define max(a,b)  ((a)>(b)?(a):(b))
#define Macro(c) sprintf(str,c,port->system_time,port->cost);fputs(str,file);port->cost=0;port->system_time=0;
#define Select(c)  Random_loading_time(ship,n,c);Random_arrive_time(ship,n);Solve_Problem(port,ship,n);
typedef struct 
{
    int system_time;
     long long int cost;
} 
Port;
typedef struct 
{
    int arrival_time;
    int loading_time;
}
Ship;
void Random_loading_time(Ship **ship,int n,char plan)
{
    double r;
    switch (plan)
    {
    case 'T':
       for(int i=0;i<n;i++)
       {
          Picewise(0.,0.05,r=random(),ship[i]->loading_time,10)
          Picewise(0.05,0.55,r,ship[i]->loading_time,12)
          Picewise(0.55,0.75,r,ship[i]->loading_time,14)
          Picewise(0.75,0.95,r,ship[i]->loading_time,15)
          Picewise(0.95,1,r,ship[i]->loading_time,17)
       }
        break;
    case 'O':
        for(int i=0;i<n;i++)
        {
          Picewise(0.,0.05,r=random(),ship[i]->loading_time,14)
          Picewise(0.05,0.55,r,ship[i]->loading_time,16)
          Picewise(0.55,0.75,r,ship[i]->loading_time,18)
          Picewise(0.75,0.95,r,ship[i]->loading_time,20)
          Picewise(0.95,1.,r,ship[i]->loading_time,22)
        }
        break;
    default:
        break;
    }        
}
void Random_arrive_time(Ship **ship,int length)
{
    double r;
    ship[0]->arrival_time=0;
    for( int i=1;i<length;i++)
    {
        Picewise(0,0.15,r=random(),ship[i]->arrival_time,ship[i-1]->arrival_time+1)
        Picewise(0.15,0.25,r,ship[i]->arrival_time,ship[i-1]->arrival_time+5)
        Picewise(0.25,0.37,r,ship[i]->arrival_time,ship[i-1]->arrival_time+10)
        Picewise(0.37,0.51,r,ship[i]->arrival_time,ship[i-1]->arrival_time+15)
        Picewise(0.51,0.68,r,ship[i]->arrival_time,ship[i-1]->arrival_time+20)
        Picewise(0.68,0.94,r,ship[i]->arrival_time,ship[i-1]->arrival_time+30)
        Picewise(0.94,1.00,r,ship[i]->arrival_time,ship[i-1]->arrival_time+40)
    }
}
void Solve_Problem(Port *port,Ship **ship,int length)
{
    int delta;
     for(int i=0;i<length;i++)
     {
        delta=port->system_time-ship[i]->arrival_time;
        change(delta,delta+ship[i]->loading_time-30,port->cost,ship[i]->loading_time)
         port->system_time=max(port->system_time,ship[i]->arrival_time)+(ship[i]->loading_time);
     }
}
int main(int argc,char**argv)
{
    if(argc==3)
    {
         if(strcmp(argv[1],"calc")==0)
         {
             int n,m;
             char FileNames[100],str[100];
             srand(time(NULL));
            sscanf(argv[2],"%d-%d-%s",&n,&m,FileNames);
            FILE *file=fopen(FileNames,"w");
            Ship **ship=(Ship**)calloc(n,sizeof(Ship*));
            Malloc(ship,n)
            Port *port=(Port*)calloc(1,sizeof(Port));
            fputs("Transpose@{",file);
            for(int i=0;i<m;i++)
            {
                Select('T')
                port->cost+=(600000+50*port->system_time/6);
                Macro("{{%d,%lld},")
                Select('O')
                port->cost+=(25*port->system_time/6);
                Macro("{%d,%lld}},")
            }
            fputs("Nothing}",file);
            fclose(file);
         }
    }
}