/*2351044 崔艺洋 大数据*/
#pragma once

//不允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20 ！！！

//自行查阅相关资料，了解下面这几个预编译命令的作用，看能否给你的作业带来方便！！！
//#pragma pack(show) //以警告信息的形式显示当前字节对齐的值
//#pragma pack(push) //将当前字节对齐值压入编译器栈的栈顶
//#pragma pack(push, 4) //将当前字节对齐值压入编译器栈的栈顶，然后再将4设置当前值
//#pragma pack(pop)  //将编译器栈栈顶的字节对齐值弹出并设置为当前值
//#pragma pack() //不带参数是恢复默认值

#pragma pack(push, 1) // 结构体对齐
//允许定义其它需要的结构体（类）、常量、常变量等
struct myBITMAPFILEHEADER {//14bytes
    unsigned short   fileType;  // 文件类型，必须为0x4D42
    unsigned int   fileSize;  // 文件大小，字节
    unsigned short reserved1; // 保留字，必须为0
    unsigned short reserved2; // 保留字，必须为0
    unsigned int   offset;    // 从文件开始到图像数据的偏移量
};
 // 位图信息头
struct myBITMAPINFOHEADER {//40bytes
    unsigned int   infoSize;        // 本结构体的大小
    int            imgWidth;        // 图像宽度，以像素为单位
    int            imgHeight;       // 图像高度，以像素为单位
    unsigned short colPlanes;       // 颜色平面数，必须为1
    unsigned short bitCount;        // 每个像素的位数
    unsigned int   compressionType; // 压缩类型
    unsigned int   imgSize;         // 图像的大小，以字节为单位
    int            xPelsPerMeter;   // 水平分辨率
    int            yPelsPerMeter;   // 垂直分辨率
    unsigned int   clrUsed;         // 使用的颜色数
    unsigned int   clrImportant;    // 重要的颜色数
};
struct myRGBQUAD {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
};
// 定义一个简单的点结构体，用于存储颜色信息
struct RGB {
    unsigned char red, green, blue;
};
#pragma pack(pop)

class bitmap {
private:
    //自行添加你需要的数据成员及成员函数，不限制数量
    myBITMAPFILEHEADER fileHeader;
    myBITMAPINFOHEADER infoHeader;

    myRGBQUAD* colorTable; //颜色表（低色深时存在）
    unsigned char* imgData; //像素数据
    int width, height;
    unsigned short bitCount;

    bool loadBitmap(const char* const filename);
public:
    //公有部分不允许添加任何内容
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, 
                void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
