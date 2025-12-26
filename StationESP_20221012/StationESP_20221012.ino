/* broadcast_Central Control ******************************************************************************************
   2021/09/16  Ver1.00 初版(ESP32) Twelite->ArduinoMAGA->RaspberryPi->Sakura->ESP32
   2021/09/16  Ver1.01 watchdog timer対応OK
   2021/09/16  Ver1.02 移植第一弾
   2021/09/20  Ver1.03 送信フォーマット（ヘッダー追加）
   2021/09/23  Ver1.04 個別速度設定、追突防止（ホーム内）  
   2021/09/26  Ver1.05 疑似送信データ変更（"98"）不要
   2021/09/28  Ver1.06 途中駅対応
   2021/10/02  Ver2.00 送信フォーマット変更（列車スピード、位置情報追加）
   2021/10/19  Ver2.01 追突防止機能追加（All）
   2021/10/27  Ver2.02 タイマーセット不具合修正
   2021/11/05  Ver2.03 MEGAリセットコマンド追加　”R"
   2022/01/16  Ver2.04 UNO Reset 追加
   2022/01/16  Ver3.00 InServo, OutServo制御機能追加
   2022/01/20  Ver3.01 上記改良
   2022/01/30  Ver3.02 InHomeでのコリジョン改良
   2022/01/31  Ver3.03 Poji13-21(Train3)改善
   2022/02/07  Ver3.04 フラグ整理
   2022/02/11  Ver3.50 不具合調整テスト
   2022/02/12  Ver4.00 サーボ設定部大幅見直し（In,Out）
   2022/03/10  Ver5.00 Swich文に変更
   2022/03/13  Ver5.01 Home内シーケンス修正(30周に1回程度誤動作）
   2022/03/13  Ver6.00 タイマー内蔵(NANO->ESP32):カウンタ数増、カウント表示の為
   2022/03/21  Ver6.01 Swich文関連改造
   2022/03/27  Ver6.02 フラグ名：物理動作イメージ変数名に変更（不要フラグ削除）
   2022/04/06  Ver6.03 ServoIN,OUTシーケンス修正
   2022/04/23  Ver7.00 出口優先シーケンス改良
   　　　　　　　　　　　JROBO junichi itoh
   ********************************************************************************************************************/
   
#include <esp_now.h>
#include <WiFi.h>

// ** define **********************************************************************************************************
#define StartSW       13                                               // Start SW (演出開始ボタン)

#define NANO_reset    27                                               // ArduinoNANO Reset

#define Sig_In_M_GR   22                                               // PointSingnal IN/Main /Green or Red
#define Sig_In_S_GR   21                                               // PointSingnal IN/Sub  /Green or Red
#define Sig_Out_M_GR  14                                               // PointSingnal OUT/Main/Green or Red
#define Sig_Out_S_GR  12                                               // PointSingnal OUT/Sub /Green or Red

#define Ser_In_Main    4                                               // Servo In/Main
#define Ser_In_Sub    18                                               // Servo In/Sub
#define Ser_Out_Main  23                                               // Servo Out/Main
#define Ser_Out_Sub   19                                               // Servo Out/Sub

#define ServoINT      15                                               // ServoIN/OUT　状態変化割り込み（MEGA）<OK>
// ********************************************************************************************************************

// ** slave_Mac Address ***********************************************************************************************
//uint8_t slaveMAC[]= {0x30,0xAE,0xA4,0x97,0x5A,0x2C};                 // Main（親機）＜80Pin＞
//uint8_t slaveMAC[]= {0x84,0x0D,0x8E,0xC8,0x8E,0x88};                 // Main（親機）＜シール１＞
//uint8_t slaveMAC1[]= {0x9C,0x9C,0x1F,0xC5,0xC7,0x7C};                // Train1 <シール２＞
//uint8_t slaveMAC2[]= {0x24,0x0A,0xC4,0xFA,0x4D,0x8C};                // Train2 <シール３＞
//uint8_t slaveMAC3[]= {0x7C,0x9E,0xBD,0x4B,0x5B,0x4C};                // Train3 <シール４＞
//uint8_t slaveMAC4[]= {0x7C,0x9E,0xBD,0x4B,0x57,0xA8};                // Train4 <シール５＞
// ********************************************************************************************************************

