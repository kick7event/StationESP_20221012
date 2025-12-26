// ** Timer Set ***************************************************************************
void S_Timer_set_Lib(){                                              // Sub Timer Set Library
  if(S_Timer_set == 0 && Sub_Timer_Flag == 0){
      Set_Time_Sub = millis();                                       // セット時・時間保存
      Sub_Timer_Flag = 1;                                            // Timer Set １回のみ<OK>
  }
}

void M_Timer_set_Lib(){                                              // Main Timer Set Library
  if(M_Timer_set == 0 && Main_Timer_Flag == 0){                      // Main側 Timer Set Flag
      Set_Time_Main = millis();                                      // セット時・時間保存
      Main_Timer_Flag = 1;                                           // Timer Set １回のみ
  }
}

void L_Timer_set_Lib(){                                              // Local Station Timer Set
  if(L_Timer_set == 0 && Local_Timer_Flag == 0){                     // Local Station Timer Set Flag
      Set_Time_Local = millis();                                     // セット時・時間保存
      Local_Timer_Flag = 1;                                          // Timer Set １回のみ
  }
}

void T_Timer_set_Lib(){                                              // Tunnel Timer Set
  if(T_Timer_set == 0 && Tunnel_Timer_Flag == 0){                    // Tunnel Timer Set Flag
      Set_Time_Tunnel = millis();                                    // セット時・時間保存
      Tunnel_Timer_Flag = 1;                                         // Timer Set １回のみ
  }
}
// ** Timer Set END ***********************************************************************
