/**
 * c_to_asm.c - Versión Semana 3 Completa
 * Compilador simplificado de C a ASM para la ISA de 16 bits
 * 
 * Soporta:
 * - Declaraciones: int x;
 * - Asignaciones: x = 5; x = y + z;
 * - Condicionales: if (x == y) { ... }
 * - Bucles: while (x != 0) { ... } y for
 * - Funciones simples con return
 * - Llamadas a funciones
 * 
 * Convención de llamada:
 * - Parámetros: R0-R3 (hasta 4 parámetros)
 * - Valor de retorno: R0
 * - Variables locales: R4-R13
 * - R14: Stack Pointer (SP)
 * - R15: Temporal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>

#define MAX_VARS 14
#define MAX_LINE 512
#define MAX_LABELS 100
#define MAX_FUNCTIONS 20

typedef struct {
    char name[64];
    int reg;  // R0-R13
    bool is_param;
} Variable;

typedef struct {
    char name[64];
    int num_params;
    int label_id;
} FunctionInfo;

typedef struct {
    Variable vars[MAX_VARS];
    int var_count;
    int label_counter;
    int indent_level;
    FunctionInfo functions[MAX_FUNCTIONS];
    int function_count;
    FunctionInfo *current_function;
    int next_local_reg;  // Siguiente registro para variables locales (empieza en 4)
    bool function_has_explicit_return;  // Flag para evitar RETORNAR duplicado
} Compiler;

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

static char *trim(char *str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

static int find_variable(Compiler *c, const char *name) {
    for (int i = 0; i < c->var_count; i++) {
        if (strcmp(c->vars[i].name, name) == 0) {
            return c->vars[i].reg;
        }
    }
    return -1;
}

static int allocate_register(Compiler *c, const char *name, bool is_param) {
    if (c->var_count >= MAX_VARS) {
        fprintf(stderr, "[ERROR COMPILADOR] Demasiadas variables (máx: %d)\n", MAX_VARS);
        exit(1);
    }
    
    int reg;
    if (is_param) {
        // Parámetros en R0-R3
        reg = c->var_count;
    } else {
        // Variables locales en R4-R13
        reg = 4 + c->next_local_reg++;
    }
    
    strncpy(c->vars[c->var_count].name, name, 63);
    c->vars[c->var_count].name[63] = '\0';
    c->vars[c->var_count].reg = reg;
    c->vars[c->var_count].is_param = is_param;
    c->var_count++;
    
    printf("; Variable '%s' -> R%d%s\n", name, reg, is_param ? " (param)" : "");
    return reg;
}

static FunctionInfo *find_function(Compiler *c, const char *name) {
    for (int i = 0; i < c->function_count; i++) {
        if (strcmp(c->functions[i].name, name) == 0) {
            return &c->functions[i];
        }
    }
    return NULL;
}

static void add_function(Compiler *c, const char *name, int num_params) {
    if (c->function_count >= MAX_FUNCTIONS) {
        fprintf(stderr, "[ERROR COMPILADOR] Demasiadas funciones\n");
        exit(1);
    }
    
    strncpy(c->functions[c->function_count].name, name, 63);
    c->functions[c->function_count].num_params = num_params;
    c->functions[c->function_count].label_id = c->label_counter++;
    c->function_count++;
}

static int get_next_label(Compiler *c) {
    return c->label_counter++;
}

static bool is_number(const char *str) {
    if (!str || !*str) return false;
    if (*str == '-') str++;
    while (*str) {
        if (!isdigit((unsigned char)*str)) return false;
        str++;
    }
    return true;
}

// ============================================================================
// PARSING Y GENERACIÓN
// ============================================================================

static void emit(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

static void compile_declaration(Compiler *c, const char *line) {
    // int x; o int x = 5;
    char type[64], rest[256];
    if (sscanf(line, "%s %[^;]", type, rest) == 2) {
        char *var_name = rest;
        char *equals = strchr(rest, '=');
        
        if (equals) {
            *equals = '\0';
            var_name = trim(rest);
            char *value = trim(equals + 1);
            
            if (find_variable(c, var_name) >= 0) {
                fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' ya declarada\n", var_name);
                exit(1);
            }
            
            int reg = allocate_register(c, var_name, false);
            
            if (is_number(value)) {
                emit("MOVI R%d, %s  ; %s = %s", reg, value, var_name, value);
            } else {
                int src_reg = find_variable(c, value);
                if (src_reg < 0) {
                    fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", value);
                    exit(1);
                }
                emit("MOVER R%d, R%d  ; %s = %s", reg, src_reg, var_name, value);
            }
        } else {
            var_name = trim(rest);
            
            if (find_variable(c, var_name) >= 0) {
                fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' ya declarada\n", var_name);
                exit(1);
            }
            
            int reg = allocate_register(c, var_name, false);
            emit("MOVI R%d, 0  ; Inicializar %s = 0", reg, var_name);
        }
    }
}

static void compile_assignment(Compiler *c, const char *line) {
    // x = 5; o x = y + z; o x = y;
    char lhs[64], rhs[256];
    if (sscanf(line, "%[^=] = %[^;]", lhs, rhs) == 2) {
        char *var_name = trim(lhs);
        char *expression = trim(rhs);
        
        int dest_reg = find_variable(c, var_name);
        if (dest_reg < 0) {
            fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", var_name);
            exit(1);
        }
        
        // Analizar expresión del lado derecho
        if (is_number(expression)) {
            // x = 5
            emit("MOVI R%d, %s  ; %s = %s", dest_reg, expression, var_name, expression);
            
        } else if (strchr(expression, '+')) {
            // x = y + z
            char op1[64], op2[64];
            if (sscanf(expression, "%[^+] + %s", op1, op2) == 2) {
                char *v1 = trim(op1);
                char *v2 = trim(op2);
                
                int r1, r2;
                if (is_number(v1)) {
                    r1 = 15;  // Temporal
                    emit("MOVI R15, %s", v1);
                } else {
                    r1 = find_variable(c, v1);
                    if (r1 < 0) {
                        fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", v1);
                        exit(1);
                    }
                }
                
                if (is_number(v2)) {
                    r2 = 15;
                    emit("MOVI R15, %s", v2);
                    emit("SUMAR R%d, R15  ; %s = %s + %s", dest_reg, var_name, v1, v2);
                } else {
                    r2 = find_variable(c, v2);
                    if (r2 < 0) {
                        fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", v2);
                        exit(1);
                    }
                    
                    if (r1 != dest_reg) {
                        emit("MOVER R%d, R%d", dest_reg, r1);
                    }
                    emit("SUMAR R%d, R%d  ; %s = %s + %s", dest_reg, r2, var_name, v1, v2);
                }
            }
            
        } else if (strchr(expression, '-')) {
            // x = y - z
            char op1[64], op2[64];
            if (sscanf(expression, "%[^-] - %s", op1, op2) == 2) {
                char *v1 = trim(op1);
                char *v2 = trim(op2);
                
                int r1 = find_variable(c, v1);
                int r2 = find_variable(c, v2);
                
                if (r1 < 0 || r2 < 0) {
                    fprintf(stderr, "[ERROR COMPILADOR] Variable no declarada en resta\n");
                    exit(1);
                }
                
                if (r1 != dest_reg) {
                    emit("MOVER R%d, R%d", dest_reg, r1);
                }
                emit("RESTAR R%d, R%d  ; %s = %s - %s", dest_reg, r2, var_name, v1, v2);
            }
            
        } else {
            // x = y (asignación simple)
            int src_reg = find_variable(c, expression);
            if (src_reg < 0) {
                fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", expression);
                exit(1);
            }
            emit("MOVER R%d, R%d  ; %s = %s", dest_reg, src_reg, var_name, expression);
        }
    }
}

static void compile_if(Compiler *c, const char *line) {
    // if (x == y) { o if (x != y) {
    char var1[64], op[4], var2[64];
    if (sscanf(line, "if ( %s %s %[^)]", var1, op, var2) == 3) {
        char *v1 = trim(var1);
        char *v2 = trim(var2);
        char *operator = trim(op);
        
        int r1 = find_variable(c, v1);
        int r2 = find_variable(c, v2);
        
        if (r1 < 0 || r2 < 0) {
            fprintf(stderr, "[ERROR COMPILADOR] Variable no declarada en if\n");
            exit(1);
        }
        
        int label = get_next_label(c);
        
        emit("; if (%s %s %s)", v1, operator, v2);
        emit("MOVER R15, R%d  ; Copiar %s", r1, v1);
        emit("RESTAR R15, R%d  ; R15 = %s - %s", r2, v1, v2);
        
        if (strcmp(operator, "==") == 0) {
            // Saltar si NO es cero (es decir, no son iguales)
            emit("SNZ R15, endif_%d  ; Saltar si %s != %s", label, v1, v2);
        } else if (strcmp(operator, "!=") == 0) {
            // Saltar si ES cero (es decir, son iguales)
            emit("SZ R15, endif_%d  ; Saltar si %s == %s", label, v1, v2);
        }
        
        c->indent_level++;
    }
}

static void compile_while(Compiler *c, const char *line) {
    // while (x != 0) {
    char var1[64], op[4], var2[64];
    if (sscanf(line, "while ( %s %s %[^)]", var1, op, var2) == 3) {
        char *v1 = trim(var1);
        char *v2 = trim(var2);
        char *operator = trim(op);
        
        int r1 = find_variable(c, v1);
        int r2;
        
        if (r1 < 0) {
            fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", v1);
            exit(1);
        }
        
        if (is_number(v2)) {
            r2 = -1;  // Literal
        } else {
            r2 = find_variable(c, v2);
            if (r2 < 0) {
                fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", v2);
                exit(1);
            }
        }
        
        int label = get_next_label(c);
        
        emit("while_%d:  ; while (%s %s %s)", label, v1, operator, v2);
        
        if (r2 >= 0) {
            emit("MOVER R15, R%d  ; Copiar %s", r1, v1);
            emit("RESTAR R15, R%d  ; R15 = %s - %s", r2, v1, v2);
        } else {
            // Comparar con literal
            emit("MOVI R15, %s", v2);
            emit("RESTAR R15, R%d  ; R15 = %s - %s", r1, v2, v1);
            emit("NO R15  ; Invertir para obtener %s - %s", v1, v2);
            emit("MOVI R14, 1");
            emit("SUMAR R15, R14");
        }
        
        if (strcmp(operator, "!=") == 0) {
            emit("SZ R15, endwhile_%d  ; Saltar si %s == %s", label, v1, v2);
        } else if (strcmp(operator, "==") == 0) {
            emit("SNZ R15, endwhile_%d  ; Saltar si %s != %s", label, v1, v2);
        }
        
        c->indent_level++;
    }
}

static void compile_closing_brace(Compiler *c) {
    if (c->indent_level > 0) {
        int label = c->label_counter - 1;
        
        // Si estamos en una función, cerrarla
        if (c->current_function && c->indent_level == 1) {
            c->indent_level--;
            emit("; Fin de función");
            if (!c->function_has_explicit_return) {
                emit("RETORNAR  ; Return implícito");
            }
            c->current_function = NULL;
            c->function_has_explicit_return = false;
        } else {
            // Es un while/for/if
            c->indent_level--;
            emit("SALTAR while_%d", label);
            emit("endwhile_%d:", label);
        }
    }
}

static void compile_function_definition(Compiler *c, const char *line) {
    // int suma(int a, int b) {
    char ret_type[64], func_name[64], params[256];
    
    // Extraer nombre de función y parámetros
    char *paren_open = strchr(line, '(');
    char *paren_close = strchr(line, ')');
    
    if (!paren_open || !paren_close) {
        fprintf(stderr, "[ERROR COMPILADOR] Sintaxis de función inválida\n");
        return;
    }
    
    // Obtener nombre de función
    *paren_open = '\0';
    sscanf(line, "%s %s", ret_type, func_name);
    *paren_open = '(';
    
    // Obtener parámetros
    *paren_close = '\0';
    strncpy(params, paren_open + 1, 255);
    params[255] = '\0';
    *paren_close = ')';
    
    // Contar parámetros
    int num_params = 0;
    if (strlen(trim(params)) > 0) {
        num_params = 1;
        for (char *p = params; *p; p++) {
            if (*p == ',') num_params++;
        }
    }
    
    // Registrar función
    add_function(c, func_name, num_params);
    c->current_function = &c->functions[c->function_count - 1];
    
    // Reiniciar tabla de variables para función
    c->var_count = 0;
    c->next_local_reg = 0;
    c->function_has_explicit_return = false;
    
    emit("\n; Función: %s(%s)", func_name, params);
    emit("func_%s:", func_name);
    
    // Parsear y registrar parámetros
    if (num_params > 0) {
        char param_list[256];
        strncpy(param_list, params, 255);
        param_list[255] = '\0';
        
        char *token = strtok(param_list, ",");
        int param_idx = 0;
        
        while (token && param_idx < 4) {
            char type[64], name[64];
            if (sscanf(trim(token), "%s %s", type, name) == 2) {
                allocate_register(c, name, true);
            }
            token = strtok(NULL, ",");
            param_idx++;
        }
    }
    
    c->indent_level++;
}

static void compile_return(Compiler *c, const char *line) {
    // return x; o return 5;
    char value[128];
    if (sscanf(line, "return %[^;]", value) == 1) {
        char *val = trim(value);
        
        emit("; return %s", val);
        
        if (is_number(val)) {
            emit("MOVI R0, %s  ; Valor de retorno", val);
        } else {
            int src_reg = find_variable(c, val);
            if (src_reg < 0) {
                fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", val);
                exit(1);
            }
            if (src_reg != 0) {
                emit("MOVER R0, R%d  ; Valor de retorno", src_reg);
            }
        }
        
        emit("RETORNAR");
        c->function_has_explicit_return = true;
    } else {
        // return sin valor
        emit("; return");
        emit("RETORNAR");
        c->function_has_explicit_return = true;
    }
}

static void compile_function_call(Compiler *c, const char *lhs, const char *call_expr) {
    // x = suma(a, b);
    char func_name[64], args[256];
    
    if (sscanf(call_expr, "%[^(](%[^)])", func_name, args) == 2) {
        char *fname = trim(func_name);
        char *arg_list = trim(args);
        
        FunctionInfo *func = find_function(c, fname);
        if (!func) {
            fprintf(stderr, "[ERROR COMPILADOR] Función '%s' no declarada\n", fname);
            exit(1);
        }
        
        emit("; Llamar %s(%s)", fname, arg_list);
        
        // Pasar argumentos a R0-R3
        if (strlen(arg_list) > 0) {
            char arg_copy[256];
            strncpy(arg_copy, arg_list, 255);
            arg_copy[255] = '\0';
            
            char *token = strtok(arg_copy, ",");
            int arg_idx = 0;
            
            while (token && arg_idx < 4) {
                char *arg = trim(token);
                
                if (is_number(arg)) {
                    emit("MOVI R%d, %s", arg_idx, arg);
                } else {
                    int src_reg = find_variable(c, arg);
                    if (src_reg < 0) {
                        fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", arg);
                        exit(1);
                    }
                    if (src_reg != arg_idx) {
                        emit("MOVER R%d, R%d", arg_idx, src_reg);
                    }
                }
                
                token = strtok(NULL, ",");
                arg_idx++;
            }
        }
        
        emit("LLAMAR func_%s", fname);
        
        // Guardar resultado
        if (lhs) {
            int dest_reg = find_variable(c, lhs);
            if (dest_reg < 0) {
                dest_reg = allocate_register(c, lhs, false);
            }
            if (dest_reg != 0) {
                emit("MOVER R%d, R0  ; Guardar resultado", dest_reg);
            }
        }
    }
}

static void compile_for(Compiler *c, const char *line) {
    // for (int i = 0; i < 10; i++) {
    char init[128], cond[128], incr[128];
    
    // Extraer las tres partes del for
    char *paren_open = strchr(line, '(');
    char *paren_close = strchr(line, ')');
    
    if (!paren_open || !paren_close) {
        fprintf(stderr, "[ERROR COMPILADOR] Sintaxis de for inválida\n");
        return;
    }
    
    char for_content[256];
    strncpy(for_content, paren_open + 1, paren_close - paren_open - 1);
    for_content[paren_close - paren_open - 1] = '\0';
    
    // Parsear init; cond; incr
    char *semi1 = strchr(for_content, ';');
    if (!semi1) return;
    
    *semi1 = '\0';
    strncpy(init, for_content, 127);
    init[127] = '\0';
    
    char *semi2 = strchr(semi1 + 1, ';');
    if (!semi2) return;
    
    *semi2 = '\0';
    strncpy(cond, semi1 + 1, 127);
    cond[127] = '\0';
    
    strncpy(incr, semi2 + 1, 127);
    incr[127] = '\0';
    
    int label = get_next_label(c);
    
    emit("; for (%s; %s; %s)", trim(init), trim(cond), trim(incr));
    
    // Inicialización
    if (strstr(init, "int ") == init) {
        compile_declaration(c, init);
    } else if (strchr(init, '=')) {
        compile_assignment(c, init);
    }
    
    emit("for_%d:", label);
    
    // Condición (convertir a while-like)
    char var1[64], op[4], var2[64];
    if (sscanf(trim(cond), "%s %s %s", var1, op, var2) == 3) {
        int r1 = find_variable(c, var1);
        
        if (r1 < 0) {
            fprintf(stderr, "[ERROR COMPILADOR] Variable '%s' no declarada\n", var1);
            return;
        }
        
        emit("MOVER R15, R%d", r1);
        
        if (is_number(var2)) {
            emit("MOVI R14, %s", var2);
            emit("RESTAR R15, R14");
        } else {
            int r2 = find_variable(c, var2);
            if (r2 >= 0) {
                emit("RESTAR R15, R%d", r2);
            }
        }
        
        if (strcmp(op, "<") == 0 || strcmp(op, "!=") == 0) {
            emit("SZ R15, endfor_%d", label);
        } else if (strcmp(op, ">=") == 0 || strcmp(op, "==") == 0) {
            emit("SNZ R15, endfor_%d", label);
        }
    }
    
    // Guardar incremento para el final del bloque
    // (se ejecutará antes del salto de vuelta)
    
    c->indent_level++;
}

// ============================================================================
// COMPILACIÓN PRINCIPAL
// ============================================================================

void compile_c_to_asm(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        fprintf(stderr, "[ERROR] No se puede abrir archivo: %s\n", input_file);
        exit(1);
    }
    
    FILE *out = NULL;
    if (output_file) {
        out = fopen(output_file, "w");
        if (!out) {
            fprintf(stderr, "[ERROR] No se puede crear archivo: %s\n", output_file);
            fclose(in);
            exit(1);
        }
        // Redirigir stdout al archivo
        dup2(fileno(out), fileno(stdout));
    }
    
    Compiler compiler = {0};
    
    emit("; Compilado desde: %s", input_file);
    emit("; ISA de 16 bits - Español/México");
    emit("");
    
    // Saltar a main() al inicio del programa
    emit("; Punto de entrada: saltar a main()");
    emit("SALTAR func_main");
    emit("");
    
    char line[MAX_LINE];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), in)) {
        line_num++;
        char *trimmed = trim(line);
        
        // Ignorar líneas vacías y comentarios
        if (*trimmed == '\0' || strncmp(trimmed, "//", 2) == 0) {
            continue;
        }
        
        // Detectar definiciones de funciones (int nombre(...) {)
        if (strncmp(trimmed, "int ", 4) == 0 && strchr(trimmed, '(') && strchr(trimmed, ')')) {
            compile_function_definition(&compiler, trimmed);
            
        // Declaraciones de variables
        } else if (strncmp(trimmed, "int ", 4) == 0) {
            compile_declaration(&compiler, trimmed);
            
        // Return statement
        } else if (strncmp(trimmed, "return", 6) == 0) {
            compile_return(&compiler, trimmed);
            
        // Llamadas a funciones: x = func(...);
        } else if (strchr(trimmed, '=') && strchr(trimmed, '(') && strchr(trimmed, ')')) {
            char lhs[128], rhs[256];
            if (sscanf(trimmed, "%[^=] = %[^;]", lhs, rhs) == 2) {
                compile_function_call(&compiler, trim(lhs), trim(rhs));
            }
            
        // Asignaciones normales
        } else if (strchr(trimmed, '=') && strchr(trimmed, ';')) {
            compile_assignment(&compiler, trimmed);
            
        // Condicional if
        } else if (strncmp(trimmed, "if ", 3) == 0) {
            compile_if(&compiler, trimmed);
            
        // Bucle while
        } else if (strncmp(trimmed, "while ", 6) == 0) {
            compile_while(&compiler, trimmed);
            
        // Bucle for
        } else if (strncmp(trimmed, "for ", 4) == 0) {
            compile_for(&compiler, trimmed);
            
        // Cierre de bloque
        } else if (strcmp(trimmed, "}") == 0) {
            compile_closing_brace(&compiler);
        }
    }
    
    emit("");
    emit("ALTO  ; Fin del programa");
    
    fclose(in);
    if (out) fclose(out);
    
    printf("; Compilación completa: %d variables, %d etiquetas\n", 
           compiler.var_count, compiler.label_counter);
}

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo.c> [salida.asm]\n", argv[0]);
        printf("\nEjemplo:\n");
        printf("  %s test.c programa.asm\n", argv[0]);
        return 1;
    }
    
    const char *input = argv[1];
    const char *output = (argc >= 3) ? argv[2] : NULL;
    
    printf("; ======================================\n");
    printf("; Compilador C -> ASM\n");
    printf("; Entrada: %s\n", input);
    if (output) {
        printf("; Salida: %s\n", output);
    }
    printf("; ======================================\n\n");
    
    compile_c_to_asm(input, output);
    
    return 0;
}
