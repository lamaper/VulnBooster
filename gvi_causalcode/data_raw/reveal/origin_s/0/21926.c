METHOD ( asn1_parser_t , get_level , u_int , private_asn1_parser_t * this ) {
 return this -> level0 + this -> objects [ this -> line ] . level ;
 }