/******************** LQ_K60_������ v1.0 ********************
 * �ļ���           ��LQKEY.c
 * ����             ����ʼ������
 * ��ע             ���ٷ��������޸�
 * ����             ��2016-09-01
 * ʵ��ƽ̨         ������ K60VG���İ� 
 * ��������         ��IAR 7.3
 * ����             �������� 006
 * �Ա���           ��https://longqiu.taobao.com
 * �������ܳ�����Ⱥ ��202949437
*************************************************************/

#include "include.h"

void KeyboardReadInit()//������̳�ʼ�� ��Ϊ����͵�ƽ  ��Ϊ����ߵ�ƽ
{
  GPIO_Init (PORTD, 8, GPO,0);
  GPIO_Init (PORTD, 9, GPO,0);
  GPIO_Init (PORTD, 10, GPO,0);
  GPIO_Init (PORTD, 11, GPO,0);
  GPIO_Init (PORTD, 12, GPI,1);
  GPIO_Init (PORTD, 13, GPI,1);
  GPIO_Init (PORTD, 14, GPI,1);
  GPIO_Init (PORTD, 15, GPI,1);
}

//-------------------------------------------------------------------------*
//������: KEY_Init����                                                      *
//��  ��: ��ʼ��IO��                                                        * 
//��  ��:                                                                   *
//��  ��: ��                                                                *
//��  ��: KEY_Init����                                                      *
//-------------------------------------------------------- -----------------*
void KEY_Init(void)//ûʲô���� ��Ҳ�����õ�����
{
   GPIO_Init(PORTD,12,GPI,0);
   GPIO_Init(PORTB,6,GPI,0);
   GPIO_Init(PORTB,16,GPI,0);
   GPIO_Init(PORTB,20,GPI,0);
}

//-------------------------------------------------------------------------*
//������: KEY_Read����                                                      *
//��  ��: ��ȡ����ֵ                                                       * 
//��  ��:                                                                *
//��  ��:                                                              *
//��  ��: KEY_Read( KEY0)                                                *
//-------------------------------------------------------------------------*
u8 KEY_Read(KEYn_e keyno)
{
    switch(keyno) 
    {
      case KEY0:
        return GPIO_Get(PTD12);
      break;
      
      case KEY1:
        return GPIO_Get(PTD13);
      break;
      
      case KEY2:
        return GPIO_Get(PTD14);
      break;
      
       case KEY3:
        return GPIO_Get(PTD15);
      break;
      
      default:
        return 0XFF;
           
    }
}
u8 qudou(KEYn_e KEYX)
{if(KEY_Read(KEYX))
   {LPTMR_delay_ms(5);
    if(KEY_Read(KEYX))
       {return 1;}
    else
       {return 0;}}
 else{return 0;}
}

void KeyboardReadline0()//���ð���
{
  GPIO_Ctrl (PORTD, 8,0);
  GPIO_Ctrl (PORTD, 9,0);
  GPIO_Ctrl (PORTD, 10,0);
  GPIO_Ctrl (PORTD, 11,0);
  GPIO_Ctrl (PORTD, 12,1);
  GPIO_Ctrl (PORTD, 13,1);
  GPIO_Ctrl (PORTD, 14,1);
  GPIO_Ctrl (PORTD, 15,1);

}


u8 KeyboardReadline1()//��ⰴ���Ƿ��ڵ�һ��
{
  GPIO_Ctrl (PORTD, 8,0);
  GPIO_Ctrl (PORTD, 9,1);
  GPIO_Ctrl (PORTD, 10,1);
  GPIO_Ctrl (PORTD, 11,1);
  if(!KEY_Read(KEY0)) return 1;        //��һ�е�һ��
  else if(!KEY_Read(KEY1)) return 2;  //��һ�еڶ���
  else if(!KEY_Read(KEY2)) return 3;
  else if(!KEY_Read(KEY3)) return 4;
  else return 0;
}

u8 KeyboardReadline2()//��ⰴ���Ƿ��ڵڶ���
{
  GPIO_Ctrl (PORTD, 8,1);
  GPIO_Ctrl (PORTD, 9,0);
  GPIO_Ctrl (PORTD, 10,1);
  GPIO_Ctrl (PORTD, 11,1);
  if(!KEY_Read( KEY0)) return 5;
  else if(!KEY_Read(KEY1)) return 6;
  else if(!KEY_Read(KEY2)) return 7;
  else if(!KEY_Read(KEY3)) return 8;
  else return 0;
}

