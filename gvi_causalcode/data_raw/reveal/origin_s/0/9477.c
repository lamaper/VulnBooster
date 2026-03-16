static int get_fixed_point_scale_factor ( int other_size , int this_size ) {
 return ( other_size << REF_SCALE_SHIFT ) / this_size ;
 }