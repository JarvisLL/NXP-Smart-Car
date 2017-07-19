#include "include.h"
#include "LQ12864.h"
#include "sensor.h"

extern u8 KeyValue,ModeValue;
extern float Servo_error;
extern u16 sensor_fazhi;
extern int16 timer;
static int main_menu_line_flag=0;
static int inductor_menu_line_flag=0;   //电感界面行选择标志位
static int servo_menu_line_flag=0;   //舵机界面行选择标志位
static int motor_menu_line_flag=0;   //电机界面行选择标志位
static int thrhd_menu_line_flag=0;   //阈值界面行选择标志位

          //模式选择变量

   //主菜单界面行选择标志位

/***********************************************************
 *  * 函数名称  :  Key_Scan
 *  * 参    数  ：
 *  * 功    能  : 按键状态检测, 没有任何键按下时返回0
 *	* 日		期	：2015/03/01
 *	*	作		者	：
************************************************************/
u8 Key_Scan()
{
  if(KeyValue == 4) return KEY_UP;
  else if(KeyValue == 8) return KEY_DOWN;
  else if(KeyValue == 12) return KEY_LEFT;
  else if(KeyValue == 16) return KEY_RIGHT;
  else if( KeyValue == 15) return KEY_OK;
  else if (KeyValue == 13) return KEY_EXIT;
  else return 0;

}
/***********************************************************
 *  * 文件说明：人机交互初始化界面
 *  * 作    者：jarvs_lin
 *  * 日    期：2016/6/30
 *  * 版    本：V1.0
 *  * 修改者  ：
 *  * 修改日期：
 ***********************************************************/
 
  /***********************************************************
 *  * 函数名称  ：view_start_up
 *  * 参    数  ：
 *  * 功    能  :
 *	* 日期	：2016/06/30
 *	*作者	：jarvis_lin
************************************************************/
void view_start_up(void)
{  
   LCD_CLS();
   LCD_P8x16Str(28,2,"Smart Car!");
   LPTMR_delay_ms(100);
   LCD_P8x16Str(20,4,"Loading.....");
   LPTMR_delay_ms(1000);
   LCD_CLS();
   
}

  /**************************蓝旗K60*********************************
 *  * 函数名称  ：view_main_menu
 *  * 参    数  ：
 *  * 功    能  :菜单主界面
 *	* 日		期	：2017/07/6
 *	*	作		者	：jarvis_lin
************************************************************/
void view_main_menu(void)
{
   u8 key_num=0;
 
   view_main_menu_refresh(main_menu_line_flag);
 
   while(1)
    {
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100);             //
      switch(key_num)
      {
        case KEY_DOWN:  //循环顺序0,1,2,3
            main_menu_line_flag++;
            main_menu_line_flag%=4;
            view_main_menu_refresh(main_menu_line_flag);//刷新界面
            break;
          
        case KEY_UP:   //循环顺序0,-3,-2,-1
            main_menu_line_flag--;
            main_menu_line_flag%=4;
            view_main_menu_refresh(main_menu_line_flag);//刷新界面
            break;
            
        case KEY_OK:
            switch(main_menu_line_flag)       //进入当前行号对应的界面
              {
                case 0:  
                    view_inductor_setting();//电感界面
                    break;
                  
                case 1:
                case -3:
                    view_servo_setting(); //舵机界面
                    break;
                                
                case 2:                  
                case -2: 
                    view_motor_setting(); //电机界面
                   break;
               
               case 3:
                case -1:
                    view_thrhd_setting(); //阈值界面
                     break;
           
                default:
                    break;
              } 
            view_main_menu_refresh(main_menu_line_flag);//刷新界面
            break;
            
        case KEY_EXIT:
           LCD_CLS();
           LPTMR_delay_ms(200);
           LCD_P8x16Str(30,3,"Run Now!!!");
          
           LPTMR_delay_ms(2000);

           LCD_CLS();
           //RampRoad.gyro_zero_val = gyro_get_zero();//读取陀螺仪零偏
           LPTMR_delay_ms(2000);
           //Motor.INH = 1;  
           return;//不加退出中断定时不准
           break;
          
        default:
            break;
      }

    }
}

  /***********************************************************
 *  * 函数名称  ：view_main_menu_refresh
 *  * 参    数  ：
 *  * 功    能  :菜单主界面刷新
 *	* 日		期	：2016/06/30
 *	*	作		者	：jarvis_lin
************************************************************/
void view_main_menu_refresh(int8 line_num)
{
  switch(line_num)        //显示当前行号对应的界面,其中上翻与下翻用同一个界面
  {
    case 0:
       
        LCD_CLS();
         LCD_P8x16Str(28,0,"Main Menu");
        INV_LCD_P8x16Str(0,2,"Induc Setting   "); 
        LCD_P8x16Str(0,4,"Servo Setting   ");
        LCD_P8x16Str(0,6,"Motor Setting   ");
        break;
    
        case -3:
    case 1:
    
        LCD_CLS();
        
        LCD_P8x16Str(28,0,"Main Menu");
        LCD_P8x16Str(0,2,"Induc Setting   ");
        INV_LCD_P8x16Str(0,4,"Servo Setting   ");
        LCD_P8x16Str(0,6,"Motor Setting   ");
        break;
    
        case -2:
    case 2:
    
        LCD_CLS();
        LCD_P8x16Str(28,0,"Main Menu");
        LCD_P8x16Str(0,2,"Induc Setting   ");
        LCD_P8x16Str(0,4,"Servo Setting   ");
        INV_LCD_P8x16Str(0,6,"Motor Setting   ");
        break;
        
        
         case -1:
    case 3:
        LCD_CLS();
        LCD_P8x16Str(28,0,"Main Menu");
        LCD_P8x16Str(0,2,"Motor Setting   ");
        LCD_P8x16Str(0,4,"Param Setting   ");
        INV_LCD_P8x16Str(0,6,"Thrhd Setting   ");
        break;
        
   
        
    default:
        break;    
  }

}


  /***********************************************************
 *  * 函数名称  view_induc_setting
 *  * 参    数  ：
 *  * 功    能  : 电感设置界面
 *	* 日		期	：2017/7/7
 *	*	作		者	：jarvis_lin
************************************************************/
void view_inductor_setting(void)
{
  uint8 key_num = 0;
  //进入电感界面
  view_inductor_menu_refresh(inductor_menu_line_flag);
  while(1)
  {
     KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100);
    switch(key_num)
    {        
      case KEY_DOWN:  //循环顺序为0,1,2
          inductor_menu_line_flag++;
          inductor_menu_line_flag%=2;
          view_inductor_menu_refresh(inductor_menu_line_flag);//刷新界面
          break;
          
      case KEY_UP:  //循环顺序为0,-1
          inductor_menu_line_flag--;
          inductor_menu_line_flag%=2;
          view_inductor_menu_refresh(inductor_menu_line_flag);//刷新界面
          break;
        
      case KEY_OK:
          switch(inductor_menu_line_flag)    //按下确认键进入当前行号下对应的界面
            {
              
                  
                   //显示当前电感采样值及对应电压
            case 0:
                  LCD_CLS();
                  while(FKeyboardRead()!=KEY_EXIT)
                    {
                      get_adc_int_val();       //采样电感值
//                      LCD_P8x16Str(4,0,"Induc"); 
//                      LCD_P8x16Str(56,0,"Valu"); 
//                      LCD_P8x16Str(96,0,"Volt"); 
                      LCD_P6x8Str(0,0,"1:");LCD_Write_5_Num(50,0,Adc.ad_avr_val[1]);LCD_Write_double1_3(90,0,Adc.ad_avr_val[1]*2.5/65535.0);
                      LCD_P6x8Str(0,1,"2:");LCD_Write_5_Num(50,1,Adc.ad_avr_val[2]);LCD_Write_double1_3(90,1,Adc.ad_avr_val[2]*2.5/65535.0);
                      LCD_P6x8Str(0,2,"3:");LCD_Write_5_Num(50,2,Adc.ad_avr_val[3]);LCD_Write_double1_3(90,2,Adc.ad_avr_val[3]*2.5/65535.0);
                      LCD_P6x8Str(0,3,"4:");LCD_Write_5_Num(50,3,Adc.ad_avr_val[4]);LCD_Write_double1_3(90,3,Adc.ad_avr_val[4]*2.5/65535.0);
                      LCD_P6x8Str(0,4,"5:");LCD_Write_5_Num(50,4,Adc.ad_avr_val[5]);LCD_Write_double1_3(90,4,Adc.ad_avr_val[5]*2.5/65535.0);
                      LCD_P6x8Str(0,5,"6:");LCD_Write_5_Num(50,5,Adc.ad_avr_val[6]);LCD_Write_double1_3(90,5,Adc.ad_avr_val[6]*2.5/65535.0);                      
                      LPTMR_delay_ms(100);
                    }
                view_inductor_menu_refresh(inductor_menu_line_flag);//刷新界面
                break;
                
              case 1:     //显示距离偏差
              case -1:
                  LCD_CLS();
                  
                  while(FKeyboardRead()!=KEY_EXIT)
                  {
                    deal_sensor(&Sensor);      //处理电感值
                    
                    LCD_P6x8Str(5,2,"error");     
                    LCD_Write_double2_2(0,7,Servo.error[0]);
                                   
                    LPTMR_delay_ms(100);
                  }
                  
                  view_inductor_menu_refresh(inductor_menu_line_flag); //刷新界面
                break;
                
              default:
                break;
            }
          break;
          
      case KEY_EXIT:  //退出电感设置界面
          return;
          break;
      
      default:
        break;    
    }
   LPTMR_delay_ms(50);
  }

}
  /***********************************************************
 *  * 函数名称  view_inductor_setting
 *  * 参    数  ：
 *  * 功    能  : 电感设置界面
 *	* 日		期	：2015/03/15
 *	*	作		者	：Joseph
************************************************************/
void view_inductor_menu_refresh(int8 line_num)
{
  switch(line_num)
  {
   
      
    case 0:
   
      LCD_CLS();
      LCD_P8x16Str(12,0,"Induc Setting");
      INV_LCD_P8x16Str(0,2,"Value           ");
      LCD_P8x16Str(0,6,"Error           ");
      break;
      
    case 1:
    case -1:
      LCD_CLS();
      LCD_P8x16Str(12,0,"Induc Setting");
      LCD_P8x16Str(0,2,"Value           ");
      INV_LCD_P8x16Str(0,6,"Error           ");
      break;
      
    default:
       break;
  }

}

