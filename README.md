# 🚀 HTTP/1.1 Server in Modern C++ (RFC 2616)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![C++](https://img.shields.io/badge/language-C++17-blue.svg)]()
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey.svg)]()

An educational yet functional HTTP/1.1 server implemented from scratch in modern C++, inspired by the official [RFC 2616](https://datatracker.ietf.org/doc/html/rfc2616) specification.

# 🧠 HTTP/1.1 Server in C++ (RFC 2616)

This project is designed to provide a clear, hands-on example of how HTTP/1.1 works under the hood. It's perfect for developers, students, and network protocol enthusiasts who want to learn:

- How HTTP requests and responses are structured and parsed
- How to build a standards-compliant server from the ground up
- How socket programming works in C++

## ✨ Features
=======
## 📚 Project Overview

- ✅ TCP socket server
- ✅ Basic HTTP/1.1 request parsing (method, path, headers)
- ✅ Response generation (status line, headers, body)
- ✅ Persistent and non-persistent connection handling
- 🔜 Header fields like `Content-Length`, `Host`
- 🔜 Keep-Alive and chunked transfer encoding
- 🔜 Static file serving
- 🔜 Full RFC 2616 compliance
- 🔜 Modular unit testing

## 📁 Project Structure

```
=======
http-server-rfc2616/
├── include/http/           # Header files
│   ├── server.hpp          # Core server logic
│   ├── request.hpp         # HTTP request parser
│   ├── response.hpp        # HTTP response builder
│   └── parser.hpp          # Low-level tokenization
├── src/                    # Source files
│   ├── main.cpp            # Entry point
│   ├── server.cpp
│   ├── request.cpp
│   ├── response.cpp
│   └── parser.cpp
├── CMakeLists.txt          # Build system
├── .gitignore
├── LICENSE
└── README.md
```

## ⚙️ Requirements
=======

## 🚀 Getting Started

### 🔧 Requirements

- C++17 or newer
- CMake ≥ 3.14
- POSIX-compliant OS (Linux, macOS, or WSL on Windows)

---

## 🛠️ Build & Run

```bash
# Clone the repo
=======
# Clone the repository
>>>>>>> f95c734453d7db3f21a339551a0efb9505f5eb04
git clone https://github.com/YOUR_USERNAME/http-server-rfc2616.git
cd http-server-rfc2616

# Create a build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Compile the server
make

# Run the server
./http_server
```

---

## 🧪 Run Tests

# From the build/ directory
ctest --verbose

## 🔍 Try It Out

After starting the server, test it using:

curl http://localhost:8080/

Or simply open a browser and navigate to:


http://localhost:8080/



## 🗺️ Roadmap

| Feature                        | Status   |
|-------------------------------|----------|
| Core HTTP/1.1 request/response| ✅ Done   |
| Basic TCP socket layer        | ✅ Done   |
| Persistent connections        | 🚧 Planned |
| Header parsing improvements   | 🚧 Planned |
| Chunked transfer encoding     | 🚧 Planned |
| Static file server            | 🚧 Planned |
| Complete RFC 2616 compliance  | 🚧 Planned |
| Unit testing for all modules  | 🚧 Planned |


## 📚 Resources

- [RFC 2616 - HTTP/1.1 Spec](https://datatracker.ietf.org/doc/html/rfc2616)
- [Beej’s Guide to Network Programming](https://beej.us/guide/bgnet/)
- [C++ Reference](https://en.cppreference.com/)

## 📄 License

Licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
