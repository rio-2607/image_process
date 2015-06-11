#include "imageprocessing.h"
#include<QDebug>
#include<math.h>
ImageProcessing::ImageProcessing()
{
}

void ImageProcessing::getImageInfo(const QImage targetImage)
{
    depth = targetImage.depth();
    width = targetImage.width();
    height = targetImage.height();
    bytesOfPerLine = targetImage.bytesPerLine();
    bytesCount = targetImage.byteCount();
    format = targetImage.format();
}

void ImageProcessing::countOfEachPixel(BYTE *pImageData, LONG *grayCount)
{
    //把grayCount元素置零
    for(int k=0;k<256;k++)
        grayCount[k] = 0;
    int i,j;
    BYTE *pImage;
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            if(8 == depth)          //8位值索引
            {
                pImage = pImageData + i * bytesOfPerLine + j;
                grayCount[*pImage]++;
            }
           // grayValue =  0.299 * R + 0.587 * G + 0.114 * B
            else if(32 == depth)    //32位值索引
            {
                pImage = pImageData + i * bytesOfPerLine + 4 * j;
//                LONG value = (*(pImage+1)*30 + *(pImage+2)*59 + *(pImage+3)*11) / 100;//RGB转换为灰度
                LONG value = *(pImage)*0.114 +*(pImage + 1)*0.587 + *(pImage + 2)*0.299;
                grayCount[value]++;
            }
            else
            {
                qDebug() << "error." <<endl;
            }
        }
    }
}

//图像的平移pSrcData代表原始数据的指针,pDestData代表处理后的数据的指针,xoffset代表水平偏移量,yoffse代表垂直偏移量
//如果直接改变pDestData,程序运行过程会发生错误，但是，如果通过中间变量temp=pDestData,
//temp=pDestData + i * bytesOfPerLine + j,程序就不会发生内存错误.为什么？
void ImageProcessing::translationImage(BYTE *pSrcData, BYTE *pDestData, int xoffset, int yoffset)
{
    int src_i,src_j,dest_i,dest_j;
    BYTE *pTempSrc,*pTempDest;
    for(src_i = 0 ,dest_i = yoffset;dest_i < height;src_i++,dest_i++)
    {
        for(src_j = 0,dest_j = xoffset;dest_j < width;src_j++,dest_j++)
        {
            if(8 == depth)
            {
                pTempSrc = pSrcData + src_i * bytesOfPerLine + src_j;
                pTempDest = pDestData + dest_i * bytesOfPerLine + dest_j;
                *pTempDest = *pTempSrc;
            }
            if(32 == depth)
            {
                pTempSrc = pSrcData + src_i * bytesOfPerLine + 4*src_j;
                pTempDest = pDestData + dest_i * bytesOfPerLine + 4*dest_j;
                *pTempDest = *pTempSrc;
                *(pTempDest+1) = *(pTempSrc+1);
                *(pTempDest+2) = *(pTempSrc+2);
                *(pTempDest+3) = *(pTempSrc+3);
            }
        }
    }

    //把平移出去的像素点赋值为255
    for(dest_i = 0;dest_i < yoffset;dest_i++)
    {
        for(dest_j = 0;dest_j < width;dest_j++)
        {
            if(8 == depth)
            {
                pTempDest =  pDestData + dest_i * bytesOfPerLine + dest_j;
                *pTempDest = 255;
            }
            else if(32 == depth)
            {
                pTempDest = pDestData + dest_i * bytesOfPerLine + 4*dest_j;
                *pTempDest = 255;
                *(pTempDest+1) = 255;
                *(pTempDest+2) = 255;
                *(pTempDest+3) = 255;
            }
        }
    }

    for(dest_i = yoffset;dest_i < height;dest_i++)
    {
        for(dest_j = 0;dest_j < xoffset;dest_j++)
        {
            if(8 == depth)
            {
                pTempDest =  pDestData + dest_i * bytesOfPerLine + dest_j;
                *pTempDest = 255;
            }
            else if(32 == depth)
            {
                pTempDest = pDestData + dest_i * bytesOfPerLine + 4*dest_j;
                *pTempDest = 255;
                *(pTempDest+1) = 255;
                *(pTempDest+2) = 255;
                *(pTempDest+3) = 255;
            }
        }
    }
}



//图像镜像变换,pSrcData代表源数据指针,pDestData代表处理后的数据指针,direct代表方向：垂直或者水平
//direct=true则表示水平镜像变换，false表示垂直镜像变换
//原理:水平变换公式:x1=width-x0,y1=x1(xo,y0)为原始数据坐标,(x1,y1)为变换后的坐标
//垂直变换公式:x0=x1,y0=height-y1
//这段代码有待改善，可以更精简
void ImageProcessing::miirroredTran(BYTE *pSrcData, BYTE *pDestData, bool direct)
{
    int src_i,src_j,dest_i,dest_j;
    BYTE *pTempSrc,*pTempDest;
    if(direct)                  //如果是水平镜像对称
    {
        for(src_i = 0,dest_i = 0;dest_i < height;src_i++,dest_i++)
        {
            for(src_j = 0,dest_j = width-1;dest_j >=0;src_j++,dest_j--)
            {
                if(8 == depth)
                {
                    pTempSrc = pSrcData + src_i * bytesOfPerLine + src_j;
                    pTempDest = pDestData + dest_i * bytesOfPerLine + dest_j;
                    *pTempDest = *pTempSrc;
                }
                if(32 == depth)
                {
                    pTempSrc = pSrcData + src_i * bytesOfPerLine + 4*src_j;
                    pTempDest = pDestData + dest_i * bytesOfPerLine + 4*dest_j;
                    *pTempDest = *pTempSrc;
                    *(pTempDest+1) = *(pTempSrc+1);
                    *(pTempDest+2) = *(pTempSrc+2);
                    *(pTempDest+3) = *(pTempSrc+3);
                }
            }
        }
    }
    else
    {
        for(src_i = 0,dest_i = height-1;dest_i >= 0;src_i++,dest_i--)
        {
            for(src_j = 0,dest_j = 0;dest_j < width;src_j++,dest_j++)
            {
                if(8 == depth)
                {
                    pTempSrc = pSrcData + src_i * bytesOfPerLine + src_j;
                    pTempDest = pDestData + dest_i * bytesOfPerLine + dest_j;
                    *pTempDest = *pTempSrc;
                }
                if(32 == depth)
                {
                    pTempSrc = pSrcData + src_i * bytesOfPerLine + 4*src_j;
                    pTempDest = pDestData + dest_i * bytesOfPerLine + 4*dest_j;
                    *pTempDest = *pTempSrc;
                    *(pTempDest+1) = *(pTempSrc+1);
                    *(pTempDest+2) = *(pTempSrc+2);
                    *(pTempDest+3) = *(pTempSrc+3);
                }
            }
        }
    }
}



//图像转置,输入参数pSrcData:准备转置的图像的首地址,pDestData:转置后的图像的首地址
void ImageProcessing::transpositionImage(BYTE *pSrcData, BYTE *pDestData)
{
    BYTE *pTempSrc,*pTempDest;
    long bytesOfPerColumn;          //每列的字节个数

    int i,j;
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            if(8 == depth)
            {
                bytesOfPerColumn = height ;
                pTempSrc = pSrcData + i * bytesOfPerLine +j;
                pTempDest = pDestData + j * bytesOfPerColumn + i;
                *pTempDest = *pTempSrc;
            }
            if(32 == depth)
            {
                bytesOfPerColumn = height *4;
                pTempSrc = pSrcData + i * bytesOfPerLine + 4*j;
                pTempDest = pDestData + j * bytesOfPerColumn + 4*i;
                *pTempDest = *pTempSrc;
                *(pTempDest+1) = *(pTempSrc+1);
                *(pTempDest+2) = *(pTempSrc+2);
                *(pTempDest+3) = *(pTempSrc+3);
            }
        }
    }
}


//图像梯度锐化,输入参数pSrcData:准备转置的图像的首地址,pDestData:转置后的图像的首地址
//算法原理:g(i,j) = |f(i,j) - f(i+1,j)| + |f(i,j) - f(i,j+1)|
//Robert梯度:g(i,j) = |f(i,j) - f(i+1,j+1)| + |f(i+1,j) - f(i,j+1)|
void ImageProcessing::gradientSharpen(BYTE *pSrcData, BYTE *pDestData)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;
    for(i = 0;i < height - 1;i++)
    {
        for(j = 0;j < width - 1;j++)
        {
            if(8 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine +j;
                pTempDest = pDestData + i * bytesOfPerLine + j;
                *pTempDest = abs(*pTempSrc - *(pTempSrc + bytesOfPerLine + 1 )) + abs(*(pTempSrc) - *(pTempSrc + 1));
            }
            if(32 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine +4*j;
                pTempDest = pDestData + i * bytesOfPerLine + 4*j;
                *pTempDest = abs(*pTempSrc-*(pTempSrc+bytesOfPerLine)) + abs(*(pTempSrc)-*(pTempSrc+4));
                *(pTempDest+1) = abs(*(pTempSrc+1)-*(pTempSrc+1+bytesOfPerLine)) + abs(*(pTempSrc+1)-*(pTempSrc+1+4));
                *(pTempDest+2) = abs(*(pTempSrc+2)-*(pTempSrc+2+bytesOfPerLine)) + abs(*(pTempSrc+2)-*(pTempSrc+2+4));
                *(pTempDest+3) = abs(*(pTempSrc+3)-*(pTempSrc+3+bytesOfPerLine)) + abs(*(pTempSrc+3)-*(pTempSrc+3+4));
            }
        }
    }
}



//RGB彩色图像转换为灰度图像
//算法:grayValue =  0.299 * R + 0.587 * G + 0.114 * B
void ImageProcessing::rgbToGray(QImage &sourceImage, QImage &targetImage)
{
    int i,j;
    uchar *pTempRgb,*pTempGray;
    uchar *pRgbImage = sourceImage.bits();
    uchar *pGrayImage = targetImage.bits();
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            pTempRgb = pRgbImage + i * sourceImage.bytesPerLine() + 4 * j ;
            pTempGray = pGrayImage + i * targetImage.bytesPerLine() + j;
            *pTempGray = *(pTempRgb + 2) * 0.299 + *(pTempRgb + 1) * 0.587 + *pTempRgb * 0.114;
        }
    }
}
//拉普拉斯锐化
//               | 0 -1  0 |
//  使用的锐化模板是|-1  5 -1 |
//               | 0 -1  0 |
void ImageProcessing::laplaceSharpen(BYTE *pSrcData, BYTE *pDestData)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;

    for(i = 1;i < height -1;i++)
    {
        for(j = 1;j < width -1;j++)
        {
            if(8 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine + j;
                pTempDest = pDestData + i * bytesOfPerLine + j;
                *pTempDest = *pTempSrc * 5 - *(pTempSrc - bytesOfPerLine) - *(pTempSrc + bytesOfPerLine) -  \
                        *(pTempSrc + 1) -*(pTempSrc - 1);

            }
            if(32 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine + 4*j;
                pTempDest = pDestData + i * bytesOfPerLine + 4*j;
                *pTempDest = *pTempSrc * 5 - *(pTempSrc - bytesOfPerLine) - *(pTempSrc + bytesOfPerLine) -  *(pTempSrc + 4) -*(pTempSrc - 4);
                *(pTempDest+1) = *(pTempSrc+1) * 5 - *(pTempSrc + 1 - bytesOfPerLine) - *(pTempSrc + 1  + bytesOfPerLine) -  *(pTempSrc + 1 + 4) -*(pTempSrc + 1 - 4);
                *(pTempDest+2) = *(pTempSrc+2) * 5 - *(pTempSrc + 2 - bytesOfPerLine) - *(pTempSrc + 2  + bytesOfPerLine) -  *(pTempSrc + 2 + 4) -*(pTempSrc + 2 - 4);
            }
        }
    }
}


