/*
某自行车商店的仓库管理人员采取一种简 单的订货策略, 当库存降低到P辆自行车时就向 厂家订货Q辆, 如果某一天的需求量超过了库存 量, 商店就有销售损失和信誉损失, 但如果库存 量过多, 将会导致资金积压和保管费增加. 
若现 在已有如表8.2中的五种库存策略。试比较选择 一种策略以使花费最少. 已知该问题的条件
125
125
150
175
150
250
250
250
方案编号 重新订货量P 辆 重新订货量Q 辆
5 175 300
已知该问题的条件:
1) 从发出订货到收到货物需隔3天;
2) 每辆自行车保管费为0.75元/天,每辆自行车的缺
货损失为1.80元/天,每次的订货费为75元; 3)每天自行车的需求量服从0到99之间的均匀分布; 4)原始库存为115辆,并假设第一天没有发出订货.
 试比较选择一种策略以使得花费最少.
*/
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#define random() rand()%100
typedef struct 
{
   int stock;
   double cost;
   int day;
} Shop;
typedef struct 
{
    int day,Q,P;
} Producer;

void Simulation(Shop *shop,Producer *producer,int d)
{
       int need;
         for(int i=0;i<d;i++)
         {
                if(shop->day==producer->day)
                {
                    shop->stock+=producer->Q;
                }
        if(shop->stock>(need=random()))
        {
            shop->cost+=0.75*(shop->stock-=need);
            if(shop->stock<producer->P)
            {
                producer->day=shop->day>=producer->day?shop->day+3:producer->day;
                shop->cost+=75;
            }
        }else{
             shop->cost+=75+(need-shop->stock)*1.8;
            shop->stock=0;
        }
        shop->day++;
        }
}
int main(int argc,char **argv)
{
    if(argc==3)
    {
         if(strcmp(argv[1],"calc")==0)
         {
             int n,m,P,Q;
             char FileNames[100],str[100];
             sscanf(argv[2],"%d-%d-%d-%d-%s",&P,&Q,&n,&m,FileNames);
             srand(time(NULL));
             Shop shop={115,0.,1};
             Producer producer={2,Q,P};
             FILE *file=fopen(FileNames,"w");
             fputs("{",file);
             for(int i=0;i<m;i++)
             {
                 Simulation(&shop,&producer,n);
                 sprintf(str,"%f,",shop.cost);
                 fputs(str,file);
                 shop.cost=0;shop.day=1;shop.stock=115;
                 producer.day=2;producer.P=P;producer.Q=Q;
             }
             fputs("Nothing}",file);
             fclose(file);
         }
    }
}
