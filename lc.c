#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

void showdir(char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL)
        return;

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    printf("\n");
}

void showfile(char *path) {
    FILE *file = fopen(path, "r");
    char buffer[1024];
    size_t n;

    if (file == NULL)
        return;

    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, n, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    char *path = argv[1];
    struct stat PathStat;

    if (stat(path, &PathStat) != 0)
        return 1;

    if (S_ISDIR(PathStat.st_mode)) {
        printf("\n[+] Directorio \n\n");
        showdir(path);
    } else if (S_ISREG(PathStat.st_mode)) {
        printf("\n[+] Archivo \n\n");
        showfile(path);
    } else {
        return 1;
    }

    return 0;
}
