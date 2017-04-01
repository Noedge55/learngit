#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define T 1000//最大迭代次数
#define n 1000//蚂蚁数量
#define cities  10//城市数量
#define bugp 0.9//每一次选择操作的出错概率
#define alpha 0.1//每一次信息素的消失速率
#define Q 1
int start;
int biggest[cities],biggestsum;//储存信息素最多时所对应的点（毕竟信息素最大值所对应的边不止一条，biggest记录下那些边的对应的终点，biggestsum为biggest的元素个数）
int distance[cities][cities];//城市的距离矩阵
double phe[cities][cities];//边所对应的信息素浓度（之所以选择边是因为点容易受到周围优秀的点的影响）
int ant;//蚂蚁当前所在点
int bugsum,bugTry[cities];//出错时可供选择的城市数量和城市下标
int visit[cities];//用来标记城市是否已经经过
int path[n][cities+1];//记录每一个蚂蚁所走过的城市
void initdistance()
{
    int i,j;
    memset(distance,0,sizeof(distance));
    srand(time(NULL));
     for (i=0;i<cities;i++)
        for (j=i+1;j<cities;j++)
        {
           distance[i][j]=rand()%100;
           distance[j][i]=distance[i][j];
        }
        printf("城市的距离矩阵如下:\n");
        for (i=0;i<cities;i++)
        {
            for (j=0;j<cities;j++)
                printf("%4d",distance[i][j]);
                printf("\n");
        }
}

int main()
 {
     int i,j,k,p,t,n1,n2,r;
     double d;
     double  max;//记录下最大信息素浓度
     double sumdistance;
     initdistance();//初始化城市矩阵
     t=0;
     for (i=0;i<cities;i++)
      for (j=0;j<cities;j++)
        phe[i][j]=1;//初始化每一条边的信息素浓度
      srand(time(NULL));
      for (i=0;i<n;i++)
        path[i][0]=rand()%cities;//每一个蚂蚁随机在起点
     while(t<T)
     {
         for (i=0;i<cities;i++)
            for (j=0;j<cities;j++)
              phe[i][j]=phe[i][j]*alpha;//每一次信息素逐渐消逝
         for (i=0;i<n;i++)//对于每一只蚂蚁
         {
             start=path[i][0];//记录下起点
             memset(visit,0,sizeof(visit));//清零标记数组
             visit[start]=1;
             ant=start;
             for (j=1;j<cities;j++)//选取剩下的cities-1个城市
             {
                 bugsum=biggestsum=max=0;
                 for (p=0;p<cities;p++)
                  if (!visit[p])
                    max=max>phe[ant][p]?max:phe[ant][p];//寻找周围最大的信息素的那条边（其实是为了找到那个p点）
                 for (p=0;p<cities;p++)
                 {
                     if ((max==phe[ant][p])&&(!visit[p]))
                      biggest[biggestsum++]=p;//记录下信息素浓度最大的点（注意一般不止一个点)
                 }
                 for (p=0;p<cities;p++)
                    if (!visit[p])
                 bugTry[bugsum++]=p;//记录下总共可供选择的点
                 d=rand()%100;
                 d=d/100;
                 if (d<bugp)//如果蚂蚁选择正确
                 ant=biggest[rand()%biggestsum];//选择信息素最大的点
                 else//如果蚂蚁选择错误
                ant=bugTry[rand()%bugsum];//只选择成立的点（未必最优）
                visit[ant]=1;
                path[i][j]=ant;
             }
         }
         //上面是每一只蚂蚁的选择，而一次全部选择后，更新信息素
         for (i=0;i<n;i++)
         {
             sumdistance=0;
             for (j=1;j<cities;j++)
             {
                n1=path[i][j-1];
                n2=path[i][j];
                sumdistance=sumdistance+distance[n1][n2];
             }
             n1=path[i][cities-1];
             n2=path[i][0];
             sumdistance=sumdistance+distance[n1][n2];//注意要回到起点
             for (j=1;j<cities;j++)
             {
                 n1=path[i][j-1];
                 n2=path[i][j];
                 phe[n1][n2]=phe[n1][n2]+Q/sumdistance;//更新信息素，注意因为信息素还要再次递减，所以就好比2进制的权，越靠近话语权越重
             }
             n1=path[i][cities-1];
             n2=path[i][0];
             phe[n1][n2]=phe[n1][n2]+Q/sumdistance;
         }
         t++;//这样迭代次数+1
        }
         max=999999;
       for (i=0;i<n;i++)
       {
           sumdistance=0;
           for (j=1;j<cities;j++)
           {
               n1=path[i][j-1];
               n2=path[i][j];
               sumdistance=sumdistance+distance[n1][n2];
           }
           n1=path[i][cities-1];
           n2=path[i][0];
           sumdistance=sumdistance+distance[n1][n2];
           if (sumdistance<max)
           {
               max=sumdistance;
               r=i;
           }
       }
       printf("最短路径为:%.4f\n",max);
       printf("路径为:\n");
       for (i=0;i<cities;i++)
       printf("%d ",path[r][i]);//第r个蚂蚁是最优的
       printf("%d\n",path[r][0]);
        return 0;
 }
