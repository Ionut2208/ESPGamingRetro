#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#define RED 25
#define GREEN 26
#define BLUE 27
const char* ssid = "SSID";
const char* password = "PASS";

AsyncWebServer server(80);

String slot1, slot2, slot3;
String user1, user2, user3, pass1, pass2, pass3;

char* tableRowData = "<tr><td>User1</td><td>Wordle</td><td>4</td></tr><tr><td>User2</td><td>X si 0</td><td>X a castigat</td></tr><tr><td>User3</td><td>Space Invaders</td><td>140</td></tr><tr><td>User1</td><td>X si 0</td><td>Egalitate</td></tr><tr><td>User3</td><td>Wordle</td><td>0</td></tr><tr><td>User3</td><td>Wordle</td><td>3</td></tr>";

// HTML template for the web page
const char* htmlTemplate = R"html(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Web Server</title>
    <style>
        table {
            font-family: arial, sans-serif;
            border-collapse: collapse;
            width: 100%;
        }

        th, td {
            border: 1px solid #dddddd;
            text-align: left;
            padding: 8px;
        }
    </style>
</head>
<body>
    <h2>Istoric</h2>
    <table>
        <tr>
            <th>Username</th>
            <th>Joc</th>
            <th>Rezultat</th>
        </tr>
        %s
    </table>
</body>
</html>
)html";