/*********************************************************
*函数名		：view_servo_setting     	*输出结果	：无
*函数描述	：舵机设置界面              *返回值		：无
*输入参数	：无
*********************************************************/
void view_servo_setting(void)
{
   u8 key_num=0;   
   //进入舵机界面
   view_servo_menu_refresh(servo_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //循环顺序为0,1,2
            servo_menu_line_flag++;
            servo_menu_line_flag%=3;
            view_servo_menu_refresh(servo_menu_line_flag);//刷新界面
            break;
          
        case KEY_UP:  //循环顺序为0,-2,-1
            servo_menu_line_flag--;
            servo_menu_line_flag%=3;
            view_servo_menu_refresh(servo_menu_line_flag);//刷新界面
            break;
        

        case KEY_RIGHT:   //参数加
            switch(servo_menu_line_flag)
              {
                case 0:     
                  Servo.pulse_width += 50;
                  FTM_PWM_Duty(FTM2,FTM_CH0,Servo.pulse_width); 
                    break;
                case 1:      
                case -2:
                    Servo.kp += 0.5;
                    break;
                case 2:     
                case -1:
                    Servo.kd += 0.5;
                    break;
                        
                default:
                  break;
              }
            view_servo_menu_refresh(servo_menu_line_flag);//刷新界面
            break;
            
        case KEY_LEFT:  //参数减
            switch(servo_menu_line_flag)
              {
                case 0:    
                  Servo.pulse_width -= 50;  //舵机中间值
                  FTM_PWM_Duty(FTM2,FTM_CH0,Servo.pulse_width); 
                    break;
                case 1:      
                case -2:
                    Servo.kp -= 0.5;
                    if(Servo.kp < 0)
                      Servo.kp = 0;
                    break;
                case 2:     
                case -1:
                    Servo.kd -= 0.5;
                    if(Servo.kd < 0)
                      Servo.kd = 0;                   
                    break;
                                  
                default:
                  break;
              }
            view_servo_menu_refresh(servo_menu_line_flag);//刷新界面
            break;
            
        case KEY_OK:   //保存参数
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //退出舵机设置界面，还原参数
              LCD_CLS();
              LPTMR_delay_ms(200);
              LCD_P8x16Str(30,3,"not Saving");
            return;
            break;
            
        default:
            break;
      }
         
   }


}

