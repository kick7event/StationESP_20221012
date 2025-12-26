// ** Sub Train Go Flag Set *******************************************************************
void S_Train_go_Lib(){
  Now_Time_Sub = millis();                                           // 途中経過時間
  Diff_Time_Sub = Now_Time_Sub - Set_Time_Sub;
  if((Diff_Time_Sub >= (OnTime1[i1] + 5000)) && S_Priority_go_Flag==1 && S_Train_go_Flag == 0){
      S_Train_go_Flag = 1;                                           // セット1回のみフラグ
      if( i1 < 9 ){
        i1 = i1 + 1;                                                 // Sub側 Timer 配列＋１
      }else{
        i1 = 0;
      }
  }
}
// ** Sub Train Go Flag Set END ****************************************************************