void setup() {
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    slot1 = "Slot 1";
    slot2 = "Slot 2";
    slot3 = "Slot 3";
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    String date = "";
    while (date.length() == 0)
    {
        date = Serial2.readString();
    }
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
    char datec[105];
    int k = 0;
    for (int i = 0; i < date.length(); i++)
        if (date[i] >= 32 && date[i] < 127)
            datec[k++] = date[i];
    user1 = strtok(datec, " ");
    pass1 = strtok(NULL, " ");
    user2 = strtok(NULL, " ");
    pass2 = strtok(NULL, " ");
    user3 = strtok(NULL, " ");
    pass3 = strtok(NULL, " ");
    if (user1 != "EMPTY")
    {
        slot1 += " - ";
        slot1 += user1;
    }
    else
    {
        user1 = "";
        pass1 = "";
        slot1 += " - slot gol";
    }


    if (user2 != "EMPTY")
    {
        slot2 += " - ";
        slot2 += user2;
    }
    else
    {
        user2 = "";
        pass2 = "";
        slot2 += " - slot gol";
    }

    if (user3 != "EMPTY")
    {
        slot3 += " - ";
        slot3 += user3;
    }
    else
    {
        user3 = "";
        pass3 = "";
        slot3 += " - slot gol";
    }
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><body style='display:flex;flex-direction:column;justify-content:center;align-items:center;text-align:center;'>";
        html += "<h1 style='color:red;'>ESPGamingRetro</h1>";
        html += "<button style='background-color:blue;color:white;' onclick='openPage(this)'>Adauga profil</button><br>";
        html += "<button style='background-color:blue;color:white;' onclick='openPage(this)'>Incarca profil</button><br>";
        html += "<button style='background-color:blue;color:white;' onclick='openPage(this)'>Sterge profil</button><br>";
        html += "<button style='background-color:blue;color:white;' onclick='openPage(this)'>Istoric</button><br>";
        html += "<script>";
        html += "function openPage(button) {";
        html += "  var pageName = button.innerHTML;";
        html += "  window.open(pageName.replace(/ /g, '_') + '.html', '_blank');";
        html += "}";
        html += "</script>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Adauga_profil.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><body style='display:flex;flex-direction:column;justify-content:center;align-items:center;text-align:center;'>";
        html += "<h1>Adauga profil</h1>";
        html += "<button name = 'Slot 1'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot1 + "</button><br>";
        html += "<button name = 'Slot 2'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot2 + "</button><br>";
        html += "<button name = 'Slot 3'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot3 + "</button><br>";
        html += "<script>";
        html += "function openPage(button) {";
        html += "    var pageName = button.name + ' adaugare';";
        html += "    if ((button.name === 'Slot 1' && '" + slot1 + "' !== 'Slot 1 - slot gol') || (button.name === 'Slot 2' && '" + slot2 + "' !== 'Slot 2 - slot gol') || (button.name === 'Slot 3' && '" + slot3 + "' !== 'Slot 3 - slot gol')) {";
        html += "        alert('Exista deja un profil pe acest slot!');";
        html += "    } else {";
        html += "        window.open(pageName.replace(/ /g, '_') + '.html', '_blank');";
        html += "    }";
        html += "}";
        html += "</script>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Incarca_profil.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><body style='display:flex;flex-direction:column;justify-content:center;align-items:center;text-align:center;'>";
        html += "<h1>Incarca profil</h1>";
        html += "<button name = 'Slot 1'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot1 + "</button><br>";
        html += "<button name = 'Slot 2'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot2 + "</button><br>";
        html += "<button name = 'Slot 3'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot3 + "</button><br>";
        html += "<script>";
        html += "function openPage(button) {";
        html += "    var pageName = button.name + ' incarcare';";
        html += "    if ((button.name === 'Slot 1' && '" + slot1 + "' === 'Slot 1 - slot gol') || (button.name === 'Slot 2' && '" + slot2 + "' === 'Slot 2 - slot gol') || (button.name === 'Slot 3' && '" + slot3 + "' === 'Slot 3 - slot gol')) {";
        html += "        alert('Nu exista niciun profil pe acest slot!');";
        html += "    } else {";
        html += "        window.open(pageName.replace(/ /g, '_') + '.html', '_blank');";
        html += "    }";
        html += "}";
        html += "</script>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Sterge_profil.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><body style='display:flex;flex-direction:column;justify-content:center;align-items:center;text-align:center;'>";
        html += "<h1>Sterge profil</h1>";
        html += "<button name = 'Slot 1'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot1 + "</button><br>";
        html += "<button name = 'Slot 2'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot2 + "</button><br>";
        html += "<button name = 'Slot 3'; style='background-color:blue;color:white;' onclick='openPage(this)'>" + slot3 + "</button><br>";
        html += "<script>";
        html += "function openPage(button) {";
        html += "    var pageName = button.name + ' stergere';";
        html += "    if ((button.name === 'Slot 1' && '" + slot1 + "' === 'Slot 1 - slot gol') || (button.name === 'Slot 2' && '" + slot2 + "' === 'Slot 2 - slot gol') || (button.name === 'Slot 3' && '" + slot3 + "' === 'Slot 3 - slot gol')) {";
        html += "        alert('Nu exista niciun profil pe acest slot!');";
        html += "    } else {";
        html += "        window.open(pageName.replace(/ /g, '_') + '.html', '_blank');";
        html += "    }";
        html += "}";
        html += "</script>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_1_adaugare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 1 - Adauga profil</h1>";
        html += "<form method='post' action='/Slot_1_adaugare.html'>";
        html += "<input type='text' name='username' placeholder='Username'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Adaugare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_1_adaugare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String username = request->arg("username");
        String password = request->arg("password");
        String dateRegister = "REGISTER1 ";
        dateRegister += username;
        dateRegister += " ";
        dateRegister += password;
        Serial2.println(dateRegister);
        request->send(200, "text/html", "Profil adaugat cu succes!");
        ESP.restart();
        });



    server.on("/Slot_2_adaugare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 2 - Adauga profil</h1>";
        html += "<form method='post' action='/Slot_2_adaugare.html'>";
        html += "<input type='text' name='username' placeholder='Username'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Adaugare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_2_adaugare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String username = request->arg("username");
        String password = request->arg("password");
        String dateRegister = "REGISTER2 ";
        dateRegister += username;
        dateRegister += " ";
        dateRegister += password;
        Serial2.println(dateRegister);
        request->send(200, "text/html", "Profil adaugat cu succes!");
        ESP.restart();
        });

    server.on("/Slot_3_adaugare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 3 - Adauga profil</h1>";
        html += "<form method='post' action='/Slot_3_adaugare.html'>";
        html += "<input type='text' name='username' placeholder='Username'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Adaugare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_3_adaugare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String username = request->arg("username");
        String password = request->arg("password");
        String dateRegister = "REGISTER3 ";
        dateRegister += username;
        dateRegister += " ";
        dateRegister += password;
        Serial2.println(dateRegister);
        request->send(200, "text/html", "Profil adaugat cu succes!");
        ESP.restart();
        });


    server.on("/Slot_1_incarcare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 1 - Incarca profil</h1>";
        html += "<form method='post' action='/Slot_1_incarcare.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user1 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Incarcare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_1_incarcare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        Serial.println(password);
        if (password == pass1)
        {
            String dateLogin = "LOGIN1";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil incarcat cu succes!");
        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Slot_2_incarcare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 2 - Incarca profil</h1>";
        html += "<form method='post' action='/Slot_2_incarcare.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user2 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Incarcare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_2_incarcare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        Serial.println(password);

        if (password == pass2)
        {
            String dateLogin = "LOGIN2";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil incarcat cu succes!");

        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Slot_3_incarcare.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 3 - Incarca profil</h1>";
        html += "<form method='post' action='/Slot_3_incarcare.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user3 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Incarcare</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_3_incarcare.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        Serial.println(password);
        if (password == pass3)
        {
            String dateLogin = "LOGIN3";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil incarcat cu succes!");
        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Slot_1_stergere.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 1 - Sterge profil</h1>";
        html += "<form method='post' action='/Slot_1_stergere.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user1 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Stergere</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_1_stergere.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        if (password == pass1)
        {
            String dateLogin = "DELETE1";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil sters cu succes!");
            ESP.restart();
        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Slot_2_stergere.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 2 - Sterge profil</h1>";
        html += "<form method='post' action='/Slot_2_stergere.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user2 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Stergere</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_2_stergere.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        Serial.println(password);
        if (password == pass2)
        {
            String dateLogin = "DELETE2";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil sters cu succes!");
            ESP.restart();
        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Slot_3_stergere.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<html><head>";
        html += "<style>body { display: flex; justify-content: center; align-items: center; height: 100vh; flex-direction: column; }</style>";
        html += "</head><body><h1>Slot 3 - Sterge profil</h1>";
        html += "<form method='post' action='/Slot_3_stergere.html'>";
        html += "<input type='text' name='username' placeholder='Username' value = '" + user3 + "'>";
        html += "<input type='password' name='password' placeholder='Password'>";
        html += "<button type='submit'>Stergere</button>";
        html += "</form>";
        html += "</body></html>";
        request->send(200, "text/html", html);
        });

    server.on("/Slot_3_stergere.html", HTTP_POST, [](AsyncWebServerRequest* request) {
        String password = request->arg("password");
        Serial.println(password);
        if (password == pass3)
        {
            String dateLogin = "DELETE3";
            Serial2.println(dateLogin);
            request->send(200, "text/html", "Profil sters cu succes!");
            ESP.restart();
        }

        else
            request->send(403, "text/plain", "Parola gresita!");
        });

    server.on("/Istoric.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        String page = String(htmlTemplate);
        page.replace("%s", tableRowData);
        request->send(200, "text/html", page);
        });

    server.begin();
}

void loop() {
}