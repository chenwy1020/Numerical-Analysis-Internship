#include <stdio.h>

void main( )

{

int i, m=0, n=0, k=0;

for(i=9; i<=11; i++)

switch( i / 10 )

{

case 0: m++; k++; break;

case 9: n++; break;

default: m++; n++;

}

printf("%d %d %d\n", m, n, k);

}
