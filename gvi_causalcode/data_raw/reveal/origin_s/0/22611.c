static void set_v8086_seg ( struct kvm_segment * lhs , const SegmentCache * rhs ) {
 lhs -> selector = rhs -> selector ;
 lhs -> base = rhs -> base ;
 lhs -> limit = rhs -> limit ;
 lhs -> type = 3 ;
 lhs -> present = 1 ;
 lhs -> dpl = 3 ;
 lhs -> db = 0 ;
 lhs -> s = 1 ;
 lhs -> l = 0 ;
 lhs -> g = 0 ;
 lhs -> avl = 0 ;
 lhs -> unusable = 0 ;
 }