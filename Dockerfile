FROM gcc:8

COPY . /sudoku

WORKDIR /sudoku/src/

RUN gcc main.c -o sudoku -lpthread && \
    chmod +x sudoku
