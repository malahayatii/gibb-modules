### Title Slide
Herzlich willkommen zu unserem Screencast über die Wazuh-API.

### Change Slide
In diesem Video wird gezeigt, wie mit der Security-Plattform Wazuh die Ressourcen von Clients, sowie andere Metriken und Informationen mithilfe der RESTful API mit einem Skript abgefragt werden können.

### Change slide
Wazuh ist nicht nur frei verfügbar, sondern auch Open Source, wobei der Quellcode auf Github zugänglich ist.

Diese innovative Plattform fungiert als Sicherheitsinformations- und Ereignisverwaltungssystem (SIEM), das in Echtzeit Sicherheitsereignisse überwacht und Bedrohungen in IT-Infrastrukturen erkennt.

Darüber hinaus kombiniert Wazuh Intrusion Detection und Intrusion Prevention (IDS und IPS) Software-Tools zu einer fortschrittlichen Detektions- und Präventions-Suite, auch bekannt als Extended Detection and Response (XDR). Die Verwaltung all dieser Tools erfolgt über eine benutzerfreundliche, einzige Web-Benutzeroberfläche. Diese Dienste werden als Software-as-a-Service angeboten, was höchste Nutzerfreundlichkeit gewährleistet.

### Click
Wazuh verwendet eine Server-Agent-Architektur, bei der der Wazuh-Server als Zentrale für die Wazuh-Agenten fungiert. Der Server sammelt Informationen über die Clients und Server, auf denen die Wazuh-Agenten installiert sind, durch Abfragen.

Nachdem die Agenten die Informationen an den Server senden, werden sie vom Manager verarbeitet. Die Wazuh API ist direkt mit dem Manager verbunden und ermöglicht Abfragen basierend auf den gesammelten Informationen. Bei entsprechender Konfiguration werden die vom Manager verarbeiteten Daten an Filebeat weitergeleitet. Filebeat generiert dann Warnmeldungen gemäß der Konfiguration, und diese werden schliesslich dem Indexer übergeben. Der Indexer kategorisiert und speichert die Warnmeldungen.

Wazuh bietet eine RESTful API an, damit benutzerdefinierte Abfragen an den Wazuh-Server gesendet werden können. Wir werden diese Funktion nutzen, um das Monitoring von Hardwareinformationen und -auslastung in einem .txt File auszugeben. Die Informationen können danach für viele weitere Zwecke wiederverwendet werden.

### Click
In diesem Abschnitt werden API-Aufrufe näher erläutert sowie deren Verwendungszwecke erklärt.

### Last Slide
In diesem Abschnitt werden einige Beispielskripte vorgestellt, und ihre Integration in Wazuh wird demonstriert.
