/*2351044 ������ ������*/
#include <iostream>
#include <fstream>
//������������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20!!!!!
using namespace std;

#include "15-b8-bmp.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������貹��
***************************************************************************/
bitmap::bitmap(const char *const filename) : width(0), height(0), bitCount(0)
{
    loadBitmap(filename);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������貹��
***************************************************************************/
bitmap::~bitmap()
{
	if (colorTable)
		delete[]colorTable;
	if (imgData)
		delete[]imgData;
}

//������������
int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
	void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const
{
    if (!imgData) {
        return -1;
    }
    int rowSize = ((bitCount * width + 31) / 32) * 4; // ÿ�а�4�ֽڶ��� ((bitCount * width + 31) >> 5) << 2;
    //����ȡ����ʽ��(n-1)/m+1, m148:821
    //int rowSize = 0;

    //if (bitCount == 1) {
    //    // 1λɫ��ÿ8������1���ֽ�
    //    rowSize = (width + 7) / 8;  // ÿ�����������ֽ���
    //}
    //else if (bitCount == 4) {
    //    // 4λɫ��ÿ2������1���ֽ�
    //    rowSize = (width + 1) / 2;  // ÿ�����������ֽ���
    //}
    //else if (bitCount == 8) {
    //    // 8λɫ��ÿ1������1���ֽ�
    //    rowSize = width;  // ÿ�����������ֽ���
    //}
    //else if (bitCount == 24) {
    //    // 24λɫ��ÿ������3���ֽ�
    //    rowSize = width * 3;  // ÿ�����������ֽ���
    //}
    //else if (bitCount == 32) {
    //    // 32λɫ��ÿ������4���ֽ�
    //    rowSize = width * 4;  // ÿ�����������ֽ���
    //}

    //// ���뵽 4 �ֽ�
    //rowSize = (rowSize + 3) & ~3;  // ȷ���� 4 �ֽڶ���
    
    // ����ͼ��ĸ߶ȷ��ţ������е���ʼ˳��
    bool isBottomUp = infoHeader.imgHeight > 0;

    for (int y = 0; y < height; ++y) {
        // ����ǵ���ͼ�񣬴ӵײ���ʼ��Ⱦ
        int dataY = isBottomUp ? (height - 1 - y) : y;

        for (int x = 0; x < width; ++x) {
            int pixelIndex;
            pixelIndex = dataY * rowSize + (x * bitCount / 8);
           /*if (bitCount >= 8)
                pixelIndex = dataY * rowSize + (x * bitCount / 8);
            else
                pixelIndex = dataY * rowSize + x;*/

            // ����������ɫ
            unsigned char red = 0, green = 0, blue = 0;
            if (bitCount == 24 || bitCount == 32) { // 24λ��32λɫ��ֱ�Ӷ�ȡÿ������
                blue = imgData[pixelIndex];
                green = imgData[pixelIndex + 1];
                red = imgData[pixelIndex + 2];
            }
            else if (bitCount == 1) {
                // 1λɫ��ÿ8��������1���ֽڱ�ʾ
                // ��ǰ�������ֽ��е�λ��
                int bitIndex = 7 - (x % 8); // �Ӹ�λ����λ���� //(0x01 <<    ) - 1
                // ��ȡ��ɫ����
                int colorIndex = (imgData[pixelIndex] >> bitIndex) & 0x01;

                // ͨ����ɫ���ȡRGBֵ
                red = colorTable[colorIndex].rgbRed;
                green = colorTable[colorIndex].rgbGreen;
                blue = colorTable[colorIndex].rgbBlue;
            }
            else if (bitCount == 4) {
                // 4λɫ��ÿ2��������1���ֽڱ�ʾ
                // �ж��Ǹ� 4 λ���ǵ� 4 λ
                int colorIndex;
                if (x % 2 == 0) {
                    colorIndex = (imgData[pixelIndex] >> 4) & 0x0F; // �� 4 λ
                }
                else {
                    colorIndex = imgData[pixelIndex] & 0x0F; // �� 4 λ
                }

                // ͨ����ɫ���ȡRGBֵ
                red = colorTable[colorIndex].rgbRed;
                green = colorTable[colorIndex].rgbGreen;
                blue = colorTable[colorIndex].rgbBlue;
            }
            else if (bitCount == 8) { // 8λɫͼ��ʹ����ɫ��
                int colorIndex = imgData[pixelIndex];
                blue = colorTable[colorIndex].rgbBlue;
                green = colorTable[colorIndex].rgbGreen;
                red = colorTable[colorIndex].rgbRed;
            }

            // �������
            int displayX = is_mirror ? (width - 1 - x) : x;
            int displayY = y;

            // ��ת����
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
                default: // 0 ��
                    rotatedX = displayX;
                    rotatedY = displayY;
                    break;
            }

            // ��ʾƫ��
            int finalX = top_left_x + rotatedX;
            int finalY = top_left_y + rotatedY;

            // ���Ƶ�
            draw_point(finalX, finalY, red, green, blue);
        }
    }

    return 0;
}
bool bitmap::loadBitmap(const char* const filename)
{
    ifstream file(filename, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "���ļ�[" << filename << "]ʧ��." << endl;
        return false;
    }
    // ��ȡ�ļ�ͷ����Ϣͷ
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(myBITMAPFILEHEADER));
    // ����ļ���ʽ
    if (fileHeader.fileType != 0x4D42) { //"BM"
        cout << "λͼ��Ϣ��ȡ����." << endl;
        file.close();
        return false;
    }
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(myBITMAPINFOHEADER));
    width = infoHeader.imgWidth;
    height = abs(infoHeader.imgHeight);
    bitCount = infoHeader.bitCount;

    // ���֧�ֵ���ɫ���
    if (bitCount != 1 && bitCount != 4 && bitCount != 8 && bitCount != 24 && bitCount != 32) {
        cout << "λͼ��ϢBitCount[" << bitCount << "]����." << endl;
        file.close();
        return false;
    }
    // ������ɫ������ɫ��ͼ����Ҫ��
    if (bitCount <= 8) {
        int biCompression = infoHeader.compressionType; // ѹ������
        //int colorTableOffset = 14 + infoHeader.infoSize + 16;
        int colorTableNum = (1 << bitCount);
        colorTable = new myRGBQUAD[colorTableNum];
        //file.seekg(colorTableOffset, std::ios::beg);
        file.read(reinterpret_cast<char*>(colorTable), sizeof(myRGBQUAD) * colorTableNum);
    }

    // ��ȡ��������(ʵ�ʴ洢��
    int rowSize = ((bitCount * width + 31) / 32) * 4; // ÿ�����ݰ� 4 �ֽڶ���
    int dataSize = rowSize * abs(height);

    imgData = new unsigned char[dataSize];

    // ��λ���������ݿ�ʼ��λ��
    file.seekg(fileHeader.offset, ios::beg);
    file.read(reinterpret_cast<char*>(imgData), dataSize);

    file.close();
    return true;
}