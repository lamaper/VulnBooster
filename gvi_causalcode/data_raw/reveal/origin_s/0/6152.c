void TSHttpIcpDynamicSet ( int value ) {
 int32_t old_value , new_value ;
 new_value = ( value == 0 ) ? 0 : 1 ;
 old_value = icp_dynamic_enabled ;
 while ( old_value != new_value ) {
 if ( ink_atomic_cas ( & icp_dynamic_enabled , old_value , new_value ) ) {
 break ;
 }
 old_value = icp_dynamic_enabled ;
 }
 }