/*********************************************************
*函数名		：view_servo_menu_refresh    *输出结果	：无
*函数描述	：舵机界面刷新                *返回值		：无
*输入参数	：无
*********************************************************/
void view_servo_menu_refresh(int8 line_num)
{

  switch(line_num)
  {
    case 0:
      LCD_CLS();
      LCD_P8x16Str(12,0,"Servo Setting");
  INV_LCD_P8x16Str(0,2,"PWidth: ");LCD_Write_5_Num(65,2,Servo.pulse_width);     
      LCD_P8x16Str(0,4,"Servo_P:");LCD_Write_double2_2(80,4,Servo.kp);
      LCD_P8x16Str(0,6,"Servo_D:");LCD_Write_double2_2(80,6,Servo.kd); 
      break;
      
    case 1:
    case -2:
      LCD_CLS();
      LCD_P8x16Str(12,0,"Servo Setting");
      LCD_P8x16Str(0,2,"PWidth   :   ");LCD_Write_5_Num(65,2,Servo.pulse_width);     
  INV_LCD_P8x16Str(0,4,"Servo_P:");LCD_Write_double2_2(80,4,Servo.kp);     
      LCD_P8x16Str(0,6,"Servo_D:");LCD_Write_double2_2(80,6,Servo.kd);     
    
    break;
    
  case 2:
    case -1:
      LCD_CLS();
      LCD_P8x16Str(12,0,"Servo Setting");
      LCD_P8x16Str(0,2,"PWidth   :"); LCD_Write_5_Num(65,2,Servo.pulse_width);    
      LCD_P8x16Str(0,4,"Servo_P:");    LCD_Write_double2_2(80,4,Servo.kp);
  INV_LCD_P8x16Str(0,6,"Servo_D:");    LCD_Write_double2_2(80,6,Servo.kd);

      break;
               
    default:
       break;
  }

}




