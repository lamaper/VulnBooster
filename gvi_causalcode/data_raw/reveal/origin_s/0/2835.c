uint32_t ps2_read_data ( PS2State * s ) {
 PS2Queue * q ;
 int val , index ;
 trace_ps2_read_data ( s ) ;
 q = & s -> queue ;
 if ( q -> count == 0 ) {
 index = q -> rptr - 1 ;
 if ( index < 0 ) index = PS2_QUEUE_SIZE - 1 ;
 val = q -> data [ index ] ;
 }
 else {
 val = q -> data [ q -> rptr ] ;
 if ( ++ q -> rptr == PS2_QUEUE_SIZE ) q -> rptr = 0 ;
 q -> count -- ;
 s -> update_irq ( s -> update_arg , 0 ) ;
 s -> update_irq ( s -> update_arg , q -> count != 0 ) ;
 }
 return val ;
 }