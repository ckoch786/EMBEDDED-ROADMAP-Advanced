#!/bin/bash

docker build -t weather_station .

docker run --rm -it \
    -v "$(pwd)":/app \
    weather_station \
    bash -c "mkdir -p build && cd build && cmake -DTARGET_HOST=ON .. && make -j && ./weather_station"