//模板操作,输入参数pSrcData:原图像指针,pDestData:处理后的图像的指针
//mask:一个数组，数组成员是每个模板元素
//coefficient:模板系数。注意：传入这个函数的coefficient一定要保证是浮点数，例如:
//如果传入的coefficient=1/9，则处理后的图像像素值为全零,应该传入(1.0) / (9.0)
void ImageProcessing::templateOperation(BYTE *pSrcData, BYTE *pDestData, int *mask, float coefficient)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;
    float result;

    for(i = 1;i< height -1;i++)
    {
        for(j = 1;j < width -1;j++)
        {
            if(8 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine + j;
                pTempDest = pDestData + i * bytesOfPerLine + j;
                result = *pTempSrc * mask[4] + *(pTempSrc - bytesOfPerLine - 1) * mask[0] + *(pTempSrc - bytesOfPerLine) * mask[1] +\
                        *(pTempSrc - bytesOfPerLine + 1) * mask[2] + *(pTempSrc - 1) * mask[3] + *(pTempSrc + 1) * mask[5] +\
                        *(pTempSrc + bytesOfPerLine - 1) * mask[6] + *(pTempSrc + bytesOfPerLine ) * mask[7] +*(pTempSrc + bytesOfPerLine + 1);
                result *= coefficient;

                *pTempDest = (BYTE) (result + 0.5);
            }
            if(32 == depth)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine + 4*j;
                pTempDest = pDestData + i * bytesOfPerLine + 4*j;
                for(int k = 0;k < 3;k++)
                {
                    result = *(pTempSrc+k) * mask[4] + *((pTempSrc+k) - bytesOfPerLine - 4) * mask[0] + *((pTempSrc+k) - bytesOfPerLine) * mask[1] +\
                            *((pTempSrc+k) - bytesOfPerLine + 4) * mask[2] + *((pTempSrc+k) - 4) * mask[3] + *((pTempSrc+k) + 4) * mask[5] +\
                            *((pTempSrc+k) + bytesOfPerLine - 4) * mask[6] + *((pTempSrc+k) + bytesOfPerLine ) * mask[7] +*((pTempSrc+k) + bytesOfPerLine + 4);

                    result *= coefficient;
                    *(pTempDest + k) = (BYTE) (result + 0.5);
                }
            }
        }
    }
}


//数组排序，采用的是冒泡排序法
void ImageProcessing::sort(int *mask)
{
    int i, j, tmp;

        for (i = 0; i < 9; i++)
        {
            for (j = 8; j > i; j--)
            {
                if (mask[j] < mask[j-1])
                {
                    tmp = mask[j-1];
                    mask[j-1] =  mask[j];
                    mask[j] = tmp;
                }
            }
        }
}


//图像中值滤波
void ImageProcessing::middleValueFilter(BYTE *pSrcData, BYTE *pDestData)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;
    int maskValue[9];
    int pixelDepth = depth / 8;

    for(i = 1;i < height - 1;i++)
    {
        for(j = 1;j < width -1;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth*j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth*j;
            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                maskValue[0] = *(pTempSrc + k  - bytesOfPerLine - pixelDepth);
                maskValue[1] = *(pTempSrc + k  - bytesOfPerLine);
                maskValue[2] = *(pTempSrc + k  - bytesOfPerLine + pixelDepth);
                maskValue[3] = *(pTempSrc+ k  - pixelDepth);
                maskValue[4] = *(pTempSrc + k);
                maskValue[5] = *(pTempSrc + k + pixelDepth);
                maskValue[6] = *(pTempSrc + k + bytesOfPerLine - pixelDepth);
                maskValue[7] = *(pTempSrc + k +  bytesOfPerLine);
                maskValue[8] = *(pTempSrc + k + bytesOfPerLine +pixelDepth);
                sort(maskValue);
                *(pTempDest + k) = maskValue[4];
            }
        }
    }

