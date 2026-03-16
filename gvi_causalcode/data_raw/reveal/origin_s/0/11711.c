static void arabic_joining ( hb_buffer_t * buffer ) {
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int prev = ( unsigned int ) - 1 , state = 0 ;
 for ( unsigned int i = 0 ;
 i < buffer -> context_len [ 0 ] ;
 i ++ ) {
 unsigned int this_type = get_joining_type ( buffer -> context [ 0 ] [ i ] , buffer -> unicode -> general_category ( buffer -> context [ 0 ] [ i ] ) ) ;
 if ( unlikely ( this_type == JOINING_TYPE_T ) ) continue ;
 const arabic_state_table_entry * entry = & arabic_state_table [ state ] [ this_type ] ;
 state = entry -> next_state ;
 break ;
 }
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) {
 unsigned int this_type = get_joining_type ( info [ i ] . codepoint , _hb_glyph_info_get_general_category ( & info [ i ] ) ) ;
 if ( unlikely ( this_type == JOINING_TYPE_T ) ) {
 info [ i ] . arabic_shaping_action ( ) = NONE ;
 continue ;
 }
 const arabic_state_table_entry * entry = & arabic_state_table [ state ] [ this_type ] ;
 if ( entry -> prev_action != NONE && prev != ( unsigned int ) - 1 ) info [ prev ] . arabic_shaping_action ( ) = entry -> prev_action ;
 info [ i ] . arabic_shaping_action ( ) = entry -> curr_action ;
 prev = i ;
 state = entry -> next_state ;
 }
 for ( unsigned int i = 0 ;
 i < buffer -> context_len [ 1 ] ;
 i ++ ) {
 unsigned int this_type = get_joining_type ( buffer -> context [ 1 ] [ i ] , buffer -> unicode -> general_category ( buffer -> context [ 1 ] [ i ] ) ) ;
 if ( unlikely ( this_type == JOINING_TYPE_T ) ) continue ;
 const arabic_state_table_entry * entry = & arabic_state_table [ state ] [ this_type ] ;
 if ( entry -> prev_action != NONE && prev != ( unsigned int ) - 1 ) info [ prev ] . arabic_shaping_action ( ) = entry -> prev_action ;
 break ;
 }
 }