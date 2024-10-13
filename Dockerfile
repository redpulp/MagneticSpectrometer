FROM rootproject/root:latest

WORKDIR /src

COPY ./src .

RUN make

RUN ./specter
