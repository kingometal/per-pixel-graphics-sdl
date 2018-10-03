FROM ubuntu:bionic

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y make
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libsdl2-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends g++
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends libsdl2-ttf-dev 
RUN rm -rf /var/lib/apt/lists/*  # clean up apt-get cache
COPY *.cpp /
COPY FreeMono.ttf /
COPY *.h /
COPY Makefile /
CMD make run