// ** variable ********************************************************************************************************
String Train, Hedder, Data1, Data2, Data3, Data4, Data5, str, footer;  // 受信データバッファー
byte Train1, Train2, Train3, Train4;                                   // 上記データの整数化
byte ServoInPoji, ServoOutPoji, ServoInInfo, ServoInPojiBuff;          // InfoはMEGAからのコールバック

// ** ブロードキャストデータ構造 *****************************************************************************************
// ********************************************************************************************************************
const uint8_t hedderH = 99;                                            // 配列上のヘッダー固定値
const uint8_t footerH = 88;                                            // 配列状のフッター固定値
//                        0    1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18    19
uint8_t data[20]   = {hedderH, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, footerH};
// ********************************************************************************************************************
// <Speed:0-255>
// data[0] : heder : 99
// data[1] : Train1(Speed)
// data[2] : Train1(LED制御)
// data[3] : Train2(Speed)
// data[4] : Train2(LED制御)
// data[5] : Train3(Speed)
// data[6] : Train3(LED制御)
// data[7] : Train4(Speed)
// data[8] : Train4(LED制御)
// data[9] : Train1(位置情報)
// data[10]: Train2(位置情報)
// data[11]: Train3(位置情報)
// data[12]: Train4(位置情報)
// data[13]: ServoInPoji
// data[14]: ServoOutPoji
// data[15]: M_Timer_set状態をmoniterへ
// data[16]: S_Timer_set状態をmoniterへ
// data[17]: L_Timer_set状態をmoniterへ
// data[18]: T_Timer_set状態をmoniterへ
// data[19]: footer : 88

uint8_t F0_L0 = 10;                                                    // forward(brake)_HeadLight F:Off/B:Off  Loom_Light Off
uint8_t F1_L0 = 11;                                                    // forward(brake)_HeadLight F:Off/B:Red  Loom_Light Off
uint8_t F2_L0 = 12;                                                    // forward(stop)_HeadLight F:Red/B:Red   Loom_Light Off
uint8_t F3_L0 = 13;                                                    // forward(speed)_HeadLight F:Blue/B:Red Loom_Light Off

uint8_t F0_L1 = 14;                                                    // forward(brake)_HeadLight F:Off/B:Off  Loom_Light On
uint8_t F1_L1 = 15;                                                    // forward(brake)_HeadLight F:Off/B:Red  Loom_Light On
uint8_t F2_L1 = 16;                                                    // forward(stop)_HeadLight F:Red/B:Red   Loom_Light On
uint8_t F3_L1 = 17;                                                    // forward(speed)_HeadLight F:Blue/B:Red Loom_Light On

uint8_t B0_L0 = 20;                                                    // back(brake)_HeadLight F:Off/B:Off     Loom_Light Off
uint8_t B1_L0 = 21;                                                    // back(brake)_HeadLight F:Off/B:Red     Loom_Light Off
uint8_t B2_L0 = 22;                                                    // back(stop)_HeadLight F:Red/B:Red      Loom_Light Off
uint8_t B3_L0 = 23;                                                    // back(speed)_HeadLight F:Blue/B:Red    Loom_Light Off

uint8_t B0_L1 = 24;                                                    // back(brake)_HeadLight F:Off/B:Off     Loom_Light On
uint8_t B1_L1 = 25;                                                    // back(brake)_HeadLight F:Off/B:Red     Loom_Light On
uint8_t B2_L1 = 26;                                                    // back(stop)_HeadLight F:Red/B:Red      Loom_Light On
uint8_t B3_L1 = 27;                                                    // back(speed)_HeadLight F:Blue/B:Red    Loom_Light On

