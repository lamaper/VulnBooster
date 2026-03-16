static int selinux_syslog ( int type ) {
 int rc ;
 switch ( type ) {
 case SYSLOG_ACTION_READ_ALL : case SYSLOG_ACTION_SIZE_BUFFER : rc = task_has_system ( current , SYSTEM__SYSLOG_READ ) ;
 break ;
 case SYSLOG_ACTION_CONSOLE_OFF : case SYSLOG_ACTION_CONSOLE_ON : case SYSLOG_ACTION_CONSOLE_LEVEL : rc = task_has_system ( current , SYSTEM__SYSLOG_CONSOLE ) ;
 break ;
 case SYSLOG_ACTION_CLOSE : case SYSLOG_ACTION_OPEN : case SYSLOG_ACTION_READ : case SYSLOG_ACTION_READ_CLEAR : case SYSLOG_ACTION_CLEAR : default : rc = task_has_system ( current , SYSTEM__SYSLOG_MOD ) ;
 break ;
 }
 return rc ;
 }