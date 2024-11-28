/*2351044 崔艺洋 大数据*/
#include <iostream>
#include <fstream>
//不再允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20!!!!!
using namespace std;

#include "15-b8-bmp.h"

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::bitmap(const char *const filename) : width(0), height(0), bitCount(0)
{
    loadBitmap(filename);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::~bitmap()
{
	if (colorTable)
		delete[]colorTable;
	if (imgData)
		delete[]imgData;
}

//按需增加内容
int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
	void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
    if (!imgData) {
        return -1;
    }
    int rowSize = ((bitCount * width + 31) / 32) * 4; // 每行按4字节对齐 ((bitCount * width + 31) >> 5) << 2;
    //向上取整公式：(n-1)/m+1, m148:821
    //int rowSize = 0;

    //if (bitCount == 1) {
    //    // 1位色，每8个像素1个字节
    //    rowSize = (width + 7) / 8;  // 每行像素所需字节数
    //}
    //else if (bitCount == 4) {
    //    // 4位色，每2个像素1个字节
    //    rowSize = (width + 1) / 2;  // 每行像素所需字节数
    //}
    //else if (bitCount == 8) {
    //    // 8位色，每1个像素1个字节
    //    rowSize = width;  // 每行像素所需字节数
    //}
    //else if (bitCount == 24) {
    //    // 24位色，每个像素3个字节
    //    rowSize = width * 3;  // 每行像素所需字节数
    //}
    //else if (bitCount == 32) {
    //    // 32位色，每个像素4个字节
    //    rowSize = width * 4;  // 每行像素所需字节数
    //}

    //// 对齐到 4 字节
    //rowSize = (rowSize + 3) & ~3;  // 确保按 4 字节对齐
    
    // 根据图像的高度符号，决定行的起始顺序
    bool isBottomUp = infoHeader.imgHeight > 0;

    for (int y = 0; y < height; ++y) {
        // 如果是倒置图像，从底部开始渲染
        int dataY = isBottomUp ? (height - 1 - y) : y;

        for (int x = 0; x < width; ++x) {
            int pixelIndex;
            pixelIndex = dataY * rowSize + (x * bitCount / 8);
           /*if (bitCount >= 8)
                pixelIndex = dataY * rowSize + (x * bitCount / 8);
            else
                pixelIndex = dataY * rowSize + x;*/

            // 解析像素颜色
            unsigned char red = 0, green = 0, blue = 0;
            if (bitCount == 24 || bitCount == 32) { // 24位或32位色，直接读取每个像素
                blue = imgData[pixelIndex];
                green = imgData[pixelIndex + 1];
                red = imgData[pixelIndex + 2];
            }
            else if (bitCount == 1) {
                // 1位色，每8个像素用1个字节表示
                // 当前像素在字节中的位置
                int bitIndex = 7 - (x % 8); // 从高位到低位解析 //(0x01 <<    ) - 1
                // 提取颜色索引
                int colorIndex = (imgData[pixelIndex] >> bitIndex) & 0x01;

                // 通过颜色表获取RGB值
                red = colorTable[colorIndex].rgbRed;
                green = colorTable[colorIndex].rgbGreen;
                blue = colorTable[colorIndex].rgbBlue;
            }
            else if (bitCount == 4) {
                // 4位色，每2个像素用1个字节表示
                // 判断是高 4 位还是低 4 位
                int colorIndex;
                if (x % 2 == 0) {
                    colorIndex = (imgData[pixelIndex] >> 4) & 0x0F; // 高 4 位
                }
                else {
                    colorIndex = imgData[pixelIndex] & 0x0F; // 低 4 位
                }

                // 通过颜色表获取RGB值
                red = colorTable[colorIndex].rgbRed;
                green = colorTable[colorIndex].rgbGreen;
                blue = colorTable[colorIndex].rgbBlue;
            }
            else if (bitCount == 8) { // 8位色图，使用颜色表
                int colorIndex = imgData[pixelIndex];
                blue = colorTable[colorIndex].rgbBlue;
                green = colorTable[colorIndex].rgbGreen;
                red = colorTable[colorIndex].rgbRed;
            }

            // 镜像操作
            int displayX = is_mirror ? (width - 1 - x) : x;
            int displayY = y;

            // 旋转操作
            int rotatedX = 0, rotatedY = 0;
            switch (angle) {
                case 90:
                    rotatedX = height - 1 - displayY;
                    rotatedY = displayX;
                    break;
                case 180:
                    rotatedX = width - 1 - displayX;
                    rotatedY = height - 1 - displayY;
                    break;
                case 270:
                    rotatedX = displayY;
                    rotatedY = width - 1 - displayX;
                    break;
                default: // 0 度
                    rotatedX = displayX;
                    rotatedY = displayY;
                    break;
            }

            // 显示偏移
            int finalX = top_left_x + rotatedX;
            int finalY = top_left_y + rotatedY;

            // 绘制点
            draw_point(finalX, finalY, red, green, blue);
        }
    }

    return 0;
}
bool bitmap::loadBitmap(const char* const filename)
{
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开文件[" << filename << "]失败." << endl;
        return false;
    }
    // 读取文件头和信息头
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(myBITMAPFILEHEADER));
    // 检查文件格式
    if (fileHeader.fileType != 0x4D42) { //"BM"
        cout << "位图信息读取错误." << endl;
        file.close();
        return false;
    }
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(myBITMAPINFOHEADER));
    width = infoHeader.imgWidth;
    height = abs(infoHeader.imgHeight);
    bitCount = infoHeader.bitCount;

    // 检查支持的颜色深度
    if (bitCount != 1 && bitCount != 4 && bitCount != 8 && bitCount != 24 && bitCount != 32) {
        cout << "位图信息BitCount[" << bitCount << "]错误." << endl;
        file.close();
        return false;
    }
    // 加载颜色表（仅低色深图像需要）
    if (bitCount <= 8) {
        int biCompression = infoHeader.compressionType; // 压缩类型
        //int colorTableOffset = 14 + infoHeader.infoSize + 16;
        int colorTableNum = (1 << bitCount);
        colorTable = new myRGBQUAD[colorTableNum];
        //file.seekg(colorTableOffset, std::ios::beg);
        file.read(reinterpret_cast<char*>(colorTable), sizeof(myRGBQUAD) * colorTableNum);
    }

    // 读取像素数据(实际存储）
    int rowSize = ((bitCount * width + 31) / 32) * 4; // 每行数据按 4 字节对齐
    int dataSize = rowSize * abs(height);

    imgData = new unsigned char[dataSize];

    // 定位到像素数据开始的位置
    file.seekg(fileHeader.offset, ios::beg);
    file.read(reinterpret_cast<char*>(imgData), dataSize);

    file.close();
    return true;
}