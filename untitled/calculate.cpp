#include "calculate.h"
#include "QDebug"

Calculate::Calculate(SETTINGS *itemSetting)
{
    this->itemSetting=itemSetting;
}

bool Calculate::isBrickRD(int widthWall)
{
    return widthWall%this->itemSetting->maxWidthBrickR==0?false:true;
}

int Calculate::colBrickBigWall(int widthWall)
{
    return qFloor(widthWall/this->itemSetting->maxWidthBrickR);
}

int Calculate::rowBrickBigWall(int heightWall)
{
    return qFloor(heightWall/this->itemSetting->heightBrickR);
}

FENCE Calculate::GetCountOnFence(int WidthWall,int HeightWall,bool topWall)
{
    FENCE result;
    if(this->isBrickRD(WidthWall))
    {
        result.count_brick=this->colBrickBigWall(WidthWall)*this->rowBrickBigWall(HeightWall);
        result.count_brick_dob=(int)this->isBrickRD(WidthWall);
        result.count_brick_dob=result.count_brick_dob*this->rowBrickBigWall(HeightWall);
    }else{
        if(this->rowBrickBigWall(HeightWall)>1)
            result.count_brick_dob=2*qFloor(this->rowBrickBigWall(HeightWall)/2);
        result.count_brick=this->colBrickBigWall(WidthWall)*
                          (qFloor(this->rowBrickBigWall(HeightWall)/2)+this->rowBrickBigWall(HeightWall)%2)+
                          (this->colBrickBigWall(WidthWall)-1)*qFloor(this->rowBrickBigWall(HeightWall)/2);
    }
    if(topWall)
        result.count_cover=WidthWall%this->itemSetting->widthWallTop>0?
                    WidthWall/this->itemSetting->widthWallTop+1:WidthWall/this->itemSetting->widthWallTop;
    return result;
}

COLORBRICKWALL Calculate::colorBrickWall(int width,int height)
{
  COLORBRICKWALL brickWall;
  if(this->rowBrickBigWall(height)==1)
  {
    brickWall.colorBrickBigWall.append(qFloor((this->colBrickBigWall(width)/2)+this->colBrickBigWall(width)%2)*
                                       this->rowBrickBigWall(height));
    brickWall.colorBrickBigWall.append(qFloor(this->colBrickBigWall(width)/2)*this->rowBrickBigWall(height));
    brickWall.colorBrickSmallWall.append(0);
    brickWall.colorBrickBigWall.append(0);
    return brickWall;
  }
  if(this->isBrickRD(width))
  {
    brickWall.colorBrickBigWall.append((qFloor(this->colBrickBigWall(width)/2)+this->colBrickBigWall(width)%2)*
                                         this->rowBrickBigWall(height));
    brickWall.colorBrickBigWall.append(qFloor(this->colBrickBigWall(width)/2)*this->rowBrickBigWall(height));
    brickWall.colorBrickSmallWall.append((this->colBrickBigWall(width)+1)%2*
                                           (qFloor(this->rowBrickBigWall(height)/2)+(this->rowBrickBigWall(height)%2)));
    brickWall.colorBrickSmallWall.append(this->rowBrickBigWall(height)-brickWall.colorBrickSmallWall.at(0));

  }else{
    brickWall.colorBrickSmallWall.append(this->colBrickBigWall(width)%2>0?
                                         qFloor(this->rowBrickBigWall(height)/2):0);
    brickWall.colorBrickSmallWall.append(this->colBrickBigWall(width)%2==0?qFloor(this->rowBrickBigWall(height)/2)*2:
                                                                           qFloor(this->rowBrickBigWall(height)/2));
    brickWall.colorBrickBigWall.append((qFloor(this->colBrickBigWall(width)/2)+this->colBrickBigWall(width)%2)*
                                           (qFloor(this->rowBrickBigWall(height)/2)+this->rowBrickBigWall(height)%2)+
                                           (qFloor(this->rowBrickBigWall(height)/2)*(qFloor((this->colBrickBigWall(width)-1)/2)+
                                                                             (this->colBrickBigWall(width)-1)%2)));
    brickWall.colorBrickBigWall.append(qFloor(this->colBrickBigWall(width)/2)*
                                        (qFloor(this->rowBrickBigWall(height)/2)+this->rowBrickBigWall(height)%2)+
                                        (qFloor(this->rowBrickBigWall(height)/2)*(qFloor((this->colBrickBigWall(width)-1)/2))));
  }
  return brickWall;
}

COLORBRICKWALL Calculate::colorListBrickWall(int width,int height)
{
    COLORBRICKWALL brickWall;
    if(this->isBrickRD(width))
    {
        for(int i=0;i<this->rowBrickBigWall(height);i++)
        {
            brickWall.colorBrickBigWall.append(this->colBrickBigWall(width));
            brickWall.colorBrickSmallWall.append(1);
        }
    }else{
        for(int i=0;i<this->rowBrickBigWall(height);i++)
        {
            brickWall.colorBrickBigWall.append((i+1)%2==0?this->colBrickBigWall(width)-1:
                                                          this->colBrickBigWall(width));
            brickWall.colorBrickSmallWall.append((i+1)%2==0?2:0);
        }
    }
    return brickWall;
}

