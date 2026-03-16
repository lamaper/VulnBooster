static int main_input ( xd3_cmd cmd , main_file * ifile , main_file * ofile , main_file * sfile ) {
 int ret ;
 xd3_stream stream ;
 size_t nread = 0 ;
 usize_t winsize ;
 int stream_flags = 0 ;
 xd3_config config ;
 xd3_source source ;
 xoff_t last_total_in = 0 ;
 xoff_t last_total_out = 0 ;
 long start_time ;
 int stdout_only = 0 ;
 int ( * input_func ) ( xd3_stream * ) ;
 int ( * output_func ) ( xd3_stream * , main_file * ) ;
 memset ( & stream , 0 , sizeof ( stream ) ) ;
 memset ( & source , 0 , sizeof ( source ) ) ;
 memset ( & config , 0 , sizeof ( config ) ) ;
 config . alloc = main_alloc ;
 config . freef = main_free1 ;
 config . iopt_size = option_iopt_size ;
 config . sprevsz = option_sprevsz ;
 do_src_fifo = 0 ;
 start_time = get_millisecs_now ( ) ;
 if ( option_use_checksum ) {
 stream_flags |= XD3_ADLER32 ;
 }
 switch ( ( int ) cmd ) {

 case CMD_PRINTHDR : stream_flags |= XD3_JUST_HDR ;
 }
 else if ( 1 ) {
 case CMD_PRINTHDRS : stream_flags |= XD3_SKIP_WINDOW ;
 }
 else {
 case CMD_PRINTDELTA : stream_flags |= XD3_SKIP_EMIT ;
 }
 ifile -> flags |= RD_NONEXTERNAL ;
 input_func = xd3_decode_input ;
 output_func = main_print_func ;
 stream_flags |= XD3_ADLER32_NOVER ;
 stdout_only = 1 ;
 break ;
 case CMD_RECODE : case CMD_MERGE : case CMD_MERGE_ARG : stream_flags |= XD3_ADLER32_NOVER | XD3_SKIP_EMIT ;
 ifile -> flags |= RD_NONEXTERNAL ;
 input_func = xd3_decode_input ;
 if ( ( ret = main_init_recode_stream ( ) ) ) {
 return EXIT_FAILURE ;
 }
 if ( cmd == CMD_RECODE ) {
 output_func = main_recode_func ;
 }
 else {
 output_func = main_merge_func ;
 }
 break ;

 input_func = xd3_encode_input ;
 output_func = main_write_output ;
 if ( option_no_compress ) {
 stream_flags |= XD3_NOCOMPRESS ;
 }
 if ( option_use_altcodetable ) {
 stream_flags |= XD3_ALT_CODE_TABLE ;
 }
 if ( option_smatch_config ) {
 const char * s = option_smatch_config ;
 char * e ;
 int values [ XD3_SOFTCFG_VARCNT ] ;
 int got ;
 config . smatch_cfg = XD3_SMATCH_SOFT ;
 for ( got = 0 ;
 got < XD3_SOFTCFG_VARCNT ;
 got += 1 , s = e + 1 ) {
 values [ got ] = strtol ( s , & e , 10 ) ;
 if ( ( values [ got ] < 0 ) || ( e == s ) || ( got < XD3_SOFTCFG_VARCNT - 1 && * e == 0 ) || ( got == XD3_SOFTCFG_VARCNT - 1 && * e != 0 ) ) {
 XPR ( NT "invalid string match specifier (-C) %d: %s\n" , got , s ) ;
 return EXIT_FAILURE ;
 }
 }
 config . smatcher_soft . large_look = values [ 0 ] ;
 config . smatcher_soft . large_step = values [ 1 ] ;
 config . smatcher_soft . small_look = values [ 2 ] ;
 config . smatcher_soft . small_chain = values [ 3 ] ;
 config . smatcher_soft . small_lchain = values [ 4 ] ;
 config . smatcher_soft . max_lazy = values [ 5 ] ;
 config . smatcher_soft . long_enough = values [ 6 ] ;
 }
 else {
 if ( option_verbose > 2 ) {
 XPR ( NT "compression level: %d\n" , option_level ) ;
 }
 if ( option_level == 0 ) {
 stream_flags |= XD3_NOCOMPRESS ;
 config . smatch_cfg = XD3_SMATCH_FASTEST ;
 }
 else if ( option_level == 1 ) {
 config . smatch_cfg = XD3_SMATCH_FASTEST ;
 }
 else if ( option_level == 2 ) {
 config . smatch_cfg = XD3_SMATCH_FASTER ;
 }
 else if ( option_level <= 5 ) {
 config . smatch_cfg = XD3_SMATCH_FAST ;
 }
 else if ( option_level == 6 ) {
 config . smatch_cfg = XD3_SMATCH_DEFAULT ;
 }
 else {
 config . smatch_cfg = XD3_SMATCH_SLOW ;
 }
 }
 break ;

 stream_flags |= XD3_ADLER32_NOVER ;
 }
 ifile -> flags |= RD_NONEXTERNAL ;
 input_func = xd3_decode_input ;
 output_func = main_write_output ;
 break ;
 default : XPR ( NT "internal error\n" ) ;
 return EXIT_FAILURE ;
 }
 main_bsize = winsize = main_get_winsize ( ifile ) ;
 if ( ( main_bdata = ( uint8_t * ) main_bufalloc ( winsize ) ) == NULL ) {
 return EXIT_FAILURE ;
 }
 config . winsize = winsize ;
 config . getblk = main_getblk_func ;
 config . flags = stream_flags ;
 if ( ( ret = main_set_secondary_flags ( & config ) ) || ( ret = xd3_config_stream ( & stream , & config ) ) ) {
 XPR ( NT XD3_LIB_ERRMSG ( & stream , ret ) ) ;
 return EXIT_FAILURE ;
 }

 XPR ( NT XD3_LIB_ERRMSG ( & stream , ret ) ) ;
 return EXIT_FAILURE ;
 }

 if ( sfile && sfile -> filename != NULL ) {
 if ( ( ret = main_set_source ( & stream , cmd , sfile , & source ) ) ) {
 return EXIT_FAILURE ;
 }
 XD3_ASSERT ( stream . src != NULL ) ;
 }
 }
 if ( cmd == CMD_PRINTHDR || cmd == CMD_PRINTHDRS || cmd == CMD_PRINTDELTA || cmd == CMD_RECODE ) {
 if ( sfile -> filename == NULL ) {
 allow_fake_source = 1 ;
 sfile -> filename = "<placeholder>" ;
 main_set_source ( & stream , cmd , sfile , & source ) ;
 }
 }
 get_millisecs_since ( ) ;
 do {
 xoff_t input_offset ;
 xoff_t input_remain ;
 usize_t try_read ;
 input_offset = ifile -> nread ;
 input_remain = XOFF_T_MAX - input_offset ;
 try_read = ( usize_t ) min ( ( xoff_t ) config . winsize , input_remain ) ;
 if ( ( ret = main_read_primary_input ( ifile , main_bdata , try_read , & nread ) ) ) {
 return EXIT_FAILURE ;
 }
 if ( nread < try_read ) {
 stream . flags |= XD3_FLUSH ;
 }

 return EXIT_FAILURE ;
 }

 if ( nread == 0 && stream . current_window > 0 ) {
 break ;
 }
 again : ret = input_func ( & stream ) ;
 switch ( ret ) {
 case XD3_INPUT : continue ;
 case XD3_GOTHEADER : {
 XD3_ASSERT ( stream . current_window == 0 ) ;
 if ( cmd == CMD_DECODE ) {
 main_get_appheader ( & stream , ifile , ofile , sfile ) ;
 if ( ( sfile -> filename != NULL ) && ( ret = main_set_source ( & stream , cmd , sfile , & source ) ) ) {
 return EXIT_FAILURE ;
 }
 }
 }
 case XD3_WINSTART : {
 goto again ;
 }
 case XD3_OUTPUT : {
 if ( ofile != NULL && ! main_file_isopen ( ofile ) && ( ret = main_open_output ( & stream , ofile ) ) != 0 ) {
 return EXIT_FAILURE ;
 }
 if ( ( ret = output_func ( & stream , ofile ) ) && ( ret != PRINTHDR_SPECIAL ) ) {
 return EXIT_FAILURE ;
 }
 if ( ret == PRINTHDR_SPECIAL ) {
 xd3_abort_stream ( & stream ) ;
 ret = EXIT_SUCCESS ;
 goto done ;
 }
 ret = 0 ;
 xd3_consume_output ( & stream ) ;
 goto again ;
 }
 case XD3_WINFINISH : {
 if ( IS_ENCODE ( cmd ) || cmd == CMD_DECODE || cmd == CMD_RECODE ) {
 if ( ! option_quiet && IS_ENCODE ( cmd ) && main_file_isopen ( sfile ) ) {
 if ( option_verbose && ! xd3_encoder_used_source ( & stream ) ) {
 XPR ( NT "warning: input window %" Q "u..%" Q "u has " "no source copies\n" , stream . current_window * winsize , ( stream . current_window + 1 ) * winsize ) ;
 XD3_ASSERT ( stream . src != NULL ) ;
 }
 if ( option_verbose > 1 && stream . srcwin_decided_early && stream . i_slots_used > stream . iopt_size ) {
 XPR ( NT "warning: input position %" Q "u overflowed " "instruction buffer, needed %u (vs. %u), " "consider changing -I\n" , stream . current_window * winsize , stream . i_slots_used , stream . iopt_size ) ;
 }
 }
 if ( option_verbose ) {
 shortbuf rrateavg , wrateavg , tm ;
 shortbuf rdb , wdb ;
 shortbuf trdb , twdb ;
 shortbuf srcpos ;
 long millis = get_millisecs_since ( ) ;
 usize_t this_read = ( usize_t ) ( stream . total_in - last_total_in ) ;
 usize_t this_write = ( usize_t ) ( stream . total_out - last_total_out ) ;
 last_total_in = stream . total_in ;
 last_total_out = stream . total_out ;
 if ( option_verbose > 1 ) {
 XPR ( NT "%" Q "u: in %s (%s): out %s (%s): " "total in %s: out %s: %s: srcpos %s\n" , stream . current_window , main_format_bcnt ( this_read , & rdb ) , main_format_rate ( this_read , millis , & rrateavg ) , main_format_bcnt ( this_write , & wdb ) , main_format_rate ( this_write , millis , & wrateavg ) , main_format_bcnt ( stream . total_in , & trdb ) , main_format_bcnt ( stream . total_out , & twdb ) , main_format_millis ( millis , & tm ) , main_format_bcnt ( sfile -> source_position , & srcpos ) ) ;
 }
 else {
 XPR ( NT "%" Q "u: in %s: out %s: total in %s: " "out %s: %s\n" , stream . current_window , main_format_bcnt ( this_read , & rdb ) , main_format_bcnt ( this_write , & wdb ) , main_format_bcnt ( stream . total_in , & trdb ) , main_format_bcnt ( stream . total_out , & twdb ) , main_format_millis ( millis , & tm ) ) ;
 }
 }
 }
 goto again ;
 }
 default : XPR ( NT XD3_LIB_ERRMSG ( & stream , ret ) ) ;
 if ( ! option_quiet && ret == XD3_INVALID_INPUT ) {
 XPR ( NT "normally this indicates that the source file is incorrect\n" ) ;
 XPR ( NT "please verify the source file with sha1sum or equivalent\n" ) ;
 }
 return EXIT_FAILURE ;
 }
 }
 while ( nread == config . winsize ) ;
 done : main_file_close ( ifile ) ;
 if ( sfile != NULL ) {
 main_file_close ( sfile ) ;
 }

 return EXIT_FAILURE ;
 }
 if ( cmd == CMD_MERGE_ARG ) {
 xd3_swap_whole_state ( & stream . whole_target , & recode_stream -> whole_target ) ;
 }

 if ( ! stdout_only && ! main_file_isopen ( ofile ) ) {
 XPR ( NT "nothing to output: %s\n" , ifile -> filename ) ;
 return EXIT_FAILURE ;
 }
 if ( main_file_close ( ofile ) != 0 ) {
 return EXIT_FAILURE ;
 }
 }

 XPR ( NT "external compression commands failed\n" ) ;
 return EXIT_FAILURE ;
 }

 XPR ( NT XD3_LIB_ERRMSG ( & stream , ret ) ) ;
 return EXIT_FAILURE ;
 }

 XPR ( NT "scanner configuration: %s\n" , stream . smatcher . name ) ;
 XPR ( NT "target hash table size: %u\n" , stream . small_hash . size ) ;
 if ( sfile != NULL && sfile -> filename != NULL ) {
 XPR ( NT "source hash table size: %u\n" , stream . large_hash . size ) ;
 }
 }
 if ( option_verbose > 2 && cmd == CMD_ENCODE ) {
 XPR ( NT "source copies: %" Q "u (%" Q "u bytes)\n" , stream . n_scpy , stream . l_scpy ) ;
 XPR ( NT "target copies: %" Q "u (%" Q "u bytes)\n" , stream . n_tcpy , stream . l_tcpy ) ;
 XPR ( NT "adds: %" Q "u (%" Q "u bytes)\n" , stream . n_add , stream . l_add ) ;
 XPR ( NT "runs: %" Q "u (%" Q "u bytes)\n" , stream . n_run , stream . l_run ) ;
 }

 if ( option_verbose ) {
 shortbuf tm ;
 long end_time = get_millisecs_now ( ) ;
 xoff_t nwrite = ofile != NULL ? ofile -> nwrite : 0 ;
 XPR ( NT "finished in %s;
 input %" Q "u output %" Q "u bytes (%0.2f%%)\n" , main_format_millis ( end_time - start_time , & tm ) , ifile -> nread , nwrite , 100.0 * nwrite / ifile -> nread ) ;
 }
 return EXIT_SUCCESS ;
 }