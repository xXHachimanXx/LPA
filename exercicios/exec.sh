#!/bin/bash

echo "Entrar com o numero do TP: "; 
read N;
echo -e "$N";

cd ~/Faculdade/LPA/exercicios/Tp"$N";

g++ Tp"$N".cpp -o Tp"$N" && ./Tp"$N" < in.txt;  
