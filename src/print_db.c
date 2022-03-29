#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct module {
    int id;
    char name_module[30];
    int number_memory;
    int number_cell;
    int flag;
} module;

module read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
void print_db(FILE *pfile, int size_db);
void search_in_db(FILE *pfile, int size_db);
int insert_value_for_search(int col, FILE *pfile, int size_db);
void write_record_in_file(FILE *pfile, module *record_to_write);
module input_data();
// void insert_record_in_db(FILE *file);

int main() {
    char *file_name = "master_modules_copy.db";
    FILE *file = NULL;
    file = fopen(file_name, "rb+");
    int size_db = get_records_count_in_file(file);

    if (file == NULL) {
        printf("n/a\n");
    } else {
        
        // search_in_db(file, size_db);


        module record;
        record = input_data();
        write_record_in_file(file, &record);

        print_db(file, size_db);


    }
    
    fclose(file);
    return 0;
}

module input_data() {
    module record;
    int len;
    printf("input id: ");
    scanf("%d", &record.id);
    printf("input name module: ");
    getchar(); 
    fgets(record.name_module, 30, stdin);
    len = strlen(record.name_module);
    record.name_module[len - 1] = '\0';
    printf("input number memory: ");
    scanf("%d", &record.number_memory);
    printf("input number cell: ");
    scanf("%d", &record.number_cell);
    printf("input flag: ");
    scanf("%d", &record.flag);    
    return record;
}

void write_record_in_file(FILE *pfile, module *record_to_write) {
    int offset = get_records_count_in_file(pfile) * sizeof(module);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(module), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int insert_value_for_search(int col, FILE *pfile, int size_db) {
    module modules;
    int flag = 0;
    int val, len;
    char name[30];
    switch(col) {
        case 1: printf("Input value: ");
                scanf("%d", &val);
                for (int i = 0; i < size_db; i++) {
                    modules = read_record_from_file(pfile, i);
                    if (modules.id == val) {
                        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
                            modules.number_cell, modules.flag);
                        flag++;
                    }
                }
                break;
        case 2: getchar(); 
                fgets(name, 30, stdin);
                len = strlen(name);
                name[len - 1] = '\0';
                for (int i = 0; i < size_db; i++) {
                    modules = read_record_from_file(pfile, i);
                    if (strcmp(modules.name_module, name) == 0) {
                        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
                            modules.number_cell, modules.flag);
                        flag++;
                    }
                }
                break;                
        case 3: printf("Input value: ");
                scanf("%d", &val);
                for (int i = 0; i < size_db; i++) {
                    modules = read_record_from_file(pfile, i);
                    if (modules.number_memory == val) {
                        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
                            modules.number_cell, modules.flag);
                        flag++;
                    }
                }
                break;
        case 4: printf("Input value: ");
                scanf("%d", &val);
                for (int i = 0; i < size_db; i++) {
                    modules = read_record_from_file(pfile, i);
                    if (modules.number_cell == val) {
                        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
                            modules.number_cell, modules.flag);
                        flag++;
                    }
                }
                break;
        case 5: printf("Input value: ");
                scanf("%d", &val);
                for (int i = 0; i < size_db; i++) {
                    modules = read_record_from_file(pfile, i);
                    if (modules.flag == val) {
                        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
                            modules.number_cell, modules.flag);
                        flag++;
                    }
                }
                break;
    }
    return flag;
}

void search_in_db(FILE *pfile, int size_db) {
    int column;
    printf("Enter the column: ");
    scanf("%d", &column);
    if(!insert_value_for_search(column, pfile, size_db)) {
        printf("n/a\n");
    }
}

void print_db(FILE *pfile, int size_db) {
    module modules;
    for (int i = 0; i < size_db; i++) {
        modules = read_record_from_file(pfile, i);
        printf("%d - %s - %d - %d - %d\n", modules.id, modules.name_module, modules.number_memory,
        modules.number_cell, modules.flag);
    }
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(module);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

module read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(module);
    fseek(pfile, offset, SEEK_SET);
    module record;
    fread(&record, sizeof(module), 1, pfile);
    rewind(pfile);
    return record;
}
