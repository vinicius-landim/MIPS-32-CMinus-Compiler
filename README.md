# Instruções de Uso:

1) Gerar o scanner a partir de `src/scanner.l`:

```bash
flex src/scanner.l
```

2) Gerar o parser a partir de `src/parser.y`:

```bash
bison -d src/parser.y
```

3) Compilar os fontes C e os arquivos gerados em um executável `compilador.exe`:

```bash
gcc *.c -o compilador.exe
```

4) Rodar o compilador sobre um arquivo de entrada (ex.: `tests/sort.txt`):

```bash
./compilador.exe tests/sort.txt
```

5) Gerar PNG da árvore Graphviz (`output_files/arvore.dot` → `output_files/arvore.png`):

```bash
dot -Tpng output_files/arvore.dot -o output_files/arvore.png
```

