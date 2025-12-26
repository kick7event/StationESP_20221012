void Priority_Select(){
    if(Priority_Select_Flag==0){
        // Sub側のみ列車が入線している場合
        if((Train1==22 || Train2==22 || Train3==22 || Train4==22) && (!(Train1==32 || Train2==32 || Train3==32 || Train4==32))){
            S_Priority_go_Flag   = 1;                                            //仮　出発優先権フラグ（Sub）
        }
        // Main側のみ列車が入線している場合
        if((Train1==32 || Train2==32 || Train3==32 || Train4==32) && (!(Train1==22 || Train2==22 || Train3==22 || Train4==22))){
            M_Priority_go_Flag   = 1;                                            //仮　出発優先フラグ（Main）
        }
        // Main Sub 両線に入線している場合
        if((Train1==32 || Train2==32 || Train3==32 || Train4==32) && ((Train1==22 || Train2==22 || Train3==22 || Train4==22))){
            
            if(InServo[sel]==1){                                                 // Sub側
                S_Priority_go_Flag   = 1;                                        //仮　出発優先権フラグ（Sub）
                Serial.println("S_Priorty");
            }
            if(InServo[sel]==2){                                                 // Main側
                M_Priority_go_Flag   = 1;                                        //仮　出発優先フラグ（Main）
                Serial.println("M_Priorty");
            }
        }
    }
    Priority_Select_Flag = 1;
}
