# Kerberos
Die 3 Köpfe stehen für die 3 Elemente Authentisierung
- Client
- Server
- Key Distribution Center (KDC) - trusted 3rd party

## Directory Services
### X-500-Spezifikation
Standard des globalen Verzeichnisdienstes, die ADDS (Active Directory Domain Services)von Microsoft und SAMBA basieren darauf.
Zugriff auf die Objekte in der X-500 basierten DB erfolgt mit LDAP (Lightweight Directory Access Protocol).
Abfragen der Server untereinander erfolgt auch mit LDAP

### Authentifizierungsprotokoll Shritt für Shritt
1. User meldet sich an seinem Arbeitsgerät mit Username und Passwort an
2. Kerberos authentifiziert den Benutzer und stellt über das Key Distribution Center (KDC) ein Ticket aus
3. Das Ticket, welches TGT (Ticket Granting Ticket) dient als Identitätsnachweise der Benutzer
4. Das KDC stellt weiter Tickets aus (Session Tickets) für die wieteren Aktivitäten des Benutzers

## Netzwerkauthentifizierung mit Kerberos
Definition der Begriffe
- Authentisierung: Nachweis der eigenen Identität
- Authentifizierung: Überprüfung der Identität

Netzwekprotokolle zur Authentisierung
- Webserver -> http
- Email -> SMTP, POP3, IMAP
- Fileservices -> CIFS, NFS, AFS, etc.
- Printservices -> IPP
- Active Directory Services -> LDAP
- Host-Server -> SSH; etc.

Es sind immer 2 Teilnehmer benötigt. Teilnehmer A der sich authentisieren will und Teilnehmer B der Teilnehmer A authentifizieren möchte.
Die Teilnehmer können sein:
- A: Anwender, B: Service
- A: Anwender, B: Anwender
- A: Service, B: Service

## Elemente
### KDC
Das Key Distribution Center vermittelt die Authentisierung zwischen Client und Netzwerkdiensten. Alle Clients und Services haben ein 
Vertrauensverhältnis (Trust) zum KDC. 

Abbildung der Kerberos-Authentisierung:
![Kerberos Authentisierung](/M159/images/Kerberos-Authentisierung.png)

### Realm
Kerberos Umgebungen werden in Realms aufgeteilt. Realms representieren Organisationen oder Teilen von Organisationen. Jeder Client,
Dienst oder Host gehört zu einem Realm. Innerhalb dieses Realm gibt es einen KDC. Es können Authentisierungsvorgänge auch zwischen
Realms stattfinden -> Cross-Realm-Authentisierung. Jedes Realm hat einen Realm-Namen. Dieser entspricht per Konvention dem DNS-Namen 
der Umgebung in Grossbuchstaben -> Achtung die Gross und Kleinschreibung spielt für Realms eine Rolle!

### Principals
Clients und Dienste innerhalb eines Realms werden durch Kerberos Principals representiert, die Client und Dienstidentitäten werden 
folgendermassen dargestellt:
- Client Principal: Beispiel Anwender jaeggi der Realm M159.IET-GIBB.CH wäre -> jaeggi@M159.IET-GIBB.CH
- Dienste-Principal: Beispiel Webdienst auf dem Server www.m159.iet-gibb.ch -> http/www.m159.iet-gibb.ch@M159.IET-GIBB.CH

### Tickets
Authentisierung basiert auf Tickets. Die Tickets sind in der Regel 8 - 10 Stunden gültig. Es gibt 2 Ticket arten:
- Ticket Granting Ticket (TGT): Nach erfolgreicher Überprüfung der Identität stellt das KDC ein TGT aus
- Session Ticket: Mit dem TGT fordert der Client Session Tickets für speziefische Dienste beim KDC

Abbildung zur Authentisierung mit Tickets:
![Ticket Authentisierung](/M159/images/Ticket-Authentisierung.png)

### Mutual Authentication
Clients können eine Authentisierung vom Dienst verlangen. Damit kann sichergestellt werden, dass der Client mit dem "richtigen" 
Server kommuniziert.

### Pluggable Authentication Module (PAM)

### Delegation

### Authorisierung, Zugriffskontrolle und Namensdienste

