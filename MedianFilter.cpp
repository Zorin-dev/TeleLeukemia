//#include "MedianFilter.h"


void MedianF(QImage &dst, int r)
{
    QImage src(dst);

    int r2=2*r+1; //пикселей в строке
    int r3=(2*r+1)*(2*r+1); //размер массива
    const int r4=(r3-r2);//кол-во анализируемых строк -1
    const int r6=(r3-1)/2;//средний элемент массива

    byte *massB = new byte [r3];
    byte *massG = new byte [r3];
    byte *massR = new byte [r3];

    ImageLink imDst(dst.width(),dst.height(),dst.bits());
    ImageLink imSrc(src.width(),src.height(),src.bits());

    for(int j=0;j<static_cast<int>(imSrc.height());++j)//Цикл по строкам
    {
        for( int i=0;i<static_cast<int>(imSrc.width());++i)//Цикл по пикселям
        {
            for(int k=-r,m=0;k<=r,m<r4;++k,m+=r2)
            {
                if((j+k<0)||(j+k>static_cast<int>(imSrc.height()-1)))
                    continue;
                for(int n=0,x=-r;x<=r,n<r2;++x,++n)
                {
                    if(i+x<0)
                        massB[n+m]=imSrc.b((i+x)+r,j+k); //srcv[j][(i+x)+r5];
                    else if (i+x>static_cast<int>(imSrc.width()))
                        massB[n+m]=imSrc.b((x+i)-r,j+k);// srcv[j][(x+i)-r5];
                    else
                        massB[n+m]=imSrc.b(i+x,j+k);// srcv[j][i+x];
                }
                for(int n=0,x=-r;x<=r,n<r2;++x,++n)
                {
                    if(i+x<0)
                        massG[n+m]=imSrc.g((i+x)+r,j+k); //srcv[j][(i+x)+r5];
                    else if (i+x>static_cast<int>(imSrc.width()))
                        massG[n+m]=imSrc.g((x+i)-r,j+k);// srcv[j][(x+i)-r5];
                    else
                        massG[n+m]=imSrc.g(i+x,j+k);// srcv[j][i+x];
                }
                for(int n=0,x=-r;x<=r,n<r2;++x,++n)
                {
                    if(i+x<0)
                        massR[n+m]=imSrc.r((i+x)+r,j+k); //srcv[j][(i+x)+r5];
                    else if (i+x>static_cast<int>(imSrc.width()))
                        massR[n+m]=imSrc.r((x+i)-r,j+k);// srcv[j][(x+i)-r5];
                    else
                        massR[n+m]=imSrc.r(i+x,j+k);// srcv[j][i+x];
                }
            }
            std::nth_element(massB,massB+r6,massB+r3);           // nth_element
            imDst.b(i,j) = massB[r6];
            std::nth_element(massG,massG+r6,massG+r3);
            imDst.g(i,j) = massG[r6];
            std::nth_element(massR,massR+r6,massR+r3);
            imDst.r(i,j) = massR[r6];
        }//Конец цикла по тройкам байтов строки

    }
}
/*lyr::TLayer24 Lsrc(Ldst);
int r2=2*r+1; //пикселей в строке
int r3=(2*r+1)*(2*r+1); //размер массива
const int r4=(r3-r2);//кол-во анализируемых строк -1
const int r6=(r3-1)/2;//средний элемент массива
Byte *massB = new Byte [r3];
Byte *massG = new Byte [r3];
Byte *massR = new Byte [r3];
Form1->Bar->Max=Lsrc.H;
Form1->Bar->Position=0;
for(int j=0;j<static_cast<int>(Lsrc.H);++j)//Цикл по строкам
{
    for( int i=0;i<static_cast<int>(Lsrc.W);++i)//Цикл по пикселям
    {
        for(int k=-r,m=0;k<=r,m<r4;++k,m+=r2)
        {
            if((j+k<0)||(j+k>static_cast<int>(Lsrc.H-1)))
                continue;
            for(int n=0,x=-r;x<=r,n<r2;++x,++n)
            {
                if(i+x<0)
                    massB[n+m]=Lsrc((i+x)+r,j+k).comp[b_rgb]; //srcv[j][(i+x)+r5];
                else if (i+x>static_cast<int>(Lsrc.W))
                    massB[n+m]=Lsrc((x+i)-r,j+k).comp[b_rgb];// srcv[j][(x+i)-r5];
                else
                    massB[n+m]=Lsrc(i+x,j+k).comp[b_rgb];// srcv[j][i+x];
            }
            for(int n=0,x=-r;x<=r,n<r2;++x,++n)
            {
                if(i+x<0)
                    massG[n+m]=Lsrc((i+x)+r,j+k).comp[g_rgb]; //srcv[j][(i+x)+r5];
                else if (i+x>static_cast<int>(Lsrc.W))
                    massG[n+m]=Lsrc((x+i)-r,j+k).comp[g_rgb];// srcv[j][(x+i)-r5];
                else
                    massG[n+m]=Lsrc(i+x,j+k).comp[g_rgb];// srcv[j][i+x];
            }
            for(int n=0,x=-r;x<=r,n<r2;++x,++n)
            {
                if(i+x<0)
                    massR[n+m]=Lsrc((i+x)+r,j+k).comp[r_rgb]; //srcv[j][(i+x)+r5];
                else if (i+x>static_cast<int>(Lsrc.W))
                    massR[n+m]=Lsrc((x+i)-r,j+k).comp[r_rgb];// srcv[j][(x+i)-r5];
                else
                    massR[n+m]=Lsrc(i+x,j+k).comp[r_rgb];// srcv[j][i+x];
            }
        }
        std::nth_element(massB,massB+r6,massB+r3);           // nth_element
        Ldst(i,j).comp[b_rgb]=massB[r6];
        std::nth_element(massG,massG+r6,massG+r3);
        Ldst(i,j).comp[g_rgb]=massG[r6];
        std::nth_element(massR,massR+r6,massR+r3);
        Ldst(i,j).comp[r_rgb]=massR[r6];
    }//Конец цикла по тройкам байтов строки
++Form1->Bar->Position;
Form1->Bar->Refresh();
}//Конец цикла по строкам
delete []massB;
delete []massG;
delete []massR;*/
