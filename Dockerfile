FROM alpine:latest

RUN apk update && apk add g++ clang
WORKDIR /var/workspace

CMD [ "sh" ]