// ** New Setting ***** 9Bit 100Hz ************************************************************************************
uint8_t SpeedZoro  =   0;                                              // 列車スペード：停止

uint8_t SpeedLow1_1=  65;                                              // 1列車スピード：低速1( 60x3=180)
uint8_t SpeedLow1_2=  70;                                              // 1列車スピード：低速2( 65x3=195)
uint8_t SpeedLow1_3=  75;                                              // 1列車スピード：低速3( 75x3=225)
uint8_t SpeedMid1  =  78;                                              // 1列車スピード：中速 ( 78x3=234)

uint8_t SpeedLow2_1=  77;                                              // 2列車スピード：低速1( 75x3=225)
uint8_t SpeedLow2_2=  80;                                              // 2列車スピード：低速2( 80x3=240)
uint8_t SpeedLow2_3=  85;                                              // 2列車スピード：低速3( 86x3=258)
uint8_t SpeedMid2  =  93;                                              // 2列車スピード：中速 ( 96x3=288)

uint8_t SpeedLow3_1=  77;                                              // 3列車スピード：低速1( 65x3=195)
uint8_t SpeedLow3_2=  80;                                              // 3列車スピード：低速2( 70x3=210)
uint8_t SpeedLow3_3=  85;                                              // 3列車スピード：低速3( 75x3=225)
uint8_t SpeedMid3  =  93;                                              // 3列車スピード：中速 ( 85x3=255)

uint8_t SpeedLow4_1=  75;                                              // 4列車スピード：低速1( 65x3=195)
uint8_t SpeedLow4_2=  80;                                              // 4列車スピード：低速2( 70x3=210)
uint8_t SpeedLow4_3=  85;                                              // 4列車スピード：低速3( 75x3=225)
uint8_t SpeedMid4  =  90;                                              // 4列車スピード：中速 ( 85x3=255)

// ********************************************************************************************************************
byte P21_P03_Stop = 0;                                                 // Poji21で他車両がPoji3を過ぎるまで停止させるフラグ
byte P31_P03_Stop = 0;                                                 // Poji31で他車両がPoji3を過ぎるまで停止させるフラグ

byte Train1_10_One = 0;                                                  // Train1のスタート時間待ちフラグ(1:通常、0：タイムアップ待ち）ローカル駅用
//*********************************************************************************************************************

// ** New *************************************************************************************************************
//byte TMS    = 0;                                                     // Main側 Timer Main Set中
//byte TSS    = 0;                                         
// ********************************************************************************************************************

// ** Timer ***********************************************************************************************************
int i1 = 0;                                                            // 配列「１」Sub    Time Set
int i2 = 0;                                                            // 配列「２」Main   Time Set
int i3 = 0;                                                            // 配列「３」Local  Time Set
int i4 = 0;                                                            // 配列「４」Tunnel Time Set

byte M_Timer_set = 0;                                                  // main   Timer set:1 Non:0
byte S_Timer_set = 0;                                                  // sub    Timer set:1 Non:0
byte L_Timer_set = 0;                                                  // local  Timer set:1 Non:0
byte T_Timer_set = 0;                                                  // tunnel Timer set:1 Non:0

byte M_Train_go = 0;                                                   // main   Train Stop:0 Go:1 
byte S_Train_go = 0;                                                   // sub    Train Stop:0 Go:1 
byte L_Train_go = 0;                                                   // local  Train Stop:0 Go:1
byte T_Train_go = 0;                                                   // tunnel Train Stop:0 Go:1

byte M_Servo_go = 0;                                                   // Servo  Sub:0 Main:1 
byte S_Servo_go = 0;                                                   // Servo  Main:0 Sub:1 

byte M_priority_set = 0;                                               // Main優先フラグセット（1回のみ）
byte S_priority_set = 0;                                               // Sub優先フラグセット（1回のみ）

