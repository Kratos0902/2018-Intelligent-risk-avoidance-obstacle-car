#ifndef CONFIG_H
#define CONFIG_H

//电机正反引脚 //接tb6612模块
#define AIN1 PAout(7)
#define AIN2 PAout(5)
#define BIN1 PAout(4)
#define BIN2 PAout(6)

//光电开关引脚 光电开关能接收到信号时为低电平
#define FPS PBin(8)//最前方的光电开关
#define LPS PBin(6)//最左边竖直的光电开关
#define RPS PBin(7)//最右边的光电开关
#define RMS PBin(9)//底盘上右边的光电开关
#define LMS1 PBin(11)//底盘上最左边的光电开关
#define LMS2 PBin(10)//底盘上偏左的光电开关

extern unsigned int vl;//电机初始转速
extern unsigned int vr;

#endif // CONFIG_H
