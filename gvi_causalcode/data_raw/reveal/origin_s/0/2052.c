int do_done ( struct st_command * command ) {
 if ( cur_block == block_stack ) {
 if ( * command -> query != '}
' ) die ( "Stray 'end' command - end of block before beginning" ) ;
 die ( "Stray '}
' - end of block before beginning" ) ;
 }
 if ( cur_block -> ok && cur_block -> cmd == cmd_while ) {
 cur_block -- ;
 parser . current_line = cur_block -> line ;
 }
 else {
 if ( * cur_block -> delim ) {
 strcpy ( delimiter , cur_block -> delim ) ;
 delimiter_length = strlen ( delimiter ) ;
 }
 cur_block -- ;
 parser . current_line ++ ;
 }
 return 0 ;
 }