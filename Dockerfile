FROM ubuntu:xenial

RUN apt-get update && apt-get install -y clang
WORKDIR /var/workspace

CMD [ "bash" ]