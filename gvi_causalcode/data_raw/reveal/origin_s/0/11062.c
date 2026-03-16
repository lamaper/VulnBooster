static inline uint32_t timerblock_scale ( TimerBlock * tb ) {
 return ( ( ( tb -> control >> 8 ) & 0xff ) + 1 ) * 10 ;
 }