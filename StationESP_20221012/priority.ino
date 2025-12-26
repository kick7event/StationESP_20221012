// ** Main/Sub Go 優先順位ずけ **************************************************************
void priority(){
    if(M_Train_go_Flag == 1 && S_Train_go_Flag == 0 && priority_Flag == 0){
      M_Train_go = 1;                                               // Servo動作後５秒後にMain側列車スタート
      priority_Flag = 1;
    }else{
      M_Train_go = 0; 
    }
    if(M_Train_go_Flag == 0 && S_Train_go_Flag == 1 && priority_Flag == 0){
      S_Train_go = 1;                                               // Servo動作後５秒後にMain側列車スタート
      priority_Flag = 1;
    }else{
      S_Train_go = 0;
    }
}
// ** Main/Sub Go 優先順位ずけ END **********************************************************