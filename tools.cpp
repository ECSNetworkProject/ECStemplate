#pragma once
#include "tools.h"


// ����ɫ���
ARGB color2Argb(DWORD c)
{
	ARGB res;
	res.r = (byte)c;
	res.g = (byte)(c >> 8);
	res.b = (byte)(c >> 16);
	res.a = (byte(c >> 24));
	return res;
}

DWORD argb2Color(ARGB c)
{
	DWORD t = RGB(c.r, c.g, c.b);
	return ((DWORD)c.a) << 24 | t;
}
//�Ѳ�ɫͼת�ɺڰ�ͼ
void toGray(IMAGE* src)
{
	DWORD* psrc = GetImageBuffer(src);
	for (int i = 0; i < src->getwidth() * src->getheight(); i++)
	{
		//��ȡÿһ�����ص����ɫֵ
		ARGB t = color2Argb(psrc[i]);
		//�Ҷ�ͼ,�����������ĸ���ɫֵ�ľ�ֵ
		byte arv = (t.r + t.g + t.b) / 3;
		ARGB res = { t.a,arv,arv,arv };
		psrc[i] = argb2Color(res);
	}
}
/*
*@png͸����ͼ
*/
void drawImg(int x, int y, IMAGE* src)
{
	//������ʼ��
	DWORD* pwin = GetImageBuffer();		//���ڻ�����ָ��
	DWORD* psrc = GetImageBuffer(src);	//ͼƬ������ָ��
	int win_w = getwidth();				//���ڿ��
	int win_h = getheight();
	int src_w = src->getwidth();		//ͼƬ���
	int src_h = src->getheight();

	//������ͼ��ʱ�䳤��
	int real_w = (x + src_w > win_w) ? win_w - x : src_w;		//�������ұ߽�
	int real_h = (y + src_h > win_h) ? win_h - y : src_h;		//�������±߽�
	if (x < 0) { psrc += -x;			real_w -= -x;	x = 0; }	//��������߽�
	if (y < 0) { psrc += (src_w * -y);	real_h -= -y;	y = 0; }	//�������ϱ߽�

	//������ͼ��ʼλ��
	pwin += (win_w * y + x);

	//ʵ��͸����ͼ
	for (int iy = 0; iy < real_h; iy++)
	{
		for (int ix = 0; ix < real_w; ix++)
		{
			byte a = (byte)(psrc[ix] >> 24);//����͸��ͨ����ֵ[0,256] 0��ȫ͸�� 255��ȫ��͸��
			if (a > 100)
			{
				pwin[ix] = psrc[ix];
			}
		}
		//������һ��
		pwin += win_w;
		psrc += src_w;
	}
}