//    for(i = 0;i < width;i++)
//    {
//        pTempDest = pDestData + pixelDepth * i;
//        for(int k = 0;k <= pixelDepth - 1;k++)
//        {
//            *pDestData = *(pTempDest + k + bytesOfPerLine);
//        }
//    }
}


//Roberts算子边缘检测
//算法原理:g(i,j) = |f(i,j) - f(i+1,j+1)| + |f(i+1,j) - f(i,j+1)|
void ImageProcessing::robertsEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;
    int pixelDepth = depth / 8;

    for(i = 0;i < height - 1;i++)
    {
        for(j = 0;j < width - 1;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;
            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                *(pTempDest+k) = abs(*(pTempSrc+k) - *(pTempSrc + k + bytesOfPerLine + pixelDepth )) + abs(*(pTempSrc +k + bytesOfPerLine) - *(pTempSrc + k + pixelDepth));
            }
        }
    }
}


//sobel算子边缘检测
//算法：用两个模板与图像每个像素卷积,把卷积结果取绝对值再相加
//模板一[-1,-2,-1,(换行)0,0,0(换行)1,2,1]模板二[-1,0,1,(换行)-2,0,2,(换行)-1,0,1]
void ImageProcessing::sobelEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
    int mask1[9] = {-1,-2,-1,0,0,0,1,2,1};
    int mask2[9] = {-1,0,1,-2,0,2,-1,0,1};
    twoTemplate(pSrcData,pDestData,mask1,mask2);

}


//prewitt算子边缘检测
//算法：用两个模板与图像每个像素卷积,把卷积结果取绝对值再相加
//模板一[-1,-1,-1,(换行)0,0,0(换行)1,1,1]模板二[1,0,-1,(换行)1,0,-1,(换行)1,0,-1]
void ImageProcessing::prewittEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
    int mask1[9] = {-1,-1,-1,0,0,0,1,1,1};
    int mask2[9] = {1,0,-1,1,0,-1,1,0,-1};
    twoTemplate(pSrcData,pDestData,mask1,mask2);
}


//拉普拉斯算子边缘检测
//算法原理:g(x,y) = 4f(x,y) - f(x-1,y) - f(x+1,y) -f(x,y-1) -f(x,y+1)
void ImageProcessing::gaslapEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
        int i,j;
        BYTE *pTempDest,*pTempSrc;
        int pixelDepth = depth / 8;

        for(i = 1;i < height -1 ;i++)
        {
            for(j = 1;j < width -1;j++)
            {
                pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
                pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;
                for(int k = 0;k <= pixelDepth - 1;k++)
                {
                    *(pTempDest + k) = *(pTempSrc+k)*4 -*(pTempSrc+k-bytesOfPerLine)-*(pTempSrc+k+bytesOfPerLine)-\
                            *(pTempSrc+k-pixelDepth)-*(pTempSrc+k+pixelDepth);
                }
            }
        }
}


