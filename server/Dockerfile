FROM node:latest

RUN mkdir /src
WORKDIR /src
COPY package.json package.json
RUN npm install

COPY . .

CMD node index.js
