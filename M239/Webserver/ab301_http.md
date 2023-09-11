## HTTP-Protokoll
### Geschichte
HTTP (Hypertext Transfer Protocol) und HTML (Hypertext Markup Language) wurden von Tim Berners-Lee erfunden, einem britischen Informatiker, der an der Europäischen Organisation für Kernforschung (CERN) arbeitete. Tim Berners-Lee entwickelte diese Technologien in den späten 1980er Jahren und veröffentlichte 1991 das erste Web-Browser-Programm sowie den ersten Webserver.

Der Hauptgrund, der Tim Berners-Lee dazu führte, HTTP und HTML zu entwickeln, war die Notwendigkeit, Informationen effizienter unter den Forschern am CERN zu teilen. Damals gab es eine große Menge an wissenschaftlichen Daten und Dokumenten, die über verschiedene Computernetzwerke verstreut waren. Berners-Lee erkannte das Potenzial, diese Informationen durch ein System zu verknüpfen, das es den Forschern ermöglichen würde, einfach auf Dokumente und Ressourcen zuzugreifen, indem sie miteinander verknüpfte Hyperlinks verwenden konnten.

Um dieses Ziel zu erreichen, entwickelte er HTTP als Protokoll, um Ressourcen (wie Text, Bilder und andere Medien) über das Internet abzurufen, und HTML als Markup-Sprache, um Dokumente mit Hyperlinks zu erstellen und zu formatieren. Zusammen bildeten HTTP und HTML die Grundlage des World Wide Web, das heute ein wesentlicher Bestandteil des Internets ist und die Grundlage für die meisten Webseiten und Webanwendungen bildet. Berners-Lee's Arbeit legte den Grundstein für die moderne vernetzte Welt, die wir heute kennen.

### Vorteile von HTTP/1.1
HTTP/1.1 brachte mehrere wichtige Verbesserungen und Vorteile gegenüber der ursprünglichen Version, HTTP/1.0, mit sich:

    Persistente Verbindungen: In HTTP/1.0 wurde für jede Anforderung (Request) eine separate TCP-Verbindung geöffnet und nach dem Empfang der Antwort sofort geschlossen. In HTTP/1.1 wurden persistente Verbindungen eingeführt, was bedeutet, dass dieselbe TCP-Verbindung für mehrere Anforderungen und Antworten verwendet werden kann. Dies reduziert die Latenzzeiten und den Overhead beim Öffnen und Schließen von Verbindungen erheblich und beschleunigt die Übertragung von Ressourcen.

    Pipelining: Mit HTTP/1.1 können mehrere Anforderungen auf derselben Verbindung gleichzeitig gesendet werden, ohne auf die Antwort auf die erste Anforderung zu warten. Dies ermöglicht eine bessere Ausnutzung der Netzwerkbandbreite und beschleunigt die Ressourcenübertragung.

    Chunked Transfer Encoding: HTTP/1.1 führte die Möglichkeit ein, große Ressourcen in Teilstücken (Chunks) zu übertragen, anstatt auf die vollständige Ressource zu warten, bevor sie gesendet wird. Dies ist nützlich für Streaming und die Übertragung von großen Dateien, da der Client die Daten bereits empfangen kann, während der Server sie generiert.

    Host Header: HTTP/1.1 führte den "Host"-Header ein, der es ermöglichte, mehrere Websites auf demselben Server zu hosten und die Anfragen an die richtige Webseite weiterzuleiten. Dies erleichterte die Verwaltung von Mehrbenutzer- und Mehrdomänen-Servern erheblich.

    Caching: HTTP/1.1 führte verbesserte Caching-Mechanismen ein, darunter die ETags (Entity Tags) und Conditional GETs, die es Servern und Clients ermöglichen, Ressourcen effizienter zu zwischenspeichern und die Übertragung von unveränderten Ressourcen zu vermeiden.

Diese Verbesserungen in HTTP/1.1 trugen dazu bei, die Leistung und Effizienz von Webanwendungen erheblich zu steigern, indem sie die Anzahl der erforderlichen Netzwerkverbindungen reduzierten, die Latenzzeiten verringerten und die Möglichkeit zur effizienteren Übertragung von Ressourcen boten. Beachten Sie jedoch, dass HTTP/2 und HTTP/3 weitere Fortschritte in Bezug auf Leistung und Sicherheit gebracht haben, insbesondere im Hinblick auf die Parallelisierung von Anfragen und die Verwendung von Multiplexing-Verfahren.

### Hauptunterschiede zwischen HTTP/1 und HTTP/2
| Eigenschaften             | HTTP/1                        | HTTP/2                             |
|---------------------------|-------------------------------|-----------------------------------|
| Multiplexing              | Nein (Sequenzielle Anfragen) | Ja (Parallelisierung von Anfragen) |
| Header-Komprimierung      | Nein (Unkomprimierte Header)  | Ja (Header-Kompression)           |
| Priorisierung             | Nein (Keine Priorisierung)    | Ja (Unterstützt Priorisierung)     |
| Protokollformat           | Textbasiert                  | Binär                             |
| Server Push               | Nein (Kein Server Push)       | Ja (Server kann Ressourcen pushen) |
| Fehlerbehandlung          | Begrenzt                      | Verbesserte Fehlerbehandlung      |
| Upgrade-Anforderung      | Ja (Für HTTPS erforderlich)   | Nein (Kein Upgrade erforderlich)  |