COLORBRICKPILLAR Calculate::colorBrickPillar(int height, int *insert)
{
    COLORBRICKPILLAR colorBrick;
    colorBrick.colorBrickSmallWall.append(qFloor(insert[2]/this->itemSetting->heightBrickAngle)+
                                          qFloor(insert[3]/this->itemSetting->heightBrickAngle));
    colorBrick.colorBrickSmallWall.append(qFloor(insert[0]/this->itemSetting->heightBrickAngle)+
                                          qFloor(insert[1]/this->itemSetting->heightBrickAngle));
    colorBrick.colorBrickBigWall.append(qFloor(height/this->itemSetting->heightBrickAngle)*2-
                                        colorBrick.colorBrickSmallWall.at(0));
    colorBrick.colorBrickBigWall.append(qFloor(height/this->itemSetting->heightBrickAngle)*2-
                                        colorBrick.colorBrickSmallWall.at(1));
    return colorBrick;
}

COLORBRICKPILLAR Calculate::colorListBrickPillar(int height, int *insert)
{
    COLORBRICKPILLAR colorBrick;
    for(int i=0;i<qFloor(height/this->itemSetting->heightBrickAngle);i++)
    {
        int angleBrick=(i+1)<=qFloor(insert[0]/this->itemSetting->heightBrickAngle)?1:0;
        angleBrick=(i+1)<=qFloor(insert[1]/this->itemSetting->heightBrickAngle)?angleBrick+1:angleBrick;
        angleBrick=(i+1)<=qFloor(insert[2]/this->itemSetting->heightBrickAngle)?angleBrick+1:angleBrick;
        angleBrick=(i+1)<=qFloor(insert[3]/this->itemSetting->heightBrickAngle)?angleBrick+1:angleBrick;
        colorBrick.colorBrickSmallWall.append(angleBrick);
        colorBrick.colorBrickBigWall.append(4-angleBrick);
    }
    return colorBrick;
}
//---------------------------------------------------------------


COLUMN Calculate::GetCountOnColumn(int HeightPillar,int* Insert,int CountSide)
{
    COLUMN result;
    int tmp_height_brick_angle=HeightPillar/this->itemSetting->heightBrickAngle;
    if (CountSide==0)
    {
        result.count_brick_angle=tmp_height_brick_angle*4;
        return result;
    }
    int tmp_height_brick_angle1=0;
    int tmp_height_brick_angle2=0;
    int tmp_height_brick_angle3=0;
    int tmp_height_brick_angle4=0;
    int j=0;
    for (int i=0;i<CountSide;i++)
    {
        if (i==0)
        {
            int tmp=Insert[j]/this->itemSetting->heightBrickAngle;
            tmp+=Insert[j+1]/this->itemSetting->heightBrickAngle;
            tmp_height_brick_angle1=tmp;
        }
        if (i==1)
        {
            int tmp=Insert[j]/this->itemSetting->heightBrickAngle;
            tmp+=Insert[j+1]/this->itemSetting->heightBrickAngle;
            tmp_height_brick_angle2=tmp;
        }
        if (i==2)
        {
            int tmp=Insert[j]/this->itemSetting->heightBrickAngle;
            tmp+=Insert[j+1]/this->itemSetting->heightBrickAngle;
            tmp_height_brick_angle3=tmp;
        }
        if (i==3)
        {
            int tmp=Insert[j]/this->itemSetting->heightBrickAngle;
            tmp+=Insert[j+1]/this->itemSetting->heightBrickAngle;
            tmp_height_brick_angle4=tmp;
        }
        j+=2;
    }
    result.count_brick_angle=tmp_height_brick_angle*4-tmp_height_brick_angle1-tmp_height_brick_angle2-tmp_height_brick_angle3-tmp_height_brick_angle4;
    result.count_brick_angle_1=tmp_height_brick_angle1;
    result.count_brick_angle_2=tmp_height_brick_angle2;
    result.count_brick_angle_3=tmp_height_brick_angle3;
    result.count_brick_angle_4=tmp_height_brick_angle4;
    return result;
}

int Calculate::getCountBrickAngle(int heightInsert)
{
    return qFloor(heightInsert/this->itemSetting->heightBrickAngle);
}

bool Calculate::BrickAngleBottom(int indexRow,int heightInsert)
{
    return heightInsert/this->itemSetting->heightBrickAngle>=indexRow?true:false;
}

bool Calculate::BrickAngleTop(int indexRow, int heightPillar, int heightInsert)
{
    return heightInsert==0?false:heightPillar/this->itemSetting->heightBrickAngle-heightInsert/this->itemSetting->heightBrickAngle<indexRow?true:false;
}

//---------------------------------------------------------------


int Calculate::GetCountBrickAngleOnPallet(int Count)
{
    float a=Count;
    float b=Count%224;
    return b/224==0?a/224:b/224>=0.4?qCeil(a/224):qFloor(a/224);
}


int Calculate::GetCountBrickAnglePrimOnPallet(int Count)
{
    float a=Count;
    float b=Count%224;
    return b/224==0?a/224:b/224>=0.4?qCeil(a/224):qFloor(a/224);
}


int Calculate::GetCountCoverColumnOnPallet(int Count)
{
    if (Count%50>0)
    {
        return Count/50+1;
    }else
    {
        return Count/50;
    }
}


int Calculate::GetCountBrickOnPallet(int Count)
{
    float a=Count;
    float b=Count%161;
    return b/161==0?a/161:b/161>=0.4?qCeil(a/161):qFloor(a/161);
}


int Calculate::GetCountBrickDobOnPallet(int Count)
{
    float a=Count;
    float b=Count%280;
    return b/280==0?a/280:b/280>=0.4?qCeil(a/280):qFloor(a/280);
}


int Calculate::GetCountCoverOnPallet(int Count)
{
    if (Count%90>0)
    {
        return Count/90+1;
    }else
    {
        return Count/90;
    }
}

int Calculate::GetCountBaseOnPallet(int Count)
{
    if (Count%12>0)
    {
        return Count/12+1;
    }else
    {
        return Count/12;
    }
}
