#include "main.h"
#include "cybergear.h"
#include "stdio.h"
#include <stdint.h>
#include "SPI.h"
#include <unistd.h>


#define spd 3
#define spd1 0.5
void delay_ms(unsigned int milliseconds) {
    usleep(milliseconds * 1000);  // ½«ºÁÃë×ª»»ÎªÎ¢Ãë
}
int main()
{
    SPI_inti();
    MI_Motor mi_motor[12];
    /* code */
    init_cybergear(&mi_motor[0], 0X11, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[1], 0X12, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[2], 0X13, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[3], 0X21, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[4], 0X22, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[5], 0X23, 1);
    delay_ms(1);
    init_cybergear(&mi_motor[5], 0X23, 1);
    delay_ms(1);
    init_cybergear(&mi_motor[5], 0X23, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[6], 0X31, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[7], 0X32, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[8], 0X33, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[9], 0X41, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[10], 0X42, 1);
     delay_ms(1);
    init_cybergear(&mi_motor[11], 0X43, 1);
     delay_ms(1);
    //for(int i=0;i<=11;i++) set_zeropos_cybergear(&mi_motor[i]);
    //for(int i=0;i<=11;i++) Set_Motor_Parameter(&mi_motor[i],loc_kp,40,'f');
    //for(int i=0;i<=11;i++) start_cybergear(&mi_motor[i]); 
    
  Set_Motor_Parameter(&mi_motor[0],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[0],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[3],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[3],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[6],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[6],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[9],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[9],Loc_Ref ,0,'f');
    
    
    //delay_ms(1000);
    
    Set_Motor_Parameter(&mi_motor[1],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[1],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[4],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[4],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[7],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[7],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[10],Limit_Spd ,spd,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[10],Loc_Ref ,0,'f');
    
    delay_ms(1000);

    Set_Motor_Parameter(&mi_motor[2],Limit_Spd ,spd1,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[2],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[5],Limit_Spd ,spd1,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[5],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[8],Limit_Spd ,spd1,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[8],Loc_Ref ,0,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[11],Limit_Spd ,spd1,'f');
    delay_ms(1);
    Set_Motor_Parameter(&mi_motor[11],Loc_Ref ,0,'f');
    delay_ms(1);
    
    return 0;
}