u8 KeyboardReadline3()//��ⰴ���Ƿ��ڵ�����
{
  GPIO_Ctrl (PORTD, 8,1);
  GPIO_Ctrl (PORTD, 9,1);
  GPIO_Ctrl (PORTD, 10,0);
  GPIO_Ctrl (PORTD, 11,1);
  if(!KEY_Read( KEY0)) return 9;
  else if(!KEY_Read(KEY1)) return 10;
  else if(!KEY_Read(KEY2)) return 11;
  else if(!KEY_Read(KEY3)) return 12;
  else return 0;
}

u8 KeyboardReadline4()//��ⰴ���Ƿ��ڵ�����
{
  GPIO_Ctrl (PORTD, 8,1);
  GPIO_Ctrl (PORTD, 9,1);
  GPIO_Ctrl (PORTD, 10,1);
  GPIO_Ctrl (PORTD, 11,0);
  if(!KEY_Read( KEY0)) return 13;
  else if(!KEY_Read(KEY1)) return 14;
  else if(!KEY_Read(KEY2)) return 15;
  else if(!KEY_Read(KEY3)) return 16;
  else return 0;
}
u8 KeyboardReadSearch()
{
  u8 line1,line2,line3,line4;
  line1 = KeyboardReadline1();
  line2 = KeyboardReadline2();
  line3 = KeyboardReadline3();
  line4 = KeyboardReadline4();
  if(line1&&!line2&&!line3&&!line4) return line1;
  else if(!line1&&line2&&!line3&&!line4) return line2;
  else if(!line1&&!line2&&line3&&!line4) return line3;
  else if(!line1&&!line2&&!line3&&line4) return line4;
  else return 0;
}

/*u8 KeyboardReadSearch()
{
  if(KeyboardReadline1()){return 1;}//��N�е�һ�а�������
  else if(KeyboardReadline2()){return 2;}//��N�еڶ��а�������
  else if(KeyboardReadline3()){return 3;}//��N�е����а�������
  else if(KeyboardReadline4()){return 4;}//��N�е����а�������
  else return 0;

}*/

/*u8 KeyboardRead()
{
  if(!qudou(KEY0)&&!qudou(KEY1)&&!qudou(KEY2)&&!qudou(KEY3))
  {
    return 0;//û�а������� ��������ֵΪ0��
  }
  else if(!KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3)){
      LPTMR_delay_ms(5);
      if(!KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3))
      //�����ڵ�һ��
    {
      switch(KeyboardReadSearch())
      {
      case 1:
        return 1; 
      break;
      
      case 2:
        return 5; 
      break;
      
      case 3:
        return 9; 
      break;
      
      case 4:
        return 13; 
      break;
      
      default:
        return 0;
      
      }
  
    }
    
      else return 0;}

    else if(KEY_Read(KEY0)&&!KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3)){
      LPTMR_delay_ms(5);
      if(KEY_Read(KEY0)&&!KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3))
      //�����ڵڶ���
    {
      switch(KeyboardReadSearch())
      {
      case 1:
        return 2; 
      break;
      
      case 2:
        return 6; 
      break;
      
      case 3:
        return 10; 
      break;
      
      case 4:
        return 14; 
      break;
      
      default:
        return 0;
      
      }
  
    }
    
      else return 0;}
    
    else if(KEY_Read(KEY0)&&KEY_Read(KEY1)&&!KEY_Read(KEY2)&&KEY_Read(KEY3)){
      LPTMR_delay_ms(5);
      if(KEY_Read(KEY0)&&KEY_Read(KEY1)&&!KEY_Read(KEY2)&&KEY_Read(KEY3))
        //�����ڵ�����
    {
      switch(KeyboardReadSearch())
      {
      case 1:
        return 3; 
      break;
      
      case 2:
        return 7; 
      break;
      
      case 3: 
        return 11; 
      break;
      
      case 4:
        return 15; 
      break;
      
      default:
        return 0;
      
      }
  
    }
    
      else return 0;}
    
     else if(KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&!KEY_Read(KEY3)){
      LPTMR_delay_ms(5);
      if(KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&!KEY_Read(KEY3))
      //�����ڵ�����
    {
      switch(KeyboardReadSearch())
      {
      case 1:
        return 4; 
      break;
      
      case 2:
        return 8; 
      break;
      
      case 3:
        return 12; 
      break;
      
      case 4:
        return 16; 
      break;
      
      default:
        return 0;
      
      }
  
    }
    
      else return 0;}
    
    
else return 0;  }*/


/******************����K60***************************
������FKeyboardRead()
��������
���ܣ����ذ�����ȡ��ֵ
*****************************************************/
u8 FKeyboardRead()
{
  u8 a;
  a = KeyboardReadSearch();
  KeyboardReadline0();
  return a;
}
