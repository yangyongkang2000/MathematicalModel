/*某公共汽车站每隔30分钟到达一辆汽车，但可能有[0,3] 分钟的误差，此误差大小与前一辆汽车的运行无关。
汽 车最多容纳50名旅客，到达该汽车站时车内旅客人数服 从[20，50]的均匀分布。到站下车的旅客人数服从[3，7] 的均匀分布，每名旅客下车的时间服从[1，7]秒的均匀 分布。
旅客按每30分钟到达12个人的泊松分布到达汽车 站，单列排队等车，先到先上，如果某位旅客未能上车， 他将不再等候。旅客上车时间服从[4，12]秒的均匀分布。 上下车的规则是:先下后上，逐个上车，逐个下车。
 假设每天共发25辆汽车，现在要求模拟一天汽车的运 行情况，了解一天中在站内等候汽车的总人数、能上 车及不能上车的人数、旅客排队时间分布情况、不能 上 车人数的分布情况等。*/
 #include<stdlib.h>
 #include<stdio.h>
 #include<time.h>
 #include<string.h>
 #include<math.h>
 #define random(a,b)  (a+rand()%(b-a+1))
 #define ExponentialDistribution() (int)(-150.0*log((double)rand()/(RAND_MAX+1.0)))
 #define min(a,b) a<b?a:b
 typedef struct 
 {
      int num_shift,people_count,success_people,failed_people,passengers_count,getoff_count,time;
 } Bus;
 void Simlation(Bus *bus,char **filenames,int n)
 {
        srand(time(NULL));
        FILE *file=fopen(filenames[0],"w"),*file1=fopen(filenames[1],"w");
        int *Array=(int*)calloc(12,sizeof(int)),length,bench;
        fputs("{",file);fputs("Transpose@{",file1);
        char str[100];
        for(int i=0;i<n;i++)
        {
              bus->people_count=0; bus->success_people=0;bus->failed_people=0;
        for(bus->num_shift=0;bus->num_shift<25;bus->num_shift++)
        {
               bus->passengers_count=random(20,50)-(bus->getoff_count=random(3,7));
               bus->time=random(27,33)*60+random(bus->getoff_count,7*bus->getoff_count);
               length=1;Array[0]=ExponentialDistribution();
               for(int i=1;i<12;i++)
               {
                      Array[length++]=Array[i-1]+(ExponentialDistribution());
                      if(Array[i]>=bus->time)
                      {
                             length--;
                             break;
                      }
               }
               bus->people_count+=length;
               bench=min(50-bus->passengers_count,length);
               bus->success_people+=bench;bus->failed_people+=(length-bench);
               for(int i=1;i<=bench;i++)
               {
                    bus->time+=random(4,12);
                    sprintf(str,"%d,",bus->time-Array[length-i]);
                    fputs(str,file);
               }
        }
              sprintf(str,"{%d,%d,%d},",bus->people_count,bus->success_people,bus->failed_people);
              fputs(str,file1);
        }
        fputs("Nothing}",file);fputs("Nothing}",file1);
        fclose(file);fclose(file1);
        free(Array);
 }
 int main(int argc,char **argv)
 {
       if(argc==5&&strcmp(argv[1],"calc")==0)
       {
                int n;
                Bus bus;
                sscanf(argv[2],"%d",&n);
                char *filenames[2]={argv[3],argv[4]};
                Simlation(&bus,filenames,n);
       }
 }