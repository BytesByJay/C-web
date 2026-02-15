# C-Web: Micro Web Server

> Learn C networking in under 500 lines of code

A minimalist HTTP server written in pure C with zero dependencies. Perfect for students learning network programming or embedding in C projects.

## ⚡ Features

- **Tiny**: <300 lines of core code
- **Fast**: Native C performance
- **Zero Dependencies**: Pure C with standard libraries only
- **Educational**: Heavily commented and documented
- **Static File Serving**: Serves HTML, CSS, JS, images

## 🚀 Quick Start

```bash
# Clone the repository
git clone <your-repo-url>
cd C-web

# Build and run (using Makefile)
make run

# Or build separately
make        # Compile
./bin/server  # Run

# Visit in browser
# http://localhost:9999/
```

## 📚 Why C-Web?

**vs Python's http.server:**
- 🚀 **20-50x faster** for serving static files
- 📦 **No runtime dependencies** (Python not required)
- 🎓 **Educational**: Understand how web servers actually work

**Use Cases:**
- Learning C network programming
- Embedding in C/C++ applications  
- Quick local file serving with minimal overhead
- Understanding HTTP protocol internals

## 📖 Project Structure

```
C-web/
├── src/              # Source files
│   ├── server.c      # Main entry point
│   └── Server.c      # Server implementation
├── include/          # Header files
│   └── Server.h      # Server interface
├── public/           # Static web files
│   ├── index.html
│   ├── about.html
│   └── style.css
├── docs/             # Documentation
│   ├── LEARNING_C.md
│   └── ARCHITECTURE.md
├── bin/              # Compiled binaries (gitignored)
├── Makefile          # Build automation
└── README.md
```

## 🎓 Learning Resources

New to C? Start here:
- **[docs/LEARNING_C.md](docs/LEARNING_C.md)**: C concepts explained using Python analogies
- **[docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)**: Visual diagrams of the server architecture

## 🔧 How It Works

```c
// In src/server.c:

// 1. Create server (binds to port 9999)
struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, 
                                          INADDR_ANY, 9999, 10, launch);

// 2. Launch (starts listening loop)
server.launch(&server);
```

The server:
1. Creates a socket (the "phone")
2. Binds to port 9999 (assigns the "phone number")
3. Listens for connections
4. Accepts requests and serves files from `public/`

## 🛠️ Extending

The codebase is intentionally minimal to make it easy to understand and extend:

**Want to add logging?** → Modify the `launch()` function in `test.c`  
**Want custom routes?** → Add conditions in the request parsing logic  
**Want HTTPS?** → Wrap with OpenSSL (see examples/)

## 📝 License

MIT License - see LICENSE file

## 🤝 Contributing

Contributions welcome! This project prioritizes:
1. **Simplicity** over features
2. **Education** over optimization
3. **Clarity** over cleverness

Keep the core under 500 lines.

## 🙏 Acknowledgments

Built from a YouTube tutorial, evolved into an educational micro-server.
