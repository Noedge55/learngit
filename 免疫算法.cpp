#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define T 1000//����������
#define n 1000//��������
#define cities  10//��������
#define bugp 0.9//ÿһ��ѡ������ĳ������
#define alpha 0.1//ÿһ����Ϣ�ص���ʧ����
#define Q 1
int start;
int biggest[cities],biggestsum;//������Ϣ�����ʱ����Ӧ�ĵ㣨�Ͼ���Ϣ�����ֵ����Ӧ�ı߲�ֹһ����biggest��¼����Щ�ߵĶ�Ӧ���յ㣬biggestsumΪbiggest��Ԫ�ظ�����
int distance[cities][cities];//���еľ������
double phe[cities][cities];//������Ӧ����Ϣ��Ũ�ȣ�֮����ѡ�������Ϊ�������ܵ���Χ����ĵ��Ӱ�죩
int ant;//���ϵ�ǰ���ڵ�
int bugsum,bugTry[cities];//����ʱ�ɹ�ѡ��ĳ��������ͳ����±�
int visit[cities];//������ǳ����Ƿ��Ѿ�����
int path[n][cities+1];//��¼ÿһ���������߹��ĳ���
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
        printf("���еľ����������:\n");
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
     double  max;//��¼�������Ϣ��Ũ��
     double sumdistance;
     initdistance();//��ʼ�����о���
     t=0;
     for (i=0;i<cities;i++)
      for (j=0;j<cities;j++)
        phe[i][j]=1;//��ʼ��ÿһ���ߵ���Ϣ��Ũ��
      srand(time(NULL));
      for (i=0;i<n;i++)
        path[i][0]=rand()%cities;//ÿһ��������������
     while(t<T)
     {
         for (i=0;i<cities;i++)
            for (j=0;j<cities;j++)
              phe[i][j]=phe[i][j]*alpha;//ÿһ����Ϣ��������
         for (i=0;i<n;i++)//����ÿһֻ����
         {
             start=path[i][0];//��¼�����
             memset(visit,0,sizeof(visit));//����������
             visit[start]=1;
             ant=start;
             for (j=1;j<cities;j++)//ѡȡʣ�µ�cities-1������
             {
                 bugsum=biggestsum=max=0;
                 for (p=0;p<cities;p++)
                  if (!visit[p])
                    max=max>phe[ant][p]?max:phe[ant][p];//Ѱ����Χ������Ϣ�ص������ߣ���ʵ��Ϊ���ҵ��Ǹ�p�㣩
                 for (p=0;p<cities;p++)
                 {
                     if ((max==phe[ant][p])&&(!visit[p]))
                      biggest[biggestsum++]=p;//��¼����Ϣ��Ũ�����ĵ㣨ע��һ�㲻ֹһ����)
                 }
                 for (p=0;p<cities;p++)
                    if (!visit[p])
                 bugTry[bugsum++]=p;//��¼���ܹ��ɹ�ѡ��ĵ�
                 d=rand()%100;
                 d=d/100;
                 if (d<bugp)//�������ѡ����ȷ
                 ant=biggest[rand()%biggestsum];//ѡ����Ϣ�����ĵ�
                 else//�������ѡ�����
                ant=bugTry[rand()%bugsum];//ֻѡ������ĵ㣨δ�����ţ�
                visit[ant]=1;
                path[i][j]=ant;
             }
         }
         //������ÿһֻ���ϵ�ѡ�񣬶�һ��ȫ��ѡ��󣬸�����Ϣ��
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
             sumdistance=sumdistance+distance[n1][n2];//ע��Ҫ�ص����
             for (j=1;j<cities;j++)
             {
                 n1=path[i][j-1];
                 n2=path[i][j];
                 phe[n1][n2]=phe[n1][n2]+Q/sumdistance;//������Ϣ�أ�ע����Ϊ��Ϣ�ػ�Ҫ�ٴεݼ������Ծͺñ�2���Ƶ�Ȩ��Խ��������ȨԽ��
             }
             n1=path[i][cities-1];
             n2=path[i][0];
             phe[n1][n2]=phe[n1][n2]+Q/sumdistance;
         }
         t++;//������������+1
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
       printf("���·��Ϊ:%.4f\n",max);
       printf("·��Ϊ:\n");
       for (i=0;i<cities;i++)
       printf("%d ",path[r][i]);//��r�����������ŵ�
       printf("%d\n",path[r][0]);
        return 0;
 }
