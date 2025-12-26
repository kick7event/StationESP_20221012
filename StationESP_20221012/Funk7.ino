// ** Train1/Poji07 *********************************************************************
void Train1_Funk07(){
// ++ Timer Set +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if(Train1==7 && Funk7_Flag==0){          // "10"に到着
    data[1] = SpeedZoro;                                             // Train1 Speed=停止
    data[2] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    
    T_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk7_Flag = 1;                                        // Local Station Startフラグ
  }
  Now_Time_Tunnel = millis();
  Diff_Time_Tunnel = Now_Time_Tunnel - Set_Time_Tunnel;
  if(Diff_Time_Tunnel >= OnTime4[i4] && T_Train_go == 0){
    data[1] = SpeedMid1;                                             // Train1 Speed=中速
    data[2] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Train_go = 1;
    i4 = i4 + 1;
    if(i4 > 9){
      i4 = 0;
    }
  }
}
// ** Train1/Poji10 END ******************************************************************

// ** Train2/Poji10 **********************************************************************
void Train2_Funk07(){
  if( Train2==7 && Funk7_Flag==0 ){                       // "10"に到着
    data[3] = SpeedZoro;                                             // Train2 Speed=停止
    data[4] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk7_Flag = 1;                                        // Local Station Start待ちフラグ
  }
  Now_Time_Tunnel = millis();
  Diff_Time_Tunnel = Now_Time_Tunnel - Set_Time_Tunnel;
  if(Diff_Time_Tunnel >= OnTime4[i4] && T_Train_go == 0){
    data[3] = SpeedMid2;                                             // Train1 Speed=中速
    data[4] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Train_go = 1;
    T_Train_go = 1;
    i4 = i4 + 1;
    if(i4 > 9){
      i4 = 0;
    }
  }
}
// ** Train2/Poji10 END ******************************************************************

// ** Train3/Poji10 **********************************************************************
void Train3_Funk07(){
  if( Train3==7 && Funk7_Flag==0 ){                     // "10"に到着
    data[5] = SpeedZoro;                                             // Train13 Speed=停止
    data[6] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk7_Flag = 1;                                        // Local Station Start待ちフラグ
  }

  Now_Time_Tunnel = millis();
  Diff_Time_Tunnel = Now_Time_Tunnel - Set_Time_Tunnel;
  if(Diff_Time_Tunnel>= OnTime4[i4] && T_Train_go == 0){
    data[5] = SpeedMid3;                                             // Train1 Speed=中速
    data[6] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Train_go = 1;
    T_Train_go = 1;
    i4 = i4 + 1;
    if(i4 > 9){
      i4 = 0;
    }
  }
}
// ** Train3/Poji10 END ******************************************************************

// ** Train4/Poji10 **********************************************************************
void Train4_Funk07(){
  if( Train4==7 && Funk7_Flag==0 ){                       // "10"に到着
    data[7] = SpeedZoro;                                             // Train4 Speed=停止
    data[8] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk7_Flag = 1;                                        // Local Station Start待ちフラグ
  }
Now_Time_Tunnel = millis();
  Diff_Time_Tunnel = Now_Time_Tunnel - Set_Time_Tunnel;
  if(Diff_Time_Tunnel >= OnTime4[i4] && T_Train_go == 0){
    data[7] = SpeedMid4;                                             // Train1 Speed=中速
    data[8] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    T_Train_go = 1;
    T_Train_go = 1;
    i4 = i4 + 1;
    if(i4 > 9){
      i4 = 0;
    }
  }
}
