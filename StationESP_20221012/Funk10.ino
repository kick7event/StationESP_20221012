// ** Train1/Poji10 *********************************************************************
void Train1_Funk10(){
// ++ Timer Set +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  if(Train1==10 && Local_Timer_Set_Flag==0){          // "10"に到着
  if(Train1==10 && Funk10_Flag==0){          // "10"に到着
    data[1] = SpeedZoro;                                             // Train1 Speed=停止
    data[2] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:1 Main:2
    L_Timer_set_Lib();                                               // Local Station Timer set(New)

    Funk10_Flag = 1;                                        // Local Station Startフラグ
  }
  Now_Time_Local = millis();
  Diff_Time_Local = Now_Time_Local - Set_Time_Local;
  if(Diff_Time_Local >= OnTime3[i3] && L_Train_go == 0){
    data[1] = SpeedMid1;                                             // Train1 Speed=中速
    data[2] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Train_go = 1;
  }
}
// ** Train1/Poji10 END ******************************************************************

// ** Train2/Poji10 **********************************************************************
void Train2_Funk10(){
  if( Train2==10 && Funk10_Flag==0 ){                       // "10"に到着
    data[3] = SpeedZoro;                                             // Train2 Speed=停止
    data[4] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk10_Flag = 1;                                        // Local Station Start待ちフラグ
/*
    if(Train1==21 || Train3==21 || Train4==21){
      ServoInPojiBuff = 2;                                           // 入口ServoをMainへ
      ServoInFlag = 0;                                               // 上記設定とペア
    }
    if(Train1==31 || Train3==31 || Train4==31){
      ServoInPojiBuff = 1;                                           // 入口ServoをSubへ
      ServoInFlag = 1;                                               // 上記設定とペア
    }
    if((!(Train1==21 || Train3==21 || Train4==21)) && (!(Train1==31 || Train3==31 || Train4==31))){
      ServoInPojiBuff = InServo[con];
      if(ServoInPojiBuff == 1){
        ServoInFlag = 1;                                             // Sub条件フラグ
      }
      if(ServoInPojiBuff == 2){
        ServoInFlag = 0;                                             // Main条件フラグ
      }
    }
    */
  }
  Now_Time_Local = millis();
  Diff_Time_Local = Now_Time_Local - Set_Time_Local;
  if(Diff_Time_Local >= OnTime3[i3] && L_Train_go == 0){
    data[3] = SpeedMid2;                                             // Train1 Speed=中速
    data[4] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Train_go = 1;
  }
}
// ** Train2/Poji10 END ******************************************************************

// ** Train3/Poji10 **********************************************************************
void Train3_Funk10(){
  if( Train3==10 && Funk10_Flag==0 ){                     // "10"に到着
    data[5] = SpeedZoro;                                             // Train13 Speed=停止
    data[6] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk10_Flag = 1;                                        // Local Station Start待ちフラグ

    /*
    if(Train1==21 || Train2==21 || Train4==21){
      ServoInPojiBuff = 2;                                           // 入口ServoをMainへ
      ServoInFlag = 0;                                               // 上記設定とペア
    }
    if(Train1==31 || Train2==31 || Train4==31){
      ServoInPojiBuff = 1;                                           // 入口ServoをSubへ
      ServoInFlag = 1;                                               // 上記設定とペア
    }
    if((!(Train1==21 || Train2==21 || Train4==21)) && (!(Train1==31 || Train2==31 || Train4==31))){
      ServoInPojiBuff = InServo[con];
      if(ServoInPojiBuff == 1){
        ServoInFlag = 1;                                             // Sub条件フラグ
      }
      if(ServoInPojiBuff == 2){
        ServoInFlag = 0;                                             // Main条件フラグ
      }
    }
    */
  }
  Now_Time_Local = millis();
  Diff_Time_Local = Now_Time_Local - Set_Time_Local;
  if(Diff_Time_Local >= OnTime3[i3] && L_Train_go == 0){
    data[5] = SpeedMid3;                                             // Train1 Speed=中速
    data[6] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Train_go = 1;
  }
}
// ** Train3/Poji10 END ******************************************************************

// ** Train4/Poji10 **********************************************************************
void Train4_Funk10(){
  if( Train4==10 && Funk10_Flag==0 ){                       // "10"に到着
    data[7] = SpeedZoro;                                             // Train4 Speed=停止
    data[8] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Timer_set_Lib();                                               // Local Station Timer set(New)
    Funk10_Flag = 1;                                        // Local Station Start待ちフラグ

    /*
    if(Train1==21 || Train2==21 || Train3==21){
      ServoInPojiBuff = 2;                                           // 入口ServoをMainへ
      ServoInFlag = 0;                                               // 上記設定とペア
    }
    if(Train1==31 || Train2==31 || Train3==31){
      ServoInPojiBuff = 1;                                           // 入口ServoをSubへ
      ServoInFlag = 1;                                               // 上記設定とペア
    }
    if((!(Train1==21 || Train2==21 || Train3==21)) && (!(Train1==31 || Train2==31 || Train3==31))){
      ServoInPojiBuff = InServo[con];
      if(ServoInPojiBuff == 1){
        ServoInFlag = 1;                                             // Sub条件フラグ
      }
      if(ServoInPojiBuff == 2){
        ServoInFlag = 0;                                             // Main条件フラグ
      }
    }
    */
  }
Now_Time_Local = millis();
  Diff_Time_Local = Now_Time_Local - Set_Time_Local;
  if(Diff_Time_Local >= OnTime3[i3] && L_Train_go == 0){
    data[7] = SpeedMid4;                                             // Train1 Speed=中速
    data[8] = F3_L0;                                                 // forward/Light On
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[14]= ServoOutPoji;                                          // Sub:0 Main:1
    L_Train_go = 1;
  }
}
// ** Train4/Poji10 END ******************************************************************
