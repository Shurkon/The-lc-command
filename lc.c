#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define ANSI_COLOR_BLUE        "\x1b[34m"
#define ANSI_COLOR_GRAY        "\x1b[90m"
#define ANSI_COLOR_LIGHT_GRAY  "\x1b[37m"
#define ANSI_COLOR_RESET       "\x1b[0m"

void showdir(char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        char *result = entry->d_name;
        unsigned char type = entry->d_type;

        if (strcmp(result, ".") != 0 && strcmp(result, "..") != 0) {
            if (result[0] == '.') {
                printf(ANSI_COLOR_GRAY "%s\n" ANSI_COLOR_RESET, result);
            } else if (type == DT_DIR) {
                printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, result);
            } else {
                printf("%s\n", result);
            }
        }
    }

    closedir(dir);
    printf("\n");
}

void showfile(char *path) {
    FILE *file = fopen(path, "r");
    char buffer[1024];
    size_t n;

    if (!file) return;

    fwrite(ANSI_COLOR_LIGHT_GRAY, 1, strlen(ANSI_COLOR_LIGHT_GRAY), stdout);

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fwrite(ANSI_COLOR_RESET, 1, strlen(ANSI_COLOR_RESET), stdout);
    fclose(file);
}

int main(int argc, char *argv[]) {
    char *path = argv[1];
    struct stat PathStat;

    if (stat(path, &PathStat) != 0) {
        return 1;
    }

    if (S_ISDIR(PathStat.st_mode)) {
        printf(ANSI_COLOR_BLUE "\n [+] Directorio \n\n" ANSI_COLOR_RESET);
        showdir(path);
    } else if (S_ISREG(PathStat.st_mode)) {
        printf(ANSI_COLOR_BLUE "\n [+] Archivo \n\n" ANSI_COLOR_RESET);
        showfile(path);
    } else {
        return 1;
    }

    return 0;
}