byte Moniter_Main_Train_go    = 0;                                     // Moniter用 M_Train_go
byte Moniter_Sub_Train_go     = 0;                                     // Moniter用 S_Train_go
byte Moniter_Local_Train_go   = 0;                                     // Moniter用 L_Train_go
byte Moniter_Tunnel_Train_go  = 0;                                     // Moniter用 T_Train_go

// ** Flag ************************************************************************************************************
byte Sub_Timer_Flag    = 0;                                            // Sub   TimerSet 1回のみフラグ
byte Main_Timer_Flag   = 0;                                            // Main  TimerSet 1回のみフラグ
byte Local_Timer_Flag  = 0;                                            //  Local TimerSet 1回のみフラグ
byte Tunnel_Timer_Flag = 0;                                            // TunnelTimerSet 1回のみフラグ

byte Servo_S_Set_Flag = 0;                                             // Servo_Set Sub側１回のみセットフラグ
byte Servo_M_Set_Flag = 0;                                             // Servo_Set Main側１回のみセットフラグ

byte M_Train_go_Flag = 0;                                              // Train_go優先順位関数へのフラグ
byte S_Train_go_Flag = 0;                                              // Train_go優先順位関数へのフラグ
byte L_Train_go_Flag = 0;                                              // Train_go優先順位関数へのフラグ

byte Train1_Funk32_Flag = 0;                                           // Train1 Funk32 １回セット Flag
byte Train1_Main_go_Flag = 0;
byte Train1_Funk22_Flag = 0;                                           // Train1 Funk22 １回セット Flag
byte Train1_Sub_go_Flag = 0;

byte Train2_Funk32_Flag = 0;                                           // Train2 Funk32 １回セット Flag
byte Train2_Main_go_Flag = 0;
byte Train2_Funk22_Flag = 0;                                           // Train2 Funk22 １回セット Flag
byte Train2_Sub_go_Flag = 0;

byte Train3_Funk32_Flag = 0;                                           // Train3 Funk32 １回セット Flag
byte Train3_Main_go_Flag = 0;
byte Train3_Funk22_Flag = 0;                                           // Train3 Funk22 １回セット Flag
byte Train3_Sub_go_Flag = 0;

byte Train4_Funk32_Flag = 0;                                           // Train4 Funk32 １回セット Flag
byte Train4_Main_go_Flag = 0;
byte Train4_Funk22_Flag = 0;                                           // Train4 Funk22 １回セット Flag
byte Train4_Sub_go_Flag = 0;

byte Funk7_Flag         = 0;                                           // Tunnel Timer set Flag
byte Funk10_Flag        = 0;                                           // Local Station Set Flag
byte Tunnel_Timer_Set_Flag      = 0;                                   // Tunnel Timer Set Flag
byte CN_Flag      = 0;                                                 // Tunnel Timer 配列カントアップ用

byte ServoInFlag  = 1;                                                 // Servo　１回のみセット（切替）
byte ServoOutFlag = 0;                                                 // Servo　１回のみセット（切替）

byte M_priority_go_Flag = 0;                                           // Main/Sub スタート優先フラグ
byte S_priority_go_Flag = 0;                                           // Main/Sub スタート優先フラグ

byte priority_Flag = 0;                                                // Main/Sub スタート優先フラグ 1回セット
byte Priority_Select_Flag = 0;
byte M_Priority_go_Flag = 0;
byte S_Priority_go_Flag = 0;

// ** Timer 関連変数 ******************************************************************************************************
unsigned long oldTime = 0;                                             // ServoSet->TrainGo delay Time
unsigned long nowTime = 0;                                             // ServoSet->TrainGo delay Time

unsigned long Set_Time_Sub;                                            // セット時の時間
unsigned long Now_Time_Sub;                                            // 現在経過時間

unsigned long Set_Time_Main;                                           // セット時の時間
unsigned long Now_Time_Main;                                           // 現在経過時間

