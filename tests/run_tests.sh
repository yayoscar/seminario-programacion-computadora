#!/bin/bash
# Script de prueba para verificar el proyecto completo

echo "======================================"
echo "  CPU Simulator - Test Runner"
echo "======================================"
echo ""

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Compilar el proyecto
echo -e "${YELLOW}[1/5] Compilando el proyecto...${NC}"
make clean > /dev/null 2>&1
if make; then
    echo -e "${GREEN}✓ Compilación exitosa${NC}"
else
    echo -e "${RED}✗ Error en la compilación${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}[2/5] Probando ensamblador standalone...${NC}"
if ./bin/assembler tests/test_simple.asm tests/test_simple.mem; then
    echo -e "${GREEN}✓ Ensamblador funciona correctamente${NC}"
else
    echo -e "${RED}✗ Error en el ensamblador${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}[3/5] Ejecutando prueba simple...${NC}"
./bin/cpu_sim -e tests/test_simple.asm

echo ""
echo -e "${YELLOW}[4/5] Ejecutando prueba de memoria...${NC}"
./bin/cpu_sim -e tests/test_memory.asm

echo ""
echo -e "${YELLOW}[5/5] Ejecutando programa principal (suma 1..10)...${NC}"
./bin/cpu_sim -e asm/programa.asm

echo ""
echo "======================================"
echo -e "${GREEN}  ✓ Todas las pruebas completadas${NC}"
echo "======================================"
