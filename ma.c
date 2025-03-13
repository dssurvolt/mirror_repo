/*
** EPITECH PROJECT, 2024
** mirror_repo [WSL: kali-linux]
** File description:
** ma.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/* ===========================
   🔹 Définition des structures
   =========================== */

#define MAX_LINE_LENGTH 1024
#define MAX_LABELS 100
#define MAX_INSTRUCTIONS 16

typedef struct {
    char name[128];
    char comment[2048];
} header_t;

typedef struct {
    char label[50];
    int position;
} label_t;

typedef struct {
    char *mnemonic;
    int opcode;
    int param_count;
} instruction_t;

/* ===========================
   🔹 Table des instructions
   =========================== */

instruction_t INSTRUCTIONS[MAX_INSTRUCTIONS] = {
    {"live", 0x01, 1}, {"ld", 0x02, 2}, {"st", 0x03, 2}, {"add", 0x04, 3},
    {"sub", 0x05, 3}, {"and", 0x06, 3}, {"or", 0x07, 3}, {"xor", 0x08, 3},
    {"zjmp", 0x09, 1}, {"ldi", 0x0a, 3}, {"sti", 0x0b, 3}, {"fork", 0x0c, 1},
    {"lld", 0x0d, 2}, {"lldi", 0x0e, 3}, {"lfork", 0x0f, 1}, {"aff", 0x10, 1}
};

/* ===========================
   🔹 Gestion des Labels
   =========================== */

label_t labels[MAX_LABELS];
int label_count = 0;

// Ajoute un label à la liste
void add_label(char *name, int position) {
    strcpy(labels[label_count].label, name);
    labels[label_count].position = position;
    label_count++;
}

// Trouve la position d'un label
int get_label_position(char *name) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].label, name) == 0) return labels[i].position;
    }
    return -1;
}

/* ===========================
   🔹 Gestion des Instructions
   =========================== */

// Trouve l'instruction dans la table
int get_opcode(char *mnemonic) {
    for (int i = 0; i < MAX_INSTRUCTIONS; i++) {
        if (strcmp(INSTRUCTIONS[i].mnemonic, mnemonic) == 0) {
            return INSTRUCTIONS[i].opcode;
        }
    }
    return -1;
}

// Vérifie si une ligne est un label
int is_label(char *line) {
    return (line[strlen(line) - 1] == ':');
}

// Convertit une instruction en bytecode
void convert_instruction(FILE *output, char *line, int pos) {
    char *mnemonic = strtok(line, " ,\n");
    int opcode = get_opcode(mnemonic);

    if (opcode == -1) {
        fprintf(stderr, "Erreur: Instruction inconnue \"%s\"\n", mnemonic);
        exit(84);
    }

    fputc(opcode, output);
    printf("🔹 Instruction \"%s\" convertie en opcode %02X\n", mnemonic, opcode);

    char *param;
    while ((param = strtok(NULL, " ,\n")) != NULL) {
        if (param[0] == 'r') {
            int reg_num = atoi(&param[1]);
            fputc(reg_num, output);
        } else if (param[0] == '%') {
            if (param[1] == ':') {  // Label
                int label_pos = get_label_position(&param[2]);
                fputc(label_pos, output);
            } else {  // Direct Value
                int value = atoi(&param[1]);
                fputc(value, output);
            }
        } else {  // Indirect
            int value = atoi(param);
            fputc(value, output);
        }
    }
}

/* ===========================
   🔹 Lecture et écriture des fichiers
   =========================== */

// Lit le fichier .s et convertit en .cor
void assemble(char *input_filename) {
    FILE *input = fopen(input_filename, "r");
    if (!input) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir %s\n", input_filename);
        exit(84);
    }

    char output_filename[256];
    strcpy(output_filename, input_filename);
    char *ext = strrchr(output_filename, '.');
    if (ext) strcpy(ext, ".cor");
    else strcat(output_filename, ".cor");

    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        fprintf(stderr, "Erreur: Impossible de créer %s\n", output_filename);
        fclose(input);
        exit(84);
    }

    printf("✅ Assemblage de %s -> %s\n", input_filename, output_filename);

    header_t header;
    int position = 0;
    char line[MAX_LINE_LENGTH];

    // Lecture du header
    while (fgets(line, sizeof(line), input)) {
        if (strncmp(line, ".name", 5) == 0) {
            sscanf(line, ".name \"%[^\"]\"", header.name);
        } else if (strncmp(line, ".comment", 8) == 0) {
            sscanf(line, ".comment \"%[^\"]\"", header.comment);
        } else break;
    }

    // Écriture du header
    fwrite(&header, sizeof(header_t), 1, output);
    fclose(input);

    // Première passe : recherche des labels
    input = fopen(input_filename, "r");
    while (fgets(line, sizeof(line), input)) {
        if (is_label(line)) {
            line[strlen(line) - 1] = '\0';  // Retire le ':'
            add_label(line, position);
        } else {
            position++;
        }
    }
    fclose(input);

    // Deuxième passe : écriture des instructions
    input = fopen(input_filename, "r");
    while (fgets(line, sizeof(line), input)) {
        if (line[0] == '.' || line[0] == '#') continue;  // Ignore les headers et commentaires
        if (is_label(line)) continue;
        convert_instruction(output, line, position++);
    }

    fclose(input);
    fclose(output);
}

/* ===========================
   🔹 Fonction principale
   =========================== */

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: ./asm file.s\n");
        return 84;
    }

    assemble(argv[1]);
    return 0;
}
