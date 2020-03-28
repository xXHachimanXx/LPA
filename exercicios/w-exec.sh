#!/bin/bash
echo "Entrar com o numero do TP: "; 
read N;
echo -e "$N";

cd ./Tp"$N";

g++ Tp"$N".cpp -o Tp"$N".exe && ./Tp"$N".exe < in.txt > out.txt;  
