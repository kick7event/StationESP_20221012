ServoOut// ** Servo Set ***************************************************************************
void S_Servo_set_Lib(){
  Now_Time_Sub = millis();                                           // 途中経過時間
  Diff_Time_Sub = Now_Time_Sub - Set_Time_Sub;  
  if((Diff_Time_Sub >= OnTime1[i1]) && S_Priority_go_Flag==1 && Servo_S_Set_Flag == 0){
      S_Servo_go = 1;                                                // 時間が来たのでSerevoをSub側に倒す
      ServoOutPoji = 1;                                              // OutServo制御（ Main:2 Sub:1 )
      OutServoContlor();
      Servo_S_Set_Flag = 1;                                          // 1回セット
      Serial.println("Servo go Sub");
  }
}  

void M_Servo_set_Lib(){
  Now_Time_Main = millis();                                          // 途中経過時間
  Diff_Time_Main = Now_Time_Main - Set_Time_Main;  
  if((Diff_Time_Main >= OnTime2[i2]) && M_Priority_go_Flag==1 && Servo_M_Set_Flag == 0){
      M_Servo_go = 1;                                                // 時間が来たのでSerevoをSub側に倒す
      ServoOutPoji = 2;                                              // OutServo制御（ Main:2 Sub:1 )
      OutServoContlor();
      Servo_M_Set_Flag = 1;                                          // 1回セット
      Serial.println("Servo go Main");
  }
}
// ** Servo Set END ***********************************************************************
