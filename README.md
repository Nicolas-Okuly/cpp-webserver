# C++ Webserver
Based on a West-MEC project made in class. The project made in class used Node.Js's http module. This project uses crow to handle http.

## Functionalities
- GET / - Loads index.html
- GET /public/* - Pulls anything from public, this contains nested directories and images for testing.
- POST /save-name - Saves the "name" from the HTTP body to a file called "usernames.txt"

