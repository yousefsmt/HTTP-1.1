# 🧠 HTTP/1.1 Server in C++ (RFC 2616)

A simple yet educational implementation of an HTTP/1.1 server in modern C++, built from scratch by closely following the [RFC 2616](https://datatracker.ietf.org/doc/html/rfc2616) specification.

## 📚 Project Overview

This project aims to implement a basic HTTP/1.1 server using C++. It focuses on the fundamental components of HTTP:

- Request parsing (methods, headers, body)
- Response construction (status codes, headers)
- Support for static file serving
- Connection management (persistent and close)
- Standards-compliant behavior according to RFC 2616

The code is modular and easy to extend for learning or production purposes.

## 📁 Project Structure


http-server-rfc2616/
├── include/
│   └── http/
│       ├── server.hpp         # Core server class
│       ├── request.hpp        # HTTP request parser
│       ├── response.hpp       # HTTP response builder
│       └── parser.hpp         # Low-level parsing logic
├── src/
│   ├── main.cpp               # Entry point
│   ├── server.cpp
│   ├── request.cpp
│   ├── response.cpp
│   └── parser.cpp
├── test/
│   └── test\_http.cpp          # Unit tests
├── CMakeLists.txt             # Build system
├── .gitignore
├── LICENSE
└── README.md

## 🚀 Getting Started

### 🔧 Requirements

- C++17 or newer
- CMake 3.14+
- A POSIX-compliant system (Linux, macOS, or WSL on Windows)

### 🛠️ Build and Run

# Clone the repository
git clone https://github.com/YOUR_USERNAME/http-server-rfc2616.git
cd http-server-rfc2616

# Create a build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the server
./http_server

### 🧪 Running Tests

# From the build directory
ctest --verbose

## ⚙️ Example Request

Once running, you can test it with:

curl http://localhost:8080/

Or open your browser and navigate to `http://localhost:8080/`.


## 📌 Roadmap

* [x] TCP socket server
* [x] Basic request parsing (method, path, headers)
* [x] Basic HTTP/1.1 response
* [ ] Header parsing (Content-Length, Host, etc.)
* [ ] Connection Keep-Alive support
* [ ] Chunked Transfer-Encoding support
* [ ] Full compliance with RFC 2616
* [ ] Static file serving
* [ ] Unit tests for each module


## 🧠 References

* [RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1](https://datatracker.ietf.org/doc/html/rfc2616)
* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
* [C++ Reference (cppreference.com)](https://en.cppreference.com/)

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


## 🤝 Contributing

Contributions are welcome! Feel free to fork the repo and submit pull requests. For major changes, please open an issue first to discuss your ideas.


## 👨‍💻 Author

Developed by Yousef.smt. Inspired by educational purposes and real-world RFC-driven development.
