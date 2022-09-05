# http-server-cpp
A simple c++ server that support Http 1.1 protocol, using epoll + mutilple threads

# Build command (Linux)
```
cd <project-folder>
mkdir build
cd build/
cmake .. -DENABLE_UNITY_BUILD=OFF -DBUILD_ONLY="core;sts;identitystore;s3;ec2"
cmake --build . -j 2
make -j
```

# Run command  (Linux)
```
chmod 777
http_server.out
cp http_server.out ../
cd ..
./http_server.out
```

