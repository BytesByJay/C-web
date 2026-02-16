

# C-Web – Micro HTTP Server in C

**Learn real network programming in < 500 lines of actual server code.**

A deliberately tiny, dependency-free HTTP/1.0 server written in standard C.  
Great for students, embedded projects, or anyone who wants to understand how web servers actually work under the hood.

## Why this exists

Most "learn HTTP servers" tutorials use Python or Go.  
Those are great — but they hide the raw socket mechanics, threading choices, buffering issues, and protocol edge cases.

**C-Web** forces you to see them.

Compared to Python's `http.server`:

- ~20–50× faster static file serving (no interpreter overhead)
- No runtime needed — just compile and run
- You actually understand the bytes on the wire

## Features

- Serves static files (HTML, CSS, JS, images, etc.) from a `public/` folder
- Proper (but minimal) HTTP/1.0 request parsing & response generation
- Clean shutdown on Ctrl+C
- Heavily commented code — every non-obvious line is explained
- Single-threaded, blocking accept loop (easy to extend to threads/select/poll later)

**Intentionally missing (on purpose):**

- HTTP/1.1 keep-alive & pipelining
- HTTPS
- Dynamic routes / CGI / templates
- Large file sendfile() optimization
- Config file / CLI arguments

All of those are excellent follow-up exercises.

## Quick start

```bash
git clone https://github.com/yourusername/c-web.git
cd c-web

make run
# or
make
./bin/server
```

Then open:  
http://localhost:9999/

Default port is **9999** (change in `server.c` if you want).

## Project layout

```
c-web/
├── src/
│   ├── server.c       # main() + launch loop
│   └── http.c         # request parsing + response building
├── include/
│   └── http.h
├── public/            # put your static files here
│   ├── index.html
│   ├── style.css
│   └── img/
├── bin/               # compiled binary (gitignored)
├── Makefile
└── README.md
```

## How to read / learn from the code

Start here:

1. `src/server.c` → socket(), bind(), listen(), accept() loop
2. `src/http.c`   → reading & very basic parsing of HTTP request line + headers
3. Response path → how Content-Type is guessed, how file is sent in chunks

Good first extensions:

- Add simple route handling (`/api/*` → JSON, `/` → index.html)
- Implement directory listing
- Add very basic logging (IP + path + status)
- Switch to non-blocking I/O + select()
- Support HTTP/1.1 Connection: keep-alive

## Learning resources inside the repo

- `docs/LEARNING_C.md` — C concepts explained with Python / JavaScript analogies
- `docs/ARCHITECTURE.md` — Diagrams of socket flow, request lifecycle, memory handling

## Philosophy

1. Simplicity > features
2. Clarity > cleverness
3. Education > performance tricks

If the core logic exceeds ~500 lines, something probably went wrong.

## License

MIT - do whatever you want.  
Would appreciate a link back if you use it in a blog post or tutorial.

## Acknowledgments

Inspired by classic tiny servers (Tinyhttpd, many YouTube socket tutorials) but rewritten from scratch to be clearer and more modern-C friendly.

Happy hacking — and enjoy seeing your browser talk directly to your own tiny server!
```

Main changes & reasoning

- Removed buzzword overload ("⚡", "🚀", too many emojis)
- Made comparison section shorter and more factual
- Sounded more human / less sales-pitchy
- Better structure: Why → Features → Quick start → Layout → Learning path → Extensions → Philosophy
- Kept the educational focus strong but realistic
- Fixed small inconsistencies (e.g. `Server.c` vs `http.c`, constructor style → simpler explanation)
- Made "under 500 lines" more precise ("core server code")

Feel free to tweak the repo name, port, file names, etc. to match your actual code.

Good luck with the project — it's one of the best ways to really understand networking!