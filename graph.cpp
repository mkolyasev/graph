#include <iostream>
#include <stdlib.h>
struct item { 
    char s;
    char c; 
    int v; 
};
struct way {
    int g;
    int v;
};
const int m=8; 
struct item map[m] = {0};
struct way way[m] = { 0 };
const int n = 8; 
int road[n]; 
bool incl[n];
int firstadr = 0;
int waylen; 
char first; 
bool found;
int len, c_len; 

int find(char s, char c) {
    for (int i = 0; i < m; i++)
        if (map[i].s == s && map[i].c == c ||
            map[i].s == c && map[i].c == s) return map[i].v;
    return 0;
}

void step(char s, char f, int p) { 
    int c; 
    if (s == f) { 
        found = true; 
        len = c_len; 
        waylen = p; 
        for (int i = 0; i < waylen; i++) {
            way[i].g = road[i];
            if (i == 0 ) way[i].v =1; // 0 - Начальный 
            else if (i == waylen -1) way[i].v = 2; // 2 - Город адресат
            else  way[i].v = 0; //транзитный город
           
        } 
    }
    else { 
        for (c = 0; c < n; c++) { 
            int w = find(s, map[c].c); 
            if (w && !incl[c] && (len == 0 || c_len + w < len)) {
                road[p] = map[c].c; 
                incl[c] = true; 
                c_len += w; 
                step(map[c].c, f, p + 1); 
                road[p] = 0; 
                incl[c] = false;
                c_len -= w;
            }
        }
    }
}

int main() {
   
    setlocale(LC_ALL, "Russian");
    int y = 0;
    FILE* file;
    fopen_s(&file, "map.txt", "r");
    char list[m], o;
    int i = -1, j = 0, k, r=0;
    while (fscanf_s(file, "%c %c %d\n", &map[i].s, 2, &map[i].c, 2, &map[i].v, ++i) != EOF);
    r = i;
    int f = 0, choice , sumlen;
    do
    {
        printf("\n1.Вывести карту городов"
            "\n2.Добавить город в маршрут"
            "\n3.Сформировать маршрут по городам"
            "\n4.Завершить"
            "\n\n Пожалуйста, выберите нужный вариант: ");

        scanf_s("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Карта городов из файола map.txt\n");
        for (k = 0; k < r; k++) {
        
            printf("%c->", map[k].s);
            printf("%s ", &map[k].c);
            printf("Расстояние %d\n", map[k].v);
        }
      
        break;
           case 2:
        
               firstadr = 0;
        for (int i = 0; i < m; i++)  list[i] = false;
        printf("Введите начальный город\n");
        scanf_s("%s", &first, 2);
        getchar();
        printf("Введите город-адресат\n");
        scanf_s("%s", &list[0] ,2);
        printf("Добавить еще 1) - да, 0) - нет: ");
        scanf_s("%d", &y, 2);
        j = 1;
        while (y != 0) {
            printf("Добавьте город-адресат\n");
            scanf_s("%s", &list[j], 2);
            printf("Добавить еще 1) - да, 0) - нет: ");
            scanf_s("%d", &y, 2);
            j++;
   
        }
        break;
    case 3:
        if (j == 0) {
            printf("\nДобавьте города в маршрут !!!\n");
            break;
        }
         sumlen = 0;
        for(i = 0; i < j; i++) {
            for (int i = 0; i < n; i++) {
                road[i] = way[i].g = way[i].v =0 ;  incl[i] = false;
            }
            len = c_len = waylen = 0;
        road[0] = first; 
        incl[first] = true; 
        found = false;
    
        step(first, list[i], 1);

        if (found) {
         
            for (int o = 0; o < waylen; o++) 
                
                if (way[o].v == 1 && firstadr == 0) {
                    printf("Начальный город -> %c \n", way[o].g);
                    firstadr = 1;
                }
                else if (way[o].v == 2) printf("Город адресат -> %c \n", way[o].g);
                else if (way[o].v == 0)  printf("Транзитный город -> %c \n", way[o].g);
                 sumlen = sumlen + len;
        }
        else    printf("Путь не найден\n");
        first = list[i];
        }
        if (sumlen > 0 ) printf("\nОбщая длина пути: %d \n", sumlen);
        j = 0;
        break;
    case 4:
        f = 1;
         break;
    default:

        printf("Недействительный ввод\n");
    }

} while (f != 1);

   return 0;
}