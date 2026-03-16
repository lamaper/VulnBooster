static guint prplcb_ev_input_add ( int fd , PurpleInputCondition cond , PurpleInputFunction func , gpointer udata ) {
 return b_input_add ( fd , cond | B_EV_FLAG_FORCE_REPEAT , ( b_event_handler ) func , udata ) ;
 }