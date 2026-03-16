static void mi_check_print_msg ( MI_CHECK * param , const char * msg_type , const char * fmt , va_list args ) {
 THD * thd = ( THD * ) param -> thd ;
 Protocol * protocol = thd -> protocol ;
 size_t length , msg_length ;
 char msgbuf [ MI_MAX_MSG_BUF ] ;
 char name [ NAME_LEN * 2 + 2 ] ;
 msg_length = my_vsnprintf ( msgbuf , sizeof ( msgbuf ) , fmt , args ) ;
 msgbuf [ sizeof ( msgbuf ) - 1 ] = 0 ;
 DBUG_PRINT ( msg_type , ( "message: %s" , msgbuf ) ) ;
 if ( ! thd -> vio_ok ( ) ) {
 sql_print_error ( "%s" , msgbuf ) ;
 return ;
 }
 if ( param -> testflag & ( T_CREATE_MISSING_KEYS | T_SAFE_REPAIR | T_AUTO_REPAIR ) ) {
 my_message ( ER_NOT_KEYFILE , msgbuf , MYF ( MY_WME ) ) ;
 return ;
 }
 length = ( uint ) ( strxmov ( name , param -> db_name , "." , param -> table_name , NullS ) - name ) ;
 if ( param -> need_print_msg_lock ) mysql_mutex_lock ( & param -> print_msg_mutex ) ;
 protocol -> prepare_for_resend ( ) ;
 protocol -> store ( name , length , system_charset_info ) ;
 protocol -> store ( param -> op_name , system_charset_info ) ;
 protocol -> store ( msg_type , system_charset_info ) ;
 protocol -> store ( msgbuf , msg_length , system_charset_info ) ;
 if ( protocol -> write ( ) ) sql_print_error ( "Failed on my_net_write, writing to stderr instead: %s\n" , msgbuf ) ;
 if ( param -> need_print_msg_lock ) mysql_mutex_unlock ( & param -> print_msg_mutex ) ;
 return ;
 }