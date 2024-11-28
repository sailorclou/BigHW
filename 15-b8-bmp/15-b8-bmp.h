/*2351044 ������ ������*/
#pragma once

//����������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20 ������

//���в���������ϣ��˽������⼸��Ԥ������������ã����ܷ�������ҵ�������㣡����
//#pragma pack(show) //�Ծ�����Ϣ����ʽ��ʾ��ǰ�ֽڶ����ֵ
//#pragma pack(push) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ��
//#pragma pack(push, 4) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ����Ȼ���ٽ�4���õ�ǰֵ
//#pragma pack(pop)  //��������ջջ�����ֽڶ���ֵ����������Ϊ��ǰֵ
//#pragma pack() //���������ǻָ�Ĭ��ֵ

#pragma pack(push, 1) // �ṹ�����
//������������Ҫ�Ľṹ�壨�ࣩ����������������
struct myBITMAPFILEHEADER {//14bytes
    unsigned short   fileType;  // �ļ����ͣ�����Ϊ0x4D42
    unsigned int   fileSize;  // �ļ���С���ֽ�
    unsigned short reserved1; // �����֣�����Ϊ0
    unsigned short reserved2; // �����֣�����Ϊ0
    unsigned int   offset;    // ���ļ���ʼ��ͼ�����ݵ�ƫ����
};
 // λͼ��Ϣͷ
struct myBITMAPINFOHEADER {//40bytes
    unsigned int   infoSize;        // ���ṹ��Ĵ�С
    int            imgWidth;        // ͼ���ȣ�������Ϊ��λ
    int            imgHeight;       // ͼ��߶ȣ�������Ϊ��λ
    unsigned short colPlanes;       // ��ɫƽ����������Ϊ1
    unsigned short bitCount;        // ÿ�����ص�λ��
    unsigned int   compressionType; // ѹ������
    unsigned int   imgSize;         // ͼ��Ĵ�С�����ֽ�Ϊ��λ
    int            xPelsPerMeter;   // ˮƽ�ֱ���
    int            yPelsPerMeter;   // ��ֱ�ֱ���
    unsigned int   clrUsed;         // ʹ�õ���ɫ��
    unsigned int   clrImportant;    // ��Ҫ����ɫ��
};
struct myRGBQUAD {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
};
// ����һ���򵥵ĵ�ṹ�壬���ڴ洢��ɫ��Ϣ
struct RGB {
    unsigned char red, green, blue;
};
#pragma pack(pop)

class bitmap {
private:
    //�����������Ҫ�����ݳ�Ա����Ա����������������
    myBITMAPFILEHEADER fileHeader;
    myBITMAPINFOHEADER infoHeader;

    myRGBQUAD* colorTable; //��ɫ����ɫ��ʱ���ڣ�
    unsigned char* imgData; //��������
    int width, height;
    unsigned short bitCount;

    bool loadBitmap(const char* const filename);
public:
    //���в��ֲ���������κ�����
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror, 
                void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};
