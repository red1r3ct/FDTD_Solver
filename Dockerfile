FROM nvidia/cuda

RUN apt-get update
RUN apt-get install clang cmake

RUN mkdir code
WORKDIR code
COPY . .

RUN cmake .
RUN make -j4

curl -sL https://deb.nodesource.com/setup_8.x | sudo -E bash -
sudo apt-get install -y nodejs

CMD node server/server/index.js
