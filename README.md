# HTTP/1.1 Server in Modern C++

A lightweight and modular implementation of an **HTTP/1.1 server** written in **C++17**, built with modern coding standards and static analysis tools.

---

## ✨ Features

- 🔹 Full support for **HTTP/1.1 request parsing**  
- 🔹 Lightweight server core (`server.hpp`, `server.cpp`)  
- 🔹 Request/response **parser** (`parser.hpp`, `parser.cpp`)  
- 🔹 **CMake-based build system**  
- 🔹 Integrated **clang-format** and **clang-tidy** configs for style and linting  
- 🔹 Pre-commit hooks for consistent code quality  

---

## 📂 Project Structure

```
HTTP-1.1-main/
├── include/           # Public headers
│   ├── parser.hpp
│   └── server.hpp
├── src/               # Implementation files
│   ├── main.cpp       # Entry point
│   ├── parser.cpp
│   └── server.cpp
├── .clang-format      # Code style configuration
├── .clang-tidy        # Static analysis configuration
├── .pre-commit-config.yaml
├── CMakeLists.txt     # Build configuration
└── README.md
```

---

## ⚡ Getting Started

### 1. Clone the repository
```bash
git clone https://github.com/yourusername/HTTP-1.1.git
cd HTTP-1.1-main
```

### 2. Build the project
```bash
mkdir build && cd build
cmake ..
make
```

### 3. Run the server
```bash
./HttpServer <IP address> <Port Address>
```

By default, the server listens on **localhost:80** (configurable in `main.cpp`).

---

## 🔧 Configuration

- Update **`main.cpp`** to set the port or customize server behavior.
- Modify **`parser.cpp`** to extend or refine request parsing.

---

## 🧪 Development & Code Quality

- **Linting & formatting**:  
  Run `clang-tidy` and `clang-format` to enforce style and catch issues.
- **Pre-commit hooks**:  
  Ensure consistency before committing:
  ```bash
  pre-commit install
  ```

---

## 📜 Requirements

- **C++17 or newer**
- **CMake 3.10+**
- **clang-format / clang-tidy** (for development)

---

## 🚀 Roadmap

- [ ] Add HTTPS (TLS) support  
- [ ] Implement request routing  
- [ ] Support for persistent connections & pipelining  
- [ ] Add unit tests (GoogleTest / Catch2)  
- [ ] Benchmarking and performance tuning  

---

## 🤝 Contributing

Contributions are welcome!  
Please fork the repo, create a branch, and submit a pull request.

---

## ❤️ Support & Donations

If you find this project useful and want to support its development, you can donate using **USDT** on different blockchains:

- **USDT (ERC-20 / Ethereum):**
`0x47D04bDb5c3C75aF977cdfeEBEdc25443d4Fe59A`  
- **USDT (TRC-20 / TRON):** 
`TCy9XkJpqzwopt99FaHMztVYJji2LJY7Wr`  
- **USDT (BEP-20 / BNB Smart Chain):**
`0x47D04bDb5c3C75aF977cdfeEBEdc25443d4Fe59A`  

💡 *Every contribution helps keep this project alive and evolving 🚀*

---


## 📄 License

This project is licensed under the **MIT License**.  
See [LICENSE](LICENSE) for details.
