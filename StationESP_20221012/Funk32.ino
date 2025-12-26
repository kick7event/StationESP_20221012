// ** Train1 Poji32 **********************************************************************
void Train1_Funk32(){
if(Train1 == 32 && Train1_Funk32_Flag == 0){                         // "32"に到着（又は"32"に列車をセット）
    data[1] = SpeedZoro;                                             // Train1 Speed=停止
    data[2] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[13]= ServoInPoji;                                           // ServoInPoji
    data[14]= ServoOutPoji;                                          // Sub:1 Main:2

    Set_Time_Main = millis();                                        // セット時・時間保存
    Train1_Funk32_Flag = 1;                                          // Train1 Funk32 セットフラグ
  }

  Priority_Select();                                                   // 出発優先順位判定
  M_Servo_set_Lib();

// == Train1 Main Go ==========================================================================
  M_Train_go_Lib();
  
  if(M_Train_go_Flag==1){
    data[1] = SpeedMid1;                                             // Train1 Speed=中速
    data[2] = F3_L0;
  }
}

void Train2_Funk32(){
if(Train2 == 32 && Train2_Funk32_Flag == 0){                         // "32"に到着（又は"32"に列車をセット）
    data[3] = SpeedZoro;                                             // Train1 Speed=停止
    data[4] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[13]= ServoInPoji;                                           // ServoInPoji
    data[14]= ServoOutPoji;                                          // Sub:1 Main:2

    Set_Time_Main = millis();                                        // セット時・時間保存
    Train2_Funk32_Flag = 1;                                          // Train2 Funk32 セットフラグ
  }

  Priority_Select();                                                   // 出発優先順位判定
  M_Servo_set_Lib();


// == Train2 Main Go ==========================================================================
  M_Train_go_Lib();

  if(M_Train_go_Flag==1){
    data[3] = SpeedMid2;                                             // Train1 Speed=中速
    data[4] = F3_L0;
  }
}

void Train3_Funk32(){
if(Train3 == 32 && Train3_Funk32_Flag == 0){                         // "32"に到着（又は"32"に列車をセット）
    data[5] = SpeedZoro;                                             // Train1 Speed=停止
    data[6] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[13]= ServoInPoji;                                           // ServoInPoji
    data[14]= ServoOutPoji;                                          // Sub:1 Main:2

    Set_Time_Main = millis();                                        // セット時・時間保存
    Train3_Funk32_Flag = 1;                                          // Train3 Funk32 セットフラグ
  }

  Priority_Select();                                                   // 出発優先順位判定
  M_Servo_set_Lib();

// == Train3 Main Go ==========================================================================
  M_Train_go_Lib();
  
  if(M_Train_go_Flag==1){
    data[5] = SpeedMid3;                                             // Train1 Speed=中速
    data[6] = F3_L0;
  }
}

void Train4_Funk32(){
if(Train4 == 32 && Train4_Funk32_Flag == 0){                         // "32"に到着（又は"32"に列車をセット）
    data[7] = SpeedZoro;                                             // Train1 Speed=停止
    data[8] = F1_L0;                                                 // forward/Light Off
    data[9] = Train1;                                                // Train1 位置情報
    data[10]= Train2;                                                // Train2 位置情報
    data[11]= Train3;                                                // Train3 位置情報
    data[12]= Train4;                                                // Train4 位置情報
    data[13]= ServoInPoji;                                           // ServoInPoji
    data[14]= ServoOutPoji;                                          // Sub:1 Main:2

    Set_Time_Main = millis();                                        // セット時・時間保存
    Train4_Funk32_Flag = 1;                                          // Train4 Funk32 セットフラグ
  }

  Priority_Select();                                                   // 出発優先順位判定  
  M_Servo_set_Lib();

// == Train4 Main Go ==========================================================================
  M_Train_go_Lib();

  if(M_Train_go_Flag==1){
    data[7] = SpeedMid4;                                             // Train1 Speed=中速
    data[8] = F3_L0;
  }
}
// ** Train4 Poji32 END *****************************************************************
