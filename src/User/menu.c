#include "include.h"
#include "LQ12864.h"
#include "sensor.h"

extern u8 KeyValue,ModeValue;
extern float Servo_error;
extern u16 sensor_fazhi;
extern int16 timer;
static int main_menu_line_flag=0;
static int inductor_menu_line_flag=0;   //��н�����ѡ���־λ
static int servo_menu_line_flag=0;   //���������ѡ���־λ
static int motor_menu_line_flag=0;   //���������ѡ���־λ
static int thrhd_menu_line_flag=0;   //��ֵ������ѡ���־λ

          //ģʽѡ�����

   //���˵�������ѡ���־λ

/***********************************************************
 *  * ��������  :  Key_Scan
 *  * ��    ��  ��
 *  * ��    ��  : ����״̬���, û���κμ�����ʱ����0
 *	* ��		��	��2015/03/01
 *	*	��		��	��
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
 *  * �ļ�˵�����˻�������ʼ������
 *  * ��    �ߣ�jarvs_lin
 *  * ��    �ڣ�2016/6/30
 *  * ��    ����V1.0
 *  * �޸���  ��
 *  * �޸����ڣ�
 ***********************************************************/
 
  /***********************************************************
 *  * ��������  ��view_start_up
 *  * ��    ��  ��
 *  * ��    ��  :
 *	* ����	��2016/06/30
 *	*����	��jarvis_lin
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

  /**************************����K60*********************************
 *  * ��������  ��view_main_menu
 *  * ��    ��  ��
 *  * ��    ��  :�˵�������
 *	* ��		��	��2017/07/6
 *	*	��		��	��jarvis_lin
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
        case KEY_DOWN:  //ѭ��˳��0,1,2,3
            main_menu_line_flag++;
            main_menu_line_flag%=4;
            view_main_menu_refresh(main_menu_line_flag);//ˢ�½���
            break;
          
        case KEY_UP:   //ѭ��˳��0,-3,-2,-1
            main_menu_line_flag--;
            main_menu_line_flag%=4;
            view_main_menu_refresh(main_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_OK:
            switch(main_menu_line_flag)       //���뵱ǰ�кŶ�Ӧ�Ľ���
              {
                case 0:  
                    view_inductor_setting();//��н���
                    break;
                  
                case 1:
                case -3:
                    view_servo_setting(); //�������
                    break;
                                
                case 2:                  
                case -2: 
                    view_motor_setting(); //�������
                   break;
               
               case 3:
                case -1:
                    view_thrhd_setting(); //��ֵ����
                     break;
           
                default:
                    break;
              } 
            view_main_menu_refresh(main_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_EXIT:
           LCD_CLS();
           LPTMR_delay_ms(200);
           LCD_P8x16Str(30,3,"Run Now!!!");
          
           LPTMR_delay_ms(2000);

           LCD_CLS();
           //RampRoad.gyro_zero_val = gyro_get_zero();//��ȡ��������ƫ
           LPTMR_delay_ms(2000);
           //Motor.INH = 1;  
           return;//�����˳��ж϶�ʱ��׼
           break;
          
        default:
            break;
      }

    }
}

  /***********************************************************
 *  * ��������  ��view_main_menu_refresh
 *  * ��    ��  ��
 *  * ��    ��  :�˵�������ˢ��
 *	* ��		��	��2016/06/30
 *	*	��		��	��jarvis_lin
************************************************************/
void view_main_menu_refresh(int8 line_num)
{
  switch(line_num)        //��ʾ��ǰ�кŶ�Ӧ�Ľ���,�����Ϸ����·���ͬһ������
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
 *  * ��������  �cview_induc_setting
 *  * ��    ��  ��
 *  * ��    ��  : ������ý���
 *	* ��		��	��2017/7/7
 *	*	��		��	��jarvis_lin
************************************************************/
void view_inductor_setting(void)
{
  uint8 key_num = 0;
  //�����н���
  view_inductor_menu_refresh(inductor_menu_line_flag);
  while(1)
  {
     KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100);
    switch(key_num)
    {        
      case KEY_DOWN:  //ѭ��˳��Ϊ0,1,2
          inductor_menu_line_flag++;
          inductor_menu_line_flag%=2;
          view_inductor_menu_refresh(inductor_menu_line_flag);//ˢ�½���
          break;
          
      case KEY_UP:  //ѭ��˳��Ϊ0,-1
          inductor_menu_line_flag--;
          inductor_menu_line_flag%=2;
          view_inductor_menu_refresh(inductor_menu_line_flag);//ˢ�½���
          break;
        
      case KEY_OK:
          switch(inductor_menu_line_flag)    //����ȷ�ϼ����뵱ǰ�к��¶�Ӧ�Ľ���
            {
              
                  
                   //��ʾ��ǰ��в���ֵ����Ӧ��ѹ
            case 0:
                  LCD_CLS();
                  while(FKeyboardRead()!=KEY_EXIT)
                    {
                      get_adc_int_val();       //�������ֵ
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
                view_inductor_menu_refresh(inductor_menu_line_flag);//ˢ�½���
                break;
                
              case 1:     //��ʾ����ƫ��
              case -1:
                  LCD_CLS();
                  
                  while(FKeyboardRead()!=KEY_EXIT)
                  {
                    deal_sensor(&Sensor);      //������ֵ
                    
                    LCD_P6x8Str(5,2,"error");     
                    LCD_Write_double2_2(0,7,Servo.error[0]);
                                   
                    LPTMR_delay_ms(100);
                  }
                  
                  view_inductor_menu_refresh(inductor_menu_line_flag); //ˢ�½���
                break;
                
              default:
                break;
            }
          break;
          
      case KEY_EXIT:  //�˳�������ý���
          return;
          break;
      
      default:
        break;    
    }
   LPTMR_delay_ms(50);
  }

}
  /***********************************************************
 *  * ��������  �cview_inductor_setting
 *  * ��    ��  ��
 *  * ��    ��  : ������ý���
 *	* ��		��	��2015/03/15
 *	*	��		��	��Joseph
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
*������		��view_servo_setting     	*������	����
*��������	��������ý���              *����ֵ		����
*�������	����
*********************************************************/
void view_servo_setting(void)
{
   u8 key_num=0;   
   //����������
   view_servo_menu_refresh(servo_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //ѭ��˳��Ϊ0,1,2
            servo_menu_line_flag++;
            servo_menu_line_flag%=3;
            view_servo_menu_refresh(servo_menu_line_flag);//ˢ�½���
            break;
          
        case KEY_UP:  //ѭ��˳��Ϊ0,-2,-1
            servo_menu_line_flag--;
            servo_menu_line_flag%=3;
            view_servo_menu_refresh(servo_menu_line_flag);//ˢ�½���
            break;
        

        case KEY_RIGHT:   //������
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
            view_servo_menu_refresh(servo_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_LEFT:  //������
            switch(servo_menu_line_flag)
              {
                case 0:    
                  Servo.pulse_width -= 50;  //����м�ֵ
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
            view_servo_menu_refresh(servo_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_OK:   //�������
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //�˳�������ý��棬��ԭ����
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
*������		��view_servo_menu_refresh    *������	����
*��������	���������ˢ��                *����ֵ		����
*�������	����
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
*������		��view_thrhd_setting     	*������	����
*��������	����ֵ���ý���             *����ֵ		����
*�������	����
*********************************************************/
void view_thrhd_setting(void)
{
   u8 key_num=0;   
   //���뷧ֵ����
   view_thrhd_menu_refresh(thrhd_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //ѭ��˳��Ϊ0,1,2
            thrhd_menu_line_flag++;
            thrhd_menu_line_flag%=3;
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//ˢ�½���
            break;
          
        case KEY_UP:  //ѭ��˳��Ϊ0,-2,-1
            thrhd_menu_line_flag--;
            thrhd_menu_line_flag%=3;
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//ˢ�½���
            break;
        

        case KEY_RIGHT:   //������
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
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_LEFT:  //������
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
            view_thrhd_menu_refresh(thrhd_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_OK:   //�������
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //�˳���ֵ���ý��棬��ԭ����
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
*������		��view_servo_menu_refresh    *������	����
*��������	����ֵ����ˢ��                *����ֵ		����
*�������	����
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
*������		��view_motor_setting     	*������	����
*��������	��������ý���              *����ֵ		����
*�������	����
*********************************************************/
void view_motor_setting(void)
{
   u8 key_num=0;   
   //����������
   view_motor_menu_refresh(motor_menu_line_flag);
   
   for(;;)
   {
      
      KeyValue = FKeyboardRead();
      ModeValue = Key_Scan();
      key_num=ModeValue;
      LPTMR_delay_ms(100); 
      switch(key_num)
      {
        case KEY_DOWN:  //ѭ��˳��Ϊ0,1,2
            motor_menu_line_flag++;
            motor_menu_line_flag%=4;
            view_motor_menu_refresh(motor_menu_line_flag);//ˢ�½���
            break;
          
        case KEY_UP:  //ѭ��˳��Ϊ0,-2,-1
            motor_menu_line_flag--;
            motor_menu_line_flag%=4;
            view_motor_menu_refresh(motor_menu_line_flag);//ˢ�½���
            break;
        

        case KEY_RIGHT:   //������
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
            view_motor_menu_refresh(motor_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_LEFT:  //������
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
            view_motor_menu_refresh(motor_menu_line_flag);//ˢ�½���
            break;
            
        case KEY_OK:   //�������
             LCD_CLS();
             LCD_P8x16Str(30,3,"Saving....");
           
             LPTMR_delay_ms(200);
             return;
             break;
          
        
        case KEY_EXIT: //�˳�������ý��棬��ԭ����
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
*������		��view_motor_menu_refresh    *������	����
*��������	�����������ˢ��                *����ֵ		����
*�������	����
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


