void ps2_queue ( PS2State * s , int b ) {
 PS2Queue * q = & s -> queue ;
 if ( q -> count >= PS2_QUEUE_SIZE - 1 ) return ;
 q -> data [ q -> wptr ] = b ;
 if ( ++ q -> wptr == PS2_QUEUE_SIZE ) q -> wptr = 0 ;
 q -> count ++ ;
 s -> update_irq ( s -> update_arg , 1 ) ;
 }