unsigned long Set_Time_Local;                                          // セット時の時間
unsigned long Now_Time_Local;                                          // 現在経過時間

unsigned long Set_Time_Tunnel;                                         // セット時の時間
unsigned long Now_Time_Tunnel;                                         // 現在経過時間

unsigned long Diff_Time_Sub;                                           // 出発までの時間(Sub側)
unsigned long Diff_Time_Main;                                          // 出発までの時間(Main側)
unsigned long Diff_Time_Local;                                         // 出発までの時間
unsigned long Diff_Time_Tunnel;                                        // 出発までの時間

// ** 特急列車構想検討 ****************************************************************************************************
unsigned long OnTime1[10]={10000,20000,19000,25000,35000,25000,20000,19000,25000,15000};
unsigned long OnTime2[10]={ 5000,23000,25000,13000,20000,35000,25000,13000,15000,25000};
unsigned long OnTime3[10]={10000,17000,15000,10000,20000,15000,15000,16000,25000,17000};
unsigned long OnTime4[10]={ 5000,10000, 5000,15000,10000, 5000,10000, 5000,15000,10000};
// ** 特急列車構想検討 ******************************************************************************************************

// ** Timer END ***********************************************************************************************************

// 入口サーボ制御（１：Sub　2:Main）*******************************************************************************************
byte sel = 0;                                                          // 下記配列のカウンター（0 - 19）
//                0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
byte InServo[20]={1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 1};
// ************************************************************************************************************************

esp_now_peer_info_t slave;

// ** 受信コールバック ******************************************************************************************************
//void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
//  char macStr[18];
//  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
//           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//}
// ***********************************************************************************************************************

