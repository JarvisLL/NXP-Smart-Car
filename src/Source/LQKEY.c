/******************** LQ_K60_函数库 v1.0 ********************
 * 文件名           ：LQKEY.c
 * 功能             ：初始化按键
 * 备注             ：官方例程上修改
 * 日期             ：2016-09-01
 * 实验平台         ：龙丘 K60VG核心板 
 * 开发环境         ：IAR 7.3
 * 作者             ：龙丘技术 006
 * 淘宝店           ：https://longqiu.taobao.com
 * 龙丘智能车讨论群 ：202949437
*************************************************************/

#include "include.h"

void KeyboardReadInit()//矩阵键盘初始化 行为输出低电平  列为输入高电平
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
//函数名: KEY_Init（）                                                      *
//功  能: 初始化IO口                                                        * 
//参  数:                                                                   *
//返  回: 无                                                                *
//简  例: KEY_Init（）                                                      *
//-------------------------------------------------------- -----------------*
void KEY_Init(void)//没什么软用 再也不会用到它了
{
   GPIO_Init(PORTD,12,GPI,0);
   GPIO_Init(PORTB,6,GPI,0);
   GPIO_Init(PORTB,16,GPI,0);
   GPIO_Init(PORTB,20,GPI,0);
}

//-------------------------------------------------------------------------*
//函数名: KEY_Read（）                                                      *
//功  能: 读取按键值                                                       * 
//参  数:                                                                *
//返  回:                                                              *
//简  例: KEY_Read( KEY0)                                                *
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

void KeyboardReadline0()//重置按键
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


u8 KeyboardReadline1()//检测按键是否在第一行
{
  GPIO_Ctrl (PORTD, 8,0);
  GPIO_Ctrl (PORTD, 9,1);
  GPIO_Ctrl (PORTD, 10,1);
  GPIO_Ctrl (PORTD, 11,1);
  if(!KEY_Read(KEY0)) return 1;        //第一行第一列
  else if(!KEY_Read(KEY1)) return 2;  //第一行第二列
  else if(!KEY_Read(KEY2)) return 3;
  else if(!KEY_Read(KEY3)) return 4;
  else return 0;
}

u8 KeyboardReadline2()//检测按键是否在第二行
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

u8 KeyboardReadline3()//检测按键是否在第三行
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

u8 KeyboardReadline4()//检测按键是否在第四行
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
  if(KeyboardReadline1()){return 1;}//第N列第一行按键按下
  else if(KeyboardReadline2()){return 2;}//第N列第二行按键按下
  else if(KeyboardReadline3()){return 3;}//第N列第三行按键按下
  else if(KeyboardReadline4()){return 4;}//第N列第四行按键按下
  else return 0;

}*/

/*u8 KeyboardRead()
{
  if(!qudou(KEY0)&&!qudou(KEY1)&&!qudou(KEY2)&&!qudou(KEY3))
  {
    return 0;//没有按键按下 函数返回值为0；
  }
  else if(!KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3)){
      LPTMR_delay_ms(5);
      if(!KEY_Read(KEY0)&&KEY_Read(KEY1)&&KEY_Read(KEY2)&&KEY_Read(KEY3))
      //按键在第一列
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
      //按键在第二列
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
        //按键在第三列
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
      //按键在第四列
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


/******************蓝旗K60***************************
函数：FKeyboardRead()
参数：无
功能：返回按键读取的值
*****************************************************/
u8 FKeyboardRead()
{
  u8 a;
  a = KeyboardReadSearch();
  KeyboardReadline0();
  return a;
}
