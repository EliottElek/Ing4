const url = require("url");
const qs = require("querystring");
module.exports = {
  serverHandle: function (req, res) {
    const route = url.parse(req.url);
    const path = route.pathname;
    const queryParams = qs.parse(url.parse(req.url).query);
    const content =
      "<!DOCTYPE html>" +
      "<html>" +
      "    <head>" +
      '        <meta charset="utf-8" />' +
      "        <title>ECE AST</title>" +
      "    </head>" +
      "    <body>" +
      "       <p>path : " +
      path +
      " </p>" +
      "<a href=/hello?name=toto'" +
      ">vers toto</a><br>" +
      "<a href='/hello?name=ulysse'" +
      ">vers ulysse</a><br>" +
      "<a href='/hello?name=hugo'" +
      ">vers hugo</a><br>" +
      "    </body>" +
      "</html>";
    res.writeHead(200, { "Content-Type": "text/html" });
    res.write(content);
    if (path === "/hello" && "name" in queryParams) {
      res.write("Hello " + queryParams["name"]);
    } else {
      res.write("404 error.. Seems like you're lost.");
    }
    res.end();
  },
};