// ** Loop ****************************************************************************************************************
void loop(){
  // ** 送信開始 ************************************************************************************************************
  if(data[0] == 99 && data[19] == 88){
    esp_err_t result = esp_now_send(slave.peer_addr, data, sizeof(data));
  }

  // ** MEGA from Data Recive **********************************************************************************************
  recive();                                                            // Data Recive
  InServoContlor();                                                    // In Servo Control
  OutServoContlor();                                                   // Out Servo Control
  Monitor();                                                         // Monitor
  
//  data[1]  = 
//  data[2]  = 
//  data[3]  = 
//  data[4]  = 
//  data[5]  = 
//  data[6]  = 
//  data[7]  = 
//  data[8]  = 
  data[9]  = Train1;                                                   // Train1 位置情報
  data[10] = Train2;                                                   // Train2 位置情報
  data[11] = Train3;                                                   // Train3 位置情報
  data[12] = Train4;                                                   // Train4 位置情報
  data[13] = ServoInPoji;                                              // 入口サーボ位置（Main:2, Sub:1）
  data[14] = ServoOutPoji;                                             // 出口サーボ位置（Main:2, Sub:1）
//  data[15] = M_Timer_set;                                            // M_Timer_set状態(set:1, nonset:0)
//  data[16] = S_Timer_set;                                            // S_Timer_set状態(set:1, nonset:0)
//  data[17] = L_Timer_set;                                            // L_Timer_set状態(set:1, nonset:0)
//  data[18] = T_Timer_set;                                            // T_Timer_set状態(set:1, nonset:0)
  
  // == Train1 ===========================================================================================================
  switch (Train1) {
    case 22:
      Train1_Funk22();
      break;
    case 32:
      Train1_Funk32();
      break;
    case 21:
      Train1_Funk21();
      break;
    case 31:
      Train1_Funk31();
      break;
    case  3:
      Train1_Funk03();
      break;
    case  4:
      Train1_Funk04();
      break;
    case  5:
      Train1_Funk05();
      break;
    case  6:
      Train1_Funk06();
      break;
    case  7:
      Train1_Funk07();
      break;
    case  8:
      Train1_Funk08();
      break;
    case  9:
      Train1_Funk09();
      break;
    case 10:
      Train1_Funk10();
      break;
    case 11:
      Train1_Funk11();
      break;
    case 12:
      Train1_Funk12();
      break;
    case 13:
      Train1_Funk13();
      break;
    default:   
      break;
  }
  // == Train2 ===========================================================================================================
  switch (Train2) {
    case 22:
      Train2_Funk22();
      break;
    case 32:
      Train2_Funk32();
      break;
    case 21:
      Train2_Funk21();
      break;
    case 31:
      Train2_Funk31();
      break;
    case  3:
      Train2_Funk03();
      break;
    case  4:
      Train2_Funk04();
      break;
    case  5:
      Train2_Funk05();
      break;
    case  6:
      Train2_Funk06();
      break;
    case  7:
      Train2_Funk07();
      break;
    case  8:
      Train2_Funk08();
      break;
    case  9:
      Train2_Funk09();
      break;
    case 10:
      Train2_Funk10();
      break;
    case 11:
      Train2_Funk11();
      break;
    case 12:
      Train2_Funk12();
      break;
    case 13:
      Train2_Funk13();
      break;
    default:
      break;
  }
  // == Train3 ===========================================================================================================
  switch (Train3) {
    case 22:
      Train3_Funk22();
      break;
    case 32:
      Train3_Funk32();
      break;
    case 21:
      Train3_Funk21();
      break;
    case 31:
      Train3_Funk31();
      break;
    case  3:
      Train3_Funk03();
      break;
    case  4:
      Train3_Funk04();
      break;
    case  5:
      Train3_Funk05();
      break;
    case  6:
      Train3_Funk06();
      break;
    case  7:
      Train3_Funk07();
      break;
    case  8:
      Train3_Funk08();
      break;
    case  9:
      Train3_Funk09();
      break;
    case 10:
      Train3_Funk10();
      break;
    case 11:
      Train3_Funk11();
      break;
    case 12:
      Train3_Funk12();
      break;
    case 13:
      Train3_Funk13();
      break;
    default:
      break;
  }
  // == Train4 =============================================================================================
   switch (Train4) {
    case 22:
      Train4_Funk22();
      break;
    case 32:
      Train4_Funk32();
      break;
    case 21:
      Train4_Funk21();
      break;
    case 31:
      Train4_Funk31();
      break;
    case  3:
      Train4_Funk03();
      break;
    case  4:
      Train4_Funk04();
      break;
    case  5:
      Train4_Funk05();
      break;
    case  6:
      Train4_Funk06();
      break;
    case  7:
      Train4_Funk07();
      break;
    case  8:
      Train4_Funk08();
      break;
    case  9:
      Train4_Funk09();
      break;
    case 10:
      Train4_Funk10();
      break;
    case 11:
      Train4_Funk11();
      break;
    case 12:
      Train4_Funk12();
      break;
    case 13:
      Train4_Funk13();
      break;
    default:
      break;
  }
  
  // == emergency stop ==================================================================================================
  if(digitalRead(StartSW) == 0){                                        // emergency stop
    while(1){                                                           // 全列車停止でプログラムの実行停止
      data[1]  = SpeedZoro;
      data[2]  = F0_L0;
      data[3]  = SpeedZoro;
      data[4]  = F0_L0;
      data[5]  = SpeedZoro;
      data[6]  = F0_L0;
      data[7]  = SpeedZoro;
      data[8]  = F0_L0;
      data[9]  = 98;
      data[10] = 98;
      data[11] = 98;
      data[12] = 98;
      data[13] = 01;
      data[14] = 01;
      data[15] = 01;
      data[16] = 01;
      data[17] = 01;
      data[18] = 01;
      esp_err_t result = esp_now_send(slave.peer_addr, data, sizeof(data));
      delay(100);
    }
  }
  // == emergency stop END ===========================================================================================
}
// ** LOOP END *******************************************************************************************************
