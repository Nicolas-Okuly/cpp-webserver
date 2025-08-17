// Import a moving van of libraries
#include "crow_all.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// Set the fs namespace,
namespace fs = std::filesystem;

// Create console.log (for fun)
class console { public: void log(std::string input){ std::cout<<input<<std::endl; } };

// File loading handler
std::string loadFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main(void) {
    // Start my app and console
    crow::SimpleApp app;
    console console;

    // GET "/" - Responds with index.html
    CROW_ROUTE(app, "/").methods("GET"_method)
    ([]() {
        // Create response object and load index.html
        crow::response response;
        auto data = loadFile("index.html");

        // Respond with proper headers and index.html
        response.set_header("Content-Type", "text/html");
        response.body = std::move(data);

        return response;
    });


    // GET "/public/*" - Responds with requested file
    CROW_ROUTE(app, "/public/<path>").methods("GET"_method)
    ([&console](std::string file) {
        // Create response object and build filepath
        crow::response response;
        fs::path filepath = fs::path("public") / file;

        // Check if the file exists
        if (fs::exists(filepath) && fs::is_regular_file(filepath)) {
            // Unordered map of possible mimetypes
            std::unordered_map<std::string, std::string> mimetypes;
            mimetypes["html"] = "text/html";
            mimetypes["css"] = "text/css";
            mimetypes["js"] = "application/javascript";
            mimetypes["png"] = "image/png";
            mimetypes["jpg"] = "image/jpg";

            // Determine and set the mimetype
            std::string mimetype = mimetypes[filepath.extension().string()];

            // Load the data
            auto data = loadFile(filepath.string());

            // Respond with the data
            response.add_header("Content-Type", mimetype);
            response.body = std::move(data);
        } else {
            // If the file does not exist, respond with 404
            response.code = 404;
            response.body = "File not found.";
        }

        // Finalize response
        return response;
    });

    // POST "/save-name" - saves a name to username.txt
    CROW_ROUTE(app, "/save-name").methods("POST"_method)
    ([&console](const crow::request &req) {
        // Create response object and load the request body
        crow::response response;
        auto body = crow::json::load(req.body);

        // Respond with a 400 if there is no body
        if (!body) {
            response.code = 400;
            response.body = "Bad JSON";
            return response;
        }

        // Get the name from the body
        std::string name = body["name"].s();

        // Open "username.txt", create it if it doesn't exist, append if it does
        std::ofstream username("username.txt", std::ios::app);

        // Imsert data and close file
        username << name << std::endl;
        username.close();

        // Respond with 200
        response.code = 200;
        response.body = "OK.";
        return response;
    });

    // Set the log level to warnings
    app.loglevel(crow::LogLevel::WARNING);

    // Start the web server
    console.log("App now running on http://127.0.0.1:5000");
    app.bindaddr("127.0.0.1").port(5000).run();
    return 0;
}