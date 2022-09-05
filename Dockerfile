FROM python:3.8

RUN apt-get update -y && \
    apt-get install -y wget

WORKDIR /
RUN apt-get install cmake -y
RUN cmake --version

# Copy source code into container
WORKDIR /
RUN mkdir server
WORKDIR /server
ADD include /server/include
ADD src /server/src
ADD web_data /server/web_data
ADD build_bash.sh /server
ADD CMakeLists.txt /server
ADD run_bash.sh /server

# Build source code
RUN chmod 777 build_bash.sh
RUN chmod 777 run_bash.sh
RUN ./build_bash.sh

# tell the port number the container should expose
EXPOSE 8080

# run the command
CMD ["./run_bash.sh"]
