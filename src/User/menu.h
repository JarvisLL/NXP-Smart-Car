#ifndef __MENU_H
#define __MENU_H

/*矩阵软键盘示意图                程序里面对应读取的值
  1  2  3  A                        1   2   3   4
                                    
  4  5  6  B                        5   6   7   8
                  --------------> 
  7  8  9  C                        9   10  11  12   
 
  *  0  #  D                        13  14  15  16

*/

#define  KEY_EXIT       13   //退出键
 
#define  KEY_UP         4   //上
 
#define  KEY_OK         15  //确认键

#define  KEY_LEFT       12  //左键
   
#define  KEY_DOWN       8   //下

#define  KEY_RIGHT      16  //右
   
 #include "common.h"
 #include "include.h"
u8 Key_Scan();
void view_main_menu_refresh(int8 line_num);
void view_main_menu(void);
void view_inductor_setting(void);
void view_servo_setting(void);
void view_servo_menu_refresh(int8 line_num);
void view_inductor_menu_refresh(int8 line_num);
void view_inductor_setting_scan(void);
void view_thrhd_menu_refresh(int8 line_num);
void view_thrhd_setting(void);
void view_motor_menu_refresh(int8 line_num);
void view_motor_setting(void);
#endif