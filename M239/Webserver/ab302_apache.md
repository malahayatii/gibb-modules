
### Apache installieren
apt update und upgrade ausführen
```bash
sudo apt update && sudo apt upgrade
```
Apache2 installieren
```bash
sudo apt install apache2 -y
```
Den Status von apache2.service kontrollieren
```bash
sudo systemctl status apache2
```
Ich gebe im Browser von vmWP1 die IP-Adresse von vmLS1 zum Kontrollieren ob die Default Webanzeige von Apache angezeigt wird.

![Apache Default Page](/Webserver/apache_default_page.png)

### Rewrite und SSL Module aktivieren
Damit diese Module aktiviert werden können müssen folgende Befehle ausgeführt werden
```bash
sudo a2enmod rewrite
sudo a2enmod ssl
```
Erklärung von a2enmod:
- a2 = apache2
- en = enable
- mod = module

Somit können die Module mit a2dismod deaktiviert werden
- dis = disable

Danach den apache2.service neustarten
```bash
sudo systemctl restart apache2
```

### Virtuelle-Hosts einrichten
Unter /etc/apache2/sites-available erstelle folgende zwei Datein
- ch.mattefit.admin.conf
- ch.mattefit.henda.conf

inhalt der Dateien:
```html
<VirtualHost 192.168.220.10:80>
ServerName vmls1
ServerAlias www.vmls1
ServerAdmin hostmaster@mattefit.ch
DocumentRoot /srv/www/1slmv/htdocs/
# Logs
ErrorLog /var/log/apache2/1slmv_error.log
CustomLog /var/log/apache2/1slmv_access.log
combined
# Directoires
<Directory /srv/www/1slmv/htdocs>
Require all granted
</Directory>
</VirtualHost>
```

ServerName
- Die ServerName-Direktive definiert den Haupt-Hostnamen (Domainnamen), der diesem VirtualHost zugeordnet ist.
- Dies bedeutet, dass dieser VirtualHost auf Anfragen antwortet, die an diesen bestimmten Hostnamen gerichtet sind.
- Im gezeigten Beispiel ist der ServerName "vmls1", was bedeutet, dass dieser VirtualHost auf Anfragen antwortet, die an "vmls1" gerichtet sind.

ServerAlias
- Die ServerAlias-Direktive ermöglicht es Ihnen, zusätzliche Hostnamen (Aliase) für denselben VirtualHost anzugeben.
- Dies bedeutet, dass dieser VirtualHost auch auf Anfragen antwortet, die an diese Aliasnamen gerichtet sind.
- Im gezeigten Beispiel ist der ServerAlias "www.vmls1", was        bedeutet, dass dieser VirtualHost auch auf Anfragen antwortet, die an "www.vmls1" gerichtet sind Das ist nützlich, wenn Sie möchten, dass derselbe VirtualHost auf Anfragen für verschiedene Versionen oder Schreibweisen desselben Hostnamens reagiert.

combined
- Format ist eine vordefinierte Log-Format-Konfiguration in Apache, die Informationen sowohl über den Zugriff auf die Ressource als auch über eventuelle Fehler enthält. Dieses Format enthält in der Regel die folgenden Informationen in den Zugriffsprotokollen:

    1. Remote-Host: Die IP-Adresse oder der Hostname des Clients, der auf den Server zugreift.
    2. Identitätsinformationen: Dies ist normalerweise ein Platzhalter und wird selten verwendet.
    3. Benutzer: Der Benutzername des Clients, sofern verfügbar (normalerweise leer).
    4. Datum und Uhrzeit: Das Datum und die Uhrzeit des Zugriffs auf die Ressource.
    5. Anforderung: Die HTTP-Anforderungsmethode (GET, POST, usw.) und der aufgerufene Pfad.
    6. Status: Der HTTP-Statuscode, der angibt, ob die Anforderung erfolgreich war oder nicht.
    7. Übertragene Datenmenge: Die Menge an Daten, die in der Antwort übertragen wurden.
    8. Referrer: Die URL, von der aus der Client auf die aktuelle Seite zugegriffen hat (sofern verfügbar).
    9. User-Agent: Informationen über den Webbrowser oder die Anwendungssoftware des Clients.

required all granted
- Zugriffskontrollkonfiguration mit welcher für den angegebenen Bereich (in diesem Fall das Verzeichnis /srv/www/1slmv/htdocs/) der Zugriff für alle Benutzer und Clients ohne Einschränkungen gewährt wird. Es erlaubt jedem, auf die Dateien und Ressourcen in diesem Verzeichnis zuzugreifen, ohne eine spezielle Authentifizierung oder Zugriffskontrolle durchzuführen.

### Kopiere die www Datei vom Modulshare nach /srv in vmLS1
Zuerst www.zip auf vmWP1 herunterladen und per scp nach /tmp von LS1
```bash
scp .\www.zip vmadmin@192.168.120.61:/tmp/www.zip
```
in vmls1 unzippen
```bash
unzip www.zip
```
Mit a2enmod können die Kofigurationsdateien "aktiviert" werden
```bash
sudo a2ensite ch.mattefit.henda
sudo a2ensite ch.mattefit.admin
```
Restart apache2 service
```bash
sudo systemctl restart apache2
```
