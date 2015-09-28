#include <FPT.h>

int main(){
  double swidth, sheight, radians;
  double n;
  swidth = 600; sheight = 600;
  scanf("%lf",&n);
  G_init_graphics (swidth, sheight);

  G_circle(300, 300, 200);
  double i;
  for(i; i<n; i++){
    radians = i *((2 * M_PI) / n);
    int x, y;
    G_rgb((n-i)/n,(n-(n-i))/n, (n-i)/n);
    G_fill_sector(300, 300, 200, radians, (i+1)*((2 * M_PI)/n));

  }




  G_wait_key();


}
