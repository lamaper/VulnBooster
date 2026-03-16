static inline int loco_predict ( uint8_t * data , int stride , int step ) {
 int a , b , c ;
 a = data [ - stride ] ;
 b = data [ - step ] ;
 c = data [ - stride - step ] ;
 return mid_pred ( a , a + b - c , b ) ;
 }