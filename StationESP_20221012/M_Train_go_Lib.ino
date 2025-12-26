// ** Main Train Go Flag Set *******************************************************************
void M_Train_go_Lib(){
  Now_Time_Main = millis();                                          // 途中経過時間
  Diff_Time_Main = Now_Time_Main - Set_Time_Main;
  if((Diff_Time_Main >= (OnTime2[i2] + 5000)) && M_Priority_go_Flag==1 && M_Train_go_Flag == 0){
      M_Train_go_Flag = 1;                                           // セット1回のみフラグ
      if( i2 < 9 ){
        i2 = i2 + 1;                                                 // Sub側 Timer 配列＋１
      }else{
        i2 = 0;
      }
  }
}
// ** Main Train Go Flag Set END *****************************************************************
