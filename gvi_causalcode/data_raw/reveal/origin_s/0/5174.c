static int s_aos_process ( stream_state * st , stream_cursor_read * ignore_pr , stream_cursor_write * pw , bool last ) {
 int blk_i , blk_off , blk_cnt , status = 1 ;
 uint count ;
 aos_state_t * ss = ( aos_state_t * ) st ;
 uint max_count = pw -> limit - pw -> ptr ;
 uint pos = stell ( ss -> s ) ;
 unsigned const char * data ;
 ref * blk_ref ;
 pos += sbufavailable ( ss -> s ) ;
 if ( pos >= ss -> file_sz ) return EOFC ;
 blk_i = pos / ss -> blk_sz ;
 blk_off = pos % ss -> blk_sz ;
 blk_cnt = r_size ( & ss -> blocks ) ;
 count = blk_i < blk_cnt - 1 ? ss -> blk_sz : ss -> blk_sz_last ;
 blk_ref = ss -> blocks . value . refs ;
 data = blk_ref [ blk_i ] . value . bytes ;
 if ( max_count > count - blk_off ) {
 max_count = count - blk_off ;
 if ( blk_i == blk_cnt - 1 ) status = EOFC ;
 }
 memcpy ( pw -> ptr + 1 , data + blk_off , max_count ) ;
 pw -> ptr += max_count ;
 return status ;
 }