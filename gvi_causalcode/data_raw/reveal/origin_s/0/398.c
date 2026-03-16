static void generate_json_string ( FBuffer * buffer , VALUE Vstate , JSON_Generator_State * state , VALUE obj ) {
 fbuffer_append_char ( buffer , '"' ) ;


 convert_UTF8_to_JSON_ASCII ( buffer , obj ) ;
 }
 else {
 convert_UTF8_to_JSON ( buffer , obj ) ;
 }
 fbuffer_append_char ( buffer , '"' ) ;
 }