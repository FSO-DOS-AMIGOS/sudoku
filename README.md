# Sudoku
## O Problema

Um Sudoku utiliza um grid 9 x 9 no qual cada linha e cada coluna, bem
como cada um dos nove subgrids 3 x 3, deve conter todos os dígitos 1 ...
9. A figura abaixo apresenta um exemplo de um Sudoku válido. Este
projeto consiste em desenvolver um programa multithread que determina
se a solução de um Sudoku é válida.

![](https://i.imgur.com/8eje0zo.png)

Há diferentes formas de fazê-lo. Uma estratégia sugerida consiste em
criar threads que checam os seguintes critérios:

- Uma thread que checa se cada coluna contém os dígitos de 1 até 9
- Uma thread que checa se cada linha contém os dígitos de 1 até 9
- Nove threads que checam se cada subgrid de 3 x 3 contém os
dígitos de 1 até 9

Essa abordagem resultaria em onze threads distintas para validar o
Sudoku. Entretanto, você é livre para criar ainda mais threads for esse
projeto. Por exemplo, em vez de criar uma thread que checa todas as
nove colunas, poderiam ser criadas nove threads distintas e cada uma
checar uma coluna.

O grid deve ser lido a partir de um arquivo texto de entrada, contendo os
elementos do Sudoku. O resultado deve ser impresso na tela.

_Retornando resultados para a thread pai_

Cada thread realizará a validação de determinada região do grid. Quando
uma thread finaliza sua análise, é necessário retornar seu resultado para
a thread pai. Uma boa maneira de lidar com isso é criar um array de
inteiros visível por todas as threads. O i-ésimo índice no array
corresponde à i-ésima thread. Se uma thread escreve em sua respectiva
posição o valor 1, há indicação de que a região do Sudoku sobre sua
responsabilidade é válida. O valor 0 indica que não é válida. Quando todas
as threads terminarem suas tarefas, a thread pai realizará a checagem
de cada entrada do array para determinar se o grid apresentado é válido.

Caso não tenha o gcc instalado localmente, utilize a seção [Usando o docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker) ou [Usando o makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile)

## Como usar

1. Instale o [Docker CE](https://docs.docker.com/install/) ***

2. Clone esse repositório - `git clone https://github.com/FSO-DOS-AMIGOS/sudoku.git`

3. Navegue até a pasta recém-clonada.

4. Siga alguma das seções de execução: [Docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker), [Makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile) ou [Gcc](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-gcc)

*** _Passo Opcional_

NOTA: Se você não seguiu os [passos pós-instalação](https://docs.docker.com/install/linux/linux-postinstall/) para o docker você precisará usar `sudo` junto as intruções das seções [Usando o docker](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-docker) ou [Usando o makefile](https://github.com/FSO-DOS-AMIGOS/sudoku#usando-o-makefile), por exemplo:

`sudo docker build -t sudoku .`
ou
`sudo make build`

### Usando o gcc
1. Compile o arquivo c 
``` bash
gcc src/main.c -o sudoku -lpthread
```

2. Execute o binário gerado
``` bash
./sudoku assets/sudoku-desejado.txt
```

### Usando o makefile
1. Construa o ambiente:
``` bash
make build 
```

2. Rode o ambiente pré-construído
``` bash
make run
```

#### Outros comandos úteis

Remove o ambiente encapsulado
``` bash
make rm
```

Remove a rede local encapsulada
``` bash
make rm-network
```

Remove a imagem criada pelo `make build`
``` bash
make rm-img
```

Mostra uma listagem de todos os comandos e uma breve descrição deles
``` bash
make help
```

### Usando o docker

1. _Builde_ o ambiente do _Dockerfile_
``` bash
docker build -t sudoku .
```

2. Execute o app
``` bash
docker run -w /sudoku/src sudoku:latest bash -c "./sudoku"
```