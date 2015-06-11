#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include<QImage>
typedef quint8  BYTE; //BYTE表示8位无符号整数，一个字节
typedef quint16 WORD; //WORD表示16位无符号整数，两个字节
typedef quint32 DWORD; //DWORD表示32位无符号整数，四个个字节
typedef qint32  LONG; //LONG表示32位整数，四个字节
#include<QImage>


class ImageProcessing
{
public:
    ImageProcessing();
private:
    int depth;              //图像的深度
    LONG width;             //图像的宽度
    LONG height;            //图像的高度
    int bytesOfPerLine;     //每行的字节数
    long bytesCount;        //总的字节数
    QImage::Format format;             //图像的格式
public:
    void countOfEachPixel(BYTE *pImageData,LONG *grayCount);        //统计每个像素点的灰度值
    void getImageInfo(const QImage targetImage);                    //获取图片的信息
    void translationImage(BYTE *pSrcData,BYTE *pDestData,int xoffset,int yoffset);//图像平移
    void miirroredTran(BYTE *pSrcData,BYTE *pDestData,bool direct);             //图像镜像 变换
    void transpositionImage(BYTE *pSrcData,BYTE *pDestData);        //图像转置 变换
    void gradientSharpen(BYTE *pSrcData,BYTE *pDestData);     //梯度锐化 变换
    void laplaceSharpen(BYTE *pSrcData, BYTE *pDestData);                    //拉普拉斯锐化 变换
    void rgbToGray(QImage &srcImage,QImage &destImage);             //RGB图像转灰度图像
    void templateOperation(BYTE *pSrcData, BYTE *pDestData, int *mask, float coefficient);       //模板操作
    void middleValueFilter(BYTE *pSrcData,BYTE *pDestData);             //中值滤波
    void sort(int *mask);                                 //把数组排序
    void robertsEdgeDect(BYTE * pSrcData,BYTE *pDestData);                  //Roberts算子边缘检测
    void sobelEdgeDect(BYTE *pSrcData,BYTE *pDestData);                     //Sobel算子边缘检测
    void prewittEdgeDect(BYTE *pSrcData,BYTE *pDestData);                   //prewitt算子边缘检测
    void krischEdgeDect(QImage &destImage);                    //krisch算子边缘检测
    void gaslapEdgeDect(BYTE *pSrcData,BYTE *pDestData);                    //高斯拉普拉斯算子边缘检测
    void twoTemplate(BYTE *pSrcData,BYTE *pDestData,int *template1,int *template2);             //两个以上的模板操作函数
    void equal(BYTE *pDrcData,BYTE *pDestData,LONG *grayCount);                 //图像均衡操作函数
    void thresholdChange(BYTE *pSrcData, BYTE *pDestData, int threshold);       //阈值变换 操作
    void zoomImage(QImage &srcImage, QImage &destImage, float fx, float fy);               //缩放图像
    void linearTransform(BYTE *pSrcData,BYTE *pDestData,int gradient,int intercept);        //灰度的线性变换
    void grayExtend(BYTE *pSrcData,BYTE *pDestData,int coor1_x,int coor1_y,int coor2_x,int coor2_y);        //灰度的拉伸
};

#endif // IMAGEPROCESSING_H