/*********************************************************
*函数名		：view_thrhd_setting     	*输出结果	：无
*函数描述	：阀值设置界面             *返回值		：无
*输入参数	：无
*********************************************************/
void view_thrhd_setting(void)
{
   u8 key_num=0;   
   //进入阀值界面
   view_thrhd_menu_refresh(thrhd_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //循环顺序为0,1,2
            thrhd_menu_line_flag++;
            thrhd_menu_line_flag%=3;
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//刷新界面
            break;
          
        case KEY_UP:  //循环顺序为0,-2,-1
            thrhd_menu_line_flag--;
            thrhd_menu_line_flag%=3;
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//刷新界面
            break;
        

        case KEY_RIGHT:   //参数加
            switch(thrhd_menu_line_flag)
              {
                case 0:
                  Servo_error += 0.1;
                   
                    break;
                case 1:      
                case -2:
                    timer += 1;
                    break;
                case 2:     
                case -1:
                  
                  sensor_fazhi +=200;
                    
                    break;
                        
                default:
                  break;
              }
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//刷新界面
            break;
            
        case KEY_LEFT:  //参数减
            switch(thrhd_menu_line_flag)
              {
                case 0:    
                  Servo_error -= 0.1;
                    break;
                case 1:      
                case -2:
                  timer -= 1;
                   
                    break;
                case 2:     
                case -1:
                  
                  sensor_fazhi -= 200;
                                    
                    break;
                                  
                default:
                  break;
              }
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//刷新界面
            break;
            
        case KEY_OK:   //保存参数
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //退出阀值设置界面，还原参数
              LCD_CLS();
              LPTMR_delay_ms(200);
              LCD_P8x16Str(30,3,"not Saving");
            return;
            break;
            
        default:
            break;
      }
         
   }


}

