#include <stdlib.h>
#include <stdio.h>
struct grade {
	char name[15];
    float course[10];
};
int main(int argc, char const *argv[]) {
    char subjects[100][10];
    struct grade *data;
    FILE *grade_file = fopen("GradeLise.txt", "r");
    char buff[1000];
    int lines = 0, i = 0, j = 0, sujNum = 0;
    if(grade_file) {
        fgets(buff, 1000, grade_file);
        for(i = 0; i < 1000; i++) {
            if(!(buff[i] == 32 || buff[i] == '\n')){
                subjects[sujNum][j] = buff[i];
                j++;
            }else {
                j = 0;
                sujNum++;
            }
        }
        printf("%d\n", sujNum);
        while(fgets(buff, 1000, grade_file)){
            lines++;
        }
        data = malloc(sizeof(struct grade) * lines);
        fclose(grade_file);
        grade_file = fopen("GradeLise.txt", "r");
        fgets(buff, 1000, grade_file);
        for(i = 0; i < lines; i++) {
            fscanf(grade_file, " %s", data[i].name);
            for(j = 0; j < sujNum; j ++) {
                fscanf(grade_file, " %f", &data[i].course[j]);
            }
        }
        printf("|%-7s", " Name");
        for(i = 0; i < sujNum; i++) {
            printf("| %-7s ", subjects[i]);
        }
        printf("%-7s|\n", "Stu_Tot.");
        for(i = 0; i < lines; i++) {
            printf("+-------+---------+---------+---------+---------+---------+---------+\n");
            printf("|%-7s| ", data[i].name);
            for(j = 0; j < sujNum; j++) {
                printf("%-7.2f | ", data[i].course[j]);
            }
            printf("\n");
        }
        
        fclose(grade_file);
        free(data);
    }else {
        printf("error!\n");
    }
    return 0;
}