### HTTP analysieren
Beispiel HTTP-Request an einem Webserver
```bash
GET / HTTP/1.1
Host: www.iet-gibb.ch
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; rv:56.0)
Gecko/20100101 Firefox/56.0
Accept:
text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: de,en-US;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate, br
Cookie: _ga=GA1.2.1663711538.1555855327;
_gid=GA1.2.1035627429.1555855327
Connection: keep-alive
```
Beispiel HTTP-Response vom Webserver
```bash
HTTP/1.1 200 OK
Server: nginx
Date: Sun, 21 Apr 2019 14:03:10 GMT
Content-Type: text/html
Content-Length: 1275
Connection: keep-alive
Last-Modified: Tue, 12 Sep 2017 15:22:54 GMT
ETag: "102ec9-bb1-558ff9e0090d0"
Accept-Ranges: bytes
Vary: Accept-Encoding
Content-Encoding: gzip
```

### Request-Header
| Header-Feld | Beschreibung |
|-------------|--------------|
| User-Agent | Informationen über den Anfragen Browser |
| Accept | Welcher Art Dateityp soll die Antwort sein, die der Browser möchte |
| Accept-Encoding | Wie die Antwort kompromiert sein darf |
| Accept-Language | Welche Inhaltssprachen der Browser bevorzugt |
| Cookie | übermittelte Cookies, (FormatName = Wert) |
| Connection | Der Browser bittet darum, die Verbindung offen zu lassen, da wahrscheinliche weitere Daten benötigt werden |

### Response-Header
| Statuscode | Bedeutung und Erklärung                            |
|------------|---------------------------------------------------|
| 301        | Moved Permanently: Die angeforderte Ressource wurde dauerhaft an eine neue URL verschoben. Clients sollten ihre Lesezeichen oder Links aktualisieren, um die neue URL zu verwenden.   |
| 302        | Found (oder 302 Found): Dieser Statuscode zeigt an, dass die angeforderte Ressource vorübergehend an einer anderen URL zu finden ist. Der Client sollte die neue URL für diese Anforderung verwenden, kann jedoch in Zukunft die alte URL weiterhin verwenden.  |
| 304        | Not Modified (Nicht geändert): Wenn ein Client eine Anforderung mit einem If-Modified-Since- oder If-None-Match-Header sendet und der Server feststellt, dass die Ressource seit dieser Zeit nicht geändert wurde, antwortet er mit einem Statuscode 304. Dies informiert den Client, dass er seine zwischengespeicherte Version der Ressource verwenden kann.  |
| 400        | Bad Request (Ungültige Anfrage): Dieser Statuscode zeigt an, dass der Server die Anforderung des Clients nicht verstehen konnte, normalerweise aufgrund von fehlerhafter Syntax oder ungültigen Parametern.  |
| 401        | Unauthorized (Nicht autorisiert): Wenn ein Client versucht, auf eine Ressource zuzugreifen, die Authentifizierung erfordert, jedoch keine gültigen Anmeldeinformationen bereitstellt, antwortet der Server mit einem Statuscode 401. Dies fordert den Client auf, gültige Authentifizierungsinformationen bereitzustellen.  |
| 403        | Forbidden (Verboten): Dieser Statuscode gibt an, dass der Server die Anforderung verstanden hat, sie jedoch ablehnt. Im Gegensatz zu 401, bei dem die Authentifizierung helfen kann, bedeutet eine 403-Antwort, dass der Server die Anforderung auch dann nicht erfüllt, wenn der Client authentifiziert ist.  |
| 404        | Not Found (Nicht gefunden): Dies ist einer der bekanntesten Statuscodes. Er bedeutet, dass der Server die angeforderte Ressource unter der angegebenen URL nicht finden konnte. Es gibt keine Aussage darüber, ob die Ressource temporär oder dauerhaft fehlt.  |
| 500        | Internal Server Error (Interner Serverfehler): Dieser Statuscode gibt an, dass der Server auf einen unerwarteten Fehler gestoßen ist, der ihn daran hinderte, die Anforderung zu erfüllen. Es handelt sich um eine generische Fehlermeldung, wenn keine spezifischere Meldung geeignet ist.  |

Weitere Informationen im Response-Header
| Response-Feld | Bedeutung |
|---------------|-----------|
| Server | Welche Serversoftware diese Antwort gegeben hat |
| Date | Datum und Uhrzeit des Servers |
| Content-Typ | Welche Art Inhalt mitgeliefert wird |
| Content-Length | Länge des Inhaltes in Bytes |
| Connection | Ob der Server damit einverstanden ist, die Verbindung aktiv zu halten |
| Last-Modified | Wann der Inhalt zuletzt modifiziert wurde |
| ETag | Eindeutige Kennung des Inhalts |
| Content-Encoding | Wie der Inhalt auf dem weg zum Browser komprimiert wurde |
