TSAction TSContScheduleEvery ( TSCont contp , ink_hrtime every , TSThreadPool tp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 TSAction action ;
 if ( ink_atomic_increment ( ( int * ) & i -> m_event_count , 1 ) < 0 ) {
 ink_assert ( ! "not reached" ) ;
 }
 EventType etype ;
 switch ( tp ) {
 case TS_THREAD_POOL_NET : case TS_THREAD_POOL_DEFAULT : etype = ET_NET ;
 break ;
 case TS_THREAD_POOL_TASK : etype = ET_TASK ;
 break ;
 default : etype = ET_TASK ;
 break ;
 }
 action = reinterpret_cast < TSAction > ( eventProcessor . schedule_every ( i , HRTIME_MSECONDS ( every ) , etype ) ) ;
 action = ( TSAction ) ( ( uintptr_t ) action | 0x1 ) ;
 return action ;
 }