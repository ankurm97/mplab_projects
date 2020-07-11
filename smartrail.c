#include <reg51.h>
void main()
{
P0=0x00;
P1=0x00;
P2=0x00;
P3=0x00;
switch(P0)
{
case 0x01:
{
P1=0x0B;
break;
}
case 0x02:
{
P1=0x14;
break;
}
default:
{
P1=0x04;
}
}
}