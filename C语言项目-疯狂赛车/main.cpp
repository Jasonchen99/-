/****
项目名称：疯狂赛车
作    者：17级2班张思谨
创建时间：2018.6.20
项目说明：完整游戏建构
****/

#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

int carcolor=1;//设置车辆颜色初始值
typedef struct postion
{
    int x;
    int y;
} POSITION;
POSITION s[5];
int y_1=0;
int y_2=-500;

PIMAGE bk;
PIMAGE r;
PIMAGE start;
PIMAGE soundon;
PIMAGE soundoff;
PIMAGE menu;
PIMAGE choosebk;
PIMAGE quit;
PIMAGE map1;
PIMAGE map2;
PIMAGE car;
PIMAGE car4;
PIMAGE car5;
PIMAGE car1;
PIMAGE car2;
PIMAGE car3;
PIMAGE coin;
PIMAGE coin1;
PIMAGE go;
PIMAGE score;
PIMAGE Rank;
PIMAGE buy;
PIMAGE buy1;

char tx[20];
int a=192;
int b=300;
int c=5;
int y1=0;
int y2=-500;
int speed=5;
int speed1=2;
int speed2=4;
int speed3=6;
int speed4=5;
int speed5=6;
int sound=1;
int coins=0;
float miles=0;
int scores=0;
int length=0;
int data[10];

int readGameFile()
{
    FILE *fp;
    char s[20];
    char t[50];
    setcolor(BLACK);
    setfont(25,0,"微软雅黑");
    fp=fopen("gamefile.txt","r+");
    if(fp==NULL)
    {
        ege::outtextxy(120,200,"Open file error !");
        exit(0);
    }
    int i=0;
    while(!feof(fp))
    {
        fread(&data[i],sizeof(data),1,fp);
        i++;
    }
    length=--i;
    for(int i=0; i<length; i++)
    {
        sprintf(s,"Score %d:%3d",i+1,data[i]);
        ege::outtextxy(147,i*26+113,s);
    }
    fclose(fp);
}

int saveGame(int Tscore)
{
    FILE *fp;
    length=0;
    fp=fopen("gamefile.txt","r");
    if(fp==NULL)
    {
        ege::outtextxy(120,200,"Open file error !");
        exit(0);
    }
    int i=0;
    while(!feof(fp) && i<10)
    {
        fread(&data[i],sizeof(data),1,fp);
        i++;
    }
    length=--i;
    fclose(fp);

    int ex;
    ex=Tscore;
    for(i=length; i>=0; i--)
    {
        if(ex>data[i])
        {
            data[i+1]=data[i];
        }
        else
            break;
        data[i]=ex;
    }

    fp=fopen("gamefile.txt","w");
    if(fp==NULL)
    {
        ege::outtextxy(120,200,"Open file error !");
        exit(0);
    }
    for(int i=0; i<length+1; i++)
        fwrite(&data[i],sizeof(data),1,fp);
    fclose(fp);
}

mouse_msg msg;
int Mouse_X, Mouse_Y;   //鼠标位置
bool Mouse_Up;
bool Mouse_Down;
bool Mouse_Left;
bool Mouse_Right;
//鼠标左键和右键信息
int initmouse()//鼠标数据初始化
{
    Mouse_X = 0;
    Mouse_Y = 0;
    Mouse_Down = false;
    Mouse_Left = false;
    Mouse_Right = false;
    Mouse_Up = false;
    return 0;
}

int updatemouse()//鼠标数据刷新
{
    mouse_msg msg = { 0 };
    while (mousemsg())//检测当前是否有鼠标消息
    {
        msg = getmouse();//获取一个鼠标消息。如果当前鼠标消息队列中没有，就一直等待
        Mouse_X = msg.x;
        Mouse_Y = msg.y;
        Mouse_Down = msg.is_down();
        Mouse_Left = msg.is_left();
        Mouse_Right = msg.is_right();
        Mouse_Up = msg.is_up();
    }
    return 0;
}

void getSound()
{
    //获取声音
    mciSendString("open pic\\welcome.mp3",NULL,0,NULL);
    mciSendString("open pic\\run.mp3",NULL,0,NULL);
}

void getImg()
//获取图片函数
{
    bk=ege::newimage();
    start=ege::newimage();
    r=ege::newimage();
    soundon=ege::newimage();
    soundoff=ege::newimage();
    menu=ege::newimage();
    choosebk=ege::newimage();
    quit=ege::newimage();
    map1=ege::newimage();
    map2=ege::newimage();
    car=ege::newimage();
    car4=ege::newimage();
    car5=ege::newimage();
    car1=ege::newimage();
    car2=ege::newimage();
    car3=ege::newimage();
    coin=ege::newimage();
    coin1=ege::newimage();
    go=ege::newimage();
    score=ege::newimage();
    Rank=ege::newimage();
    buy=ege::newimage();
    buy1=ege::newimage();
    ege::getimage(bk,"pic\\bg.png");
    ege::getimage(start,"pic\\play.png");
    ege::getimage(r,"pic\\rank.png");
    ege::getimage(soundon,"pic\\sound.png");
    ege::getimage(soundoff,"pic\\soundoff.png");
    ege::getimage(menu,"pic\\menu.png");
    ege::getimage(choosebk,"pic\\choose.png");
    ege::getimage(quit,"pic\\exit.png");
    ege::getimage(map1,"pic\\road1.jpg");
    ege::getimage(map2,"pic\\road2.jpg");
    ege::getimage(car,"pic\\mycar.png");
    ege::getimage(car4,"pic\\mycar1.png");
    ege::getimage(car5,"pic\\mycar2.png");
    ege::getimage(car1,"pic\\car1.png");
    ege::getimage(car2,"pic\\car2.png");
    ege::getimage(car3,"pic\\car3.png");
    ege::getimage(coin,"pic\\coin.png");
    ege::getimage(coin1,"pic\\coin.png");
    ege::getimage(go,"pic\\go.png");
    ege::getimage(score,"pic\\score.png");
    ege::getimage(Rank,"pic\\rank1.png");
    ege::getimage(buy,"pic\\buyno.png");
    ege::getimage(buy1,"pic\\buyyes.png");
}

void delImg()
{
    //取消图片函数
    ege::delimage(bk);
    ege::delimage(start);
    ege::delimage(r);
    ege::delimage(soundon);
    ege::delimage(soundoff);
    ege::delimage(menu);
    ege::delimage(quit);
    ege::delimage(map1);
    ege::delimage(map2);
    ege::delimage(car);
    ege::delimage(car1);
    ege::delimage(car2);
    ege::delimage(car3);
    ege::delimage(coin);
    ege::delimage(choosebk);
    ege::delimage(car4);
    ege::delimage(car5);
    ege::delimage(go);
    ege::delimage(score);
    ege::delimage(Rank);
    ege::delimage(buy);
    ege::delimage(buy1);
}

DWORD WINAPI FireMusic(LPVOID lpParameter)//多线程
{
    //鼠标滴答声
    mciSendString("open pic\\click.mp3",NULL,0,NULL);
    mciSendString("play pic\\click.mp3",NULL,0,NULL);
    return 0;
}

void PlayMusic()
{
    HANDLE threadtoplay;
    threadtoplay=CreateThread(NULL,0,FireMusic,NULL,0,NULL);
    CloseHandle(threadtoplay);
}

DWORD WINAPI hurtMusic(LPVOID lpParameter)
{
    //鼠标滴答声
    mciSendString("open pic\\hurt.mp3",NULL,0,NULL);
    mciSendString("play pic\\hurt.mp3",NULL,0,NULL);
    return 0;
}

void hurtMusic()
{
    HANDLE threadtoplay;
    threadtoplay=CreateThread(NULL,0,hurtMusic,NULL,0,NULL);
    CloseHandle(threadtoplay);
}

DWORD WINAPI coinMusic(LPVOID lpParameter)
{
    //鼠标滴答声
    mciSendString("open pic\\coin.mp3",NULL,0,NULL);
    mciSendString("play pic\\coin.mp3",NULL,0,NULL);
    return 0;
}

