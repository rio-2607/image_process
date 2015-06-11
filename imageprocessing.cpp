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
    //��grayCountԪ������
    for(int k=0;k<256;k++)
        grayCount[k] = 0;
    int i,j;
    BYTE *pImage;
    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            if(8 == depth)          //8λֵ����
            {
                pImage = pImageData + i * bytesOfPerLine + j;
                grayCount[*pImage]++;
            }
           // grayValue =  0.299 * R + 0.587 * G + 0.114 * B
            else if(32 == depth)    //32λֵ����
            {
                pImage = pImageData + i * bytesOfPerLine + 4 * j;
//                LONG value = (*(pImage+1)*30 + *(pImage+2)*59 + *(pImage+3)*11) / 100;//RGBת��Ϊ�Ҷ�
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

//ͼ���ƽ��pSrcData����ԭʼ���ݵ�ָ��,pDestData�����������ݵ�ָ��,xoffset����ˮƽƫ����,yoffse����ֱƫ����
//���ֱ�Ӹı�pDestData,�������й��̻ᷢ�����󣬵��ǣ����ͨ���м����temp=pDestData,
//temp=pDestData + i * bytesOfPerLine + j,����Ͳ��ᷢ���ڴ����.Ϊʲô��
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

    //��ƽ�Ƴ�ȥ�����ص㸳ֵΪ255
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



//ͼ����任,pSrcData����Դ����ָ��,pDestData������������ָ��,direct�����򣺴�ֱ����ˮƽ
//direct=true���ʾˮƽ����任��false��ʾ��ֱ����任
//ԭ��:ˮƽ�任��ʽ:x1=width-x0,y1=x1(xo,y0)Ϊԭʼ��������,(x1,y1)Ϊ�任�������
//��ֱ�任��ʽ:x0=x1,y0=height-y1
//��δ����д����ƣ����Ը�����
void ImageProcessing::miirroredTran(BYTE *pSrcData, BYTE *pDestData, bool direct)
{
    int src_i,src_j,dest_i,dest_j;
    BYTE *pTempSrc,*pTempDest;
    if(direct)                  //�����ˮƽ����Գ�
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



//ͼ��ת��,�������pSrcData:׼��ת�õ�ͼ����׵�ַ,pDestData:ת�ú��ͼ����׵�ַ
void ImageProcessing::transpositionImage(BYTE *pSrcData, BYTE *pDestData)
{
    BYTE *pTempSrc,*pTempDest;
    long bytesOfPerColumn;          //ÿ�е��ֽڸ���

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


//ͼ���ݶ���,�������pSrcData:׼��ת�õ�ͼ����׵�ַ,pDestData:ת�ú��ͼ����׵�ַ
//�㷨ԭ��:g(i,j) = |f(i,j) - f(i+1,j)| + |f(i,j) - f(i,j+1)|
//Robert�ݶ�:g(i,j) = |f(i,j) - f(i+1,j+1)| + |f(i+1,j) - f(i,j+1)|
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



//RGB��ɫͼ��ת��Ϊ�Ҷ�ͼ��
//�㷨:grayValue =  0.299 * R + 0.587 * G + 0.114 * B
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
//������˹��
//               | 0 -1  0 |
//  ʹ�õ���ģ����|-1  5 -1 |
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


//ģ�����,�������pSrcData:ԭͼ��ָ��,pDestData:������ͼ���ָ��
//mask:һ�����飬�����Ա��ÿ��ģ��Ԫ��
//coefficient:ģ��ϵ����ע�⣺�������������coefficientһ��Ҫ��֤�Ǹ�����������:
//��������coefficient=1/9��������ͼ������ֵΪȫ��,Ӧ�ô���(1.0) / (9.0)
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


//�������򣬲��õ���ð������
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


//ͼ����ֵ�˲�
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


//Roberts���ӱ�Ե���
//�㷨ԭ��:g(i,j) = |f(i,j) - f(i+1,j+1)| + |f(i+1,j) - f(i,j+1)|
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


//sobel���ӱ�Ե���
//�㷨��������ģ����ͼ��ÿ�����ؾ��,�Ѿ�����ȡ����ֵ�����
//ģ��һ[-1,-2,-1,(����)0,0,0(����)1,2,1]ģ���[-1,0,1,(����)-2,0,2,(����)-1,0,1]
void ImageProcessing::sobelEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
    int mask1[9] = {-1,-2,-1,0,0,0,1,2,1};
    int mask2[9] = {-1,0,1,-2,0,2,-1,0,1};
    twoTemplate(pSrcData,pDestData,mask1,mask2);

}


//prewitt���ӱ�Ե���
//�㷨��������ģ����ͼ��ÿ�����ؾ��,�Ѿ�����ȡ����ֵ�����
//ģ��һ[-1,-1,-1,(����)0,0,0(����)1,1,1]ģ���[1,0,-1,(����)1,0,-1,(����)1,0,-1]
void ImageProcessing::prewittEdgeDect(BYTE *pSrcData, BYTE *pDestData)
{
    int mask1[9] = {-1,-1,-1,0,0,0,1,1,1};
    int mask2[9] = {1,0,-1,1,0,-1,1,0,-1};
    twoTemplate(pSrcData,pDestData,mask1,mask2);
}


//������˹���ӱ�Ե���
//�㷨ԭ��:g(x,y) = 4f(x,y) - f(x-1,y) - f(x+1,y) -f(x,y-1) -f(x,y+1)
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


//����ģ��ͬʱ����ʱ������
//�������:pSrcData:ָ��ԭʼ����ָ��;pDestData:ֻ�봦��������ָ��
//template1:ָ��ģ��һ��ָ��;tempalte2:ָ��ģ�����ָ��
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



//krisch���ӱ�Ե���
//�㷨:8��ģ��ͬʱ����ԭʼͼ������,���а˸������е����ֵ��Ϊ��Ե����ͼ������
//���㷨ʵ�ִ���������
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



//ͼ��ֱ��ͼ���⻯
//�㷨��g(x,y)��������ֵ��������С��f(x,y)��������ֵ�ĸ���֮���ٳ������Ҷ�ֵ�����ͼ������
//Ҳ���ǳ���(width * height)
void ImageProcessing::equal(BYTE *pSrcData, BYTE *pDestData, LONG *grayCount)
{
    int i,j;
    int map[256];
    LONG tempCount;
    BYTE *pTempSrc,*pTempDest;
    int pixelDepth = depth / 8;

    //����Ҷ�ӳ���
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

//ͼ�����Ŵ���
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
                //�ж��Ƿ���ԭͼ��Χ��
                if((src_i >= 0 ) && (src_i <= srcImage.height()) && (src_j >= 0) && (src_j <= srcImage.width()))
                {
                    *(pTempDest + k) = *(pTempSrc + k);
                }
                else
                    *(pTempDest + k) = 255;    //����ԭͼ����û�е����أ�ֱ�Ӹ�ֵΪ255
            }
        }
    }
}


//�Ҷȵ����Ա任
//�㷨:g(x,y) = f(x,y) * gradient + intercept
//�������:pSrcData:ָ��ԭʼ����ָ�� pDestData:ָ����������ָ�� gradient:���Ա任��б��
//intercept:���Ա任�Ľؾ�
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



//�Ҷȵ�����
//�㷨:g(x,y) = (cooy1_y / coor1_x) * f(x,y) if f(x,y) < coor1_x
//g(x,y) = (coor2_y - coor1_y) * ( f(x,y) - coor1_x ) / (coor2_x - coor1_x) + coor1_y if coor1_x < f(x,y) < coor2_x
//g(x,y) = (255 - coor2_y) *( f(x,y) - coor2_x) / (255 - coor2_x) + coor2_y if f(x,y) > coor2_x
//�������:pSrcData:ָ��ԭʼ���ݵ�ָ�� pDestData:ָ���������ݵ�ָ�� coor1_x:��һ��X���� coor1_y:��һ��Y����
//coor2_x:�ڶ���X���� coor2_y:�ڶ���Y����
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
