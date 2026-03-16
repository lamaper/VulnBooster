inline static void update_current_info ( HttpTransact : : CurrentInfo * into , HttpTransact : : ConnectionAttributes * from , HttpTransact : : LookingUp_t who , int attempts ) {
 into -> request_to = who ;
 into -> server = from ;
 into -> attempts = attempts ;
 }