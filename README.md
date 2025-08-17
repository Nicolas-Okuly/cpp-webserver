# C++ Webserver
Based on a West-MEC project made in class. The project made in class used Node.Js's http module. This project uses crow to handle http.

## Functionalities
- GET / - Loads index.html
- GET /public/* - Pulls anything from public, this contains nested directories and images for testing.
- POST /save-name - Saves the "name" from the HTTP body to a file called "usernames.txt"

## Build & Run Instructions - Linux
1. Use `g++ server.cpp -o server` to compile with G++.
2. Use `./server` to run it.
3. Visit "http://127.0.0.1:5000" to view it.
