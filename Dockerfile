FROM ubuntu:bionic

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --fix-missing libsdl2-dev
COPY *.cpp /
COPY *.h /
COPY Makefile /
CMD make run

