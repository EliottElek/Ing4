const http = require("http");
const url = require("url");
const qs = require("querystring");

// Declare an http server
http
  .createServer(function (req, res) {
    const path = url.parse(req.url).pathname;
    const queryParams = qs.parse(url.parse(req.url).query);
    const parameters =
      "<p>L'ID : " +
      queryParams.id +
      " </p> Le prénom : " +
      queryParams.name +
      "</p> Le nom : " +
      queryParams.lastname +
      "</p>";
    const content =
      "<!DOCTYPE html>" +
      "<html>" +
      "    <head>" +
      '        <meta charset="utf-8" />' +
      "        <title>ECE AST</title>" +
      "    </head>" +
      "    <body>" +
      "       <p>Hello World !</p>" +
      "<p>The path is " +
      path +
      "</p>" +
      "<a href = '/parameters?id=1&name=eliott&lastname=morcillo'>" +
      "le lien </a>" +
      "    </body>" +
      "</html>";
    // Write a response header
    res.writeHead(200, { "Content-Type": "text/html" });
    if (path === "/parameters" && "name" in queryParams) {
      res.write("Hello " + parameters);
    } else if (path === "/") {
      res.write(content);
    } else {
      res.write("404 error. Seems like you're lost");
    }
    res.end();

    // Start the server
  })
  .listen(8080);
