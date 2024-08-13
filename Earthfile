VERSION 0.8
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND noninteractive
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

RUN apt update && apt install --no-install-recommends -y build-essential ca-certificates cmake clang gcc git libgtest-dev

WORKDIR /workspace

build:
  GIT CLONE https://github.com/ccmagruder/json.git json
  WORKDIR json
  RUN cmake . -B build -DCMAKE_BUILD_TYPE=Release
  RUN cmake --build build
  SAVE ARTIFACT build/libjson.so
  SAVE ARTIFACT include/JSON.h 
  SAVE ARTIFACT include/Variant.h