void coinMusic()
{
    HANDLE threadtoplay;
    threadtoplay=CreateThread(NULL,0,coinMusic,NULL,0,NULL);
    CloseHandle(threadtoplay);
}

void playGame();
void interFace();

void disPlayMap()
{
    //展示地图
    putimage_transparent(NULL,map1,0,y1,0);
    putimage_transparent(NULL,map2,0,y2,0);
    y1=y1+speed;
    y2=y2+speed;
    if(y1>500)
        y1=0;
    if(y2>0)
        y2=-500;
}


void enemy_move( )
{
    //敌车移动
    for(int i=0; i<5; i++)
    {
        if(i==0)
        {
            s[i].y=s[i].y+speed1;
            if(s[i].x>=127&&s[i].x<=295)
                ege::putimage_withalpha(NULL,car1,s[i].x,s[i].y);
        }
        if(i==1)
        {
            s[i].y=s[i].y+speed2;
            if(s[i].x>=127&&s[i].x<=295)
                ege::putimage_withalpha(NULL,car2,s[i].x,s[i].y);
        }
        if(i==2)
        {
            s[i].y=s[i].y+speed3;
            if(s[i].x>=127&&s[i].x<=295)
                ege::putimage_withalpha(NULL,car3,s[i].x,s[i].y);
        }
        if(i==3)
        {
            s[i].y=s[i].y+speed4;
            if(s[i].x>=127&&s[i].x<=295)
                ege::putimage_withalpha(NULL,coin,s[i].x,s[i].y);
        }
        if(i==4)
        {
            s[i].y=s[i].y+speed5;
            if(s[i].x>=127&&s[i].x<=295)
                ege::putimage_withalpha(NULL,coin1,s[i].x,s[i].y);
        }
    }
    srand(time(0));
    for(int j=0; j<5; ++j)
    {
        if(j==0&&s[j].y>=500)
        {
            s[j].y=-150;
            s[j].x = rand()%300;
            while(s[j].x<=127||s[j].x>=295)
                s[j].x = rand()%300;

        }
        if(j==1&&s[j].y>=500)
        {
            s[j].y=-300;
            s[j].x = rand()%300;
            while(s[j].x<=127||s[j].x>=295)
                s[j].x = rand()%300;

        }
        if(j==2&&s[j].y>=500)
        {
            s[j].y=-500;
            s[j].x = rand()%300;
            while(s[j].x<=127||s[j].x>=295)
                s[j].x = rand()%300;
        }
        if(j==3&&s[j].y>=500)
        {
            s[j].y=-700;
            s[j].x = rand()%300;
            while(s[j].x<=127||s[j].x>=295)
                s[j].x = rand()%300;
        }
        if(j==4&&s[j].y>=500)
        {
            s[j].y=-900;
            s[j].x = rand()%300;
            while(s[j].x<=127||s[j].x>=295)
                s[j].x = rand()%300;
        }
    }
}

void disPlayCar()
{
    //在地图上显示车辆
    if(carcolor==1)//显示红蜘蛛
    {
        putimage_transparent(NULL,car,a,b,0);
    }
    else if(carcolor==2)//显示大黄蜂
    {
        putimage_transparent(NULL,car4,a,b,0);
    }
    else//显示绿巨人
    {
        putimage_transparent(NULL,car5,a,b,0);
    }
    if (keystate(VK_UP))//控制车辆移动
    {
        b=b-c;
    }
    if (keystate(VK_LEFT)&&a>92)
    {
        a=a-c;
    }
    if (keystate(VK_DOWN))
    {
        b=b+c;
    }
    if (keystate(VK_RIGHT)&&a<293)
    {
        a=a+c;
    }
    enemy_move();
}
void chooseCar();

void Buy()
{
    initmouse();
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        ege::putimage(0,0,buy);
        ege::setbkmode(TRANSPARENT);
        updatemouse();
        if(Mouse_X>=340&&Mouse_Y>=305&&Mouse_X<=380&&Mouse_Y<=340&&Mouse_Left&&Mouse_Down)
        {
            chooseCar();
        }
    }
}