/*********************************************************
*函数名		：view_servo_menu_refresh    *输出结果	：无
*函数描述	：阀值界面刷新                *返回值		：无
*输入参数	：无
*********************************************************/
void view_thrhd_menu_refresh(int8 line_num)
{

  switch(line_num)
  {
    case 0:
      LCD_CLS();
      LCD_P8x16Str(12,0,"thrhd Setting");
     INV_LCD_P8x16Str(0,2,"S_error:");LCD_Write_double2_2(80,2,Servo_error);     
      LCD_P8x16Str(0,4,"timer:");LCD_Write_double2_2(80,4,timer);
      LCD_P8x16Str(0,6,"fazhi:"); LCD_Write_5_Num(80,6,sensor_fazhi);
      break;
      
    case 1:
    case -2:
      LCD_CLS();
      LCD_P8x16Str(12,0,"thrhd Setting");
      LCD_P8x16Str(0,2,"S_error:");LCD_Write_double2_2(80,2,Servo_error);     
  INV_LCD_P8x16Str(0,4,"timer:");LCD_Write_double2_2(80,4,timer);    
      LCD_P8x16Str(0,6,"fazhi:");LCD_Write_5_Num(80,6,sensor_fazhi);    
    
    break;
    
  case 2:
    case -1:
      LCD_CLS();
      LCD_P8x16Str(12,0,"thrhd Setting");
      LCD_P8x16Str(0,2,"S_error:"); LCD_Write_double2_2(80,2,Servo_error);    
      LCD_P8x16Str(0,4,"timer:");LCD_Write_double2_2(80,4,timer);
  INV_LCD_P8x16Str(0,6,"fazhi:");LCD_Write_5_Num(80,6,sensor_fazhi);

      break;
               
    default:
       break;
  }

}
  
  
  /*********************************************************
*函数名		：view_motor_setting     	*输出结果	：无
*函数描述	：电机设置界面              *返回值		：无
*输入参数	：无
*********************************************************/
void view_motor_setting(void)
{
   u8 key_num=0;   
   //进入舵机界面
   view_motor_menu_refresh(motor_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //循环顺序为0,1,2
            motor_menu_line_flag++;
            motor_menu_line_flag%=4;
            view_motor_menu_refresh(motor_menu_line_flag);//刷新界面
            break;
          
        case KEY_UP:  //循环顺序为0,-2,-1
            motor_menu_line_flag--;
            motor_menu_line_flag%=4;
            view_motor_menu_refresh(motor_menu_line_flag);//刷新界面
            break;
        

        case KEY_RIGHT:   //参数加
            switch(motor_menu_line_flag)
              {
                case 0:     
                  Motor.motorduty +=5;
                  
                    break;
                case 1:      
                case -3:
                    Motor.kp += 100;
                    break;
                
              case 2:     
                case -2:
                    Motor.kd += 1;
                    break;
                 
              case 3:
              case -1:
                Motor.ki += 2;
                break;
                    
                default:
                  break;
              }
            view_motor_menu_refresh(motor_menu_line_flag);//刷新界面
            break;
            
        case KEY_LEFT:  //参数减
            switch(motor_menu_line_flag)
              {
                case 0:
                  Motor.motorduty -=5;
                    break;
                
              case 1:     
              case -3:
                    Motor.kp -= 100;
                    if(Motor.kp < 0)
                      Motor.kp = 0;
                    break;
                
              case 2:    
              case -2:
                    Motor.kd -= 1;
                    if(Motor.kd < 0)
                      Motor.kd = 0;                   
                    break;
                    
              case 3 :
              case -1: 
                Motor.ki -= 2;
                if(Motor.ki<0)
                  Motor.ki = 0;
                                  
                default:
                  break;
              }
            view_motor_menu_refresh(motor_menu_line_flag);//刷新界面
            break;
            
        case KEY_OK:   //保存参数
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //退出舵机设置界面，还原参数
              LCD_CLS();
              LPTMR_delay_ms(200);
              LCD_P8x16Str(30,3,"not Saving");
            return;
            break;
            
        default:
            break;
      }
         
   }


}

/*********************************************************
*函数名		：view_motor_menu_refresh    *输出结果	：无
*函数描述	：电机机界面刷新                *返回值		：无
*输入参数	：无
*********************************************************/
void view_motor_menu_refresh(int8 line_num)
{

  switch(line_num)
  {
    case 0:
      LCD_CLS();
      LCD_P8x16Str(12,0,"motor Setting");
  INV_LCD_P8x16Str(0,2,"motorduty:");LCD_Write_5_Num(80,2,Motor.motorduty);     
      LCD_P8x16Str(0,4,"motor_p:");LCD_Write_5_Num(80,4,Motor.kp);
     LCD_P8x16Str(0,6,"motor_d:");LCD_Write_5_Num(80,6,Motor.kd);
      
      break;
      
    case 1:
    case -3:
      LCD_CLS();
      LCD_P8x16Str(12,0,"motor Setting");
      LCD_P8x16Str(0,2,"motorduty:");LCD_Write_5_Num(80,2,Motor.motorduty);     
  INV_LCD_P8x16Str(0,4,"motor_p:");LCD_Write_5_Num(80,4,Motor.kp);     
      LCD_P8x16Str(0,6,"motor_d:");LCD_Write_5_Num(80,6,Motor.kd);
      
    
    break;
    
  case 2:
    case -2:
      LCD_CLS();
      LCD_P8x16Str(12,0,"motor Setting");
      LCD_P8x16Str(0,2,"motorduty:"); LCD_Write_5_Num(80,2,Motor.motorduty);    
      LCD_P8x16Str(0,4,"motor_p:");    LCD_Write_5_Num(80,4,Motor.kp);
  INV_LCD_P8x16Str(0,6,"motor_d:");    LCD_Write_5_Num(80,6,Motor.kd);
    
break;  

  case 3:
  case -1:
    LCD_CLS();
      LCD_P8x16Str(12,0,"motor Setting");
      LCD_P8x16Str(0,2,"motor_p:");    LCD_Write_5_Num(80,2,Motor.kp);
      LCD_P8x16Str(0,4,"motor_d:");    LCD_Write_5_Num(80,4,Motor.kd);
      INV_LCD_P8x16Str(0,6,"motor_i:");   LCD_Write_5_Num(80,6,Motor.ki);
    
      
      break;
               
    default:
       break;
  }

}