//两个模板同时作用时处理函数
//输入参数:pSrcData:指向原始数据指针;pDestData:只想处理后的数据指针
//template1:指向模板一的指针;tempalte2:指向模板二的指针
void ImageProcessing::twoTemplate(BYTE *pSrcData, BYTE *pDestData, int *template1, int *template2)
{
    int i,j;
    BYTE *pTempDest,*pTempSrc;
    int value1,value2;
    int pixelDepth = depth / 8;

    for(i = 1;i < height -1 ;i++)
    {
        for(j = 1;j < width -1;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;
            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                value1 = *(pTempSrc+k-bytesOfPerLine-pixelDepth)*template1[0]+*(pTempSrc+k-bytesOfPerLine)*template1[1]+\
                        *(pTempSrc+k-bytesOfPerLine+pixelDepth)*template1[2]+*(pTempSrc+k-pixelDepth)*template1[3]+*(pTempSrc+k)*template1[4]+\
                        *(pTempSrc+k+pixelDepth)*template1[5]+*(pTempSrc+k+bytesOfPerLine-pixelDepth)*template1[6]+\
                        *(pTempSrc+k+bytesOfPerLine)*template1[7]+*(pTempSrc+k+bytesOfPerLine+pixelDepth)*template1[8];
                value2 = *(pTempSrc+k-bytesOfPerLine-pixelDepth)*template2[0]+*(pTempSrc+k-bytesOfPerLine)*template2[1]+\
                        *(pTempSrc+k-bytesOfPerLine+pixelDepth)*template2[2]+*(pTempSrc+k-pixelDepth)*template2[3]+*(pTempSrc+k)*template2[4]+\
                        *(pTempSrc+k+pixelDepth)*template2[5]+*(pTempSrc+k+bytesOfPerLine-pixelDepth)*template2[6]+\
                        *(pTempSrc+k+bytesOfPerLine)*template2[7]+*(pTempSrc+k+bytesOfPerLine+pixelDepth)*template2[8];
                *(pTempDest + k) = abs(value1) + abs(value2);
            }
        }
    }
}



//krisch算子边缘检测
//算法:8个模板同时作用原始图像数据,所有八个方向中的最大值作为边缘幅度图像的输出
//此算法实现代码有问题
void ImageProcessing::krischEdgeDect(QImage &destImage)
{
    int mask1[9] = {5,5,5,-3,0,-3,-3,-3,-3};
    int mask2[9] = {-3,5,5,-3,0,5,-3,-3,-3};
    int mask3[9] = {-3,-3,5,-3,0,5,-3,-3,5};
    int mask4[9] = {-3,-3,-3,-3,0,5,-3,5,5};
    int mask5[9] = {-3,-3,-3,-3,0,-3,5,5,5};
    int mask6[9] = {-3,-3,-3,5,0,-3,5,5,-3};
    int mask7[9] = {5,-3,-3,5,0,-3,5,-3,-3};
    int mask8[9] = {5,5,-3,5,0,-3,-3,-3,-3};

    QImage image = destImage;

    int *mask[8] = {mask1,mask2,mask3,mask4,mask5,mask6,mask7,mask8};


    for(int i = 0;i < 8;i += 2)
    {
        twoTemplate(image.bits(),destImage.bits(),mask[i],mask[i+1]);
        image = destImage;
    }
}



//图像直方图均衡化
//算法：g(x,y)处的像素值等于所有小于f(x,y)处的像素值的个数之和再乘以最大灰度值后除以图像的面积
//也就是除以(width * height)
void ImageProcessing::equal(BYTE *pSrcData, BYTE *pDestData, LONG *grayCount)
{
    int i,j;
    int map[256];
    LONG tempCount;
    BYTE *pTempSrc,*pTempDest;
    int pixelDepth = depth / 8;

    //计算灰度映射表
    for(i = 0;i < 256;i++)
    {
        tempCount = 0;
        for(j = 0;j <= i;j++)
        {
            tempCount += grayCount[j];
        }

        map[i] = tempCount * 255 / width / height;
    }

    for(i = 0;i< height;i++)
    {
        for(j = 0;j< width;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;
            for(int k = 0;k <= pixelDepth -1;k++)
            {
                *(pTempDest + k) = map[*(pTempSrc + k)];
            }
        }
    }
}



void ImageProcessing::thresholdChange(BYTE *pSrcData, BYTE *pDestData, int threshold)
{
    int i,j;
    BYTE *pTempSrc,*pTempDest;
    int pixelDepth = depth / 8;

    for(i = 0;i < height - 1;i++)
    {
        for(j = 0;j < height - 1;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth *j;

            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                if(*(pTempSrc + k) < threshold)
                    *(pTempDest + k) = 0;
                else
                    *(pTempDest + k) = 255;
            }
        }
    }
}

