#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "mainwindow.h"
using namespace std;

ChunkList::ChunkList()//??????????????????line????????????Chunk?pos.num=0?pos.line=1
{
    int i;
    LineNum=1;
    heads=new CPtr[1];
    heads[0]=new Chunk;
    heads[0]->pre=NULL;
    heads[0]->next=NULL;
    heads[0]->Total=0;
    for(i=0; i<=99; i++)heads[0]->data[i]='\0';
    pos.num=0;
    pos.line=1;
    pos2.num=0;
    pos2.line=0;
}

void ChunkList::Delete()//?????????,???Back,??????Locate
{
    qDebug()<<"dfelete";
    int linet;
    LineTotal(pos.line,linet);
    if(pos.line!=LineNum||pos.num!=linet)
    {
        if(pos.num!=linet)
        {
            pos.num++;
            Locate();
            Back();
        }
        else
        {
            pos.line++;
            pos.num=0;
            Locate();
            Back();
        }
    }
}

void ChunkList::Back()//??????????current????????????Locate
{
    CPtr p1,p2;
    int i,t;
    if(pos.num!=0||pos.line!=1)
    {
        if(pos.num==0)
        {
            p2=heads[pos.line-1];
            p1=heads[pos.line-2];
            while(p1->next!=NULL)p1=p1->next;
            p1->next=p2;
            for(i=pos.line-1; i<=LineNum-2; i++)
            {
                heads[i]=heads[i+1];
            }
            heads[LineNum-1]=NULL;
            LineNum--;
            heads=(CPtr *)realloc(heads,sizeof(CPtr)*LineNum);
            LineTotal(pos.line-1,t);
            pos.num=t;
            pos.line--;
        }
        else
        {
            *current='\0';
            currentchunk->Total--;
            pos.num--;
        }
    }
}

void ChunkList::Insert(char ch)//???ch????????????,????????????????????
{
    qDebug()<<"insert";
    CPtr q,p1,p2;
    int i,j,k,flag;
    flag=0;
    j=(current-currentchunk->data)/sizeof(char);
    j++;
    if(j<=99&&currentchunk->data[j]=='\0')
    {
        currentchunk->data[j]=ch;
        currentchunk->Total++;
        flag=1;
        pos.num++;
    }
    if(flag==0)
    {
        if(j==100)
        {
            if(currentchunk->next==NULL)
            {
                AddChunk(pos.line);
                p1=currentchunk->next;
                p1->data[0]=ch;
                p1->Total++;
                pos.num++;
            }
            else
            {
                p1=currentchunk;
                p2=currentchunk->next;
                q=new chunk();
                for(i=1; i<=99; i++)q->data[i]='\0';
                q->data[0]=ch;
                q->Total=1;
                p1->next=q;
                q->pre=p1;
                q->next=p2;
                p2->pre=q;
                pos.num++;
            }
        }
        else
        {
            if(currentchunk->next==NULL)
            {
                AddChunk(pos.line);
                p1=currentchunk;
                p2=currentchunk->next;
                p2->data[0]=ch;
                p2->Total++;
                pos.num++;
                k=1;
                while(j<=99)
                {
                    if(p1->data[j]!='\0')
                    {
                    p2->data[k]=p1->data[j];
                    p2->Total++;
                    k++;
                    p1->data[j]='\0';
                    p1->Total--;
                    }
                    j++;
                }
            }
            else
            {
                p1=currentchunk;
                p2=currentchunk->next;
                q=new chunk();
                for(i=1; i<=99; i++)q->data[i]='\0';
                q->data[0]=ch;
                q->Total=1;
                p1->next=q;
                q->pre=p1;
                q->next=p2;
                p2->pre=q;
                pos.num++;
                k=1;
                while(j<=99)
                {
                    if(p1->data[j]!='\0')
                    {
                    q->data[k]=p1->data[j];
                    q->Total++;
                    k++;
                    p1->data[j]='\0';
                    p1->Total--;
                    }
                    j++;
                }
            }
        }
    }
}

void ChunkList::InsertLine()//?????Locate
{
    int linet,i,j,k;
    CPtr p,p2,p3;
    LineTotal(pos.line,linet);
    AddLine();
    p=heads[LineNum-1];
    for(i=LineNum; i>=pos.line+2; i--)
    {
        heads[i-1]=heads[i-2];
        heads[i-2]=p;
    }
    if(linet!=pos.num)
    {
        p2=heads[pos.line];
        j=(current-currentchunk->data)/sizeof(char);
        k=0;
        for(i=j+1; i<=99; i++)
        {
            if(currentchunk->data[i]!='\0')
            {
                p2->data[k]=currentchunk->data[i];
                k++;
                p2->Total++;
                currentchunk->data[i]='\0';
                currentchunk->Total--;
            }
        }
        if(currentchunk->next)
        {
            p3=currentchunk->next;
            p2->next=p3;
            p3->pre=p2;
            currentchunk->next=NULL;
        }
    }
    pos.line++;
    pos.num=0;
}

