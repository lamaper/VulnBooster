static void validate_stream_config ( const struct stream_state * stream , const struct VpxEncoderConfig * global ) {
 const struct stream_state * streami ;
 if ( ! stream -> config . cfg . g_w || ! stream -> config . cfg . g_h ) fatal ( "Stream %d: Specify stream dimensions with --width (-w) " " and --height (-h)" , stream -> index ) ;
 if ( stream -> config . cfg . g_profile != 0 && ! global -> experimental_bitstream ) {
 fatal ( "Stream %d: profile %d is experimental and requires the --%s flag" , stream -> index , stream -> config . cfg . g_profile , experimental_bitstream . long_name ) ;
 }
 if ( stream -> config . cfg . g_input_bit_depth > ( unsigned int ) stream -> config . cfg . g_bit_depth ) {
 fatal ( "Stream %d: codec bit depth (%d) less than input bit depth (%d)" , stream -> index , ( int ) stream -> config . cfg . g_bit_depth , stream -> config . cfg . g_input_bit_depth ) ;
 }
 for ( streami = stream ;
 streami ;
 streami = streami -> next ) {
 if ( ! streami -> config . out_fn ) fatal ( "Stream %d: Output file is required (specify with -o)" , streami -> index ) ;
 if ( streami != stream ) {
 const char * a = stream -> config . out_fn ;
 const char * b = streami -> config . out_fn ;
 if ( ! strcmp ( a , b ) && strcmp ( a , "/devull" ) && strcmp ( a , ":nul" ) ) fatal ( "Stream %d: duplicate output file (from stream %d)" , streami -> index , stream -> index ) ;
 }
 if ( streami != stream ) {
 const char * a = stream -> config . stats_fn ;
 const char * b = streami -> config . stats_fn ;
 if ( a && b && ! strcmp ( a , b ) ) fatal ( "Stream %d: duplicate stats file (from stream %d)" , streami -> index , stream -> index ) ;
 }

 const char * a = stream -> config . fpmb_stats_fn ;
 const char * b = streami -> config . fpmb_stats_fn ;
 if ( a && b && ! strcmp ( a , b ) ) fatal ( "Stream %d: duplicate mb stats file (from stream %d)" , streami -> index , stream -> index ) ;
 }

 }