//图像缩放处理
void ImageProcessing::zoomImage(QImage &srcImage, QImage &destImage, float fx, float fy)
{
    int dest_i,dest_j;
    BYTE *pTempDest,*pTempSrc;
    int pixelDepth = depth / 8;

    LONG src_i,src_j;

    for(dest_i = 0;dest_i < destImage.height();dest_i++)
    {
        for(dest_j = 0;dest_j < destImage.width();dest_j++)
        {
            pTempDest = destImage.bits() + dest_i * destImage.bytesPerLine() + pixelDepth * dest_j;
            src_i = (LONG)(dest_i / fx + 0.5);
            src_j = (LONG) (dest_j / fy + 0.5);
            pTempSrc = srcImage.bits() + src_i * srcImage.bytesPerLine() + pixelDepth * src_j;
            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                //判断是否在原图范围内
                if((src_i >= 0 ) && (src_i <= srcImage.height()) && (src_j >= 0) && (src_j <= srcImage.width()))
                {
                    *(pTempDest + k) = *(pTempSrc + k);
                }
                else
                    *(pTempDest + k) = 255;    //对于原图像中没有的像素，直接赋值为255
            }
        }
    }
}


//灰度的线性变换
//算法:g(x,y) = f(x,y) * gradient + intercept
//输入参数:pSrcData:指向原始数据指针 pDestData:指向处理后的数据指针 gradient:线性变换的斜率
//intercept:线性变换的截距
void ImageProcessing::linearTransform(BYTE *pSrcData, BYTE *pDestData, int gradient, int intercept)
{
    int i,j;
    int pixelDepth = depth / 8;
    BYTE *pTempDest,*pTempSrc;

    for(i = 0;i< height;i++)
    {
        for(j = 0;j< width;j++)
        {
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j;
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;

            for(int k = 0;k <= pixelDepth - 1;k++)
            {
                *(pTempDest + k) = *(pTempSrc + k) * gradient + intercept;
                if(*(pTempDest + k) < 0)
                    *(pTempDest + k) = 0;
                if(*(pTempDest + k) > 255)
                    *(pTempDest + k) = 255;
            }
        }
    }
}



//灰度的拉伸
//算法:g(x,y) = (cooy1_y / coor1_x) * f(x,y) if f(x,y) < coor1_x
//g(x,y) = (coor2_y - coor1_y) * ( f(x,y) - coor1_x ) / (coor2_x - coor1_x) + coor1_y if coor1_x < f(x,y) < coor2_x
//g(x,y) = (255 - coor2_y) *( f(x,y) - coor2_x) / (255 - coor2_x) + coor2_y if f(x,y) > coor2_x
//输入参数:pSrcData:指向原始数据的指针 pDestData:指向处理后的数据的指针 coor1_x:第一个X坐标 coor1_y:第一个Y坐标
//coor2_x:第二个X坐标 coor2_y:第二个Y坐标
void ImageProcessing::grayExtend(BYTE *pSrcData, BYTE *pDestData, int coor1_x, int coor1_y, int coor2_x, int coor2_y)
{
    int i,j;
    BYTE *pTempDest,*pTempSrc;
    int pixelDepth = depth / 8;

    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            pTempDest = pDestData + i * bytesOfPerLine + pixelDepth * j;
            pTempSrc = pSrcData + i * bytesOfPerLine + pixelDepth * j ;

            for(int k = 0; k <= pixelDepth - 1;k++)
            {
                if(*(pTempSrc + k) < coor1_x)
                {
                    *(pTempDest + k) = *(pTempSrc + k) * ((float)(coor1_y ) / (float)(coor1_x)) ;
                }
                else if(coor1_x <= *(pTempSrc + k) && *(pTempSrc + k) < coor2_x)
                {
                    *(pTempDest + k) = ((float)((*(pTempSrc+k) - coor1_x) * (coor2_y - coor1_y))) / (float)(coor2_x - coor1_x) + coor1_y;
                }
                else
                    *(pTempDest + k) = ((float)((255 - coor2_y)*(*(pTempSrc+k)-coor2_x))) / (float)(255 - coor2_x) + coor2_y;
            }
        }
    }
}