void Buy1()
{
    initmouse();
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        ege::putimage(0,0,buy1);
        ege::setbkmode(TRANSPARENT);
        updatemouse();
        if(Mouse_X>=340&&Mouse_Y>=305&&Mouse_X<=380&&Mouse_Y<=340&&Mouse_Left&&Mouse_Down)
        {
            chooseCar();
        }
    }
}
void chooseCar()
{
    char tx4[20];//menu进入选车界面
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        initmouse();
        ege::putimage(0,0,choosebk);
        ege::setbkmode(TRANSPARENT);
        updatemouse();
        setcolor(BLACK);
        setfont(25,0,"微软雅黑");
        sprintf(tx4,"您的资产:%d 枚",coins);
        ege::outtextxy(147,340,tx4);
        if(coins<20&&Mouse_X>=20&&Mouse_Y>=280&&Mouse_X<=380&&Mouse_Y<=320&&Mouse_Left&&Mouse_Down)
        {
            Buy();
        }
        else
        {
            if(Mouse_X>=160&&Mouse_Y>=280&&Mouse_X<=240&&Mouse_Y<=320&&Mouse_Left&&Mouse_Down)
            {
                //选择红蜘蛛
                PlayMusic();
                carcolor=1;
                coins-=20;
                Buy1();
            }
            else if(Mouse_X>=20&&Mouse_Y>=280&&Mouse_X<=100&&Mouse_Y<=320&&Mouse_Left&&Mouse_Down)
            {
                //选择大黄蜂
                PlayMusic();
                carcolor=2;
                coins-=20;
                Buy1();
            }
            else if(Mouse_X>=300&&Mouse_Y>=280&&Mouse_X<=380&&Mouse_Y<=320&&Mouse_Left&&Mouse_Down)
            {
                //选择绿巨人
                PlayMusic();
                carcolor=3;
                coins-=20;
                Buy1();
            }
        }
        if(Mouse_X>=135&&Mouse_Y>=380&&Mouse_X<=275&&Mouse_Y<=430&&Mouse_Left&&Mouse_Down)
        {
            //选择后进入游戏
            PlayMusic();
            playGame();
        }
    }
}

void scoreRank()
{
    initmouse();
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        ege::putimage(0,0,Rank);
        ege::setbkmode(TRANSPARENT);
        readGameFile();
        updatemouse();
        putimage_transparent(NULL,quit,350,390,0);
        if(Mouse_X>=350&&Mouse_Y>=390&&Mouse_X<=390&&Mouse_Y<=425&&Mouse_Left&&Mouse_Down)//退出按钮
        {
            interFace();
        }
    }
}

int gameOver()
{
    //撞车后游戏结束
    int playGame();
    void interFace();
    mciSendString("stop pic\\run.mp3",NULL,0,NULL);
    char tx2[20];
    char tx3[20];
    initmouse();
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        putimage(0,0,go);
        ege::setbkmode(TRANSPARENT);
        updatemouse();
        setcolor(BLACK);
        setfont(25,0,"微软雅黑");
        sprintf(tx2,"金币:%d个;路程:%.0f米",coins,miles);
        ege::outtextxy(135,40,tx2);
        setcolor(BLACK);
        setfont(25,0,"微软雅黑");
        sprintf(tx3,"您的成绩为:%d分",scores);
        ege::outtextxy(135,200,tx3);
        if(Mouse_X>=135&&Mouse_Y>=250&&Mouse_X<=290&&Mouse_Y<=305&&Mouse_Left&&Mouse_Down)
        {
            //点击retry，再次开启游戏
            playGame();
        }
        if(Mouse_X>=360&&Mouse_Y>=375&&Mouse_X<=400&&Mouse_Y<=410&&Mouse_Left&&Mouse_Down)
        {
            interFace();
        }
    }
}

