FROM gcc:8

COPY . /sudoku

WORKDIR /sudoku/src/

RUN gcc -o sudoku main.c && \
    chmod +x sudoku
