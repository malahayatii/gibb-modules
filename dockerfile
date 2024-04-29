FROM debian:bookworm-20240110
ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt upgrade -y && \
    apt install --no-install-recommends --no-install-suggests -y \
    npm && \
    mkdir arduino-status && cd arduino-status && \
    npm init -y && \
    npm install express

COPY index.js arduino-status/
COPY entrypoint.sh /usr/local/bin

ENTRYPOINT ["entrypoint.sh"]