# 🚀 HTTP/1.1 Server in Modern C++ (RFC 2616)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![C++17](https://img.shields.io/badge/language-C++17-blue.svg)]()
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey.svg)]()

An educational yet functional HTTP/1.1 server implemented from scratch using modern C++. Inspired by the official [RFC 2616](https://datatracker.ietf.org/doc/html/rfc2616), this project helps you understand how web servers work under the hood.

---

## 🧠 Why This Project?

This project is ideal for:

- 🧑‍💻 Developers wanting to understand raw HTTP communication  
- 🎓 Students learning about networking and socket programming  
- 🤓 Enthusiasts exploring low-level protocols  

Learn how to:

- Parse and respond to raw HTTP/1.1 requests  
- Build a standards-compliant server  
- Use TCP sockets in C++  

---

## ✨ Features

- ✅ TCP socket server  
- ✅ HTTP/1.1 request parsing (method, path, headers)  
- ✅ Response generation (status line, headers, body)  
- ✅ Persistent/non-persistent connection support  
- 🔜 Header parsing (`Content-Length`, `Host`)  
- 🔜 Keep-Alive and chunked transfer encoding  
- 🔜 Static file serving  
- 🔜 Full RFC 2616 compliance  
- 🔜 Modular unit testing  

---

## 📁 Project Structure

HTTP-1.1/
├── include/ # Header files
│ ├── server.hpp # Core server logic
│ └── parser.hpp # HTTP parser
├── src/ # Source files
│ ├── main.cpp # Entry point
│ ├── server.cpp # Server implementation
│ └── parser.cpp # Parsing implementation
├── CMakeLists.txt # Build configuration
├── .gitignore
├── LICENSE
└── README.md


---

## ⚙️ Requirements

- C++17 or later  
- CMake ≥ 3.14  
- POSIX-compliant OS (Linux, macOS, or WSL)  

---

## 🚀 Getting Started

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/http-server-rfc2616.git
cd http-server-rfc2616

# Create a build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Compile the server
make

# Run the server
./HttpServer <Address> <PORT>