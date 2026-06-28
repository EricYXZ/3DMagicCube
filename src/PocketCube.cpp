#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include<GL/glut.h>      
#include<GL/freeglut.h>
#include<GL/gl.h>
#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/gl.h>
#include<iostream>
#include<cstring>
#include<queue>
#include<easyx.h>
#include<cstdio>
#include<string>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
char  Version_Information[] = "1.0.0";//程序版本号
int f1, f2, f3, f4, f5, f6, f_allX, f_allx, f_allY, f_ally, f_allZ, f_allz, f_left, f_right, f_up, f_down, f_front, f_behind;//控制动画效果
const float PI = 3.141592653589793f;
const float ag = (PI / 18);//一个面每帧转角度
const float l = 1.0;//每帧移动距离
const float clr = 0;//魔方底板色调灰度，0-1为黑-白
float R = 0.496f, G = 0.769f, B = 1.0f;//视图背景色
int CHANGE = 1, idx, stop, Flag, OK, Angle;//改变方向
char Path_Record[100000];//路径记录数组
float Ox = 0, Oy = 0, Oz = 0;//初始化魔方中心点坐标
float lookx = 85, lookz = -85, looky = 85;//初始相机位置
bool LEFT_isDragging = 0;//检测是否左键拖动
bool RIGHT_isDragging = 0;//检测是否右键拖动
bool MIDDLE_isDragging = 0;//检测是否中键拖动
float rot = 0.05f;//相机每次旋转的角度
int speed = 1;//魔方复原时的速度
IMAGE Show_How_Use;//展示如何使用的图片的定义
GLuint textureID;
struct Cube
{
    int a[55] = { 0 };
    queue <char> step;//定义一个存储类型为char的队列step记录当前状态的魔方的来源
}cube, Aim_Cube;//定义“魔方”结构体