void ChunkList::Merge(CPtr &p,int line)//???p????????????100??????????p??null????????new?????????
{
    int i,k;
    k=0;
    CPtr newptr,p2;
    p2=NULL;
    newptr=NULL;
    if(p->next)
    {
        if(p->Total+p->next->Total<=100)
        {
            newptr=new Chunk;
            for(i=0; i<=99; i++)
            {
                newptr->data[i]='\0';
            }
            for(i=0; i<=99; i++)
            {
                if(p->data[i]!='\0')
                {
                    newptr->data[k]=p->data[i];
                    k++;
                }
            }
            p2=p->next;
            for(i=0; i<=99; i++)
            {
                if(p2->data[i]!='\0')
                {
                    newptr->data[k]=p2->data[i];
                    k++;
                }
            }
            if(p2->next)p2->next->pre=newptr;
            newptr->next=p2->next;
            newptr->Total=p->Total+p2->Total;
            if(p->pre==NULL)
            {
                heads[line-1]=newptr;
                newptr->pre=NULL;
            }
            else
            {
                newptr->pre=p->pre;
                p->pre->next=newptr;
            }
            delete(p2);
            delete(p);
            p=newptr;
        }
        else
        {
            p=p->next;
        }
    }
    else
    {
        p=NULL;
    }
}

void ChunkList::MergeLine(int line)
{
    CPtr p;
    p=heads[line-1];
    while(p)
    {
        Merge(p,line);
    }
}

void ChunkList::Locate()//????????position??????????????
{
    CPtr p;
    int i,j;
    if(pos.num==0)current=NULL;//?????????????????????????NULL
    else
    {
        p=heads[pos.line-1];
        i=pos.num;
        while(i>p->Total)
        {
            i=i-p->Total;
            p=p->next;
        }
        j=-1;
        while(i>0)
        {
            j++;
            if(p->data[j]!='\0')
            {
                i--;
            }
        }
        current=&(p->data[j]);//??current???????????????????????????????
        currentchunk=p;
    }
}





void ChunkList::AddLine()//???????????????????Chunk
{
    int i;
    CPtr p;
    LineNum++;
    heads=(CPtr *)realloc(heads,sizeof(CPtr)*LineNum);
    heads[LineNum-1]=new Chunk;
    p=heads[LineNum-1];
    p->next=NULL;
    p->pre=NULL;
    p->Total=0;
    for(i=0; i<=99; i++)p->data[i]='\0';
}

void ChunkList::AddChunk(int line)//?line???????????Chunk??next=NULL
{
    CPtr t,t2;
    int i;
    t=heads[line-1];
    while(t->next!=NULL)t=t->next;
    t->next=new Chunk;
    t2=t->next;
    t2->next=NULL;
    t2->pre=t;
    for(i=0; i<=99; i++)t2->data[i]='\0';
    t2->Total=0;
}


void ChunkList::LineTotal(int line,int &t)
{
    CPtr p;
    t=0;
    p=heads[line-1];
    while(p!=NULL)
    {
        t=t+p->Total;
        p=p->next;
    }
}

void ChunkList::OutputLine(int line)//???????????
{
    CPtr p;
    int i;
    p=heads[line-1];
    while(p->next!=NULL)
    {
        for(i=0; i<=99; i++)
        {
            if(p->data[i]!='\0') qDebug()<<p->data[i];
        }
        p=p->next;
        qDebug()<<"&&";
    }
    for(i=0; i<=99; i++)
    {
        if(p->data[i]!='\0') qDebug()<<p->data[i];
    }
}

void ChunkList::CopyLine(int line,char *&cpline)//?line?????????char???,???Locate??,??????????
{
    int i,j,k;
    int lsize;
    lsize=0;
    CPtr p,p1;//p1????????
    p=currentchunk;
    j=(current-p->data)/sizeof(char);
    j++;//?????j????
    p1=heads[line-1];
    while(p1!=NULL)
    {
        lsize=lsize+p1->Total;
        p1=p1->next;
    }
    lsize=lsize-pos.num;
    cpline=new char[lsize+1];
    k=0;
    for(i=j;i<=99;i++)
    {
        if(p->data[i]!='\0')
        {
            cpline[k]=p->data[i];
            k++;
        }
    }
    p=p->next;
    while(p!=NULL)
    {
        for(i=0; i<=99; i++)
        {
            if(p->data[i]!='\0')
            {
                cpline[k]=p->data[i];
                k++;
            }
        }
        p=p->next;
    }
    cpline[lsize]='\0';
}
void ChunkList::LineString(int line,char *&cpline)//?line?????????char???
{
    int i,k;
       int lsize;
       lsize=0;
       CPtr p;
       p=heads[line-1];
       LineTotal(line,lsize);
       cpline=new char[lsize+1];
       k=0;
       while(p!=NULL)
       {
           for(i=0; i<=99; i++)
           {
               if(p->data[i]!='\0')

               {
                   cpline[k]=p->data[i];
                   k++;
               }
           }
           p=p->next;
       }
       cpline[lsize]='\0';
}
