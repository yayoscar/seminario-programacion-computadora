#!/bin/bash
# Script de prueba para verificar el proyecto completo

echo "=========================================="
echo "  Simulador CPU - Ejecutor de Pruebas"
echo "=========================================="
echo ""

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;36m'
NC='\033[0m' # Sin Color

# Compilar el proyecto
echo -e "${YELLOW}[1/4] Compilando el proyecto...${NC}"
make clean > /dev/null 2>&1
if make; then
    echo -e "${GREEN}✓ Compilación exitosa${NC}"
else
    echo -e "${RED}✗ Error en la compilación${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}[2/4] Probando programa simple (5 + 3 = 8)...${NC}"
echo -e "${BLUE}Comando: ./bin/main -e asm/programa.asm${NC}"
if ./bin/main -e asm/programa.asm | grep -q "R0 = 8"; then
    echo -e "${GREEN}✓ Resultado correcto: 5 + 3 = 8${NC}"
else
    echo -e "${RED}✗ Error: resultado incorrecto${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}[3/4] Probando ensamblado separado...${NC}"
echo -e "${BLUE}Paso 1: Ensamblar${NC}"
./bin/main -a asm/programa.asm asm/programa.mem
echo ""
echo -e "${BLUE}Paso 2: Ejecutar${NC}"
if ./bin/main -r asm/programa.mem | grep -q "R0 = 8"; then
    echo -e "${GREEN}✓ Pipeline de dos pasos funciona correctamente${NC}"
else
    echo -e "${RED}✗ Error en pipeline de dos pasos${NC}"
    exit 1
fi

echo ""
echo -e "${YELLOW}[4/4] Probando test_simple.asm (10 + 20 = 30)...${NC}"
echo -e "${BLUE}Comando: ./bin/main -e tests/test_simple.asm${NC}"
if ./bin/main -e tests/test_simple.asm | grep -q "R0 = 30"; then
    echo -e "${GREEN}✓ Resultado correcto: 10 + 20 = 30${NC}"
else
    echo -e "${RED}✗ Error: resultado incorrecto${NC}"
    exit 1
fi

echo ""
echo "=========================================="
echo -e "${GREEN}  ✓ Todas las pruebas completadas${NC}"
echo "=========================================="
