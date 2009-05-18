TAM1 = "2000"
TAM1 = "200000"


#---G1-------TAMANHO 10 000 REGISTROS------------------
./lab04 listafinal.txt arq111.out $TAM1
1

./lab04 listafinal.txt arq121.out $TAM2
1

./lab04 listafinal.txt arq112.out $TAM1
2

./lab04 listafinal.txt arq122.out $TAM2
2


#--G2-------TAMANHO 100-----------------------

./lab04 registros\(100\).txt arq411.out $TAM1
1

./lab04 registros\(100\).txt  arq421.out $TAM2
1

./lab04 registros\(100\).txt  arq412.out $TAM1
2

./lab04 registros\(100\).txt  arq422.out $TAM2
2

#----G2------TAMANHO 1 000---------------------
./lab04 registros\(1.000\).txt  arq511.out $TAM1
1

./lab04 registros\(1.000\).txt   arq521.out $TAM2
1

./lab04 registros\(1.000\).txt   arq512.out $TAM1
2

./lab04 registros\(1.000\).txt   arq522.out $TAM2
2

#---G2--------TAMANHO 10 000-----------------------
./lab04 registros\(10.000\).txt   arq611.out $TAM1
1

./lab04 registros\(1.000\).txt   arq621.out $TAM2
1

./lab04 registros\(1.000\).txt   arq612.out $TAM1
2

./lab04 registros\(1.000\).txt   arq622.out $TAM2
2


