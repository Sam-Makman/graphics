#include <stdio.h>
#include <stdlib.h>

int fac(int x){
	int total = 1;
	if(x < 0){
		return -1; 
	}
	else if(x == 0){
	 return 0;
	}
	else{
		int i;
		for(i = x; i>0; i--){
			total = total * i;
		}
		return total;
	}
}

int choose (int a, int b){
	if(b > a){
		printf("Choice Error\n");
		return -1;
		
	}else if (b > 12 || a > 12){
		printf("Integer Overflow Error\n");
		return -1;
	}else if(a==b){
		return 1;
	}else{
	int choices = (fac(a))/(fac(b)*(fac(a - b)));
	return choices;
}
}

int main(void){
	int jf, ji, jc, sf, si, sc; 
	printf("How many friends does Jeff have? >");
	scanf("%d", &jf);
	printf("How many friends can Jeff invite? >");
	scanf("%d", &ji);
	printf("How many friends does Sally have? >");
	scanf("%d", &sf);
	printf("How many friends can Sally invite? >");
	scanf("%d", &si);

	jc = choose(jf, ji);
	sc = choose(sf, si);
	

	if(jc == -1 || sc == -1){
		return -1;
	}else{
	printf("Jeff has %d choices \n", jc);
	printf("Sally has %d choices \n", sc);

	if(jc > sc){
		printf("Jeff has more freedom! \n" );
	}else if(sc > jc){
		printf("Sally has more freedom! \n" );}
	else{
		printf("Jeff and Sally have equal freedom! \n" );
	}
}
}