#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include<QImage>
typedef quint8  BYTE; //BYTE��ʾ8λ�޷���������һ���ֽ�
typedef quint16 WORD; //WORD��ʾ16λ�޷��������������ֽ�
typedef quint32 DWORD; //DWORD��ʾ32λ�޷����������ĸ����ֽ�
typedef qint32  LONG; //LONG��ʾ32λ�������ĸ��ֽ�
#include<QImage>


class ImageProcessing
{
public:
    ImageProcessing();
private:
    int depth;              //ͼ������
    LONG width;             //ͼ��Ŀ��
    LONG height;            //ͼ��ĸ߶�
    int bytesOfPerLine;     //ÿ�е��ֽ���
    long bytesCount;        //�ܵ��ֽ���
    QImage::Format format;             //ͼ��ĸ�ʽ
public:
    void countOfEachPixel(BYTE *pImageData,LONG *grayCount);        //ͳ��ÿ�����ص�ĻҶ�ֵ
    void getImageInfo(const QImage targetImage);                    //��ȡͼƬ����Ϣ
    void translationImage(BYTE *pSrcData,BYTE *pDestData,int xoffset,int yoffset);//ͼ��ƽ��
    void miirroredTran(BYTE *pSrcData,BYTE *pDestData,bool direct);             //ͼ���� �任
    void transpositionImage(BYTE *pSrcData,BYTE *pDestData);        //ͼ��ת�� �任
    void gradientSharpen(BYTE *pSrcData,BYTE *pDestData);     //�ݶ��� �任
    void laplaceSharpen(BYTE *pSrcData, BYTE *pDestData);                    //������˹�� �任
    void rgbToGray(QImage &srcImage,QImage &destImage);             //RGBͼ��ת�Ҷ�ͼ��
    void templateOperation(BYTE *pSrcData, BYTE *pDestData, int *mask, float coefficient);       //ģ�����
    void middleValueFilter(BYTE *pSrcData,BYTE *pDestData);             //��ֵ�˲�
    void sort(int *mask);                                 //����������
    void robertsEdgeDect(BYTE * pSrcData,BYTE *pDestData);                  //Roberts���ӱ�Ե���
    void sobelEdgeDect(BYTE *pSrcData,BYTE *pDestData);                     //Sobel���ӱ�Ե���
    void prewittEdgeDect(BYTE *pSrcData,BYTE *pDestData);                   //prewitt���ӱ�Ե���
    void krischEdgeDect(QImage &destImage);                    //krisch���ӱ�Ե���
    void gaslapEdgeDect(BYTE *pSrcData,BYTE *pDestData);                    //��˹������˹���ӱ�Ե���
    void twoTemplate(BYTE *pSrcData,BYTE *pDestData,int *template1,int *template2);             //�������ϵ�ģ���������
    void equal(BYTE *pDrcData,BYTE *pDestData,LONG *grayCount);                 //ͼ������������
    void thresholdChange(BYTE *pSrcData, BYTE *pDestData, int threshold);       //��ֵ�任 ����
    void zoomImage(QImage &srcImage, QImage &destImage, float fx, float fy);               //����ͼ��
    void linearTransform(BYTE *pSrcData,BYTE *pDestData,int gradient,int intercept);        //�Ҷȵ����Ա任
    void grayExtend(BYTE *pSrcData,BYTE *pDestData,int coor1_x,int coor1_y,int coor2_x,int coor2_y);        //�Ҷȵ�����
};

#endif // IMAGEPROCESSING_H