/******************************函数声明******************************/
void init();//初始化
void inite_cube_color();//初始化颜色
void Inite_EasyX();//初始化easyx
void Draw_TEXT(int x, int y, int w, int h, const char* text);//文本框绘制函数
bool CHECK_F(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_R(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_U(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_D(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_L(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_B(GLfloat a[][4][3], int i);//检查元素是否在此面
bool CHECK_ALL(Cube t);//检查魔方是否全部复原
void turn_fF(int USELESS);//魔方F旋转函数
void turn_fR(int USELESS);//魔方R旋转函数
void turn_fU(int USELESS);//魔方U旋转函数
void turn_fD(int USELESS);//魔方D旋转函数
void turn_fL(int USELESS);//魔方L旋转函数
void turn_fB(int USELESS);//魔方B旋转函数
void turn_ff(int USELESS);//魔方f旋转函数
void turn_fr(int USELESS);//魔方r旋转函数
void turn_fu(int USELESS);//魔方u旋转函数
void turn_fd(int USELESS);//魔方d旋转函数
void turn_fl(int USELESS);//魔方l旋转函数
void turn_fb(int USELESS);//魔方b旋转函数
void turn_allX(int USELESS);//魔方X轴正向旋转函数
void turn_allx(int USELESS);//魔方X轴反向旋转函数
void turn_allY(int USELESS);//魔方Y轴正向旋转函数
void turn_ally(int USELESS);//魔方Y轴反向旋转函数
void turn_allZ(int USELESS);//魔方Z轴正向旋转函数
void turn_allz(int USELESS);//魔方Z轴反向旋转函数
void move_left(int USELESS);//魔方左平移函数
void move_right(int USELESS);//魔方右平移函数
void move_up(int USELESS);//魔方上平移函数
void move_down(int USELESS);//魔方下平移函数
void move_front(int USELESS);//魔方前平移函数
void move_behind(int USELESS);//魔方后平移函数
void move_F();//魔方F颜色变换函数
void move_R();//魔方R颜色变换函数
void move_U();//魔方U颜色变换函数
void move_D();//魔方D颜色变换函数
void move_L();//魔方L颜色变换函数
void move_B();//魔方B颜色变换函数
void move_f();//魔方f颜色变换函数
void move_r();//魔方r颜色变换函数
void move_u();//魔方u颜色变换函数
void move_d();//魔方d颜色变换函数
void move_l();//魔方l颜色变换函数
void move_b();//魔方b颜色变换函数
void move_X();//魔方X颜色变换函数
void move_x();//魔方x颜色变换函数
void move_Y();//魔方Y颜色变换函数
void move_y();//魔方y颜色变换函数
void move_Z();//魔方Z颜色变换函数
void move_z();//魔方z颜色变换函数
void CORRECT_Y(int a[]);//Y轴校正方向函数
void CORRECT_XZ(int a[]);//XZ轴校正方向函数
void SOLVE_WHITE_ORANGE_RIDGE(int a[]);//复原白橙棱块
void SOLVE_WHITE_GREEN_RIDGE(int a[]);//复原白绿棱块
void SOLVE_WHITE_RED_RIDGE(int a[]);//复原白红棱块
void SOLVE_WHITE_BLUE_RIDGE(int a[]);//复原白蓝棱块
void SOLVE_ORANGE_GREEN_CORNOR(int a[]);//复原橙绿角块
void SOLVE_GREEN_RED_CORNOR(int a[]);//复原绿红角块
void SOLVE_RED_BLUE_CORNOR(int a[]);//复原红蓝角块
void SOLVE_BLUE_ORANDE_CORNOR(int a[]);//复原蓝橙角块
void SOLVE_ORANGE_GREEN_RIDGE(int a[]);//复原橙绿棱块
void SOLVE_GREEN_RED_RIDGE(int a[]);//复原绿红棱块
void SOLVE_RED_BLUE_RIDGE(int a[]);//复原红蓝棱块
void SOLVE_BLUE_ORANGE_RIDGE(int a[]);//复原蓝橙棱块
void SOLVE_ORIENT(int a[]);//复原顶面
void SOLVE_PERMUT(int a[]);//复原顶层
void TRANS_COLOR(int a[]);//调整最后一层朝向
void FIND_RECOVER_PATH();//寻找求解路径
void AUTOMATIC_RECOVERY(int idx);//自动复原
void performNextScrambleMove(int idx);//执行下一次打乱
void Scramblecube();//打乱魔方回调
void Mos_Left_turn_look(int USELESS);//鼠标左键回调控制
void Mos_Right_turn_look(int USELESS);//鼠标右键回调控制
void Mos_Middle_turn_look(int USELESS);//鼠标中键回调控制
void GL_mouseCallback(int button, int state, int x, int y);//鼠标回调
void onKeyboard(unsigned char key, int x, int y);//键盘控制
void loadTexture(const char* filename);//加载纹理贴图
void myDisplay();//绘制整个魔方
/******************************初始化模块******************************/
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 30000);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(lookx, looky, lookz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

}
//初始魔方各个方块的颜色
//6黄色  1绿色  2红色  3蓝色    4橙色   5白色
void inite_cube_color()
{
    for (int i = 1; i <= 9; i++)  cube.a[i] = 5;
    for (int i = 10; i <= 18; i++)  cube.a[i] = 1;
    for (int i = 19; i <= 27; i++)  cube.a[i] = 6;
    for (int i = 28; i <= 36; i++)  cube.a[i] = 3;
    for (int i = 37; i <= 45; i++)  cube.a[i] = 4;
    for (int i = 46; i <= 54; i++)  cube.a[i] = 2;
}
void Inite_EasyX()
{
    initgraph(1000, 600);
    setbkcolor(RGB(245, 247, 250));
    cleardevice();

    setfillcolor(RGB(235, 239, 246));
    solidrectangle(0, 0, 470, 600);
    loadimage(&Show_How_Use, "assets/Show_How_Use.jpg", 420, 520);
    putimage(25, 40, &Show_How_Use);

    setlinecolor(RGB(207, 214, 226));
    rectangle(24, 39, 445, 560);

    setfillcolor(RGB(255, 255, 255));
    solidrectangle(470, 0, 1000, 600);

    setbkmode(TRANSPARENT);

    settextstyle(34, 0, "Consolas");
    settextcolor(RGB(26, 32, 44));
    outtextxy(525, 48, "Pocket Cube");

    settextstyle(18, 0, "Consolas");
    settextcolor(RGB(95, 107, 130));
    outtextxy(528, 92, "OpenGL cube trainer and solver");

    setlinecolor(RGB(226, 232, 240));
    line(525, 126, 930, 126);

    settextstyle(20, 0, "Consolas");
    settextcolor(RGB(51, 65, 85));
    outtextxy(528, 152, "Controls");

    Draw_TEXT(525, 190, 405, 42, "U D F B R L / lower-case: rotate faces");
    Draw_TEXT(525, 242, 405, 42, "X Y Z / lower-case: rotate the whole cube");
    Draw_TEXT(525, 294, 405, 42, "Mouse left / middle / right: adjust camera");
    Draw_TEXT(525, 346, 405, 42, "S: scramble cube");
    Draw_TEXT(525, 398, 405, 42, "Enter: auto solve");

    settextstyle(16, 0, "Consolas");
    settextcolor(RGB(100, 116, 139));
    outtextxy(528, 548, "Version ");
    outtextxy(600, 548, Version_Information);
}

void Draw_TEXT(int x, int y, int w, int h, const char* text)
{
    setfillcolor(RGB(248, 250, 252));
    solidrectangle(x, y, x + w, y + h);
    setlinecolor(RGB(226, 232, 240));
    rectangle(x, y, x + w, y + h);

    setfillcolor(RGB(59, 130, 246));
    solidrectangle(x, y, x + 6, y + h);

    settextstyle(15, 0, "Consolas");
    settextcolor(RGB(30, 41, 59));
    int vSpace = (h - textheight(text)) / 2;
    outtextxy(x + 16, y + vSpace, text);
}

// Cube face vertex data
GLfloat red[18][4][3] = {
    //9个底板
    10,10,-30,
    -10,10,-30,
    -10,-10,-30,
    10,-10,-30,

    30,30,-30,
    10,30,-30,
    10,10,-30,
    30,10,-30,

    10,30,-30,
    -10,30,-30,
    -10,10,-30,
    10,10,-30,

    -10,30,-30,
    -30,30,-30,
    -30,10,-30,
    -10,10,-30,

    -10,10,-30,
    -30,10,-30,
    -30,-10,-30,
    -10,-10,-30,

    -10,-10,-30,
    -30,-10,-30,
    -30,-30,-30,
    -10,-30,-30,

    10,-10,-30,
    -10,-10,-30,
    -10,-30,-30,
    10,-30,-30,

    30,-10,-30,
    10,-10,-30,
    10,-30,-30,
    30,-30,-30,

    30,10,-30,
    10,10,-30,
    10,-10,-30,
    30,-10,-30,

    //红色face
     9,9,-31,
    -9,9,-31,
    -9,-9,-31,
    9,-9,-31,

    29,29,-31,
    11,29,-31,
    11,11,-31,
    29,11,-31,

    9,29,-31,
    -9,29,-31,
    -9,11,-31,
    9,11,-31,

    -11,29,-31,
    -29,29,-31,
    -29,11,-31,
    -11,11,-31,

    -11,9,-31,
    -29,9,-31,
    -29,-9,-31,
    -11,-9,-31,

    -11,-11,-31,
    -29,-11,-31,
    -29,-29,-31,
    -11,-29,-31,

    9,-11,-31,
    -9,-11,-31,
    -9,-29,-31,
    9,-29,-31,

    29,-11,-31,
    11,-11,-31,
    11,-29,-31,
    29,-29,-31,

    29,9,-31,
    11,9,-31,
    11,-9,-31,
    29,-9,-31,

};
GLfloat green[18][4][3] = {

    //9个底板
30,10,10,
30,-10,10,
30,-10,-10,
30,10,-10,

30,30,30,
30,10,30,
30,10,10,
30,30,10,

30,10,30,
30,-10,30,
30,-10,10,
30,10,10,

30,-10,30,
30,-30,30,
30,-30,10,
30,-10,10,

30,-10,10,
30,-30,10,
30,-30,-10,
30,-10,-10,

30,-10,-10,
30,-30,-10,
30,-30,-30,
30,-10,-30,

30,10,-10,
30,-10,-10,
30,-10,-30,
30,10,-30,

30,30,-10,
30,10,-10,
30,10,-30,
30,30,-30,

30,30,10,
30,10,10,
30,10,-10,
30,30,-10,

//绿色face

31,9,9,
31,-9,9,
31,-9,-9,
31,9,-9,

31,29,29,
31,11,29,
31,11,11,
31,29,11,

31,9,29,
31,-9,29,
31,-9,11,
31,9,11,

31,-11,29,
31,-29,29,
31,-29,11,
31,-11,11,

31,-11,9,
31,-29,9,
31,-29,-9,
31,-11,-9,

31,-11,-11,
31,-29,-11,
31,-29,-29,
31,-11,-29,

31,9,-11,
31,-9,-11,
31,-9,-29,
31,9,-29,

31,29,-11,
31,11,-11,
31,11,-29,
31,29,-29,

31,29,9,
31,11,9,
31,11,-9,
31,29,-9,
};
GLfloat orange[18][4][3] = {
    //9个底板
    10,10,30,
    -10,10,30,
    -10,-10,30,
    10,-10,30,

    30,30,30,
    10,30,30,
    10,10,30,
    30,10,30,

    10,30,30,
    -10,30,30,
    -10,10,30,
    10,10,30,

    -10,30,30,
    -30,30,30,
    -30,10,30,
    -10,10,30,

    -10,10,30,
    -30,10,30,
    -30,-10,30,
    -10,-10,30,

    -10,-10,30,
    -30,-10,30,
    -30,-30,30,
    -10,-30,30,

    10,-10,30,
    -10,-10,30,
    -10,-30,30,
    10,-30,30,

    30,-10,30,
    10,-10,30,
    10,-30,30,
    30,-30,30,

    30,10,30,
    10,10,30,
    10,-10,30,
    30,-10,30,

    //橙色face
     9,9,31,
    -9,9,31,
    -9,-9,31,
    9,-9,31,

    29,29,31,
    11,29,31,
    11,11,31,
    29,11,31,

    9,29,31,
    -9,29,31,
    -9,11,31,
    9,11,31,

    -11,29,31,
    -29,29,31,
    -29,11,31,
    -11,11,31,

    -11,9,31,
    -29,9,31,
    -29,-9,31,
    -11,-9,31,

    -11,-11,31,
    -29,-11,31,
    -29,-29,31,
    -11,-29,31,

    9,-11,31,
    -9,-11,31,
    -9,-29,31,
    9,-29,31,

    29,-11,31,
    11,-11,31,
    11,-29,31,
    29,-29,31,

    29,9,31,
    11,9,31,
    11,-9,31,
    29,-9,31,

};
GLfloat blue[18][4][3] = {

    //9个底板
       -30,10,10,
       -30,-10,10,
       -30,-10,-10,
       -30,10,-10,

       -30,30,30,
       -30,10,30,
       -30,10,10,
       -30,30,10,

       -30,10,30,
       -30,-10,30,
       -30,-10,10,
       -30,10,10,

       -30,-10,30,
       -30,-30,30,
       -30,-30,10,
       -30,-10,10,

       -30,-10,10,
       -30,-30,10,
       -30,-30,-10,
       -30,-10,-10,

       -30,-10,-10,
       -30,-30,-10,
       -30,-30,-30,
       -30,-10,-30,

       -30,10,-10,
       -30,-10,-10,
       -30,-10,-30,
       -30,10,-30,

       -30,30,-10,
       -30,10,-10,
       -30,10,-30,
       -30,30,-30,

       -30,30,10,
       -30,10,10,
       -30,10,-10,
       -30,30,-10,

       //蓝色face

       -31,9,9,
       -31,-9,9,
       -31,-9,-9,
       -31,9,-9,

       -31,29,29,
       -31,11,29,
       -31,11,11,
       -31,29,11,

       -31,9,29,
       -31,-9,29,
       -31,-9,11,
       -31,9,11,

       -31,-11,29,
       -31,-29,29,
       -31,-29,11,
       -31,-11,11,

       -31,-11,9,
       -31,-29,9,
       -31,-29,-9,
       -31,-11,-9,

       -31,-11,-11,
       -31,-29,-11,
       -31,-29,-29,
       -31,-11,-29,

       -31,9,-11,
       -31,-9,-11,
       -31,-9,-29,
       -31,9,-29,

       -31,29,-11,
       -31,11,-11,
       -31,11,-29,
       -31,29,-29,

       -31,29,9,
       -31,11,9,
       -31,11,-9,
       -31,29,-9,

};
GLfloat white[18][4][3] = {
    //9个底板
     10,30,10,
    -10,30,10,
    -10,30,-10,
     10,30,-10,

     30,30,30,
     10,30,30,
     10,30,10,
     30,30,10,

     10,30,30,
    -10,30,30,
    -10,30,10,
     10,30,10,

    -10,30,30,
    -30,30,30,
    -30,30,10,
    -10,30,10,

    -10,30,10,
    -30,30,10,
    -30,30,-10,
    -10,30,-10,

    -10,30,-10,
    -30,30,-10,
    -30,30,-30,
    -10,30,-30,

     10,30,-10,
    -10,30,-10,
    -10,30,-30,
     10,30,-30,

     30,30,-10,
     10,30,-10,
     10,30,-30,
     30,30,-30,

     30,30,10,
     10,30,10,
     10,30,-10,
     30,30,-10,

     //白色face
       9,31,9,
      -9,31,9,
      -9,31,-9,
       9,31,-9,

      29,31,29,
      11,31,29,
      11,31,11,
      29,31,11,

       9,31,29,
      -9,31,29,
      -9,31,11,
       9,31,11,

     -11,31,29,
     -29,31,29,
     -29,31,11,
     -11,31,11,

     -11,31,9,
     -29,31,9,
     -29,31,-9,
     -11,31,-9,

     -11,31,-11,
     -29,31,-11,
     -29,31,-29,
     -11,31,-29,

       9,31,-11,
      -9,31,-11,
      -9,31,-29,
       9,31,-29,

      29,31,-11,
      11,31,-11,
      11,31,-29,
      29,31,-29,

      29,31,9,
      11,31,9,
      11,31,-9,
      29,31,-9,

};
GLfloat yellow[18][4][3] = {

    //9个底板
    10,-30,10,
   -10,-30,10,
   -10,-30,-10,
    10,-30,-10,

    30,-30,30,
    10,-30,30,
    10,-30,10,
    30,-30,10,

    10,-30,30,
   -10,-30,30,
   -10,-30,10,
    10,-30,10,

   -10,-30,30,
   -30,-30,30,
   -30,-30,10,
   -10,-30,10,

   -10,-30,10,
   -30,-30,10,
   -30,-30,-10,
   -10,-30,-10,

   -10,-30,-10,
   -30,-30,-10,
   -30,-30,-30,
   -10,-30,-30,

    10,-30,-10,
   -10,-30,-10,
   -10,-30,-30,
    10,-30,-30,

    30,-30,-10,
    10,-30,-10,
    10,-30,-30,
    30,-30,-30,

    30,-30,10,
    10,-30,10,
    10,-30,-10,
    30,-30,-10,

    //黄色face
     9,-31,9,
    -9,-31,9,
    -9,-31,-9,
     9,-31,-9,

    29,-31,29,
    11,-31,29,
    11,-31,11,
    29,-31,11,

     9,-31,29,
    -9,-31,29,
    -9,-31,11,
     9,-31,11,

   -11,-31,29,
   -29,-31,29,
   -29,-31,11,
   -11,-31,11,

   -11,-31,9,
   -29,-31,9,
   -29,-31,-9,
   -11,-31,-9,

   -11,-31,-11,
   -29,-31,-11,
   -29,-31,-29,
   -11,-31,-29,

     9,-31,-11,
    -9,-31,-11,
    -9,-31,-29,
     9,-31,-29,

    29,-31,-11,
    11,-31,-11,
    11,-31,-29,
    29,-31,-29,

    29,-31,9,
    11,-31,9,
    11,-31,-9,
    29,-31,-9,
};
GLfloat color[6][3] = {
    1 , 0 , 0,
    0 , 1 , 0,
    1 , 0.5 ,0,
    0 , 0 , 1,
    1 , 1, 1,
    1 , 1, 0
};
GLfloat texture[4][4] = { 0,0,1,0,1,1,0,1 };

#pragma pack(push, 1)
typedef struct {
    char type[2];        // 文件类型，必须是"BM"
    int size;            // 文件大小
    short reserved1;     // 保留，必须为0
    short reserved2;     // 保留，必须为0
    int offset;          // 像素数据的偏移量
} BMPHeader;

typedef struct {
    int headerSize;      // 头信息的大小
    int width;           // 图像宽度
    int height;          // 图像高度
    short planes;        // 颜色平面数，必须为1
    short bitsPerPixel;  // 每像素的位数
    int compression;     // 压缩方式
    int imageSize;       // 图像数据大小
    int xPixelsPerMeter; // 水平分辨率
    int yPixelsPerMeter; // 垂直分辨率
    int colorsUsed;      // 实际使用的颜色
    int importantColors; // 重要颜色数
} BMPInfoHeader;
#pragma pack(pop)
void loadTexture(const char* filename) {
    FILE* file;
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfoHeader;

    // 打开BMP文件
    file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // 读取BMP文件头
    if (fread(&bmpHeader, sizeof(BMPHeader), 1, file) != 1) {
        perror("Error reading BMP header");
        fclose(file);
        return;
    }

    // 检查BMP文件头
    if (bmpHeader.type[0] != 'B' || bmpHeader.type[1] != 'M') {
        printf("Error: Not a valid BMP file\n");
        fclose(file);
        return;
    }

    // 读取BMP信息头
    if (fread(&bmpInfoHeader, sizeof(BMPInfoHeader), 1, file) != 1) {
        perror("Error reading BMP info header");
        fclose(file);
        return;
    }

    // 检查位深度是否为24位
    if (bmpInfoHeader.bitsPerPixel != 24) {
        printf("Error: Only 24-bit BMP files are supported\n");
        fclose(file);
        return;
    }

    // 提取图像信息
    int width = bmpInfoHeader.width;
    int height = bmpInfoHeader.height;
    int imageSize = bmpInfoHeader.imageSize;
    if (imageSize == 0) imageSize = width * height * 3; // 有些文件没有填写图像数据大小

    // 分配内存存储图像数据
    unsigned char* data = (unsigned char*)malloc(imageSize);
    if (!data) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    // 移动文件指针到图像数据位置
    fseek(file, bmpHeader.offset, SEEK_SET);

    // 读取图像数据
    if (fread(data, 1, imageSize, file) != imageSize) {
        perror("Error reading image data");
        fclose(file);
        free(data);
        return;
    }

    // 关闭文件
    fclose(file);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    // 生成纹理对象
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // 设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 绑定图像数据到纹理对象
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    // 生成多级渐远纹理
    glGenerateMipmap(GL_TEXTURE_2D);

    // 释放图像数据
    free(data);
}

/******************************魔方变换模块******************************/

//颜色矩阵的12个操作(小写字母代表大写字母的反向旋转)
void move_F()
{
    Cube t = cube;
    cube.a[12] = t.a[18];
    cube.a[11] = t.a[15];
    cube.a[10] = t.a[12];
    cube.a[13] = t.a[11];
    cube.a[16] = t.a[10];
    cube.a[17] = t.a[13];
    cube.a[18] = t.a[16];
    cube.a[15] = t.a[17];
    cube.a[14] = t.a[14];
    cube.a[9] = t.a[46];
    cube.a[8] = t.a[49];
    cube.a[7] = t.a[52];
    cube.a[37] = t.a[9];
    cube.a[40] = t.a[8];
    cube.a[43] = t.a[7];
    cube.a[19] = t.a[37];
    cube.a[20] = t.a[40];
    cube.a[21] = t.a[43];
    cube.a[46] = t.a[19];
    cube.a[49] = t.a[20];
    cube.a[52] = t.a[21];

}
void move_f()
{
    Cube t = cube;
    cube.a[18] = t.a[12];
    cube.a[15] = t.a[11];
    cube.a[12] = t.a[10];
    cube.a[11] = t.a[13];
    cube.a[10] = t.a[16];
    cube.a[13] = t.a[17];
    cube.a[16] = t.a[18];
    cube.a[17] = t.a[15];
    cube.a[14] = t.a[14];
    cube.a[46] = t.a[9];
    cube.a[49] = t.a[8];
    cube.a[52] = t.a[7];
    cube.a[9] = t.a[37];
    cube.a[8] = t.a[40];
    cube.a[7] = t.a[43];
    cube.a[37] = t.a[19];
    cube.a[40] = t.a[20];
    cube.a[43] = t.a[21];
    cube.a[19] = t.a[46];
    cube.a[20] = t.a[49];
    cube.a[21] = t.a[52];

}
void move_R()
{
    Cube t = cube;
    cube.a[52] = t.a[46];
    cube.a[53] = t.a[49];
    cube.a[54] = t.a[52];
    cube.a[51] = t.a[53];
    cube.a[48] = t.a[54];
    cube.a[47] = t.a[51];
    cube.a[46] = t.a[48];
    cube.a[49] = t.a[47];
    cube.a[50] = t.a[50];
    cube.a[9] = t.a[18];
    cube.a[6] = t.a[15];
    cube.a[3] = t.a[12];
    cube.a[36] = t.a[9];
    cube.a[33] = t.a[6];
    cube.a[30] = t.a[3];
    cube.a[27] = t.a[36];
    cube.a[24] = t.a[33];
    cube.a[21] = t.a[30];
    cube.a[18] = t.a[27];
    cube.a[15] = t.a[24];
    cube.a[12] = t.a[21];
}
void move_r()
{
    Cube t = cube;
    cube.a[46] = t.a[52];
    cube.a[49] = t.a[53];
    cube.a[52] = t.a[54];
    cube.a[53] = t.a[51];
    cube.a[54] = t.a[48];
    cube.a[51] = t.a[47];
    cube.a[48] = t.a[46];
    cube.a[47] = t.a[49];
    cube.a[50] = t.a[50];
    cube.a[18] = t.a[9];
    cube.a[15] = t.a[6];
    cube.a[12] = t.a[3];
    cube.a[9] = t.a[36];
    cube.a[6] = t.a[33];
    cube.a[3] = t.a[30];
    cube.a[36] = t.a[27];
    cube.a[33] = t.a[24];
    cube.a[30] = t.a[21];
    cube.a[27] = t.a[18];
    cube.a[24] = t.a[15];
    cube.a[21] = t.a[12];
}
void move_U()
{
    Cube t = cube;
    cube.a[1] = t.a[7];
    cube.a[2] = t.a[4];
    cube.a[3] = t.a[1];
    cube.a[6] = t.a[2];
    cube.a[9] = t.a[3];
    cube.a[8] = t.a[6];
    cube.a[7] = t.a[9];
    cube.a[4] = t.a[8];
    cube.a[5] = t.a[5];
    cube.a[34] = t.a[37];
    cube.a[35] = t.a[38];
    cube.a[36] = t.a[39];
    cube.a[54] = t.a[34];
    cube.a[53] = t.a[35];
    cube.a[52] = t.a[36];
    cube.a[12] = t.a[54];
    cube.a[11] = t.a[53];
    cube.a[10] = t.a[52];
    cube.a[37] = t.a[12];
    cube.a[38] = t.a[11];
    cube.a[39] = t.a[10];
}
void move_u()
{
    Cube t = cube;
    cube.a[7] = t.a[1];
    cube.a[4] = t.a[2];
    cube.a[1] = t.a[3];
    cube.a[2] = t.a[6];
    cube.a[3] = t.a[9];
    cube.a[6] = t.a[8];
    cube.a[9] = t.a[7];
    cube.a[8] = t.a[4];
    cube.a[5] = t.a[5];
    cube.a[37] = t.a[34];
    cube.a[38] = t.a[35];
    cube.a[39] = t.a[36];
    cube.a[34] = t.a[54];
    cube.a[35] = t.a[53];
    cube.a[36] = t.a[52];
    cube.a[54] = t.a[12];
    cube.a[53] = t.a[11];
    cube.a[52] = t.a[10];
    cube.a[12] = t.a[37];
    cube.a[11] = t.a[38];
    cube.a[10] = t.a[39];
}
void move_D()
{
    Cube t = cube;
    cube.a[25] = t.a[19];
    cube.a[26] = t.a[22];
    cube.a[27] = t.a[25];
    cube.a[24] = t.a[26];
    cube.a[21] = t.a[27];
    cube.a[20] = t.a[24];
    cube.a[19] = t.a[21];
    cube.a[22] = t.a[20];
    cube.a[23] = t.a[23];
    cube.a[28] = t.a[43];
    cube.a[29] = t.a[44];
    cube.a[30] = t.a[45];
    cube.a[48] = t.a[28];
    cube.a[47] = t.a[29];
    cube.a[46] = t.a[30];
    cube.a[18] = t.a[48];
    cube.a[17] = t.a[47];
    cube.a[16] = t.a[46];
    cube.a[43] = t.a[18];
    cube.a[44] = t.a[17];
    cube.a[45] = t.a[16];
}
void move_d()
{
    Cube t = cube;
    cube.a[19] = t.a[25];
    cube.a[22] = t.a[26];
    cube.a[25] = t.a[27];
    cube.a[26] = t.a[24];
    cube.a[27] = t.a[21];
    cube.a[24] = t.a[20];
    cube.a[21] = t.a[19];
    cube.a[20] = t.a[22];
    cube.a[23] = t.a[23];
    cube.a[43] = t.a[28];
    cube.a[44] = t.a[29];
    cube.a[45] = t.a[30];
    cube.a[28] = t.a[48];
    cube.a[29] = t.a[47];
    cube.a[30] = t.a[46];
    cube.a[48] = t.a[18];
    cube.a[47] = t.a[17];
    cube.a[46] = t.a[16];
    cube.a[18] = t.a[43];
    cube.a[17] = t.a[44];
    cube.a[16] = t.a[45];
}
void move_L()
{
    Cube t = cube;
    cube.a[37] = t.a[43];
    cube.a[38] = t.a[40];
    cube.a[39] = t.a[37];
    cube.a[42] = t.a[38];
    cube.a[45] = t.a[39];
    cube.a[44] = t.a[42];
    cube.a[43] = t.a[45];
    cube.a[40] = t.a[44];
    cube.a[41] = t.a[41];
    cube.a[7] = t.a[16];
    cube.a[4] = t.a[13];
    cube.a[1] = t.a[10];
    cube.a[34] = t.a[7];
    cube.a[31] = t.a[4];
    cube.a[28] = t.a[1];
    cube.a[25] = t.a[34];
    cube.a[22] = t.a[31];
    cube.a[19] = t.a[28];
    cube.a[16] = t.a[25];
    cube.a[13] = t.a[22];
    cube.a[10] = t.a[19];
}
void move_l()
{
    Cube t = cube;
    cube.a[43] = t.a[37];
    cube.a[40] = t.a[38];
    cube.a[37] = t.a[39];
    cube.a[38] = t.a[42];
    cube.a[39] = t.a[45];
    cube.a[42] = t.a[44];
    cube.a[45] = t.a[43];
    cube.a[44] = t.a[40];
    cube.a[41] = t.a[41];
    cube.a[16] = t.a[7];
    cube.a[13] = t.a[4];
    cube.a[10] = t.a[1];
    cube.a[7] = t.a[34];
    cube.a[4] = t.a[31];
    cube.a[1] = t.a[28];
    cube.a[34] = t.a[25];
    cube.a[31] = t.a[22];
    cube.a[28] = t.a[19];
    cube.a[25] = t.a[16];
    cube.a[22] = t.a[13];
    cube.a[19] = t.a[10];
}
void move_B()
{
    Cube t = cube;
    cube.a[36] = t.a[30];
    cube.a[35] = t.a[33];
    cube.a[34] = t.a[36];
    cube.a[31] = t.a[35];
    cube.a[28] = t.a[34];
    cube.a[29] = t.a[31];
    cube.a[30] = t.a[28];
    cube.a[33] = t.a[29];
    cube.a[32] = t.a[32];
    cube.a[3] = t.a[48];
    cube.a[2] = t.a[51];
    cube.a[1] = t.a[54];
    cube.a[39] = t.a[3];
    cube.a[42] = t.a[2];
    cube.a[45] = t.a[1];
    cube.a[25] = t.a[39];
    cube.a[26] = t.a[42];
    cube.a[27] = t.a[45];
    cube.a[48] = t.a[25];
    cube.a[51] = t.a[26];
    cube.a[54] = t.a[27];

}
void move_b()
{
    Cube t = cube;
    cube.a[30] = t.a[36];
    cube.a[33] = t.a[35];
    cube.a[36] = t.a[34];
    cube.a[35] = t.a[31];
    cube.a[34] = t.a[28];
    cube.a[31] = t.a[29];
    cube.a[28] = t.a[30];
    cube.a[29] = t.a[33];
    cube.a[32] = t.a[32];
    cube.a[48] = t.a[3];
    cube.a[51] = t.a[2];
    cube.a[54] = t.a[1];
    cube.a[3] = t.a[39];
    cube.a[2] = t.a[42];
    cube.a[1] = t.a[45];
    cube.a[39] = t.a[25];
    cube.a[42] = t.a[26];
    cube.a[45] = t.a[27];
    cube.a[25] = t.a[48];
    cube.a[26] = t.a[51];
    cube.a[27] = t.a[54];

}
void move_X() {
    Cube t = cube;
    //U face
    cube.a[1] = t.a[54];
    cube.a[2] = t.a[51];
    cube.a[3] = t.a[48];
    cube.a[4] = t.a[53];
    cube.a[5] = t.a[50];
    cube.a[6] = t.a[47];
    cube.a[7] = t.a[52];
    cube.a[8] = t.a[49];
    cube.a[9] = t.a[46];
    //D face
    cube.a[19] = t.a[37];
    cube.a[20] = t.a[40];
    cube.a[21] = t.a[43];
    cube.a[22] = t.a[38];
    cube.a[23] = t.a[41];
    cube.a[24] = t.a[44];
    cube.a[25] = t.a[39];
    cube.a[26] = t.a[42];
    cube.a[27] = t.a[45];
    //L face
    cube.a[37] = t.a[9];
    cube.a[40] = t.a[8];
    cube.a[43] = t.a[7];
    cube.a[38] = t.a[6];
    cube.a[41] = t.a[5];
    cube.a[44] = t.a[4];
    cube.a[39] = t.a[3];
    cube.a[42] = t.a[2];
    cube.a[45] = t.a[1];
    //R face
    cube.a[54] = t.a[27];
    cube.a[51] = t.a[26];
    cube.a[48] = t.a[25];
    cube.a[53] = t.a[24];
    cube.a[50] = t.a[23];
    cube.a[47] = t.a[22];
    cube.a[52] = t.a[21];
    cube.a[49] = t.a[20];
    cube.a[46] = t.a[19];
    //F face
    cube.a[10] = t.a[12];
    cube.a[11] = t.a[15];
    cube.a[12] = t.a[18];
    cube.a[15] = t.a[17];
    cube.a[18] = t.a[16];
    cube.a[17] = t.a[13];
    cube.a[16] = t.a[10];
    cube.a[13] = t.a[11];
    cube.a[14] = t.a[14];
    //B face
    cube.a[34] = t.a[36];
    cube.a[35] = t.a[33];
    cube.a[36] = t.a[30];
    cube.a[33] = t.a[29];
    cube.a[30] = t.a[28];
    cube.a[29] = t.a[31];
    cube.a[28] = t.a[34];
    cube.a[31] = t.a[35];
    cube.a[32] = t.a[32];
}
void move_x() {
    Cube t = cube;
    //U face
    cube.a[54] = t.a[1];
    cube.a[51] = t.a[2];
    cube.a[48] = t.a[3];
    cube.a[53] = t.a[4];
    cube.a[50] = t.a[5];
    cube.a[47] = t.a[6];
    cube.a[52] = t.a[7];
    cube.a[49] = t.a[8];
    cube.a[46] = t.a[9];
    //D face
    cube.a[37] = t.a[19];
    cube.a[40] = t.a[20];
    cube.a[43] = t.a[21];
    cube.a[38] = t.a[22];
    cube.a[41] = t.a[23];
    cube.a[44] = t.a[24];
    cube.a[39] = t.a[25];
    cube.a[42] = t.a[26];
    cube.a[45] = t.a[27];
    //L face
    cube.a[9] = t.a[37];
    cube.a[8] = t.a[40];
    cube.a[7] = t.a[43];
    cube.a[6] = t.a[38];
    cube.a[5] = t.a[41];
    cube.a[4] = t.a[44];
    cube.a[3] = t.a[39];
    cube.a[2] = t.a[42];
    cube.a[1] = t.a[45];
    //R face
    cube.a[27] = t.a[54];
    cube.a[26] = t.a[51];
    cube.a[25] = t.a[48];
    cube.a[24] = t.a[53];
    cube.a[23] = t.a[50];
    cube.a[22] = t.a[47];
    cube.a[21] = t.a[52];
    cube.a[20] = t.a[49];
    cube.a[19] = t.a[46];
    //F face
    cube.a[12] = t.a[10];
    cube.a[15] = t.a[11];
    cube.a[18] = t.a[12];
    cube.a[17] = t.a[15];
    cube.a[16] = t.a[18];
    cube.a[13] = t.a[17];
    cube.a[10] = t.a[16];
    cube.a[11] = t.a[13];
    cube.a[14] = t.a[14];
    //B face
    cube.a[36] = t.a[34];
    cube.a[33] = t.a[35];
    cube.a[30] = t.a[36];
    cube.a[29] = t.a[33];
    cube.a[28] = t.a[30];
    cube.a[31] = t.a[29];
    cube.a[34] = t.a[28];
    cube.a[35] = t.a[31];
    cube.a[32] = t.a[32];
}
void move_Y() {
    Cube t = cube;
    //U face
    cube.a[7] = t.a[9];
    cube.a[8] = t.a[6];
    cube.a[9] = t.a[3];
    cube.a[6] = t.a[2];
    cube.a[3] = t.a[1];
    cube.a[2] = t.a[4];
    cube.a[1] = t.a[7];
    cube.a[4] = t.a[8];
    cube.a[5] = t.a[5];
    //D face
    cube.a[19] = t.a[21];
    cube.a[20] = t.a[24];
    cube.a[21] = t.a[27];
    cube.a[24] = t.a[26];
    cube.a[27] = t.a[25];
    cube.a[26] = t.a[22];
    cube.a[25] = t.a[19];
    cube.a[22] = t.a[20];
    cube.a[23] = t.a[23];
    //L face
    cube.a[37] = t.a[12];
    cube.a[38] = t.a[11];
    cube.a[39] = t.a[10];
    cube.a[40] = t.a[15];
    cube.a[41] = t.a[14];
    cube.a[42] = t.a[13];
    cube.a[43] = t.a[18];
    cube.a[44] = t.a[17];
    cube.a[45] = t.a[16];
    //R face
    cube.a[52] = t.a[36];
    cube.a[53] = t.a[35];
    cube.a[54] = t.a[34];
    cube.a[49] = t.a[33];
    cube.a[50] = t.a[32];
    cube.a[51] = t.a[31];
    cube.a[46] = t.a[30];
    cube.a[47] = t.a[29];
    cube.a[48] = t.a[28];
    //F face
    cube.a[10] = t.a[52];
    cube.a[11] = t.a[53];
    cube.a[12] = t.a[54];
    cube.a[13] = t.a[49];
    cube.a[14] = t.a[50];
    cube.a[15] = t.a[51];
    cube.a[16] = t.a[46];
    cube.a[17] = t.a[47];
    cube.a[18] = t.a[48];
    //B face
    cube.a[34] = t.a[37];
    cube.a[35] = t.a[38];
    cube.a[36] = t.a[39];
    cube.a[31] = t.a[40];
    cube.a[32] = t.a[41];
    cube.a[33] = t.a[42];
    cube.a[28] = t.a[43];
    cube.a[29] = t.a[44];
    cube.a[30] = t.a[45];
}
void move_y() {
    Cube t = cube;
    //U face
    cube.a[9] = t.a[7];
    cube.a[6] = t.a[8];
    cube.a[3] = t.a[9];
    cube.a[2] = t.a[6];
    cube.a[1] = t.a[3];
    cube.a[4] = t.a[2];
    cube.a[7] = t.a[1];
    cube.a[8] = t.a[4];
    cube.a[5] = t.a[5];
    //D face
    cube.a[21] = t.a[19];
    cube.a[24] = t.a[20];
    cube.a[27] = t.a[21];
    cube.a[26] = t.a[24];
    cube.a[25] = t.a[27];
    cube.a[22] = t.a[26];
    cube.a[19] = t.a[25];
    cube.a[20] = t.a[22];
    cube.a[23] = t.a[23];
    //L face
    cube.a[12] = t.a[37];
    cube.a[11] = t.a[38];
    cube.a[10] = t.a[39];
    cube.a[15] = t.a[40];
    cube.a[14] = t.a[41];
    cube.a[13] = t.a[42];
    cube.a[18] = t.a[43];
    cube.a[17] = t.a[44];
    cube.a[16] = t.a[45];
    //R face
    cube.a[36] = t.a[52];
    cube.a[35] = t.a[53];
    cube.a[34] = t.a[54];
    cube.a[33] = t.a[49];
    cube.a[32] = t.a[50];
    cube.a[31] = t.a[51];
    cube.a[30] = t.a[46];
    cube.a[29] = t.a[47];
    cube.a[28] = t.a[48];
    //F face
    cube.a[52] = t.a[10];
    cube.a[53] = t.a[11];
    cube.a[54] = t.a[12];
    cube.a[49] = t.a[13];
    cube.a[50] = t.a[14];
    cube.a[51] = t.a[15];
    cube.a[46] = t.a[16];
    cube.a[47] = t.a[17];
    cube.a[48] = t.a[18];
    //B face
    cube.a[37] = t.a[34];
    cube.a[38] = t.a[35];
    cube.a[39] = t.a[36];
    cube.a[40] = t.a[31];
    cube.a[41] = t.a[32];
    cube.a[42] = t.a[33];
    cube.a[43] = t.a[28];
    cube.a[44] = t.a[29];
    cube.a[45] = t.a[30];
}
void move_Z() {
    Cube t = cube;
    //U face
    cube.a[1] = t.a[28];
    cube.a[2] = t.a[29];
    cube.a[3] = t.a[30];
    cube.a[4] = t.a[31];
    cube.a[5] = t.a[32];
    cube.a[6] = t.a[33];
    cube.a[7] = t.a[34];
    cube.a[8] = t.a[35];
    cube.a[9] = t.a[36];
    //D face
    cube.a[19] = t.a[10];
    cube.a[20] = t.a[11];
    cube.a[21] = t.a[12];
    cube.a[22] = t.a[13];
    cube.a[23] = t.a[14];
    cube.a[24] = t.a[15];
    cube.a[25] = t.a[16];
    cube.a[26] = t.a[17];
    cube.a[27] = t.a[18];
    //L face
    cube.a[37] = t.a[39];
    cube.a[38] = t.a[42];
    cube.a[39] = t.a[45];
    cube.a[42] = t.a[44];
    cube.a[45] = t.a[43];
    cube.a[44] = t.a[40];
    cube.a[43] = t.a[37];
    cube.a[40] = t.a[38];
    cube.a[41] = t.a[41];
    //R face
    cube.a[52] = t.a[54];
    cube.a[53] = t.a[51];
    cube.a[54] = t.a[48];
    cube.a[51] = t.a[47];
    cube.a[48] = t.a[46];
    cube.a[47] = t.a[49];
    cube.a[46] = t.a[52];
    cube.a[49] = t.a[53];
    cube.a[50] = t.a[50];
    //F face
    cube.a[10] = t.a[1];
    cube.a[11] = t.a[2];
    cube.a[12] = t.a[3];
    cube.a[13] = t.a[4];
    cube.a[14] = t.a[5];
    cube.a[15] = t.a[6];
    cube.a[16] = t.a[7];
    cube.a[17] = t.a[8];
    cube.a[18] = t.a[9];
    //B face
    cube.a[34] = t.a[25];
    cube.a[35] = t.a[26];
    cube.a[36] = t.a[27];
    cube.a[31] = t.a[22];
    cube.a[32] = t.a[23];
    cube.a[33] = t.a[24];
    cube.a[28] = t.a[19];
    cube.a[29] = t.a[20];
    cube.a[30] = t.a[21];
}
void move_z() {
    Cube t = cube;
    //U face
    cube.a[28] = t.a[1];
    cube.a[29] = t.a[2];
    cube.a[30] = t.a[3];
    cube.a[31] = t.a[4];
    cube.a[32] = t.a[5];
    cube.a[33] = t.a[6];
    cube.a[34] = t.a[7];
    cube.a[35] = t.a[8];
    cube.a[36] = t.a[9];
    //D face
    cube.a[10] = t.a[19];
    cube.a[11] = t.a[20];
    cube.a[12] = t.a[21];
    cube.a[13] = t.a[22];
    cube.a[14] = t.a[23];
    cube.a[15] = t.a[24];
    cube.a[16] = t.a[25];
    cube.a[17] = t.a[26];
    cube.a[18] = t.a[27];
    //L face
    cube.a[39] = t.a[37];
    cube.a[42] = t.a[38];
    cube.a[45] = t.a[39];
    cube.a[44] = t.a[42];
    cube.a[43] = t.a[45];
    cube.a[40] = t.a[44];
    cube.a[37] = t.a[43];
    cube.a[38] = t.a[40];
    cube.a[41] = t.a[41];
    //R face
    cube.a[54] = t.a[52];
    cube.a[51] = t.a[53];
    cube.a[48] = t.a[54];
    cube.a[47] = t.a[51];
    cube.a[46] = t.a[48];
    cube.a[49] = t.a[47];
    cube.a[52] = t.a[46];
    cube.a[53] = t.a[49];
    cube.a[50] = t.a[50];
    //F face
    cube.a[1] = t.a[10];
    cube.a[2] = t.a[11];
    cube.a[3] = t.a[12];
    cube.a[4] = t.a[13];
    cube.a[5] = t.a[14];
    cube.a[6] = t.a[15];
    cube.a[7] = t.a[16];
    cube.a[8] = t.a[17];
    cube.a[9] = t.a[18];
    //B face
    cube.a[25] = t.a[34];
    cube.a[26] = t.a[35];
    cube.a[27] = t.a[36];
    cube.a[22] = t.a[31];
    cube.a[23] = t.a[32];
    cube.a[24] = t.a[33];
    cube.a[19] = t.a[28];
    cube.a[20] = t.a[29];
    cube.a[21] = t.a[30];
}
//判断该块是否位于该旋转层
bool CHECK_F(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][0] - Ox < 9) return false;
    return true;

}
bool CHECK_R(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][2] - Oz > -9) return false;
    return true;
}
bool CHECK_U(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][1] - Oy < 9)  return false;
    return true;
}
bool CHECK_D(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][1] - Oy > -9)  return false;
    return true;
}
bool CHECK_L(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][2] - Oz < 9)  return false;
    return true;
}
bool CHECK_B(GLfloat a[][4][3], int i)
{
    for (int j = 0; j < 4; j++)
        if (a[i][j][0] - Ox > -9)  return false;
    return true;
}
bool CHECK_ALL(Cube t)
{
    if (t.a[1] == t.a[2] && t.a[1] == t.a[3] && t.a[1] == t.a[4] && t.a[1] == t.a[5] && t.a[1] == t.a[6] && t.a[1] == t.a[7] && t.a[1] == t.a[8] && t.a[1] == t.a[9] &&
        t.a[10] == t.a[11] && t.a[10] == t.a[12] && t.a[10] == t.a[13] && t.a[10] == t.a[14] && t.a[10] == t.a[15] && t.a[10] == t.a[16] && t.a[10] == t.a[17] && t.a[10] == t.a[18] &&
        t.a[19] == t.a[20] && t.a[19] == t.a[21] && t.a[19] == t.a[22] && t.a[19] == t.a[23] && t.a[19] == t.a[24] && t.a[19] == t.a[25] && t.a[19] == t.a[26] && t.a[19] == t.a[27] &&
        t.a[28] == t.a[29] && t.a[28] == t.a[30] && t.a[28] == t.a[31] && t.a[28] == t.a[32] && t.a[28] == t.a[33] && t.a[28] == t.a[34] && t.a[28] == t.a[35] && t.a[28] == t.a[36] &&
        t.a[37] == t.a[38] && t.a[37] == t.a[39] && t.a[37] == t.a[40] && t.a[37] == t.a[41] && t.a[37] == t.a[42] && t.a[37] == t.a[43] && t.a[37] == t.a[44] && t.a[37] == t.a[45] &&
        t.a[46] == t.a[47] && t.a[46] == t.a[48] && t.a[46] == t.a[49] && t.a[46] == t.a[50] && t.a[46] == t.a[51] && t.a[46] == t.a[52] && t.a[46] == t.a[53] && t.a[46] == t.a[54]
        )
        return true;
    else return false;
}
int inter(float f) {
    float x = abs(floor(f) - f);
    float y = abs(floor(f) + 1 - f);
    if (x < y) return floor(f);
    else return floor(f) + 1;
}
bool CHECK_CUBE(GLfloat a[][4][3], GLfloat b[][4][3], GLfloat c[][4][3], GLfloat d[][4][3], GLfloat e[][4][3], GLfloat f[][4][3]) {
    int n = 0;
    GLfloat p = 0.001;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(a[i][0][j]) - a[i][0][j]) <= p) n++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(b[i][0][j]) - b[i][0][j]) <= p) n++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(c[i][0][j]) - c[i][0][j]) <= p) n++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(d[i][0][j]) - d[i][0][j]) <= p) n++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(e[i][0][j]) - e[i][0][j]) <= p) n++;
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            if (abs(inter(f[i][0][j]) - f[i][0][j]) <= p) n++;
        }
    }
    if (n == 162) return true;
    else return false;
}
//处理键盘鼠标事件，实现旋转和平移效果
void turn_fF(int USELESS)

