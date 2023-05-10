#include "ui_graph.h"
#include "bsp_delay.h"
Graph_Data G1,G2,G3,G4,G5;

void ui_task()
{
//main函数内容
memset(&G1, 0 ,sizeof(Graph_Data));
memset(&G2,0,sizeof(G2));
memset(&G3,0,sizeof(G3));
memset(&G4,0,sizeof(G4));
memset(&G5,0,sizeof(G5));

Line_Draw(&G1,"001",UI_Graph_ADD,9,UI_Color_Orange,3,960,570,960,200);
Rectangle_Draw(&G2,"002",UI_Graph_ADD,9,UI_Color_Pink,5,700,450,1000,650);
Arc_Draw(&G3,"003",UI_Graph_ADD,9,UI_Color_Green,70,180,5,960,400,80,80);
Circle_Draw(&G4,"004",UI_Graph_ADD,9,UI_Color_Cyan,8,700,700,100);
Line_Draw(&G5,"001",UI_Graph_ADD,9,UI_Color_Orange,3,1100,800,700,800);
UI_ReFresh(5,G1,G2,G3,G4,G5);                          //绘制图形

while(1)
{
    delay_ms(700);
    Circle_Draw(&G4,"004",UI_Graph_Change,9,UI_Color_Pink,8,700,700,100);
    UI_ReFresh(1,G4);
    delay_ms(700);
    Circle_Draw(&G4,"004",UI_Graph_Change,9,UI_Color_Cyan,8,700,700,100);
    UI_ReFresh(1,G4);                                                     //刷新圆形颜色
}
}