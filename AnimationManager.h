#pragma once
#include "MonoObject.h"
#include<map>
#include<vector>
#include<easyx.h>
using namespace std;

//��������
enum animationType
{
    Man_Idle,
    Man_walk,
    DebuffMan_walk,
    Pig_Idle,
    Pig_Walk,
    Ghost_fly,
    Pangxie_walk,
    Bat_fly,
    Coin_rotate,
    Musicbox
};
class AnimationManager :virtual public  MonoObject
{
public:
    AnimationManager(); 
    virtual ~AnimationManager();
    virtual void onFrameUpdate();

    //��ʼ��
    void initAnimation(animationType animType, int sizeX=0, int sizeY=0);
    //���Ŷ���
    void playAnimation(int x, int y);
private:
    //��������
    void createAnimation(const vector<wstring>& filenames, int sizeX, int sizeY);
    //��mapʹ�������ͺ͸ö�������
    map<animationType, vector<IMAGE>> animations;
    //���ڴ洢��Ҫ���ŵĶ�������
    animationType finalType;
    //����ѭ��������һ������
    int i;
};