void playGame()
{
    char tx1[20];
    mciSendString("stop pic\\welcome.mp3",NULL,0,NULL);
    s[0].y=-150;
    s[1].y=-300;
    s[2].y=-500;
    a=192;
    b=300;
    int flag1=1;
    int flag2=1;
    int flag3=1;
    speed1=2;
    speed2=4;
    speed3=6;
    //金币计数器
    miles=0;//里程计数器
    if(sound==1)
    {
        mciSendString("play pic\\run.mp3 repeat",NULL,0,NULL);
    }
    for(; is_run(); delay_fps(60))
    {
        cleardevice();
        disPlayMap();
        disPlayCar();
        updatemouse();
        putimage_transparent(NULL,score,0,30,0);
        miles=miles+0.05;//里程增加
        setcolor(WHITE);
        setfont(20,0,"微软雅黑");
        sprintf(tx1,"金币:%d,路程:%.0f",coins,miles);
        ege::outtextxy(1,32,tx1);
        scores=(int)(miles*2);
        if(miles>=100&&miles<=200&&flag1==1)
        {
            speed1+=2;
            speed2+=2;
            speed3+=2;
            flag1=0;
        }
        if(miles>=200&&miles<=300&&flag2==1)
        {
            speed1=speed1+2;
            speed2=speed2+2;
            speed3=speed3+2;
            flag2=0;
        }
        if(miles>=300&&flag3==1)
        {
            speed1=speed1+2;
            speed2=speed2+2;
            speed3=speed3+2;
            flag3=0;
        }
        for(int i=0; i<3; i++)
        {
            if(abs(a-s[i].x)<=20&&abs(b-s[i].y)<=20)//撞到敌车
            {
                hurtMusic();
                saveGame(scores);
                gameOver();
            }
        }
        for(int i=3; i<5; i++)
        {
            if(abs(a-s[i].x)<=20&&abs(b-s[i].y)<=20)//得到金币
            {
                s[i].y=-700;
                coinMusic();
                coins++;
            }
        }
    }
}

void interFace()
{
    //进入主界面
    initmouse();
    mciSendString("stop pic\\run.mp3",NULL,0,NULL);
    if(sound==1)
    {
        mciSendString("play pic\\welcome.mp3 repeat",NULL,0,NULL);
    }
    else
    {
        mciSendString("stop pic\\welcome.mp3",NULL,0,NULL);
    }
    for(; is_run(); delay_fps(60))
    {
        ege::cleardevice();
        ege::putimage(0,0,bk);
        ege::putimage(152,210,start);//开始游戏
        ege::putimage(152,290,menu);//选择界面
        ege::putimage(350,390,r);//排行榜
        putimage_transparent(NULL,quit,350,40,0);//退出按钮
        ege::setbkmode(TRANSPARENT);
        ege::setcolor(BLUE);
        updatemouse();
        if(Mouse_X>=350&&Mouse_Y>=450&&Mouse_X<=390&&Mouse_Y<=485&&Mouse_Left&&Mouse_Down)
        {
            //判断声音按钮
            if(sound==1)
                sound=0;
            else
                sound=1;
            interFace();
        }
        if(sound==1)
        {
            //声音打开
            putimage_transparent(NULL,soundon,350,450,0);
        }
        else
        {
            //声音关闭
            putimage_transparent(NULL,soundoff,350,450,0);
        }
        if(Mouse_X>=152&&Mouse_Y>=290&&Mouse_X<=270&&Mouse_Y<=340&&Mouse_Left&&Mouse_Down)
        {
            //选择车辆
            PlayMusic();
            chooseCar();
        }
        if(Mouse_X>=152&&Mouse_Y>=210&&Mouse_X<=270&&Mouse_Y<=250&&Mouse_Left&&Mouse_Down)
        {
            //开始游戏
            PlayMusic();
            playGame();
        }
        if(Mouse_X>=350&&Mouse_Y>=40&&Mouse_X<=390&&Mouse_Y<=70&&Mouse_Left&&Mouse_Down)
        {
            //退出游戏
            exit(0);
        }
        if(Mouse_X>=350&&Mouse_Y>=390&&Mouse_X<=390&&Mouse_Y<=425&&Mouse_Left&&Mouse_Down)
        {
            //查看游戏排行
            scoreRank();
        }
    }
}

int main()
{
    setinitmode(0);
    initgraph(425,500);
    getImg();
    getSound();
    interFace();
    delImg();
    getch();
    closegraph();
    return 0;
}
