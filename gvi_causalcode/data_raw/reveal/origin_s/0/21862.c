static void cirrus_write_hidden_dac ( CirrusVGAState * s , int reg_value ) {
 if ( s -> cirrus_hidden_dac_lockindex == 4 ) {
 s -> cirrus_hidden_dac_data = reg_value ;


 s -> cirrus_hidden_dac_lockindex = 0 ;
 }