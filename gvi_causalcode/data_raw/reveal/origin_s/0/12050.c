void pk_transaction_cancel_bg ( PkTransaction * transaction ) {
 g_debug ( "CancelBg method called on %s" , transaction -> priv -> tid ) ;
 if ( transaction -> priv -> state == PK_TRANSACTION_STATE_FINISHED ) return ;
 if ( ! pk_backend_is_implemented ( transaction -> priv -> backend , PK_ROLE_ENUM_CANCEL ) ) {
 g_warning ( "Cancel not supported by backend" ) ;
 return ;
 }
 if ( transaction -> priv -> state <= PK_TRANSACTION_STATE_READY ) {
 pk_transaction_finished_emit ( transaction , PK_EXIT_ENUM_CANCELLED , 0 ) ;
 return ;
 }
 pk_backend_job_set_status ( transaction -> priv -> job , PK_STATUS_ENUM_CANCEL ) ;
 pk_backend_job_set_allow_cancel ( transaction -> priv -> job , FALSE ) ;
 pk_backend_job_set_exit_code ( transaction -> priv -> job , PK_EXIT_ENUM_CANCELLED_PRIORITY ) ;
 pk_backend_cancel ( transaction -> priv -> backend , transaction -> priv -> job ) ;
 }