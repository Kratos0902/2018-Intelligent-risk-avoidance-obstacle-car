#ifndef CONFIG_H
#define CONFIG_H

//����������� //��tb6612ģ��
#define AIN1 PAout(7)
#define AIN2 PAout(5)
#define BIN1 PAout(4)
#define BIN2 PAout(6)

//��翪������ ��翪���ܽ��յ��ź�ʱΪ�͵�ƽ
#define FPS PBin(8)//��ǰ���Ĺ�翪��
#define LPS PBin(6)//�������ֱ�Ĺ�翪��
#define RPS PBin(7)//���ұߵĹ�翪��
#define RMS PBin(9)//�������ұߵĹ�翪��
#define LMS1 PBin(11)//����������ߵĹ�翪��
#define LMS2 PBin(10)//������ƫ��Ĺ�翪��

extern unsigned int vl;//�����ʼת��
extern unsigned int vr;

#endif // CONFIG_H