{
    if (f2 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = red[i][j][1] - Oy;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    red[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = green[i][j][1] - Oy;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    green[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = orange[i][j][1] - Oy;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    orange[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = blue[i][j][1] - Oy;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    blue[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = white[i][j][1] - Oy;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    white[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = yellow[i][j][1] - Oy;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    yellow[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        glutPostRedisplay();
        glutTimerFunc(10, turn_fF, 1);
        f2++;
    }
    else {
        f2 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_ff(int USELESS)

{
    if (f2 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = red[i][j][1] - Oy;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    red[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = green[i][j][1] - Oy;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    green[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = orange[i][j][1] - Oy;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    orange[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = blue[i][j][1] - Oy;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    blue[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = white[i][j][1] - Oy;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    white[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_F(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = yellow[i][j][1] - Oy;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    yellow[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        glutPostRedisplay();
        glutTimerFunc(10, turn_ff, 1);
        f2++;
    }
    else {
        f2 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fR(int USELESS)
{
    if (f1 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat ty = red[i][j][1] - Oy;
                    red[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    red[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat ty = green[i][j][1] - Oy;
                    green[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    green[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat ty = orange[i][j][1] - Oy;
                    orange[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat ty = blue[i][j][1] - Oy;
                    blue[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat ty = white[i][j][1] - Oy;
                    white[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    white[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat ty = yellow[i][j][1] - Oy;
                    yellow[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fR, 1);
        f1++;
    }
    else {
        f1 = 0;
        if (Flag)  AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fr(int USELESS)
{
    if (f1 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat ty = red[i][j][1] - Oy;
                    red[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    red[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat ty = green[i][j][1] - Oy;
                    green[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    green[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat ty = orange[i][j][1] - Oy;
                    orange[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat ty = blue[i][j][1] - Oy;
                    blue[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat ty = white[i][j][1] - Oy;
                    white[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    white[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_R(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat ty = yellow[i][j][1] - Oy;
                    yellow[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fr, 1);
        f1++;
    }
    else {
        f1 = 0;
        if (Flag)  AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fU(int USELESS)
{
    if (f3 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_U(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    red[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    green[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    white[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fU, 1);
        f3++;

    }
    else {
        f3 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fu(int USELESS)
{
    if (f3 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_U(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    red[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    green[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    white[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_U(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fu, 1);
        f3++;

    }
    else {
        f3 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fD(int USELESS)
{
    if (f4 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_D(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    red[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    green[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    white[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][0] = (tx * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][2] = ((tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fD, 1);
        f4++;

    }
    else
    {
        f4 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fd(int USELESS)
{
    if (f4 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_D(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    red[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    green[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    white[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        for (int i = 0; i < 18; i++)
            if (CHECK_D(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][0] = (tx * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][2] = (-(tx * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fd, 1);
        f4++;

    }
    else
    {
        f4 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fL(int USELESS)
{
    if (f5 < 9)
    {

        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat ty = red[i][j][1] - Oy;
                    red[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    red[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat ty = green[i][j][1] - Oy;
                    green[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    green[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat ty = orange[i][j][1] - Oy;
                    orange[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat ty = blue[i][j][1] - Oy;
                    blue[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat ty = white[i][j][1] - Oy;
                    white[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    white[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat ty = yellow[i][j][1] - Oy;
                    yellow[i][j][0] = (tx * cos(ag)) - ((ty * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][1] = ((tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fL, 1);
        f5++;
    }
    else
    {
        f5 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fl(int USELESS)
{
    if (f5 < 9)
    {

        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = red[i][j][0] - Ox;
                    GLfloat ty = red[i][j][1] - Oy;
                    red[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    red[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = green[i][j][0] - Ox;
                    GLfloat ty = green[i][j][1] - Oy;
                    green[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    green[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = orange[i][j][0] - Ox;
                    GLfloat ty = orange[i][j][1] - Oy;
                    orange[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    orange[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = blue[i][j][0] - Ox;
                    GLfloat ty = blue[i][j][1] - Oy;
                    blue[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    blue[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = white[i][j][0] - Ox;
                    GLfloat ty = white[i][j][1] - Oy;
                    white[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    white[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_L(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat tx = yellow[i][j][0] - Ox;
                    GLfloat ty = yellow[i][j][1] - Oy;
                    yellow[i][j][0] = (tx * cos(ag)) + ((ty * sin(ag)) * CHANGE) + Ox;
                    yellow[i][j][1] = (-(tx * sin(ag)) * CHANGE) + (ty * cos(ag)) + Oy;
                }
            }
        glutPostRedisplay();
        glutTimerFunc(10, turn_fl, 1);
        f5++;
    }
    else
    {
        f5 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fB(int USELESS)
{
    if (f6 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = red[i][j][1] - Oy;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    red[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = green[i][j][1] - Oy;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    green[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = orange[i][j][1] - Oy;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    orange[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = blue[i][j][1] - Oy;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    blue[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = white[i][j][1] - Oy;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    white[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = yellow[i][j][1] - Oy;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][1] = (ty * cos(ag)) - ((tz * sin(ag)) * CHANGE) + Oy;
                    yellow[i][j][2] = ((ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        glutPostRedisplay();
        glutTimerFunc(10, turn_fB, 1);
        f6++;


    }
    else {
        f6 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_fb(int USELESS)
{
    if (f6 < 9)
    {
        //红色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(red, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = red[i][j][1] - Oy;
                    GLfloat tz = red[i][j][2] - Oz;
                    red[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    red[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //绿色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(green, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = green[i][j][1] - Oy;
                    GLfloat tz = green[i][j][2] - Oz;
                    green[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    green[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //橙色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(orange, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = orange[i][j][1] - Oy;
                    GLfloat tz = orange[i][j][2] - Oz;
                    orange[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    orange[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //蓝色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(blue, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = blue[i][j][1] - Oy;
                    GLfloat tz = blue[i][j][2] - Oz;
                    blue[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    blue[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //白色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(white, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = white[i][j][1] - Oy;
                    GLfloat tz = white[i][j][2] - Oz;
                    white[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    white[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        //黄色变
        for (int i = 0; i < 18; i++)
            if (CHECK_B(yellow, i))
            {
                for (int j = 0; j < 4; j++)
                {
                    GLfloat ty = yellow[i][j][1] - Oy;
                    GLfloat tz = yellow[i][j][2] - Oz;
                    yellow[i][j][1] = (ty * cos(ag)) + ((tz * sin(ag)) * CHANGE) + Oy;
                    yellow[i][j][2] = (-(ty * sin(ag)) * CHANGE) + (tz * cos(ag)) + Oz;
                }
            }

        glutPostRedisplay();
        glutTimerFunc(10, turn_fb, 1);
        f6++;


    }
    else {
        f6 = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_allX(int USELESS)
{
    if (f_allX < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][1] - Oy;
                GLfloat tz = red[i][j][2] - Oz;
                red[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                red[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][1] - Oy;
                GLfloat tz = green[i][j][2] - Oz;
                green[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                green[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][1] - Oy;
                GLfloat tz = orange[i][j][2] - Oz;
                orange[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                orange[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][1] - Oy;
                GLfloat tz = blue[i][j][2] - Oz;
                blue[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                blue[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][1] - Oy;
                GLfloat tz = white[i][j][2] - Oz;
                white[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                white[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][1] - Oy;
                GLfloat tz = yellow[i][j][2] - Oz;
                yellow[i][j][1] = (ty * cos(ag)) - (tz * sin(ag)) + Oy;
                yellow[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_allX, 1);

        f_allX++;
    }
    else {
        f_allX = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }

}
void turn_allx(int USELESS) {
    if (f_allx < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][1] - Oy;
                GLfloat tz = red[i][j][2] - Oz;
                red[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                red[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][1] - Oy;
                GLfloat tz = green[i][j][2] - Oz;
                green[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                green[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][1] - Oy;
                GLfloat tz = orange[i][j][2] - Oz;
                orange[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                orange[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][1] - Oy;
                GLfloat tz = blue[i][j][2] - Oz;
                blue[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                blue[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][1] - Oy;
                GLfloat tz = white[i][j][2] - Oz;
                white[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                white[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][1] - Oy;
                GLfloat tz = yellow[i][j][2] - Oz;
                yellow[i][j][1] = (ty * cos(ag)) + (tz * sin(ag)) + Oy;
                yellow[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_allx, 1);

        f_allx++;
    }
    else {
        f_allx = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_allY(int USELESS)
{
    if (f_allY < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][0] - Ox;
                GLfloat tz = red[i][j][2] - Oz;
                red[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                red[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][0] - Ox;
                GLfloat tz = green[i][j][2] - Oz;
                green[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                green[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][0] - Ox;
                GLfloat tz = orange[i][j][2] - Oz;
                orange[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                orange[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][0] - Ox;
                GLfloat tz = blue[i][j][2] - Oz;
                blue[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                blue[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][0] - Ox;
                GLfloat tz = white[i][j][2] - Oz;
                white[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                white[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][0] - Ox;
                GLfloat tz = yellow[i][j][2] - Oz;
                yellow[i][j][0] = (ty * cos(ag)) - (tz * sin(ag)) + Ox;
                yellow[i][j][2] = (ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_allY, 1);

        f_allY++;
    }
    else {
        f_allY = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_ally(int USELESS)
{
    if (f_ally < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][0] - Ox;
                GLfloat tz = red[i][j][2] - Oz;
                red[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                red[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][0] - Ox;
                GLfloat tz = green[i][j][2] - Oz;
                green[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                green[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][0] - Ox;
                GLfloat tz = orange[i][j][2] - Oz;
                orange[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                orange[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][0] - Ox;
                GLfloat tz = blue[i][j][2] - Oz;
                blue[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                blue[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][0] - Ox;
                GLfloat tz = white[i][j][2] - Oz;
                white[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                white[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][0] - Ox;
                GLfloat tz = yellow[i][j][2] - Oz;
                yellow[i][j][0] = (ty * cos(ag)) + (tz * sin(ag)) + Ox;
                yellow[i][j][2] = -(ty * sin(ag)) + (tz * cos(ag)) + Oz;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_ally, 1);

        f_ally++;
    }
    else {
        f_ally = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }
}
void turn_allZ(int USELESS)
{
    if (f_allZ < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][1] - Oy;
                GLfloat tx = red[i][j][0] - Ox;
                red[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                red[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][1] - Oy;
                GLfloat tx = green[i][j][0] - Ox;
                green[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                green[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][1] - Oy;
                GLfloat tx = orange[i][j][0] - Ox;
                orange[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                orange[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][1] - Oy;
                GLfloat tx = blue[i][j][0] - Ox;
                blue[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                blue[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][1] - Oy;
                GLfloat tx = white[i][j][0] - Ox;
                white[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                white[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][1] - Oy;
                GLfloat tx = yellow[i][j][0] - Ox;
                yellow[i][j][1] = (ty * cos(ag)) - (tx * sin(ag)) + Oy;
                yellow[i][j][0] = (ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_allZ, 1);

        f_allZ++;
    }
    else {
        f_allZ = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }

}
void turn_allz(int USELESS)
{
    if (f_allz < 9)
    {
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = red[i][j][1] - Oy;
                GLfloat tx = red[i][j][0] - Ox;
                red[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                red[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }
        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = green[i][j][1] - Oy;
                GLfloat tx = green[i][j][0] - Ox;
                green[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                green[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = orange[i][j][1] - Oy;
                GLfloat tx = orange[i][j][0] - Ox;
                orange[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                orange[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = blue[i][j][1] - Oy;
                GLfloat tx = blue[i][j][0] - Ox;
                blue[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                blue[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = white[i][j][1] - Oy;
                GLfloat tx = white[i][j][0] - Ox;
                white[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                white[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }

        for (int i = 0; i < 18; i++)
            for (int j = 0; j < 4; j++) {
                GLfloat ty = yellow[i][j][1] - Oy;
                GLfloat tx = yellow[i][j][0] - Ox;
                yellow[i][j][1] = (ty * cos(ag)) + (tx * sin(ag)) + Oy;
                yellow[i][j][0] = -(ty * sin(ag)) + (tx * cos(ag)) + Ox;
            }


        glutPostRedisplay();
        glutTimerFunc(10, turn_allz, 1);

        f_allz++;
    }
    else {
        f_allz = 0;
        if (Flag) AUTOMATIC_RECOVERY(++idx);
    }

}
void move_left(int USELESS) {
    if (f_left < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][0] = red[i][j][0] + l;
                orange[i][j][0] = orange[i][j][0] + l;
                green[i][j][0] = green[i][j][0] + l;
                blue[i][j][0] = blue[i][j][0] + l;
                white[i][j][0] = white[i][j][0] + l;
                yellow[i][j][0] = yellow[i][j][0] + l;
            }
        }
        Ox = Ox + l;
        f_left++;
        glutPostRedisplay();
        glutTimerFunc(10, move_left, 1);
    }
    else
        f_left = 0;
}
void move_right(int USELESS) {
    if (f_right < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][0] = red[i][j][0] - l;
                orange[i][j][0] = orange[i][j][0] - l;
                green[i][j][0] = green[i][j][0] - l;
                blue[i][j][0] = blue[i][j][0] - l;
                white[i][j][0] = white[i][j][0] - l;
                yellow[i][j][0] = yellow[i][j][0] - l;
            }
        }
        Ox = Ox - l;
        f_right++;
        glutPostRedisplay();
        glutTimerFunc(1, move_right, 1);
    }
    else
        f_right = 0;
}
void move_up(int USELESS) {
    if (f_up < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][1] = red[i][j][1] + l;
                orange[i][j][1] = orange[i][j][1] + l;
                green[i][j][1] = green[i][j][1] + l;
                blue[i][j][1] = blue[i][j][1] + l;
                white[i][j][1] = white[i][j][1] + l;
                yellow[i][j][1] = yellow[i][j][1] + l;

            }
        }
        Oy = Oy + l;
        f_up++;
        glutPostRedisplay();
        glutTimerFunc(1, move_up, 1);
    }
    else
        f_up = 0;
}
void move_down(int USELESS) {
    if (f_down < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][1] = red[i][j][1] - l;
                orange[i][j][1] = orange[i][j][1] - l;
                green[i][j][1] = green[i][j][1] - l;
                blue[i][j][1] = blue[i][j][1] - l;
                white[i][j][1] = white[i][j][1] - l;
                yellow[i][j][1] = yellow[i][j][1] - l;

            }
        }
        Oy = Oy - l;
        f_down++;
        glutPostRedisplay();
        glutTimerFunc(1, move_down, 1);
    }
    else
        f_down = 0;
}
void move_front(int USELESS) {
    if (f_front < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][2] = red[i][j][2] + l;
                orange[i][j][2] = orange[i][j][2] + l;
                green[i][j][2] = green[i][j][2] + l;
                blue[i][j][2] = blue[i][j][2] + l;
                white[i][j][2] = white[i][j][2] + l;
                yellow[i][j][2] = yellow[i][j][2] + l;

            }
        }
        Oz = Oz + l;
        f_front++;
        glutPostRedisplay();
        glutTimerFunc(1, move_front, 1);
    }
    else
        f_front = 0;
}
void move_behind(int USELESS) {
    if (f_behind < 10) {
        for (int i = 0; i < 18; i++) {
            for (int j = 0; j < 4; j++) {
                red[i][j][2] = red[i][j][2] - l;
                orange[i][j][2] = orange[i][j][2] - l;
                green[i][j][2] = green[i][j][2] - l;
                blue[i][j][2] = blue[i][j][2] - l;
                white[i][j][2] = white[i][j][2] - l;
                yellow[i][j][2] = yellow[i][j][2] - l;

            }
        }
        Oz = Oz - l;
        f_behind++;
        glutPostRedisplay();
        glutTimerFunc(1, move_behind, 1);
    }
    else
        f_behind = 0;
}
/******************************复原算法模块******************************/
void CORRECT_Y(int a[]) {
    if (cube.a[14] == 5) {
        printf("z\n");
        Aim_Cube.step.push('z');
        move_z();
    }
    if (cube.a[50] == 5) {
        printf("X\n");
        Aim_Cube.step.push('x');
        move_x();
    }
    if (cube.a[32] == 5) {
        printf("Z\n");
        Aim_Cube.step.push('Z');
        move_Z();
    }
    if (cube.a[41] == 5) {
        printf("x\n");
        Aim_Cube.step.push('x');
        move_x();
    }
    if (cube.a[23] == 5) {
        printf("X X\n");
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('X');
        move_X();
    }
}

void CORRECT_XZ(int a[]) {
    if (cube.a[50] == 1) {
        printf("Y\n");
        Aim_Cube.step.push('Y');
        move_Y();
    }
    if (cube.a[32] == 1) {
        printf("Y Y\n");
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();
    }
    if (cube.a[41] == 1) {
        printf("y\n");
        Aim_Cube.step.push('y');
        move_y();

    }
}
/********************第一层复原算法函数********************/
/**********白面十字复原**********/
//白橙棱块复原
void SOLVE_WHITE_ORANGE_RIDGE(int a[]) {

    //白棱块位于顶层
    if ((cube.a[4] == 4) && (cube.a[38] == 5)) {
        printf("C_O1 l u f U\n");

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[8] == 4) && (cube.a[11] == 5)) {
        printf("C_O2 U l u f U\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[8] == 5) && (cube.a[11] == 4)) {
        printf("C_O3 U\n");

        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[6] == 4) && (cube.a[53] == 5)) {
        printf("C_O4 U U l u f U\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[6] == 5) && (cube.a[53] == 4)) {
        printf("C_O5 U U\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[2] == 4) && (cube.a[35] == 5)) {
        printf("C_O6 u l u f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[2] == 5) && (cube.a[35] == 4)) {
        printf("C_O7 u\n");

        Aim_Cube.step.push('u');
        move_u();
    }

    //白棱块位于中间层
    else if ((cube.a[13] == 5) && (cube.a[40] == 4)) {
        printf("C_O8 L\n");

        Aim_Cube.step.push('L');
        move_L();
    }
    else if ((cube.a[13] == 4) && (cube.a[40] == 5)) {
        printf("C_O9 u f U\n");

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[49] == 5) && (cube.a[15] == 4)) {
        printf("C_O10 u F U\n");

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[49] == 4) && (cube.a[15] == 5)) {
        printf("C_O11 u u R U U\n");

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[33] == 5) && (cube.a[51] == 4)) {
        printf("C_O12 U U r U U\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[33] == 4) && (cube.a[51] == 5)) {
        printf("C_O13 U B u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 5) && (cube.a[31] == 4)) {
        printf("C_O14 U b u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 4) && (cube.a[31] == 5)) {
        printf("C_O15 l\n");

        Aim_Cube.step.push('l');
        move_l();
    }
    //白棱块位于底层
    else if ((cube.a[22] == 5) && (cube.a[44] == 4)) {
        printf("C_O16 L L\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if ((cube.a[22] == 4) && (cube.a[44] == 5)) {
        printf("C_O17 L u f U\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[20] == 5) && (cube.a[17] == 4)) {
        printf("C_O18 D L L\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if ((cube.a[20] == 4) && (cube.a[17] == 5)) {
        printf("C_O19 D L u f U\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[24] == 5) && (cube.a[47] == 4)) {
        printf("C_O20 D D L L\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if ((cube.a[24] == 4) && (cube.a[47] == 5)) {
        printf("C_O21 D D L u f U\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[26] == 5) && (cube.a[29] == 4)) {
        printf("C_O22 d L L\n");

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if ((cube.a[26] == 4) && (cube.a[29] == 5)) {
        printf("C_O23 d L u f U\n");

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
    }

}
//白绿棱块复原
void SOLVE_WHITE_GREEN_RIDGE(int a[]) {

    //白棱块位于顶层
    if ((cube.a[8] == 1) && (cube.a[11] == 5)) {
        printf("C_G1 f u R U\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[6] == 1) && (cube.a[53] == 5)) {
        printf("C_G2 r F\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
    }
    else if ((cube.a[6] == 5) && (cube.a[53] == 1)) {
        printf("C_G3 r u R U\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[2] == 1) && (cube.a[35] == 5)) {
        printf("C_G4 b u r U\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();;
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[2] == 5) && (cube.a[35] == 1)) {
        printf("C_G5 b U U B U U\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
    }
    //白棱块位于中间层
    else if ((cube.a[13] == 5) && (cube.a[40] == 1)) {
        printf("C_G6 U L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[13] == 1) && (cube.a[40] == 5)) {
        printf("C_G7 U u f U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[49] == 5) && (cube.a[15] == 1)) {
        printf("C_G8 U u F U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[49] == 1) && (cube.a[15] == 5)) {
        printf("C_G9 U u u R U U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[33] == 5) && (cube.a[51] == 1)) {
        printf("C_G10 U U U r U U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[33] == 1) && (cube.a[51] == 5)) {
        printf("C_G11 U U B u u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 5) && (cube.a[31] == 1)) {
        printf("C_G12 U U b u u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 1) && (cube.a[31] == 5)) {
        printf("C_G13 U l u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();

        Aim_Cube.step.push('u');
        move_u();
    }
    //白棱块位于底层
    else if ((cube.a[22] == 5) && (cube.a[44] == 1)) {
        printf("C_G14 d F F\n");

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
    }
    else if ((cube.a[22] == 1) && (cube.a[44] == 5)) {
        printf("C_G15 U L u f U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[20] == 5) && (cube.a[17] == 1)) {
        printf("C_G16 F F\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
    }
    else if ((cube.a[20] == 1) && (cube.a[17] == 5)) {
        printf("C_G17 U D L u f U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[24] == 5) && (cube.a[47] == 1)) {
        printf("C_G18 D F F\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
    }
    else if ((cube.a[24] == 1) && (cube.a[47] == 5)) {
        printf("C_G19 U D D L u f U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[26] == 5) && (cube.a[29] == 1)) {
        printf("C_G20 d d F F\n");

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
    }
    else if ((cube.a[26] == 1) && (cube.a[29] == 5)) {
        printf("C_G21 U d L u f U u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
    }
}
//白红棱块复原
void SOLVE_WHITE_RED_RIDGE(int a[]) {
    //白棱块位于顶层
    if ((cube.a[6] == 2) && (cube.a[53] == 5)) {
        printf("C_R1 r U F u\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[2] == 2) && (cube.a[35] == 5)) {
        printf("C_R2 b r\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('r');
        move_r();

    }
    else if ((cube.a[2] == 5) && (cube.a[35] == 2)) {
        printf("C_R3 b u B U\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('U');
        move_U();
    }
    //白棱块位于中间层
    else if ((cube.a[13] == 5) && (cube.a[40] == 2)) {
        printf("C_R4 U U L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[13] == 2) && (cube.a[40] == 5)) {
        printf("C_R5 U U u f U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[49] == 5) && (cube.a[15] == 2)) {
        printf("C_R6 U U u F U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[49] == 2) && (cube.a[15] == 5)) {
        printf("C_R7 U U u u R U U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[33] == 5) && (cube.a[51] == 2)) {
        printf("C_R8 U U u u r U U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[33] == 2) && (cube.a[51] == 5)) {
        printf("C_R9 U U U B u u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 5) && (cube.a[31] == 2)) {
        printf("C_R10 U U U b u u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[42] == 2) && (cube.a[31] == 5)) {
        printf("C_R11 U U l u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    //白棱块位于底层
    else if ((cube.a[22] == 5) && (cube.a[44] == 2)) {
        printf("C_R12 U U L L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[22] == 2) && (cube.a[44] == 5)) {
        printf("C_R13 U U L u f U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[20] == 5) && (cube.a[17] == 2)) {
        printf("C_R14 U U D L L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[20] == 2) && (cube.a[17] == 5)) {
        printf("C_R15 U U D L u f U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[24] == 5) && (cube.a[47] == 2)) {
        printf("C_R16 U U D D L L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[24] == 2) && (cube.a[47] == 5)) {
        printf("C_R17 U U D D L u f U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[26] == 5) && (cube.a[29] == 2)) {
        printf("C_R18 U U d L L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if ((cube.a[26] == 2) && (cube.a[29] == 5)) {
        printf("C_R19 U U d L u f U u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
}
//白蓝棱块复原
void SOLVE_WHITE_BLUE_RIDGE(int a[]) {
    //白棱块位于顶层
    if ((cube.a[2] == 3) && (cube.a[35] == 5)) {
        printf("C_B1 B u l U\n");

        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
    }
    //白棱块位于中间层
    else if ((cube.a[13] == 5) && (cube.a[40] == 3)) {
        printf("C_B2 u L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[13] == 3) && (cube.a[40] == 5)) {
        printf("C_B3 u u f U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[49] == 5) && (cube.a[15] == 3)) {
        printf("C_B4 u u F U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[49] == 3) && (cube.a[15] == 5)) {
        printf("C_B5 u u u R U U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[33] == 5) && (cube.a[51] == 3)) {
        printf("C_B6 u U U r U U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[33] == 3) && (cube.a[51] == 5)) {
        printf("C_B7 u U B u U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[42] == 5) && (cube.a[31] == 3)) {
        printf("C_B8 u U b u U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[42] == 3) && (cube.a[31] == 5)) {
        printf("C_B9 u l U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('l');
        move_l();

        Aim_Cube.step.push('U');
        move_U();

    }
    //白棱块位于底层
    else if ((cube.a[22] == 5) && (cube.a[44] == 3)) {
        printf("C_B10 u L L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[22] == 3) && (cube.a[44] == 5)) {
        printf("C_B11 u L u f U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[20] == 5) && (cube.a[17] == 3)) {
        printf("C_B12 u D L L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[20] == 3) && (cube.a[17] == 5)) {
        printf("C_B13 u D L u f U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[24] == 5) && (cube.a[47] == 3)) {
        printf("C_B14 u D D L L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if ((cube.a[24] == 3) && (cube.a[47] == 5)) {
        printf("C_B15 u D D L u f U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[26] == 5) && (cube.a[29] == 3)) {
        printf("C_B16 u d L L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if ((cube.a[26] == 3) && (cube.a[29] == 5)) {
        printf("C_B17 u d L u f U U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('U');
        move_U();
    }
}
/**********白面角块复原*********/
//橙绿角块复原
void SOLVE_ORANGE_GREEN_CORNOR(int a[]) {
    //角块位于上层
    if (cube.a[7] == 4 && cube.a[37] == 1 && cube.a[10] == 5) {
        printf("C_OG1 F D f d F D f\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[7] == 1 && cube.a[37] == 5 && cube.a[10] == 4) {
        printf("C_OG2 l d L D l d L\n");

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[9] == 4 && cube.a[12] == 1 && cube.a[52] == 5) {
        printf("C_OG3 r D R F D f\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[9] == 1 && cube.a[12] == 5 && cube.a[52] == 4) {
        printf("C_OG4 r d R D l d L\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[9] == 5 && cube.a[12] == 4 && cube.a[52] == 1) {
        printf("C_OG5 r D R l d L\n ");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[3] == 4 && cube.a[54] == 1 && cube.a[36] == 5) {
        printf("C_OG6 b D B D F D f\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[3] == 1 && cube.a[54] == 5 && cube.a[36] == 4) {
        printf("C_OG7 b d B D D l d L\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[3] == 5 && cube.a[54] == 4 && cube.a[36] == 1) {
        printf("C_OG8 b D B D l d L\n");

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[1] == 4 && cube.a[34] == 1 && cube.a[39] == 5) {
        printf("C_OG9 L D l d d F D f\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[1] == 1 && cube.a[34] == 5 && cube.a[39] == 4) {
        printf("C_OG10 B d b D F d f\n");

        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[1] == 5 && cube.a[34] == 4 && cube.a[39] == 1) {
        printf("C_OG11 L d l d F D f\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    //角块位于下层
    else if (cube.a[19] == 4 && cube.a[43] == 5 && cube.a[16] == 1) {
        printf("C_OG12 D F d f\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[19] == 1 && cube.a[43] == 4 && cube.a[16] == 5) {
        printf("C_OG13 F D f\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[19] == 5 && cube.a[43] == 1 && cube.a[16] == 4) {
        printf("C_OG14 F D D f d F D f\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[21] == 4 && cube.a[18] == 5 && cube.a[46] == 1) {
        printf("C_OG15 D D F d f\n");

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[21] == 1 && cube.a[18] == 4 && cube.a[46] == 5) {
        printf("C_OG16 D F D f\n");

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[21] == 5 && cube.a[18] == 1 && cube.a[46] == 4) {
        printf("C_OG17 D F D D f d F D f\n");

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[27] == 4 && cube.a[48] == 5 && cube.a[30] == 1) {
        printf("C_OG18 D D D F d f\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[27] == 1 && cube.a[48] == 4 && cube.a[30] == 5) {
        printf("C_OG19 D D F D f\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[27] == 5 && cube.a[48] == 1 && cube.a[30] == 4) {
        printf("C_OG20 D D F D D f d F D f\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[25] == 4 && cube.a[28] == 5 && cube.a[45] == 1) {
        printf("C_OG21 d D F d f\n");

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[25] == 1 && cube.a[28] == 4 && cube.a[45] == 5) {
        printf("C_OG22 d F D f\n");

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[25] == 5 && cube.a[28] == 1 && cube.a[45] == 4) {
        printf("C_OG23 d F D D f d F D f\n");

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
    }

}
//绿红角块复原
void SOLVE_GREEN_RED_CORNOR(int a[]) {
    //角块位于上层
    if (cube.a[9] == 1 && cube.a[12] == 2 && cube.a[52] == 5) {
        printf("C_GR1 U F D f d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[9] == 2 && cube.a[12] == 5 && cube.a[52] == 1) {
        printf("C_GR2 U l d L D l d L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[3] == 1 && cube.a[54] == 2 && cube.a[36] == 5) {
        printf("C_GR3 U r D R F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[3] == 2 && cube.a[54] == 5 && cube.a[36] == 1) {
        printf("C_GR4 U r d R D l d L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[3] == 5 && cube.a[54] == 1 && cube.a[36] == 2) {
        printf("C_GR5 U r D R l d L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 1 && cube.a[34] == 2 && cube.a[39] == 5) {
        printf("C_GR6 U b D B D F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 2 && cube.a[34] == 5 && cube.a[39] == 1) {
        printf("C_GR7 U b d B D D l d L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 5 && cube.a[34] == 1 && cube.a[39] == 2) {
        printf("C_GR8 U b D B D l d L u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();

    }
    //角块位于下层
    else if (cube.a[19] == 1 && cube.a[43] == 5 && cube.a[16] == 2) {
        printf("C_GR9 U D F d f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[19] == 2 && cube.a[43] == 1 && cube.a[16] == 5) {
        printf("C_GR10 U F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[19] == 5 && cube.a[43] == 2 && cube.a[16] == 1) {
        printf("C_GR11 U F D D f d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 1 && cube.a[18] == 5 && cube.a[46] == 2) {
        printf("C_GR12 U D D F d f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 2 && cube.a[18] == 1 && cube.a[46] == 5) {
        printf("C_GR13 U D F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 5 && cube.a[18] == 2 && cube.a[46] == 1) {
        printf("C_GR14 U D F D D f d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 1 && cube.a[48] == 5 && cube.a[30] == 2) {
        printf("C_GR15 U D D D F d f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 2 && cube.a[48] == 1 && cube.a[30] == 5) {
        printf("C_GR16 U D D F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 5 && cube.a[48] == 2 && cube.a[30] == 1) {
        printf("C_GR17 U D D F D D f d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 1 && cube.a[28] == 5 && cube.a[45] == 2) {
        printf("C_GR18 U d D F d f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 2 && cube.a[28] == 1 && cube.a[45] == 5) {
        printf("C_GR19 U d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 5 && cube.a[28] == 2 && cube.a[45] == 1) {
        printf("C_GR20 U d F D D f d F D f u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
    }
}
//红蓝角块复原
void SOLVE_RED_BLUE_CORNOR(int a[]) {
    //角块位于上层
    if (cube.a[3] == 2 && cube.a[54] == 3 && cube.a[36] == 5) {
        printf("C_RB1 U U F D f d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();


        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[3] == 3 && cube.a[54] == 5 && cube.a[36] == 2) {
        printf("C_RB2 U U l d L D l d L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 2 && cube.a[34] == 3 && cube.a[39] == 5) {
        printf("C_RB3 U U r D R F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();


        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 3 && cube.a[34] == 5 && cube.a[39] == 2) {
        printf("C_RB4 U U r d R D l d L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();


        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();

    }
    else if (cube.a[1] == 5 && cube.a[34] == 2 && cube.a[39] == 3) {
        printf("C_RB5 U U r D R l d L u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();


        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();

    }
    //角块位于下层
    else if (cube.a[19] == 2 && cube.a[43] == 5 && cube.a[16] == 3) {
        printf("C_RB6 U U D F d f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[19] == 3 && cube.a[43] == 2 && cube.a[16] == 5) {
        printf("C_RB7 U U F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[19] == 5 && cube.a[43] == 3 && cube.a[16] == 2) {
        printf("C_RB8 U U F D D f d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 2 && cube.a[18] == 5 && cube.a[46] == 3) {
        printf("C_RB9 U U D D F d f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 3 && cube.a[18] == 2 && cube.a[46] == 5) {
        printf("C_RB10 U U D F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[21] == 5 && cube.a[18] == 3 && cube.a[46] == 2) {
        printf("C_RB11 U U D F D D f d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 2 && cube.a[48] == 5 && cube.a[30] == 3) {
        printf("C_RB12 U U D D D F d f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 3 && cube.a[48] == 2 && cube.a[30] == 5) {
        printf("C_RB13 U U D D F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[27] == 5 && cube.a[48] == 3 && cube.a[30] == 2) {
        printf("C_RB14 U U D D F D D f d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 2 && cube.a[28] == 5 && cube.a[45] == 3) {
        printf("C_RB15 U U d D F d f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 3 && cube.a[28] == 2 && cube.a[45] == 5) {
        printf("C_RB16 U U d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
    else if (cube.a[25] == 5 && cube.a[28] == 3 && cube.a[45] == 2) {
        printf("C_RB17 U U d F D D f d F D f u u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
    }
}
//蓝橙角块复原
void SOLVE_BLUE_ORANDE_CORNOR(int a[]) {
    //角块位于上层
    if (cube.a[1] == 3 && cube.a[34] == 4 && cube.a[39] == 5) {
        printf("C_BO1 u F D f d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[1] == 4 && cube.a[34] == 5 && cube.a[39] == 3) {
        printf("C_BO2 u l d L D l d L U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('U');
        move_U();
    }
    //角块位于下层
    else if (cube.a[19] == 3 && cube.a[43] == 5 && cube.a[16] == 4) {
        printf("C_BO3 u D F d f U\n");


        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if (cube.a[19] == 4 && cube.a[43] == 3 && cube.a[16] == 5) {
        printf("C_BO4 u F D f U\n");

        Aim_Cube.step.push('u');
        move_u();;

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[19] == 5 && cube.a[43] == 4 && cube.a[16] == 3) {
        printf("C_BO5 u F D D f d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[21] == 3 && cube.a[18] == 5 && cube.a[46] == 4) {
        printf("C_BO6 u D D F d f U\n");


        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[21] == 4 && cube.a[18] == 3 && cube.a[46] == 5) {
        printf("C_BO7 u D F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[21] == 5 && cube.a[18] == 4 && cube.a[46] == 3) {
        printf("C_BO8 u D F D D f d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if (cube.a[27] == 3 && cube.a[48] == 5 && cube.a[30] == 4) {
        printf("C_BO9 u D D D F d f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[27] == 4 && cube.a[48] == 3 && cube.a[30] == 5) {
        printf("C_BO10 u D D F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();
    }
    else if (cube.a[27] == 5 && cube.a[48] == 4 && cube.a[30] == 3) {
        printf("C_BO11 u D D F D D f d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[25] == 3 && cube.a[28] == 5 && cube.a[45] == 4) {
        printf("C_BO12 u d D F d f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[25] == 4 && cube.a[28] == 3 && cube.a[45] == 5) {
        printf("C_BO13 u d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
    else if (cube.a[25] == 5 && cube.a[28] == 4 && cube.a[45] == 3) {
        printf("C_BO14 u d F D D f d F D f U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('U');
        move_U();

    }
}
/********************第二层复原算法函数********************/
//橙绿棱块复原
void SOLVE_ORANGE_GREEN_RIDGE(int a[]) {

    //棱块位于底层
    if (cube.a[44] == 4 && cube.a[22] == 1) {
        printf("F_OG1 D F d f d l D L\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

    }
    else if (cube.a[17] == 4 && cube.a[20] == 1) {
        printf("F_OG2 D D F d f d l D L\n");

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[47] == 4 && cube.a[24] == 1) {
        printf("F_OG3 D D D F d f d l D L\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[29] == 4 && cube.a[26] == 1) {
        printf("F_OG4 d D F d f d l D L\n");

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[17] == 1 && cube.a[20] == 4) {
        printf("F_OG5 d l D L D F d f\n");

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();


    }
    else if (cube.a[47] == 1 && cube.a[24] == 4) {
        printf("F_OG6 D d l D L D F d f\n");

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

    }
    else if (cube.a[29] == 1 && cube.a[26] == 4) {
        printf("F_OG7 D D d l D L D F d f\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

    }
    else if (cube.a[44] == 1 && cube.a[22] == 4) {
        printf("F_OG8 d d l D L D F d f\n");

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

    }
    //棱块位于中间层
    else if (cube.a[40] == 1 && cube.a[13] == 4) {
        printf("F_OG9 D F d f d l D L d F d f d l D L\n");

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[15] == 1 && cube.a[49] == 4) {
        printf("F_OG10 Y D F d f d l D L y D d F d f d l D L\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[51] == 1 && cube.a[33] == 4) {
        printf("F_OG11 Y Y D F d f d l D L y y D D d F d f d l D L\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[31] == 1 && cube.a[42] == 4) {
        printf("F_OG12 y D F d f d l D L Y d d F d f d l D L\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
    }
    else if (cube.a[15] == 4 && cube.a[49] == 1) {
        printf("F_OG13 Y D F d f d l D L y D l D L D F d f\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[51] == 4 && cube.a[33] == 1) {
        printf("F_OG14 Y Y D F d f d l D L y y D D l D L D F d f\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
    else if (cube.a[31] == 4 && cube.a[42] == 1) {
        printf("F_OG15 y D F d f d l D L Y D D D l D L D F d f\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
    }
}
//绿红棱块复原
void SOLVE_GREEN_RED_RIDGE(int a[]) {
    //棱块位于底层
    if (cube.a[17] == 1 && cube.a[20] == 2) {
        printf("F_GR1 Y D F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[47] == 1 && cube.a[24] == 2) {
        printf("F_GR2 Y D D F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[29] == 1 && cube.a[26] == 2) {
        printf("F_GR3 Y D D D F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[44] == 1 && cube.a[22] == 2) {
        printf("F_GR4 Y d D F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[47] == 2 && cube.a[24] == 1) {
        printf("F_GR5 Y d l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[29] == 2 && cube.a[26] == 1) {
        printf("F_GR6 Y D d l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[44] == 2 && cube.a[22] == 1) {
        printf("F_GR7 Y D D d l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[17] == 2 && cube.a[20] == 1) {
        printf("F_GR8 Y d d l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }
    //棱块位于中间层
    else if (cube.a[15] == 2 && cube.a[49] == 1) {
        printf("F_GR9 Y D F d f d l D L d F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

    }
    else if (cube.a[51] == 2 && cube.a[33] == 1) {
        printf("F_GR10 Y Y D F d f d l D L y D d F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[31] == 2 && cube.a[42] == 1) {
        printf("F_GR11 Y Y Y D F d f d l D L y y D D d F d f d l D L y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[51] == 1 && cube.a[33] == 2) {
        printf("F_GR12 Y Y D F d f d l D L y D l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[31] == 1 && cube.a[42] == 2) {
        printf("F_GR13 Y Y Y D F d f d l D L y y D D l D L D F d f y\n");

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
    }

}
//红蓝棱块复原
void SOLVE_RED_BLUE_RIDGE(int a[]) {
    //棱块位于底层
    if (cube.a[47] == 2 && cube.a[24] == 3) {
        printf("F_RB1 Y Y D F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[29] == 2 && cube.a[26] == 3) {
        printf("F_RB2 Y Y D D F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[44] == 2 && cube.a[22] == 3) {
        printf("F_RB3 Y Y D D D F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[17] == 2 && cube.a[20] == 3) {
        printf("F_RB4 Y Y d D F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[29] == 3 && cube.a[26] == 2) {
        printf("F_RB5 Y Y d l D L D F d f y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[44] == 3 && cube.a[22] == 2) {
        printf("F_RB6 Y Y D d l D L D F d f y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[17] == 3 && cube.a[20] == 2) {
        printf("F_RB7 Y Y D D d l D L D F d f y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[47] == 3 && cube.a[24] == 2) {
        printf("F_RB8 Y Y d d l D L D F d f y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    //棱块位于中间层
    else if (cube.a[51] == 3 && cube.a[33] == 2) {
        printf("F_RB9 Y Y D F d f d l D L d F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();

    }
    else if (cube.a[31] == 3 && cube.a[42] == 2) {
        printf("F_RB10 Y Y Y D F d f d l D L y D d F d f d l D L y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }
    else if (cube.a[31] == 2 && cube.a[42] == 3) {
        printf("F_RB11 Y Y Y D F d f d l D L y D l D L D F d f y y\n");

        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('Y');
        move_Y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('y');
        move_y();
    }

}
//蓝橙棱块复原
void SOLVE_BLUE_ORANGE_RIDGE(int a[]) {
    //棱块位于底层
    if (cube.a[29] == 3 && cube.a[26] == 4) {
        printf("F_BO1 y D F d f d l D L Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[44] == 3 && cube.a[22] == 4) {
        printf("F_BO2 y D D F d f d l D L Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();

    }
    else if (cube.a[17] == 3 && cube.a[20] == 4) {
        printf("F_BO3 y D D D F d f d l D L Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[47] == 3 && cube.a[24] == 4) {
        printf("F_BO4 y d D F d f d l D L Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[44] == 4 && cube.a[22] == 3) {
        printf("F_BO5 y d l D L D F d f Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[17] == 4 && cube.a[20] == 3) {
        printf("F_BO6 y D d l D L D F d f Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[47] == 4 && cube.a[24] == 3) {
        printf("F_BO7 y D D d l D L D F d f Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('D');
        move_D();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    else if (cube.a[29] == 4 && cube.a[26] == 3) {
        printf("F_BO8 y d d l D L D F d f Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('d');
        move_d();

        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();

        Aim_Cube.step.push('Y');
        move_Y();
    }
    //棱块位于中间层
    else if (cube.a[31] == 4 && cube.a[42] == 3) {
        printf("F_BO9 y D F d f d l D L d F d f d l D L Y\n");

        Aim_Cube.step.push('y');
        move_y();

        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('L');
        move_L();

        Aim_Cube.step.push('Y');
        move_Y();

    }
}
/********************第三层复原算法函数********************/
//Orientation of Last Layer
void SOLVE_ORIENT(int a[]) {
    //将魔方上下翻转便于观察
    Aim_Cube.step.push('x');
    move_x();
    Aim_Cube.step.push('x');
    move_x();
    printf("x x\n");
    //7种顶面十字情况
    //情况1
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_1F R U U r u R U r u R u r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_1R U R U U r u R U r u R u r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
    }
    //情况2
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_2F R u u r r u R R u r r u u R\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_2R U R u u r r u R R u r r u u R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_2B U U R u u r r u R R u r r u u R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_2L u R u u r r u R R u r r u u R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
    }
    //情况3
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_3F R R d r U U R D r U U r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_3R U R R d r U U R D r U U r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_3B U U R R d r U U R D r U U r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_3B u R R d r U U R D r U U r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
    }
    //情况4
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_4F z l U r u Z L f R F\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_4R U z l U r u Z L f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_4B U U z l U r u Z L f R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_4L u z l U r u Z L f R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况5
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_5F f r F z l U R u Z L\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_5R U f r F z l U R u Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_5B U U f r F z l U R u Z L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_5L u f r F z l U R u Z L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    //情况6
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_6F R U r U R U U r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_6R U R U r U R U U r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_6B U U R U r U R U U r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_6L u R U r U R U U r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况7
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_7F L u l u L u u l\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_7R U L u l u L u u l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_7B U U L u l u L u u l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_7L u L u l u L u u l\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();

    }
    //8种顶面单块情况
    //情况8
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_8F R u u r r f R F U U r f R F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_8R U R u u r r f R F U U r f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况9
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_9F f R U r u x F B R U r u X b\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_9R U f R U r u x F B R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_9B U U f R U r u x F B R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_9L u f R U r u x F B R U r u X b\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();

    }
    //情况10
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_10F f u R u r u r f R F U U F\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_10R U f u R u r u r f R F U U F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('F');
        move_F();


    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_10B U U f u R u r u r f R F U U F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_10L u f u R u r u r f R F U U F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('F');
        move_F();


    }
    //情况11
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_11F F U L U l U l F L f u u f\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_11R U F U L U l U l F L f u u f\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_11B U U F U L U l U l F L f u u f\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_11L u F U L U l U l F L f u u f\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
    }
    //情况12
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_12F R U r U r f R F U U r f R F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_12R U R U r U r f R F U U r f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_12B U U R U r U r f R F U U r f R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_12L u R U r U r f R F U U r f R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况13
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_13F z l U r U R u u Z L Z L u R u r u u z l\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_13R U z l U r U R u u Z L Z L u R u r u u z l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_13B U U z l U r U R u u Z L Z L u R u r u u z l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_13l u z l U r U R u u Z L Z L u R u r u u z l\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况14
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_14F Z L R U R U r u z l r r f R F\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();


    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_14R U Z L R U R U r u z l r r f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();


    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_14B U U Z L R U R U r u z l r r f R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();


    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_14L u Z L R U R U r u z l r r f R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();


    }
    //情况15
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_15F Z L R U R U r u z l r z l r U R u Z L\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    //15种顶面一字情况
    //情况16
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_16F x B R U r u R U r u X b\n");

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_16R U x B R U r u R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_16B U U x B R U r u R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_16L u x B R U r u R U r u X b\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    //情况17
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_17F Z L u z l u r U R u r U R Z L U z l\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_17R U Z L u z l u r U R u r U R Z L U z l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况18
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_18F r u R u r U y r U R B Y\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_18R U r u R u r U y r U R B Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_18B U U r u R u r U y r U R B Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_18L u r u R u r U y r U R B Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //情况19
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_19F R u u r r u R u r u u f R F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_19R U R u u r r u R u r u u f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况20
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_20F r f R U r u F U R\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_20R U r f R U r u F U R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_20B U U r f R U r u F U R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_20L u r f R U r u F U R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况21
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_21F l F L u l U f u L\n");

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_21R U l F L u l U f u L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_21B U U l F L u l U f u L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_21L u l F L u l U f u L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();

    }
    //情况22
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_22F R U r u z l r U R u Z L\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_22R U R U r u z l r U R u Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    //情况23
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_23F z l u Z L u z l U Z L Y L U l y\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_23R U z l u Z L u z l U Z L Y L U l y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_23B U U z l u Z L u z l U Z L Y L U l y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_23L u z l u Z L u z l U Z L Y L U l y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('y');
        move_y();

    }
    //情况24
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_24F z r U Z R U z r u Z R y R u r Y\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_24R U z r U Z R U z r u Z R y R u r Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_24B U U z r U Z R U z r u Z R y R u r Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_24L u z r U Z R U z r u Z R y R u r Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //情况25
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_25F z l U Z L R U r u z l u Z L\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();


    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_25R U z l U Z L R U r u z l u Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();


    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[8] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_25B U U z l U Z L R U r u z l u Z L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();


    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_25L u z l U Z L R U r u z l u Z L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();


    }
    //情况26
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_26F z r u Z R L u l U z r U Z R\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_26R U z r u Z R L u l U z r U Z R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_26B U U z r u Z R L u l U z r U Z R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_26L u z r u Z R L u l U z r U Z R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况27 
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_27F f R U r u F\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_27R U f R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_27B U U f R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_27L u f R U r u F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况28
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_28F R U r u r f R F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_28R U R U r u r f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_28B U U R U r u r f R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_28L u R U r u r f R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况29
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_29F r u r f R F U R\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_29R U r u r f R F U R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_29B U U r u r f R F U R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_29L u r u r f R F U R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况30 
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_30F R U r u y Z L u R U z l r Y\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_30R U R U r u y Z L u R U z l r Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_30B U U R U r u y Z L u R U z l r Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_30L u R U r u y Z L u R U z l r Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //6种拐角情况
    //情况31
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_31F f R U r u R U r u F\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_31R U f R U r u R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_31B U U f R U r u R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_31L u f R U r u R U r u F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况32
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_32F F L u l U L u l U f\n");

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_32R U F L u l U L u l U f\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_32B U U F L u l U L u l U f\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_32L u F L u l U L u l U f\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    //情况33
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_33F Z L U z l z l u Z L Z L u z l z l U Z L\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_33R U Z L U z l z l u Z L Z L u z l z l U Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_33B U U Z L U z l z l u Z L Z L u z l z l U Z L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_33L u Z L U z l z l u Z L Z L u z l z l U Z L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
    }
    //情况34
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_34F Z R u z r z r U Z R Z R U z r z r u Z R\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_34R U Z R u z r z r U Z R Z R U z r z r u Z R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_34B U U Z R u z r z r U Z R Z R U z r z r u Z R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_34L u Z R u z r z r U Z R Z R U z r z r u Z R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
    }
    //情况35
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_35F Z L u R u r U R u r U U z l\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_35R U Z L u R u r U R u r U U z l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_35B U U Z L u R u r U R u r U U z l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_35L u Z L u R u r U R u r U U z l\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况36
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_36F Z R U L U l u L U l u u z r\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_36R U Z R U L U l u L U l u u z r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_36B U U Z R U L U l u L U l u u z r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_36L u Z R U L U l u L U l u u z r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    //21种拐角衍生情况
    //情况37
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_37F R u u r z l r u R u r U Z L R\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_37R U R u u r z l r u R u r U Z L R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_37B U U R u u r z l r u R u r U Z L R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_37L u R u u r z l r u R u r U Z L R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况38
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_38F L U U l z l r U L U l u Z L R\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_38R U L U U l z l r U L U l u Z L R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_38B U U L U U l z l r U L U l u Z L R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_38L u L U U l z l r U L U l u Z L R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况39
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_39F z l U U r u R u Z L\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_39R U z l U U r u R u Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_39B U U z l U U r u R u Z L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_39L u z l U U r u R u Z L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    //情况40
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_40F z r u u l U L U Z R\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_40R U z r u u l U L U Z R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_40B U U z r u u l U L U Z R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_40L u z r u u l U L U Z R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况41
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_41F R u u r r f R F R u u r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_41R U R u u r r f R F R u u r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_41B U U R u u r r f R F R u u r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_41L u R u u r r f R F R u u r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况42
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_42F f r F R U R u r\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_42R U f r F R U R u r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_42B U U f r F R U R u r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_42L u f r F R U R u r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况43
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_43F R U X b L u l U x B r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_43R U R U X b L u l U x B r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_43B U U R U X b L u l U x B r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_43L u R U X b L u l U x B r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况44
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_44F L u x B R U r u X b l\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_44R U L u x B R U r u X b l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_44B U U L u x B R U r u X b l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_44L u L u x B R U r u X b l\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况45
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_45F X b L u l U x B\n");

        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_45R U X b L u l U x B\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_45B U U X b L u l U x B\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_45L u X b L u l U x B\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();

    }
    //情况46
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_46F x B R U r u X b\n");

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_46R U x B R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_46B U U x B R U r u X b\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_46L u x B R U r u X b\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
    }
    //情况47
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_47F Z L u R u r u u z l\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_47R U Z L u R u r u u z l\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_47B U U Z L u R u r u u z l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_47L u Z L u R u r u u z l\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况48
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_48F Z R U L U l U U z r\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_48R U Z R U L U l U U z r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_48B U U Z R U L U l U U z r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_48L u Z R U L U l U U z r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况49
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_49F z l r r u R u r u u R u R Z L\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_49R U z l r r u R u r u u R u R Z L\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_49B U U z l r r u R u r u u R u R Z L\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_49L u z l r r u R u r u u R u R Z L\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();

    }
    //情况50
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_50F z r l l U L U l U U L U L Z R\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_50R U z r l l U L U l U U L U L Z R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_50B U U z r l l U L U l U U L U L Z R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[52] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_50L u z r l l U L U l U U L U L Z R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();

    }
    //情况51
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_51F r f R F R u u r u y r u R Y\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_51R U r f R F R u u r u y r u R Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_51B U U r f R F R u u r u y r u R Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_51L u r f R F R u u r u y r u R Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //情况52
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_52F l F L f L U U l U Y l U L y\n");

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_52R U l F L f L U U l U Y l U L y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_52B U U l F L f L U U l U Y l U L y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_52L u l F L f L U U l U Y l U L y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('y');
        move_y();

    }
    //情况53
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_53F R U r U R U U r f R U r u F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_53R U R U r U R U U r f R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_53B U U R U r U R U U r f R U r u F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_53L u R U r U R U U r f R U r u F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况54
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_54F L u l u L u u l F L u l U f\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_54R U L u l u L u u l F L u l U f\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_54B U U L u l u L u u l F L u l U f\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_54L u L u l u L u u l F L u l U f\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('f');
        move_f();

    }
    //情况55
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[54] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[10] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_55F R u u r r f f z l u R u u Z L f\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[34] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[52] == 6) {
        printf("OLL_55R U R u u r r f f z l u R u u Z L f\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[36] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[37] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_55B U U R u u r r f f z l u R u u Z L f\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();

    }
    if (cube.a[39] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[12] == 6) {
        printf("OLL_55L u R u u r r f f z l u R u u Z L f\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('f');
        move_f();

    }
    //情况56
    if (cube.a[39] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[12] == 6) {
        printf("OLL_56F L U U l l F F z r U L U U Z R F\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[54] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[10] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_56R U L U U l l F F z r U L U U Z R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[52] == 6) {
        printf("OLL_56B U U L U U l l F F z r U L U U Z R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[36] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[37] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_56L u L U U l l F F z r U L U U Z R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况57
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_57F Z L u R U z l r u r U R\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[35] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[8] == 6 && cube.a[9] == 6) {
        printf("OLL_57R U Z L u R U z l r u r U R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[38] == 6 && cube.a[5] == 6 && cube.a[6] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_57B U U Z L u R U z l r u r U R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[1] == 6 && cube.a[2] == 6 && cube.a[3] == 6 &&
        cube.a[4] == 6 && cube.a[5] == 6 && cube.a[53] == 6 &&
        cube.a[7] == 6 && cube.a[11] == 6 && cube.a[9] == 6) {
        printf("OLL_57L u Z L u R U z l r u r U R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();

    }
}
//Permutation of Last Layer
void SOLVE_PERMUT(int a[]) {
    //4种基本情况
    //情况1
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[11] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[53] &&
        cube.a[10] == cube.a[38] && cube.a[10] == cube.a[12]) {
        printf("PLL_1F R u R U R U R u r u r r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[11] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[38] &&
        cube.a[10] == cube.a[35] && cube.a[10] == cube.a[12]) {
        printf("PLL_1R U R u R U R U R u r u r r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[38] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[35] &&
        cube.a[10] == cube.a[11] && cube.a[10] == cube.a[12]) {
        printf("PLL_1B U U R u R U R U R u r u r r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[11] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[53] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[35] &&
        cube.a[10] == cube.a[38] && cube.a[10] == cube.a[12]) {
        printf("PLL_1L u R u R U R U R u r u r r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况2
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[38] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[11] &&
        cube.a[10] == cube.a[53] && cube.a[10] == cube.a[12]) {
        printf("PLL_2F R R U R U r u r u r U r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[11] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[35] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[38] &&
        cube.a[10] == cube.a[53] && cube.a[10] == cube.a[12]) {
        printf("PLL_2R U R R U R U r u r u r U r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[35] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[53] &&
        cube.a[10] == cube.a[11] && cube.a[10] == cube.a[12]) {
        printf("PLL_2B U U R R U R U r u r u r U r\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[53] &&
        cube.a[39] == cube.a[37] && cube.a[39] == cube.a[11] &&
        cube.a[10] == cube.a[35] && cube.a[10] == cube.a[12]) {
        printf("PLL_2L u R R U R U r u r u r U r\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况3
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[53]) {
        printf("PLL_3F Z R R d d r u R d d r U r z\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[52]) {
        printf("PLL_3R U Z R R d d r u R d d r U r z\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[39]) {
        printf("PLL_3B U U Z R R d d r u R d d r U r z\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[38] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[36]) {
        printf("PLL_3L u Z R R d d r u R d d r U r z\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    //情况4
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[11]) {
        printf("PLL_4F Z R u R d d r U R d d r r z\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[38]) {
        printf("PLL_4R U Z R u R d d r U R d d r r z\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[52]) {
        printf("PLL_4B U U Z R u R d d r U R d d r r z\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[39] && cube.a[37] == cube.a[11]) {
        printf("PLL_4L u Z R u R d d r U R d d r r z\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();

    }
    //13种一般情况
    //情况5
    if (cube.a[34] == cube.a[11] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[39]) {
        printf("PLL_5F z l r z l r U z l r z l r U U z l r z l r U z l r z l r\n");

        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();


    }
    //情况6
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[38] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[39]) {
        printf("PLL_6F R U r f f u L U l F F U R u u r\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[11] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[39]) {
        printf("PLL_6R U R U r f f u L U l F F U R u u r\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况7
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[52]) {
        printf("PLL_7F Z R u r d R U r D R U r d R u r D z\n");

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_7R U Z R u r d R U r D R U r d R u r D z\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[52]) {
        printf("PLL_7B U U Z R u r d R U r D R U r d R u r D z\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_7L u Z R u r d R U r D R U r d R u r D z\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('z');
        move_z();

    }
    //情况8
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[39] && cube.a[37] == cube.a[53]) {
        printf("PLL_8F R U r u r f R R u r u R U r F\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[36]) {
        printf("PLL_8R U R U r u r f R R u r u R U r F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[52] && cube.a[54] == cube.a[38] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[11] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[36]) {
        printf("PLL_8B U U R U r u r f R R u r u R U r F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[35]) {
        printf("PLL_8L u R U r u r f R R u r u R U r F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况9
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[53]) {
        printf("PLL_9F r U R u r r F u f U R u Z R R u r U z\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[36]) {
        printf("PLL_9R U r U R u r r F u f U R u Z R R u r U z\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[11]) {
        printf("PLL_9B U U r U R u r r F u f U R u Z R R u r U z\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[39]) {
        printf("PLL_9L u r U R u r r F u f U R u Z R R u r U z\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
    }
    //情况10
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[38]) {
        printf("PLL_10F r U R u r X b u R U U r u R u r x B R\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[36] && cube.a[12] == cube.a[11] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[53]) {
        printf("PLL_10R U r U R u r X b u R U U r u R u r x B R\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_10B U U r U R u r X b u R U U r u R u r x B R\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[38] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_10L u r U R u r X b u R U U r u R u r x B R\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('X');
        move_X();
        Aim_Cube.step.push('b');
        move_b();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('x');
        move_x();
        Aim_Cube.step.push('B');
        move_B();
        Aim_Cube.step.push('R');
        move_R();
    }
    //情况11
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[35]) {
        printf("PLL_11F f R u r u R U r F R U r u r f R F\n");

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[53]) {
        printf("PLL_11R U f R u r u R U r F R U r u r f R F\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[38]) {
        printf("PLL_11B U U f R u r u R U r F R U r u r f R F\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[38] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[52]) {
        printf("PLL_11L u f R u r u R U r F R U r u r f R F\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('F');
        move_F();

    }
    //情况12
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[53]) {
        printf("PLL_12F U r U L u u R u z l r Z U L u u R u l\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();

    }
    //情况13
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[35] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[38]) {
        printf("PLL_13F u l u R U U L U z l r Z u R U U L U r\n");

        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('z');
        move_z();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Z');
        move_Z();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();

    }
    //情况14
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[39]) {
        printf("PLL_14F R U r F R U r u r f R R u r u\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[36]) {
        printf("PLL_14R U R U r F R U r u r f R R u r u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[36]) {
        printf("PLL_14B U U R U r F R U r u r f R R u r u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[52]) {
        printf("PLL_14L u R U r F R U r u r f R R u r u\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    //情况15
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[53] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[36]) {
        printf("PLL_15F L u l f L u l U l F L L U l U \n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[52] && cube.a[37] == cube.a[53]) {
        printf("PLL_15R U L u l f L u l U l F L L U l U \n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[39]) {
        printf("PLL_15B U U L u l f L u l U l F L L U l U \n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[36]) {
        printf("PLL_15L u L u l f L u l U l F L L U l U \n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    //情况16
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[36] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[39]) {
        printf("PLL_16F R U r F R u u r U U r f R U R u u r u\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[11]) {
        printf("PLL_16R U R U r F R u u r U U r f R U R u u r u\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[11] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[35]) {
        printf("PLL_16B U U R U r F R u u r U U r f R U R u u r u\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_16L u R U r F R u u r U U r f R U R u u r u\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();

    }
    //情况17
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[11] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[36]) {
        printf("PLL_17F L u l f L U U l u u l F L u L U U l U\n");

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[52]) {
        printf("PLL_17R U L u l f L U U l u u l F L u L U U l U\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[38] &&
        cube.a[12] == cube.a[36] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[39]) {
        printf("PLL_17B U U L u l f L U U l u u l F L u L U U l U\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    if (cube.a[34] == cube.a[11] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[36]) {
        printf("PLL_17L u L u l f L U U l u u l F L u L U U l U\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('f');
        move_f();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('F');
        move_F();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('L');
        move_L();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('l');
        move_l();
        Aim_Cube.step.push('U');
        move_U();

    }
    //4种复杂情况
    //情况18
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[39]) {
        printf("PLL_18F r r y D R u R U r Y d R R Y R u r y\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[36]) {
        printf("PLL_18R U r r y D R u R U r Y d R R Y R u r y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[36]) {
        printf("PLL_18B U U r r y D R u R U r Y d R R Y R u r y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[52]) {
        printf("PLL_18L u r r y D R u R U r Y d R R Y R u r y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    //情况19
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[39]) {
        printf("PLL_19F R U r y r r y D R u r U r Y d R R Y\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[11] &&
        cube.a[12] == cube.a[10] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[36]) {
        printf("PLL_19R U R U r y r r y D R u r U r Y d R R Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[53] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[36]) {
        printf("PLL_19B U U R U r y r r y D R u r U r Y d R R Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[38] && cube.a[34] == cube.a[36] &&
        cube.a[54] == cube.a[11] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[53] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[52]) {
        printf("PLL_19L u R U r y r r y D R u r U r Y d R R Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //情况20
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[35] && cube.a[54] == cube.a[10] &&
        cube.a[12] == cube.a[36] && cube.a[12] == cube.a[11] &&
        cube.a[37] == cube.a[53] && cube.a[37] == cube.a[39]) {
        printf("PLL_20F R R Y d r U r u R y D r r y r U R Y\n");

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[38] &&
        cube.a[54] == cube.a[39] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[35] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[36]) {
        printf("PLL_20R U R R Y d r U r u R y D r r y r U R Y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[10] &&
        cube.a[54] == cube.a[38] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[11] && cube.a[37] == cube.a[36]) {
        printf("PLL_20B U U R R Y d r U r u R y D r r y r U R Y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[35] &&
        cube.a[12] == cube.a[53] && cube.a[12] == cube.a[39] &&
        cube.a[37] == cube.a[38] && cube.a[37] == cube.a[52]) {
        printf("PLL_20L u R R Y d r U r u R y D r r y r U R Y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();

    }
    //情况21
    if (cube.a[34] == cube.a[52] && cube.a[34] == cube.a[11] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[53] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[36] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[39]) {
        printf("PLL_21F r u R Y R R Y d r U R u R y D r r y\n");

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[35] && cube.a[34] == cube.a[52] &&
        cube.a[54] == cube.a[11] && cube.a[54] == cube.a[39] &&
        cube.a[12] == cube.a[38] && cube.a[12] == cube.a[10] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[53]) {
        printf("PLL_21R U r u R Y R R Y d r U R u R y D r r y\n");

        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[10] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[11] && cube.a[54] == cube.a[52] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[35] &&
        cube.a[37] == cube.a[36] && cube.a[37] == cube.a[38]) {
        printf("PLL_21B U U r u R Y R R Y d r U R u R y D r r y\n");

        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }
    if (cube.a[34] == cube.a[36] && cube.a[34] == cube.a[53] &&
        cube.a[54] == cube.a[10] && cube.a[54] == cube.a[38] &&
        cube.a[12] == cube.a[39] && cube.a[12] == cube.a[11] &&
        cube.a[37] == cube.a[35] && cube.a[37] == cube.a[52]) {
        printf("PLL_21L u r u R Y R R Y d r U R u R y D r r y\n");

        Aim_Cube.step.push('u');
        move_u();

        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('Y');
        move_Y();
        Aim_Cube.step.push('d');
        move_d();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('u');
        move_u();
        Aim_Cube.step.push('R');
        move_R();
        Aim_Cube.step.push('y');
        move_y();
        Aim_Cube.step.push('D');
        move_D();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('r');
        move_r();
        Aim_Cube.step.push('y');
        move_y();

    }

}
//调整最后一层的颜色
void TRANS_COLOR(int a[]) {
    if (cube.a[53] == 1) {
        printf("U\n");
        Aim_Cube.step.push('U');
        move_U();
    }
    if (cube.a[35] == 1) {
        printf("U U\n");
        Aim_Cube.step.push('U');
        move_U();
        Aim_Cube.step.push('U');
        move_U();
    }
    if (cube.a[38] == 1) {
        printf("u\n");
        Aim_Cube.step.push('u');
        move_u();
    }
    //将魔方上下翻转回到初始状态
    Aim_Cube.step.push('x');
    move_x();
    Aim_Cube.step.push('x');
    move_x();
    printf("x x\n");
}

//寻找魔方的解法
void FIND_RECOVER_PATH()
{
    //校正魔方朝向
    CORRECT_Y(cube.a);

    CORRECT_XZ(cube.a);
    //还原底面十字
    SOLVE_WHITE_ORANGE_RIDGE(cube.a);

    SOLVE_WHITE_GREEN_RIDGE(cube.a);

    SOLVE_WHITE_RED_RIDGE(cube.a);

    SOLVE_WHITE_BLUE_RIDGE(cube.a);
    //还原底面角块
    SOLVE_ORANGE_GREEN_CORNOR(cube.a);

    SOLVE_GREEN_RED_CORNOR(cube.a);

    SOLVE_RED_BLUE_CORNOR(cube.a);

    SOLVE_BLUE_ORANDE_CORNOR(cube.a);
    //还原中间层棱块
    SOLVE_ORANGE_GREEN_RIDGE(cube.a);

    SOLVE_GREEN_RED_RIDGE(cube.a);

    SOLVE_RED_BLUE_RIDGE(cube.a);

    SOLVE_BLUE_ORANGE_RIDGE(cube.a);
    //Orientation of Last Layer
    SOLVE_ORIENT(cube.a);
    //Permutation of Last Layer
    SOLVE_PERMUT(cube.a);
    //调整最后一层颜色
    TRANS_COLOR(cube.a);
}
//实现自动复原效果
void AUTOMATIC_RECOVERY(int idx)
{
    if (idx <= stop)
    {
        switch (Path_Record[idx])
        {
        case 'R':
            glutTimerFunc(speed, turn_fR, 1);
            break;
        case 'r':
            glutTimerFunc(speed, turn_fr, 1);
            break;
        case 'F':
            glutTimerFunc(speed, turn_fF, 1);
            break;
        case 'f':
            glutTimerFunc(speed, turn_ff, 1);
            break;
        case 'U':
            glutTimerFunc(speed, turn_fU, 1);
            break;
        case 'u':
            glutTimerFunc(speed, turn_fu, 1);
            break;
        case 'D':
            glutTimerFunc(speed, turn_fD, 1);
            break;
        case 'd':
            glutTimerFunc(speed, turn_fd, 1);
            break;
        case 'L':
            glutTimerFunc(speed, turn_fL, 1);
            break;
        case 'l':
            glutTimerFunc(speed, turn_fl, 1);
            break;
        case 'B':
            glutTimerFunc(speed, turn_fB, 1);
            break;
        case 'b':
            glutTimerFunc(speed, turn_fb, 1);
            break;
        case 'X':
            glutTimerFunc(speed, turn_allX, 1);
            break;
        case 'x':
            glutTimerFunc(speed, turn_allx, 1);
            break;
        case 'Y':
            glutTimerFunc(speed, turn_allY, 1);
            break;
        case 'y':
            glutTimerFunc(speed, turn_ally, 1);
            break;
        case 'Z':
            glutTimerFunc(speed, turn_allZ, 1);
            break;
        case 'z':
            glutTimerFunc(speed, turn_allz, 1);
            break;
        }
    }
    else//复原完成时
    {
        Flag = 0;
        memset(Path_Record, 0, sizeof Path_Record);
        CHANGE = 1;
        R = 0.7, G = 1, B = 0.1;
        init();
        glutPostRedisplay();


        Sleep(200);
        if (CHECK_ALL(cube))
            Draw_TEXT(600, 450, 300, 30, "Solved");
        else
            Draw_TEXT(600, 450, 300, 30, "Solve failed");
    }
}

/******************************魔方的自动打乱模块******************************/

void performNextScrambleMove(int idx) {
    int numMoves = 25;//随机打乱步数
    if (idx < numMoves) {
        int move = rand() % 9; // 生成一个0到8之间的随机数，对应不同的魔方操作
        switch (move) {
        case 0:
            turn_fR(0);
            move_R();
            printf("R\n");
            break;
        case 1:
            turn_fF(0);
            move_F();
            printf("F\n");
            break;
        case 2:
            turn_fU(0);
            move_U();
            printf("U\n");
            break;
        case 3:
            turn_fD(0);
            move_D();
            printf("D\n");
            break;
        case 4:
            turn_fL(0);
            move_L();
            printf("L\n");
            break;
        case 5:
            turn_fB(0);
            move_B();
            printf("B\n");
            break;
        case 6:
            turn_allX(0);
            move_X();
            printf("X\n");
            break;
        case 7:
            turn_allY(0);
            move_Y();
            printf("Y\n");
            break;
        case 8:
            turn_allZ(0);
            move_Z();
            printf("Z\n");
            break;
        }
        glutTimerFunc(180, performNextScrambleMove, idx + 1);
    }
}

void Scramblecube() {
    printf("Start to scramble the cube!\n");
    srand(static_cast<unsigned int>(time(NULL))); // 初始化随机数生成器
    performNextScrambleMove(0); // 开始执行打乱操作
}

/******************************鼠标键盘回调控制模块******************************/

void onKeyboard(unsigned char key, int x, int y)
{
    if (key == VK_RETURN) {

        printf("start to solve the cube!\n");

        if (!CHECK_ALL(cube)) FIND_RECOVER_PATH();

        for (; !Aim_Cube.step.empty(); )
        {
            Path_Record[++idx] = Aim_Cube.step.front();
            Aim_Cube.step.pop();
        }
        cout << endl;
        cout << "The step of recovery: " << idx << endl;
        stop = idx;
        idx = 0;
        Flag = 1;
        AUTOMATIC_RECOVERY(++idx);
    }

    else if (key == '1')
        glutTimerFunc(1, move_left, 1);

    else if (key == '3')
        glutTimerFunc(1, move_right, 1);

    else if (key == '4')
        glutTimerFunc(1, move_up, 1);

    else if (key == '6')
        glutTimerFunc(1, move_down, 1);

    else if (key == '7')
        glutTimerFunc(1, move_front, 1);

    else if (key == '9')
        glutTimerFunc(1, move_behind, 1);

    else if (key == 'C') {
 /*       for (int i = 1; i <= 54; i++) {
            printf("a[%d]=%d\n", i, cube.a[i]);
        }*/
        printf("%f", inter(red[0][0][0]) - red[0][0][0]);
        
    }
    if (CHECK_CUBE(red, orange, blue, green, white, yellow)) {


    if (key == 'R') {
        printf("R\n");
        glutTimerFunc(1, turn_fR, 1);
        move_R();
    }

    else if (key == 'r') {
        printf("r\n");
        glutTimerFunc(1, turn_fr, 1);
        move_r();
    }

    else if (key == 'F')
    {
        printf("F\n");
        glutTimerFunc(1, turn_fF, 1);
        move_F();
    }

    else if (key == 'f')
    {
        printf("f\n");
        glutTimerFunc(1, turn_ff, 1);
        move_f();
    }

    else if (key == 'U')
    {
        printf("U\n");
        glutTimerFunc(1, turn_fU, 1);
        move_U();
    }

    else if (key == 'u')
    {
        printf("u\n");
        glutTimerFunc(1, turn_fu, 1);
        move_u();
    }

    else if (key == 'D')
    {
        printf("D\n");
        glutTimerFunc(1, turn_fD, 1);
        move_D();
    }

    else if (key == 'd')
    {
        printf("d\n");
        glutTimerFunc(1, turn_fd, 1);
        move_d();
    }

    else if (key == 'L')
    {
        printf("L\n");
        glutTimerFunc(1, turn_fL, 1);
        move_L();
    }

    else if (key == 'l')
    {
        printf("l\n");
        glutTimerFunc(1, turn_fl, 1);
        move_l();
    }

    else if (key == 'B')
    {
        printf("B\n");
        glutTimerFunc(1, turn_fB, 1);
        move_B();
    }

    else if (key == 'b')
    {
        printf("b\n");
        glutTimerFunc(1, turn_fb, 1);
        move_b();
    }

    else if (key == 'S')
        Scramblecube();

    else if (key == 'X') {
        printf("X\n");
        glutTimerFunc(1, turn_allX, 1);
        move_X();
    }

    else if (key == 'x') {
        printf("x\n");
        glutTimerFunc(1, turn_allx, 1);
        move_x();
    }

    else if (key == 'Y') {
        printf("Y\n");
        glutTimerFunc(1, turn_allY, 1);
        move_Y();
    }

    else if (key == 'y') {
        printf("y\n");
        glutTimerFunc(1, turn_ally, 1);
        move_y();
    }

    else if (key == 'Z') {
        printf("Z\n");
        glutTimerFunc(1, turn_allZ, 1);
        move_Z();
    }

    else if (key == 'z') {
        printf("z\n");
        glutTimerFunc(1, turn_allz, 1);
        move_z();
    }
    }
}

void Mos_Left_turn_look(int USELESS)
{
    if (LEFT_isDragging)
    {
        float temp_lookx = lookx;
        float temp_lookz = lookz;
        lookx = (temp_lookx * cos(rot)) - (temp_lookz * sin(rot));
        lookz = (temp_lookx * sin(rot)) + (temp_lookz * cos(rot));

        init();

        glutPostRedisplay();

        glutTimerFunc(10, Mos_Left_turn_look, 10);
    }
}

void Mos_Right_turn_look(int USELESS)
{
    if (RIGHT_isDragging)
    {
        float temp_lookx = lookx;
        float temp_lookz = lookz;
        lookx = (temp_lookx * cos(rot)) + (temp_lookz * sin(rot));
        lookz = (-1 * temp_lookx * sin(rot)) + (temp_lookz * cos(rot));

        init();

        glutPostRedisplay();

        glutTimerFunc(10, Mos_Right_turn_look, 10);
    }
}

void Mos_Middle_turn_look(int USELESS)
{
    if (MIDDLE_isDragging)
    {
        float temp_lookz = lookz;
        float temp_looky = looky;
        lookz = (temp_lookz * cos(rot)) + (temp_looky * sin(rot));
        looky = (-1 * temp_lookz * sin(rot)) + (temp_looky * cos(rot));

        init();

        glutPostRedisplay();

        glutTimerFunc(10, Mos_Middle_turn_look, 10);
    }
}

void GL_mouseCallback(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        LEFT_isDragging = 1;
        glutTimerFunc(1, Mos_Left_turn_look, 1);

    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        LEFT_isDragging = 0;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        RIGHT_isDragging = 1;
        glutTimerFunc(1, Mos_Right_turn_look, 1);

    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        RIGHT_isDragging = 0;
    }

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        MIDDLE_isDragging = 1;
        glutTimerFunc(1, Mos_Middle_turn_look, 1);

    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        MIDDLE_isDragging = 0;
    }

}

/******************************绘制整个魔方与大循环******************************/
void myDisplay()
{

    glClearColor(R, G, B, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //红色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[0][0], color[0][1], color[0][2]);
                glVertex3f(red[i][j][0], red[i][j][1], red[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(red[i][j][0], red[i][j][1], red[i][j][2]);
            }
        }
    if (int i = 0) {
        glTexCoord2f(0.0f, 0.0f); glVertex3f(red[i][0][0], red[i][0][1], red[0][0][2]);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(red[i][1][0], red[i][1][1], red[i][1][2]);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(red[i][2][0], red[i][2][1], red[i][2][2]);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(red[i][3][0], red[i][3][1], red[i][3][2]);
    }
        
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(red[9][0][0], red[9][0][1], red[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(red[9][1][0], red[9][1][1], red[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(red[9][2][0], red[9][2][1], red[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(red[9][3][0], red[9][3][1], red[9][3][2]);
    glEnd();



    //绿色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[1][0], color[1][1], color[1][2]);
                glVertex3f(green[i][j][0], green[i][j][1], green[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(green[i][j][0], green[i][j][1], green[i][j][2]);
            }
        }
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(green[9][0][0], green[9][0][1], green[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(green[9][1][0], green[9][1][1], green[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(green[9][2][0], green[9][2][1], green[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(green[9][3][0], green[9][3][1], green[9][3][2]);
    glEnd();


    //橙色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[2][0], color[2][1], color[2][2]);
                glVertex3f(orange[i][j][0], orange[i][j][1], orange[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(orange[i][j][0], orange[i][j][1], orange[i][j][2]);
            }
        }
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(orange[9][0][0], orange[9][0][1], orange[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(orange[9][1][0], orange[9][1][1], orange[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(orange[9][2][0], orange[9][2][1], orange[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(orange[9][3][0], orange[9][3][1], orange[9][3][2]);
    glEnd();

    //蓝色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[3][0], color[3][1], color[3][2]);
                glVertex3f(blue[i][j][0], blue[i][j][1], blue[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(blue[i][j][0], blue[i][j][1], blue[i][j][2]);
            }
        }
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(blue[9][0][0], blue[9][0][1], blue[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(blue[9][1][0], blue[9][1][1], blue[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(blue[9][2][0], blue[9][2][1], blue[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(blue[9][3][0], blue[9][3][1], blue[9][3][2]);
    glEnd();




    //黄色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[5][0], color[5][1], color[5][2]);
                glVertex3f(yellow[i][j][0], yellow[i][j][1], yellow[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(yellow[i][j][0], yellow[i][j][1], yellow[i][j][2]);
            }
        }
    glEnd();


    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(yellow[9][0][0], yellow[9][0][1], yellow[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(yellow[9][1][0], yellow[9][1][1], yellow[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(yellow[9][2][0], yellow[9][2][1], yellow[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(yellow[9][3][0], yellow[9][3][1], yellow[9][3][2]);
    glEnd();


    //白色
    glBegin(GL_QUADS);
    for (int i = 0; i < 18; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i >= 9) {
                glColor3f(color[4][0], color[4][1], color[4][2]);
                glVertex3f(white[i][j][0], white[i][j][1], white[i][j][2]);
            }
            else {
                glColor3f(clr, clr, clr);
                glVertex3f(white[i][j][0], white[i][j][1], white[i][j][2]);
            }
        }
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(white[9][0][0], white[9][0][1], white[9][0][2]);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(white[9][1][0], white[9][1][1], white[9][1][2]);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(white[9][2][0], white[9][2][1], white[9][2][2]);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(white[9][3][0], white[9][3][1], white[9][3][2]);
    glEnd();
  
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();

}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    Inite_EasyX();

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(800, 0);
    glutInitWindowSize(900, 900);

    glutCreateWindow("Pocket Cube");

    inite_cube_color();//初始魔方颜色数组数据

    init();
    glewInit();

    loadTexture("assets/pic.bmp");
    glutDisplayFunc(myDisplay);//启动绘制

    glutKeyboardFunc(onKeyboard);//实时监测键盘的变化
    glutMouseFunc(GL_mouseCallback);

    glutMainLoop();
    return 0;
}