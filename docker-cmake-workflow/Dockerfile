FROM debian:stable-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc-arm-none-eabi gdb-multiarch binutils-arm-none-eabi \
    cmake make openocd git ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /work