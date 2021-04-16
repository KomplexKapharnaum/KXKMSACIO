#ifndef SPIFFS_EDIT_H
#define SPIFFS_EDIT_H

//////////////////////////////////////////spiffs///////////////////////////////////////////////
#include <WebServer.h>
File fsUploadFile;
WebServer spiffServer(80);

////////////////////////////////////////// format bytes //////////////////////////////////////
String spiffs_formatBytes(size_t bytes)
{
    if (bytes < 1024)
    {
        return String(bytes) + "B";
    }
    else if (bytes < (1024 * 1024))
    {
        return String(bytes / 1024.0) + "KB";
    }
    else if (bytes < (1024 * 1024 * 1024))
    {
        return String(bytes / 1024.0 / 1024.0) + "MB";
    }
    else
    {
        return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
    }
} //spiffs_formatBytes(size_t bytes)

String spiffs_getContentType(String filename)
{
    if (spiffServer.hasArg("download"))
        return "application/octet-stream";
    else if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    return "text/plain";
} //spiffs_getContentType(String filename)

bool spiffs_handleFileRead(String path)
{
#ifdef DEBUGi
    LOG("spiffs_handleFileRead: " + path);
#endif
    if (path.endsWith("/"))
        path += "index.htm";
    String contentType = spiffs_getContentType(path);
    String pathWithGz = path + ".gz";
    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
    {
        if (SPIFFS.exists(pathWithGz))
            path += ".gz";
        File file = SPIFFS.open(path, "r");
        size_t sent = spiffServer.streamFile(file, contentType);
        file.close();
        return true;
    }
    return false;
} //spiffs_handleFileRead(String path)

void spiffs_handleFileUpload()
{
    if (spiffServer.uri() != "/edit")
        return;
    HTTPUpload &upload = spiffServer.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        String filename = upload.filename;
        if (!filename.startsWith("/"))
            filename = "/" + filename;
#ifdef DEBUGi
        Serial.print("spiffs_handleFileUpload Name: ");
        LOG(filename);
#endif
        fsUploadFile = SPIFFS.open(filename, "w");
        filename = String();
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        //DBG_OUTPUT_PORT.print("spiffs_handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
        if (fsUploadFile)
            fsUploadFile.write(upload.buf, upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (fsUploadFile)
            fsUploadFile.close();
#ifdef DEBUGi
        Serial.print("spiffs_handleFileUpload Size: ");
        LOG(upload.totalSize);
#endif
    }
} //spiffs_handleFileUpload()

void spiffs_handleFileDelete(){
    if (spiffServer.args() == 0)
        return spiffServer.send(500, "text/plain", "BAD ARGS");
    String path = spiffServer.arg(0);
#ifdef DEBUGi
    LOG("spiffs_handleFileDelete: " + path);
#endif
    if (path == "/")
        return spiffServer.send(500, "text/plain", "BAD PATH");
    if (!SPIFFS.exists(path))
        return spiffServer.send(404, "text/plain", "FileNotFound");
    SPIFFS.remove(path);
    spiffServer.send(200, "text/plain", "");
    path = String();
} //spiffs_handleFileDelete()

void spiffs_handleFileCreate()
{
    if (spiffServer.args() == 0)
        return spiffServer.send(500, "text/plain", "BAD ARGS");
    String path = spiffServer.arg(0);
#ifdef DEBUGi
    LOG("spiffs_handleFileCreate: " + path);
#endif
    if (path == "/")
        return spiffServer.send(500, "text/plain", "BAD PATH");
    if (SPIFFS.exists(path))
        return spiffServer.send(500, "text/plain", "FILE EXISTS");
    File file = SPIFFS.open(path, "w");
    if (file)
        file.close();
    else
        return spiffServer.send(500, "text/plain", "CREATE FAILED");
    spiffServer.send(200, "text/plain", "");
    path = String();
} //spiffs_handleFileCreate()

void spiffs_handleFileList()
{
    if (!spiffServer.hasArg("dir"))
    {
        LOG("!spiffServer.hasArg");
        spiffServer.send(500, "text/plain", "BAD ARGS");
        return;
    }

    String path = spiffServer.arg("dir");
#ifdef DEBUGi
    LOG("spiffs_handleFileList: " + path);
#endif
    File dir = SPIFFS.open(path);
    path = String();

    if (!dir.isDirectory())
    {
        dir.close();
        LOG("NOT DIR");
        spiffServer.send(500, "text/plain", "NOT DIR");
        return;
    }
    dir.rewindDirectory();

    String output = "[";

    for (int cnt = 0; true; ++cnt)
    {
        File entry = dir.openNextFile();
        if (!entry)
            break;

        if (cnt > 0)
            output += ',';

        output += "{\"type\":\"";
        output += (entry.isDirectory()) ? "dir" : "file";
        output += "\",\"name\":\"";
        output += String(entry.name()).substring(1);
        output += "\"}";
        entry.close();
    }

    output += "]";
    LOG(output);
    spiffServer.send(200, "text/json", output);
} //spiffs_handleFileList()

void spiffs_listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        LOG("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        LOG("Not a directory");
        return;
    }
} //spiffs_listDir(fs::FS &fs, const char *dirname, uint8_t levels)

void spiffs_handleClient(void *pvParameters)
{
    while(true) {
        spiffServer.handleClient();
        delay(1);
    }
    vTaskDelete(NULL);
} //spiffs_handleClient(void *pvParameters)


void spiffs_init()
{
    LOG("SPIFFS_INIT");
    //////////////////////////////////////////////////// SPIFFS
    SPIFFS.begin();
    spiffs_listDir(SPIFFS, "/", 0);

    //////////////////////////////////////////////////// SERVER INIT
    //list directory
    spiffServer.on("/list", HTTP_GET, spiffs_handleFileList);
    //load editor
    spiffServer.on("/edit", HTTP_GET, []() {
        if (!spiffs_handleFileRead("/edit.html"))
        {
            LOG("!spiffs_handleFileRead( / edit.html )");
            spiffServer.send(404, "text/plain", "FileNotFound");
        }
    });
    //create file
    spiffServer.on("/edit", HTTP_PUT, spiffs_handleFileCreate);
    //delete file
    spiffServer.on("/edit", HTTP_DELETE, spiffs_handleFileDelete);
    //first callback is called after the request has ended with all parsed arguments
    //second callback handles file uploads at that location
    spiffServer.on(
        "/edit", HTTP_POST, []() {
            spiffServer.send(200, "text/plain", "");
        },
        spiffs_handleFileUpload);

    //called when the url is not defined here
    //use it to load content from SPIFFS
    spiffServer.onNotFound([]() {
        if (!spiffs_handleFileRead(spiffServer.uri()))
        {
            LOG(" FileNotFound ");
            spiffServer.send(404, "text/plain", "FileNotFound");
        }
    }); //spiffServer.onNotFound

    if (MDNS.begin("edit"))
    {
        LOG("MDNS responder started");
    }

    spiffServer.serveStatic("/", SPIFFS, "/edit.html");
    spiffServer.begin();
    MDNS.addService("http", "tcp", 80);

    ////////////////////////////////////////// TASK //////////////////////////////////////////
    xTaskCreatePinnedToCore(spiffs_handleClient, "spiffs_handleClient", 4096, NULL, 1, NULL, 0); // core 0 = wifi
}//spiffs_init()

#endif