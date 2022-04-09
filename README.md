# UMayor-Inteligencia-Artificial-2011
Programas que realice para el ramo de Inteligencia Artificial de la Universidad Mayor

#Laboratorio 1: Estacionamiento: estacionamiento.pl

el formato de las consultas es el siguiente
ejemplo:

oracion([estaciona,auto,x1,en,garage],[]).
true

oracion([lleva,vehiculo,x2,en,piso],[]).
true

oracion([estaciona,auto,x2,en,garage],[]).
false

oracion([estaciona,vehiculo,x3,en,piso],[]).
false

oracion([estaciona,auto,x4,en,piso1,y,x5,en,piso2],[]).
true

oracion([saca,auto,x2],[]).
true

oracion([trae,vehiculo,x1],[]).
true

oracion([trae,vehiculo,x2],[]).
false

#Laboratorio 2: Algoritmo Evolutivo : evolutivo.cpp
solo ejecutarlo creara sujetos de una poblacion a los cuales se les pondra una metrica expresada por compararsujetos

#Laboratorio 3: Hermecio el Killer : hermecio.c,traindata.txt,vale.data,vale_float.net
Un Chess Player entrenado con redes neuronales utilizando
   Fast Artificial Neural Network Library (fann)
Copyright (C) 2003 Steffen Nissen (lukesky@diku.dk)
